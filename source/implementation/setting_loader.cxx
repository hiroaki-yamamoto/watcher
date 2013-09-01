#include "setting_loader.h"
#include "setting_default.h"
#include <QtDebug>
#include <QDir>
#include <property_storage.h>
#include <fstream>
#include <libserializer/serializer.h>
namespace loader{
    setting_loader::setting_loader(const QString &file,const int element_size,const QString &objName){
        this->_storage=new storage::property_storage(element_size,objName);
        this->_default=new default_value::setting_default();
        this->_file=file;
    }
    setting_loader::~setting_loader(){
        delete this->_storage;
        delete this->_default;
    }
    
    storage::property_storage &setting_loader::storage() const{return (*this->_storage);}
    QString setting_loader::filePath() const{return this->_file;}
    bool setting_loader::read(){
        std::ifstream setting_in(this->_file.toStdString());
        bool success=false;
        if(!setting_in){
            qWarning()<<"("<<this->_storage->objectName()<<"):"<<"Setting file couldn't be read:"<<this->_file;
        }else{
            serializer serializer_in(setting_in);
            serializer_in>>(*this->_storage);
            serializer_in.close();
            qDebug()<<"("<<this->_storage->objectName()<<"):"<<"Read setting file:"<<this->_file;
            success=true;
        }
        setting_in.close();
        this->_storage->differencial_copy(*this->_default);
        return success;
    }
    bool setting_loader::write(){
        QFileInfo fileinfo(this->_file);
        QDir &&dir=fileinfo.dir();
        if(!dir.exists()){
            dir.cdUp();
            dir.mkpath(fileinfo.absolutePath());
        }
        std::ofstream setting_out(this->_file.toStdString(),ios_base::trunc);
        serializer serializer_out(setting_out);
        serializer_out<<((*this->_storage)-(*this->_default));
        serializer_out.close();
        setting_out.close();
        qDebug()<<"("<<this->_storage->objectName()<<"):"<<"Wrote setting to:"<<this->_file;
        return true;
    }
}
