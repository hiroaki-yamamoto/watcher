#include "themepanel.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonObject>
#include <QtDebug>

#include <list>
#include <tuple>

#include <logging/logging.h>

using namespace logging;
namespace ui{
    ThemePanel::ThemePanel(const QDir &dir, QWidget *parent):QWidget(parent){
        this->setupUi(this);
        this->setObjectName(dir.absolutePath());
        this->_dir=dir;
        QFile info(dir.absoluteFilePath("info.json"));
        qDebug()<<"Information file:"<<info.fileName();
        if(info.exists()){
            if(info.open(QFile::ReadOnly)){
                QJsonDocument &&json=QJsonDocument::fromJson(info.readAll());
                if(json.isObject()){
                    std::list<std::tuple<QString,QJsonValue::Type,QWidget *> > object_key_type={
                        std::make_tuple("title",        QJsonValue::String,this->_themeTitle),
                        std::make_tuple("description",  QJsonValue::String,this->_themeDesc),
                        std::make_tuple("icon",         QJsonValue::String,this->_themeIcon),
                        std::make_tuple("version",      QJsonValue::String,this->_themeVersion),
                        std::make_tuple("author",       QJsonValue::String,this->_author)
                    };
                    QJsonObject &&object=json.object();
                    for(const std::tuple<QString,QJsonValue::Type,QWidget *> &tuple:object_key_type){
                        if(object.contains(std::get<0>(tuple))){
                            if(object[std::get<0>(tuple)].type()==std::get<1>(tuple)){
                                if(std::get<0>(tuple)=="icon"){
                                    QMetaObject::invokeMethod(std::get<2>(tuple),"setPixmap",
                                                              Q_ARG(QPixmap,
                                                                    QIcon(dir.absoluteFilePath(object[std::get<0>(tuple)].toString()))
                                                              .pixmap(32,QIcon::Normal,QIcon::On)));
                                }else{
                                    QMetaObject::invokeMethod(std::get<2>(tuple),"setText",Q_ARG(QString,object[std::get<0>(tuple)].toString()));
                                }
                            }else{
                                qWarning()<<this<<std::get<0>(tuple)<<" is invalid type.";
                            }
                        }else qWarning()<<this<<std::get<0>(tuple)<<" couldn't be found.";
                    }
                }else{
                    qWarning()<<this<<"Format of the information file is invalid.";
                    this->setEmptyTitleAndDesc();
                }
                info.close();
            }else{
                qWarning()<<this<<"Opening the information file failed:"<<info.errorString();
                this->setEmptyTitleAndDesc();
            }
        }else{
            qWarning()<<this<<"The information file counldn't be found.";
            this->setEmptyTitleAndDesc();
        }
        
        connect(this->_select,SIGNAL(toggled(bool)),SIGNAL(selectionChanged(bool)));
    }
    void ThemePanel::setEmptyTitleAndDesc(){this->_themeDesc->setText("Theme Description");}
    void ThemePanel::setEmptyTitle(){this->_themeTitle->setText(this->_dir.dirName());}
    void ThemePanel::setEmptyDesc(){this->_themeDesc->setText("Theme Description");}
    
    bool ThemePanel::selected() const{return this->_select->isChecked();}
    QDir ThemePanel::dir() const{return this->_dir;}
    QString ThemePanel::theme_title() const{return this->_themeTitle->text();}
    QString ThemePanel::theme_desc() const{return this->_themeDesc->text();}
    QString ThemePanel::theme_author() const{return this->_author->text();}
    QString ThemePanel::theme_version() const{return this->_author->text();}
    
    void ThemePanel::setThemeTitle(const QString &title) {this->_themeTitle->setText(title);}
    void ThemePanel::setThemeDesc(const QString &desc){this->_themeDesc->setText(desc);}
    void ThemePanel::setThemeVersion(const QString &version){this->_themeVersion->setText(version);}
    void ThemePanel::setThemeAuthor(const QString &author){this->_author->setText(author);}
    void ThemePanel::setSelected(const bool selected) const{this->_select->setChecked(selected);}
}
