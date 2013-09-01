#include <QList>
#include <QPluginLoader>
#include <QUuid>
#include <QDir>
#include <loader/root.h>
#include <QtDebug>
#include "plugin_loader.h"
namespace loader{
    plugin_loader::plugin_loader(const QString &root_dir, const QString &objName, QObject *parent):QObject(parent){
        this->_root_dir=root_dir;
        this->setObjectName(objName);
        this->_instances=new QList<plugin::root *>();
        this->_loaders=new QList<QPluginLoader *>();
    }
    plugin_loader::~plugin_loader(){
        delete this->_instances;
        delete this->_loaders;
    }
    
    QString plugin_loader::root_dir() const{return this->_root_dir;}
    QList<plugin::root *> *plugin_loader::instances() const{return this->_instances;}
    
    bool plugin_loader::load(){
        QDir dir(this->_root_dir);
        if(!dir.exists()){
            qWarning()<<"Plugin root dir:"<<dir.path()<<" doesn't exist.";
            return false;
        }
        for(const QFileInfo &info:dir.entryInfoList(QDir::Files|QDir::NoDotAndDotDot|QDir::Readable|QDir::Executable)){
            if(!QLibrary::isLibrary(info.filePath())){
                qWarning()<<"Impossible to load the file:"<<info.absoluteFilePath();
                continue;
            }
            qDebug()<<"Loading: "<<info.filePath();
            QPluginLoader *loader=new QPluginLoader(info.filePath());
            QObject *instance=loader->instance();
            if(instance!=0){
                (*this->_instances)<<qobject_cast<plugin::root *>(instance);
                (*this->_loaders)<<loader;
                qDebug()<<"Loaded:  "<<loader->fileName();
                qDebug()<<"    Plugin Name:"<<qobject_cast<plugin::root *>(instance)->title();
                qDebug()<<"    Plugin UUID:"<<qobject_cast<plugin::root *>(instance)->identifier().toString();
            }else{
                qWarning()<<"Loading failed: "<<loader->fileName();
                qWarning()<<"    Reason: "<<loader->errorString();
                loader->unload();
                loader->deleteLater();
            }
        }
        emit this->loaded();
        return true;
    }
    bool plugin_loader::unload(){
        for(plugin::root *instance:*this->_instances) instance->closing();
        for(QPluginLoader *loader:*this->_loaders){
            if(loader->unload()) qDebug()<<"Unloaded: "<<loader->fileName();
            else{
                qWarning()<<"Unloading failed: "<<loader->fileName();
                qWarning()<<"    Reason:"<<loader->errorString();
            }
            delete loader;
        }
        this->_instances->clear();
        this->_loaders->clear();
        return true;
    }
    void plugin_loader::setRootDir(const QString &root_dir){this->_root_dir=root_dir;}
    bool plugin_loader::reload(const QString &root_dir){
        this->setRootDir(root_dir);
        this->unload();
        bool ret=this->load();
        return ret;
    }
    bool plugin_loader::reload(){return this->reload(this->_root_dir);}
}
