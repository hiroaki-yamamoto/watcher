#include <QDir>
#include <QFileInfo>
#include <QPair>
#include <QHash>
#include <QtDebug>
#include <QUuid>
#include <QtWidgets/QFileDialog>
#include <QtQuick/QQuickItem>

#include <loader/root.h>
#include <loader/topic.h>
#include <setting_default.h>

#include <fstream>
#include <libserializer/serializer.h>

#include "rootwindow.h"
#include "versionwindow.h"
#include "configwindow.h"
#include "boardwindow.h"
#include "roottabcontents.h"

namespace ui{
    void RootWindow::_createRelationBetweenSignalsAndSlots(){
        for(const QString &objName:this->_children.uniqueKeys()){
            if(objName=="info")             connect(this->_children.value(objName),SIGNAL(clicked()),SLOT(_show_version_window()));
            else if(objName=="config")      connect(this->_children.value(objName),SIGNAL(clicked()),SLOT(_config()));
            else if(objName=="back")        connect(this->_children.value(objName),SIGNAL(clicked()),SLOT(_go_back()));
            else if(objName=="next")        connect(this->_children.value(objName),SIGNAL(clicked()),SLOT(_go_forward()));
            else if(objName=="reload")      connect(this->_children.value(objName),SIGNAL(clicked()),SLOT(_reloadView()));
            else if(objName=="bookmark")    connect(this->_children.value(objName),SIGNAL(clicked()),SLOT(_openBookmark()));
            else if(objName=="save")        connect(this->_children.value(objName),SIGNAL(clicked()),SLOT(_export_setting()));
            else if(objName=="open")        connect(this->_children.value(objName),SIGNAL(clicked()),SLOT(_import_setting()));
            else if(objName=="exit")        connect(this->_children.value(objName),SIGNAL(clicked()),SLOT(exitApplication()));
        }
        connect(this->_property,SIGNAL(propertyChanged(QString,QVariant,QVariant)),SLOT(_property_changed(QString,QVariant,QVariant)));
        connect(this->_loader,SIGNAL(loaded()),SLOT(_plugin_loaded()));
        connect(this->rootObject(),SIGNAL(currentTabChanged(QVariant,QVariant)),
                SLOT(_tabContentStateChanged(const QVariant,const QVariant)));
    }
    
    //Slots
    void RootWindow::_show_version_window(){this->_version->show();}
    void RootWindow::_config(){this->_config_dialog->exec();}
    void RootWindow::_go_back(){
        RootTabContents *current=this->_getCurrentTabContent();
        if(current!=nullptr) current->back();
        else qWarning()<<"("<<this->objectName()<<",_go_back):current is null.";
    }
    
    void RootWindow::_go_forward(){
        RootTabContents *current=this->_getCurrentTabContent();
        if(current!=nullptr)current->forward();
        else qWarning()<<"("<<this->objectName()<<",_go_forward):current is null.";
    }
    
    void RootWindow::_reloadView(){
        RootTabContents *current=this->_getCurrentTabContent();
        if(current!=nullptr) current->reload();
        else qWarning()<<"("<<this->objectName()<<",_reloadView):current is null.";
    }
    
    //TODO: Implement Bookmark Manager
    void RootWindow::_openBookmark(){
        
    }
    
    void RootWindow::_import_setting(){
        QString import_path=QFileDialog::getOpenFileName(nullptr,tr("Import"),"",tr("All files (*)"));
        if(!import_path.isEmpty()){
            QFileInfo info(import_path);
            if(info.exists()&&info.isReadable()){
                std::ifstream in(import_path.toStdString());
                serializer sr(in);
                sr>>(*this->_property);
                sr.close();
                in.close();
                this->_config_dialog->updateProperties();
            }else{
                QMessageBox::critical(nullptr,tr("Import error"),tr("Importing settings is failed."));
            }
        }
    }
    
    void RootWindow::_export_setting(){
        QString export_path=QFileDialog::getSaveFileName(nullptr,tr("Export"),"",tr("All files (*)"));
        if(!export_path.isEmpty()){
            QFileInfo info(export_path);
            std::ofstream out(export_path.toStdString());
            serializer sr(out);
            sr<<(*this->_property);
            sr.close();
            out.close();
        }
    }
    void RootWindow::_property_changed(const QString &key, const QVariant &prev, const QVariant &now){
        Q_UNUSED(prev);
        /*
         *There is a bug the application gets segfault when QMLWindowBase::setSource() is called.
         */
        if(key==default_value::setting_default::name_plugin_root_dir()){
            if(now.type()==QMetaType::QString){
                if(this->_loader->reload(now.toString())){
                    qDebug()<<"Plugin reloading succeeded.";
                }else qWarning()<<"Reloading failed!";
            }
        }
        else if(key==default_value::setting_default::name_theme_selected_dir()){
    #ifdef EXPERIMENT
            if(now.type()==QMetaType::QString){
                this->_loadQMLFile(QFileInfo(now.toString(),"RootWindow.qml"));
            }else qWarning()<<this->objectName()<<": Setting key:"<<default_value::setting_default::name_theme_selected_dir()<<" has an invalid value type.";
    #endif
        }else if(key==default_value::setting_default::name_disabled_plugins_uuid()){
            this->_loader->reload();
        }
    }
    void RootWindow::_plugin_loaded(){
        for(auto i=this->_tabcontents.begin();i!=this->_tabcontents.end();i++) (*i)->deleteLater();
        this->_tabcontents.clear();
        for(plugin::root *&plugin_root:*this->plugins()){
            if(!this->_property->get(default_value::setting_default::name_disabled_plugins_uuid()).toList().contains(QVariant(plugin_root->identifier()))){
                QPair<QString,QUuid> key=qMakePair(plugin_root->title(),plugin_root->identifier());
                this->_tabcontents[key]=new RootTabContents(plugin_root,this);
                connect(this->_tabcontents[key],SIGNAL(topicMode(plugin::board*)),
                        SLOT(_topicMode(plugin::board*)));
                connect(this->_tabcontents[key],SIGNAL(stateChanged()),SLOT(_tabContentStateChanged()));
            }
        }
    }
    void RootWindow::_tabContentStateChanged(){this->_tabContentStateChanged(QVariant(),QVariant());}
    void RootWindow::_tabContentStateChanged(const QVariant &previous, const QVariant &current){
        Q_UNUSED(previous)
        Q_UNUSED(current)
        RootTabContents *cur=this->_getCurrentTabContent();
        if(cur==nullptr){
            qWarning()<<"("<<this->objectName()<<")"<<"Current TabContent is nullptr";
            return;
        }
        switch(cur->state()){
            case RootTabContents::Category:
                this->_children["back"]->setProperty("enabled",false);
                this->_children["next"]->setProperty("enabled",!cur->boards_empty());
                break;
            case RootTabContents::Board:
                this->_children["next"]->setProperty("enabled",false);
                this->_children["back"]->setProperty("enabled",!cur->categories_empty());
                break;
            default:
                this->_children["back"]->setProperty("enabled",false);
                this->_children["next"]->setProperty("enabled",false);
                break;
        }
    }

    void RootWindow::_topicMode(plugin::board *board){
        qDebug()<<"Topic Mode";
        this->_boardwindow->show();
        this->_boardwindow->addTabContents(board);
    }
}
