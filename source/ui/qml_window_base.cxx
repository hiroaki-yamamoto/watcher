#include <QList>
#include <QObject>
#include <QDir>

#include <QDebug>
#include <QProcess>

#include <QtQuick/QQuickItem>
#include <QtQml/QQmlContext>
#include <QtQml/QQmlEngine>

#include <QtWidgets/QMessageBox>
#include <QtWidgets/QApplication>

#include <loader/root.h>

#include "qml_window_base.h"
#include "property_storage.h"
#include "setting_default.h"

namespace ui{
    QMLWindowBase::QMLWindowBase(const QString &title, const QIcon &icon, QWindow *parent):QQuickView(parent){
        this->setTitle(title);
        this->setIcon(icon);
    }
    QFileInfo QMLWindowBase::_getQMLFileFromSelectedThemes(const QString &file){
        QFileInfo info=QFileInfo();
        const QString &&selected_theme=default_value::setting_default::name_theme_selected_dir();
        const QString &&name_theme_root=default_value::setting_default::name_theme_root_dir();
        
        if(this->property()->exists(selected_theme)&&
                this->property()->get(selected_theme).type()==QMetaType::QString&&
                !this->property()->get(selected_theme).toString().isEmpty()){
            info.setFile(QDir(this->property()->get(selected_theme).toString()),file);
        }else if(this->property()->exists(name_theme_root)&&this->property()->get(name_theme_root).type()==QMetaType::QString){
            info.setFile(QDir(this->property()->get(name_theme_root).toString()),
                         default_value::setting_default::default_theme_name()+
                         QDir::separator()+file);
        }
        return info;
    }
    
    void QMLWindowBase::_loadQMLFile(const QFileInfo &info){
        this->setFlags(Qt::Window);
        this->setResizeMode(QQuickView::SizeRootObjectToView);
        
        if(info.exists()){
            this->setSource(QUrl::fromLocalFile(info.absoluteFilePath()));
            this->_filename=info.fileName();
        }else{
            QMessageBox::critical(
                        nullptr,tr("UI Setting is invalid."),
                        tr("The specified theme directory:%1 couldn't be found.\n"
                           "Running as faisafe mode.").arg(info.absoluteFilePath()));
            this->setTitle(this->title()+tr(" (Failsafe mode)"));
            this->setSource(QUrl("qrc:///themes/failsafe/"+info.fileName()));
        }
        this->setMinimumSize(this->sizeHint());
        this->rootContext()->setContextProperty("window",this);
        this->rootContext()->setContextProperty("property",qobject_cast<storage::property_storage *>(this->property()));
    }
    void QMLWindowBase::_loadQMLFile(const QString &file){
        QFileInfo info=this->_getQMLFileFromSelectedThemes(file);
        this->_loadQMLFile(info);
    }
    
    void QMLWindowBase::setSource(const QUrl &new_source){
        QQuickView::setSource(new_source);
        this->_collectChildren();
    }
    
    void QMLWindowBase::_collectChildren(){
        this->_children.clear();
        for(QObject* object:this->rootObject()->findChildren<QObject *>()) this->_children.insertMulti(object->objectName(),object);
    }
    void QMLWindowBase::_reloadQMLFile(){
        QFileInfo info=this->_getQMLFileFromSelectedThemes(this->_filename);
        this->_loadQMLFile(info);
    }
    void QMLWindowBase::exitApplication(){
        this->close();
        qApp->quit();
        qDebug()<<"Application Exit.";
    }
    void QMLWindowBase::restartApplication(){
        this->exitApplication();
        QProcess::startDetached(qApp->arguments()[0],qApp->arguments());
    }
}