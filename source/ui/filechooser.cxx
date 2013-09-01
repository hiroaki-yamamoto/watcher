#include "filechooser.h"
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QFileDialog>

#include <QtDebug>

namespace ui{
    FileChooser::FileChooser(const QString &objName,QWidget *parent){
        FileChooser(QFileInfo(),FileChooser::File,objName,parent);
    }
    
    FileChooser::FileChooser(const QFileInfo &file_path, const ChooseMode mode,const QString &objName, QWidget *parent):QWidget(parent){
        this->setObjectName(objName);
        if(!file_path.exists()) qWarning()<<"("<<this->objectName()<<"): "<<file_path.filePath()<<"doesn't exist.";
        else qWarning()<<"("<<this->objectName()<<"): FilePath"<< file_path.absoluteFilePath();
        this->_info=file_path;
        this->_filepath=new QLineEdit(file_path.absoluteFilePath(),this);
        this->_mode=mode;
        
        this->_filepath->setReadOnly(true);
        this->_refbutton=new QPushButton("...",this);
        this->_refbutton->setFixedWidth(this->_refbutton->height());
        this->_refbutton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
        
        QHBoxLayout *layout=new QHBoxLayout(this);
        layout->setContentsMargins(0,0,0,0);
        layout->addWidget(this->_filepath);
        layout->addWidget(this->_refbutton);
        
        this->setLayout(layout);
        this->show();
        
        connect(this->_refbutton,SIGNAL(clicked()),SLOT(_refbutton_clicked()));
    }
    FileChooser::ChooseMode FileChooser::mode() const{return this->_mode;}
    void FileChooser::setMode(const ChooseMode mode){this->_mode=mode;}
    QString FileChooser::filter() const{return this->_filter;}
    void FileChooser::setFilter(const QString &filter){this->_filter=filter;}
    void FileChooser::setPath(const QString &path){
        QFileInfo previous_path=this->_info,now_path=QFileInfo(path);
        bool cancel=false;
        if(!now_path.exists()){qWarning()<<"("<<this->objectName()<<"): "<<now_path.absoluteFilePath()<<" doesn't exist.";}
        if(this->_mode==FileChooser::Dir&&!now_path.isDir()) qWarning()<<now_path.absoluteFilePath()<<" is not a directory.";
        else if(this->_mode==FileChooser::File&&now_path.isDir()) qWarning()<<now_path.absoluteFilePath()<<"is not a file.";
        this->_filepath->setText(now_path.absoluteFilePath());
        if(previous_path!=now_path){
            this->_info=now_path;
            qDebug()<<"("<<this->objectName()<<"): Previous Path:"<<previous_path.absoluteFilePath();
            qDebug()<<"("<<this->objectName()<<"): Current Path:"<<now_path.absoluteFilePath();
            emit this->filePathChanged(previous_path,now_path,cancel);
        }
        if(cancel){
            this->_info=previous_path;
            this->_filepath->setText(this->_info.filePath());
        }
    }
    
    QFileInfo FileChooser::fileinfo() const{return this->_info;}
    void FileChooser::_refbutton_clicked(){
        QString str;
        switch(this->_mode){
            case FileChooser::File:
                str=QFileDialog::getOpenFileName(this,"Open",QString(),this->_filter);
                break;
            case FileChooser::Dir:
                str=QFileDialog::getExistingDirectory(this,"Open",this->_filter);
                break;
        }
        if(!str.isEmpty()) this->setPath(str);
    }
}
