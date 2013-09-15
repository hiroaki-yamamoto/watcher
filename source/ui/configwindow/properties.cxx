#include <QtDebug>
#include "configwindow.h"

#include "filechooser.h"
#include "themepanel.h"

#include "setting_default.h"
#include "plugin_loader.h"
namespace ui{
    void ConfigDialog::_createRelationUIandSetting(){
        this->_setting_object[default_value::setting_default::name_plugin_root_dir()]=this->_plugin_dir;
        this->_setting_object[default_value::setting_default::name_theme_root_dir()]=this->_theme_dir;
        this->_setting_object[default_value::setting_default::name_display_thumbnails()]=this->displayThumbnailCheckbox;
        this->_setting_object[default_value::setting_default::name_display_anchors()]=this->anchorCheckbox;
        this->_setting_object[default_value::setting_default::name_theme_selected_dir()]=this->_theme_list;
    }
    void ConfigDialog::updateProperties(){
        for(const QString &key:this->_setting_object.uniqueKeys()){
            const QString class_name(this->_setting_object[key]->metaObject()->className());
            QWidget *obj=this->_setting_object[key];
            qDebug()<<"Control Type:"<<class_name;
            
            if(this->_property->exists(key)){
                qDebug()<<"Key:"<<key<<" is found in setting storage. reading...";
                this->_setVariantToUI(obj,this->_property->get(key));
            }else{
                qDebug()<<"Key:"<<key<<" couldn't be found in setting storage. Ignoring...";
            }
        }
    }
    void ConfigDialog::_setVariantToUI(QWidget *ui, const QVariant &value){
        QString &&class_name=ui->metaObject()->className();
        qDebug()<<"Control Type:"<<class_name;
        if(class_name=="QCheckBox"||class_name=="QRadioButton")
            QMetaObject::invokeMethod(ui,"setChecked",Q_ARG(bool,value.toBool()));
        else if(class_name=="QSpinBox")
            QMetaObject::invokeMethod(ui,"setValue",Q_ARG(int,value.toInt()));
        else if(class_name=="ui::filechooser")
            QMetaObject::invokeMethod(ui,"setPath",Q_ARG(QString,value.toString()));
        else if(class_name=="ui::theme_scroll_area"){
            switch(value.type()){
                case QMetaType::QString:
                    QMetaObject::invokeMethod(ui,"selectDir",Q_ARG(QDir,QDir(value.toString())));
                    break;
                case QMetaType::Int:
                {
                    int index=value.toInt();
                    ThemeScrollArea *theme_area=qobject_cast<decltype(theme_area)>(ui);
                    if (theme_area->children_size()<=index){
                        qWarning()<<"("<<ui->objectName()<<"):"<<"Out of range.";
                        break;
                    }
                    ThemePanel *panel=qobject_cast<decltype(panel)>((*theme_area)[value.toInt()]);
                    panel->setSelected(true);
                }
                    break;
                default:
                    qWarning()<<"("<<ui->objectName()<<"):"<<"The type of specified value is invalid.";
                    break;
            }
        }
    }
}
