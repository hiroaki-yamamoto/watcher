#include "theme_scroll_area.h"
#include "themepanel.h"
#include <QVector>
#include <QtDebug>
#include <QStringList>

namespace ui{
    ThemeScrollArea::ThemeScrollArea(const QVector<QDir> &theme_root_dirs, QWidget *parent):MultipleScrollArea(parent){
        this->_theme_root_dirs=new QVector<QDir>();
        this->setThemeRootDirs(theme_root_dirs);
    }
    ThemeScrollArea::ThemeScrollArea(QWidget *parent):MultipleScrollArea(parent){
        this->_theme_root_dirs=new QVector<QDir>();
        this->_previous_selected=nullptr;
    }
    ThemeScrollArea::~ThemeScrollArea(){delete this->_theme_root_dirs;}
    
    void ThemeScrollArea::setThemeRootDirs(const QVector<QDir> &theme_root_dirs){
        (*this->_theme_root_dirs)=theme_root_dirs;
        this->checkEntry();
        this->_previous_selected=nullptr;
    }
    void ThemeScrollArea::selectDir(const QDir &dir){
        for(int index=0;index<this->children_size();index++){
            ThemePanel *panel=qobject_cast<ThemePanel *>((*this)[index]);
            if(panel->dir()==dir){
                panel->setSelected(true);
                return;
            }
        }
    }
    
    QVector<QDir> ThemeScrollArea::themeRootDirs() const{return (*this->_theme_root_dirs);}
    void ThemeScrollArea::checkEntry(){
        this->clear();
        for(QDir &dir:*this->_theme_root_dirs){
            if(!dir.exists()){
                qWarning()<<"Theme root dir:"<<dir.path()<<"doesn't exist.";
                continue;
            }
            QStringList nameFilter;
            nameFilter<<"*";
            for(QFileInfo &info:dir.entryInfoList(nameFilter,QDir::NoDotAndDotDot|QDir::Dirs)){
                qDebug()<<"Theme dir found:"<<info.filePath();
                ui::ThemePanel *panel=new ui::ThemePanel(QDir(info.filePath()),this);
                connect(panel,SIGNAL(selectionChanged(bool)),SLOT(selectionChanged(bool)));
                (*this)<<panel;
            }
        }
    }
    void ThemeScrollArea::selectionChanged(bool selected){
        ThemePanel *sender=qobject_cast<ThemePanel *>(this->sender());
        if(!selected&&sender==this->_previous_selected){
            sender->setSelected(true);
        }
        if(this->_previous_selected!=nullptr&&this->_previous_selected!=sender&&selected){
            this->_previous_selected->disconnect(SIGNAL(selectionChanged(bool)));
            this->_previous_selected->setSelected(false);
            connect(this->_previous_selected,SIGNAL(selectionChanged(bool)),SLOT(selectionChanged(bool)));
            emit this->themeSelected(sender);
        }
        this->_previous_selected=sender;
    }
}
