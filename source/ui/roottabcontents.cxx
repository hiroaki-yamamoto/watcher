#include <QtWidgets/QMessageBox>
#include <QMetaObject>
#include <QtQuick/QQuickItem>
#include <QtDebug>
#include <QUuid>

#include <algorithm>
#include <list>

#include <loader/root.h>
#include <loader/category.h>
#include <loader/board.h>
#include <loader/topic.h>
#include <loader/response.h>

#include "roottabcontents.h"
#include "rootwindow.h"
#include "tabcontents_base.h"
namespace ui{
    RootTabContents::RootTabContents(plugin::root *plugin_root, ui::RootWindow *parent):
        TabContentsBase(plugin_root->title(),plugin_root->identifier(),parent){
        this->_root=plugin_root;
        this->_state=RootTabContents::Category;

        connect(this->_root,SIGNAL(get_categories_finished(QVector<plugin::category*>)),
                SLOT(_get_category_completed(QVector<plugin::category*>)));
        connect(this->_root,SIGNAL(get_categories_failed(QNetworkReply::NetworkError,QString)),
                            SLOT(_get_category_failed(QNetworkReply::NetworkError,QString)));
        connect(this->_tabcontents,SIGNAL(buttonClicked(QVariant)),SLOT(button_clicked(QVariant)));
        QVariant &&hasAnimation=this->_tabcontents->property("hasAnimation");
        this->_hasAnimation=hasAnimation.type()==QMetaType::Bool&&hasAnimation.toBool();
        this->_root->get_categories();
    }
    bool RootTabContents::categories_empty()const{return this->_category_hash.isEmpty();}
    bool RootTabContents::boards_empty()const{return this->_board_hash.isEmpty();}
    void RootTabContents::_get_category_completed(const QVector<plugin::category *> &categories){
        this->_category_hash.clear();
        for(plugin::category *category:categories){
            connect(category,SIGNAL(get_boards_finished(QVector<plugin::board*>)),
                             SLOT(_get_boards_completed(QVector<plugin::board*>)));
            connect(category,SIGNAL(get_boards_failed(QNetworkReply::NetworkError,QString)),
                             SLOT(_get_boards_failed(QNetworkReply::NetworkError,QString)));
            this->_category_hash.insert(qMakePair(category->identifier(),category->title()),category);
        }
        if(this->_state==ui::RootTabContents::Category) this->_set_category();
    }
    void RootTabContents::_get_boards_completed(const QVector<plugin::board *> &boards){
        this->_board_hash.clear();
        for(plugin::board *board:boards){
            this->_board_hash.insert(qMakePair(board->identifier(),board->title()),board);
        }
        if(this->_state==ui::RootTabContents::Board) this->_set_board();
    }
    
    RootTabContents::ViewState RootTabContents::state(){return this->_state;}
    QString RootTabContents::TabName() const{
        if(this->_tabcontents->property("title").type()!=QMetaType::QString){
            qWarning()<<this->objectName()<<": Couldn't get the name of the tab.";
            return QString();
        }
        return this->_tabcontents->property("title").toString();
    }
    void RootTabContents::setTabName(const QString &name){this->_tabcontents->setProperty("title",name);}
    void RootTabContents::button_clicked(QVariant button_var){
        qDebug()<<"("<<this->objectName()<<"):Current State:"<<this->_state;
        this->_contentsName.insert(this->_state,
                                   qMakePair(
                                       QUuid(QByteArray(button_var.value<QQuickItem *>()->property("uuid").toString().toUtf8())),
                                        button_var.value<QQuickItem *>()->property("text").toString()));
        this->_do_switch(ContentsSwitch);
        qDebug()<<"("<<this->objectName()<<"):"<<this->_contentsName;
    }
    void RootTabContents::_do_switch(const SwitchInstruction sw){
        this->_sw_inst=sw;
        if(this->_hasAnimation&&(sw!=RootTabContents::ContentsSwitch||this->_state==RootTabContents::Category)){
            connect(this->_tabcontents,SIGNAL(hideAnimationCompleted()),SLOT(_process_switch_instruction()));
            QMetaObject::invokeMethod(this->_tabcontents,"hide");
        }else this->_process_switch_instruction();
    }
    void RootTabContents::_process_switch_instruction(){
        switch(this->_sw_inst){
                case RootTabContents::ContentsSwitch:this->_switch_contents();   break;
                case RootTabContents::Back:          this->_back();              break;
                case RootTabContents::Forward:       this->_forward();           break;
                case RootTabContents::Reload:        this->_reload();            break;
        }
        if(this->_hasAnimation) this->_tabcontents->disconnect(SIGNAL(hideAnimationCompleted()));
    }
    
    void RootTabContents::_switch_contents(){
        switch(this->_state){
            case RootTabContents::Category:
                if(this->_category_hash.contains(this->_contentsName[RootTabContents::Category])){
                    this->_state=RootTabContents::Board;
                    emit this->stateChanged();
                    this->_category_hash[this->_contentsName[RootTabContents::Category]]->get_boards();
                }else{
                    qWarning()<<"("<<this->objectName()<<"): "<<"Value of "<<this->_contentsName<<" couldn't be found.";
                    qWarning()<<"    State:"<<this->_state;
                }
                break;
            case RootTabContents::Board:
                if(this->_board_hash.contains(this->_contentsName[RootTabContents::Board])){
                    emit this->topicMode(this->_board_hash[this->_contentsName[RootTabContents::Board]]);
                }else{
                    qWarning()<<"("<<this->objectName()<<"): "<<"Value of "<<this->_contentsName<<" couldn't be found.";
                    qWarning()<<"    State:"<<this->_state;
                }
                break;
            default:
                qWarning()<<"("<<this->objectName()<<"): Undefined state.";
                break;
        }
    }
    
    void RootTabContents::back(){this->_do_switch(Back);}
    void RootTabContents::forward(){this->_do_switch(Forward);}
    void RootTabContents::reload(){this->_do_switch(Reload);}
    
    void RootTabContents::_back(){
        switch(this->_state){
            case RootTabContents::Category:
                qWarning()<<"("<<this->objectName()<<"): State is Category. Cannot go back.";
                break;
            case RootTabContents::Board:
                this->_state=RootTabContents::Category;
                emit this->stateChanged();
                this->_set_category();
                break;
            default:
                qWarning()<<"("<<this->objectName()<<"): Undefined state.";
                break;
        }
    }
    void RootTabContents::_forward(){
        switch(this->_state){
            case RootTabContents::Category:
                this->_state=RootTabContents::Board;
                emit this->stateChanged();
                this->_set_board();
                break;
            case RootTabContents::Board:
                qWarning()<<"("<<this->objectName()<<"): End of state.";
                break;
            default:
                qWarning()<<"("<<this->objectName()<<"): Undefined state.";
                break;
        }
    }
    void RootTabContents::_reload(){
        switch(this->_state){
            case RootTabContents::Category:
                this->_root->get_categories();
                break;
            case RootTabContents::Board:
                this->_category_hash[this->_contentsName[RootTabContents::Category]]->get_boards();
                break;
            default:
                qWarning()<<"("<<this->objectName()<<"): Undefined state.";
                break;
        }
    }
    void RootTabContents::_addButton(const QString &button_text, const QString &detailed_text, const QUuid &id){
        QMetaObject::invokeMethod(this->_tabcontents,
                                  "addButton",
                                  Q_ARG(QVariant,button_text),
                                  Q_ARG(QVariant,detailed_text),
                                  Q_ARG(QVariant,QVariant(id.toString())));
    }
    void RootTabContents::_clearButtons(){QMetaObject::invokeMethod(this->_tabcontents,"clearButtons");}

    void RootTabContents::_set_category(){
        this->_clearButtons();
        std::list<plugin::category *> &&categories=this->_category_hash.values().toStdList();
        categories.sort([](const plugin::category *a,const plugin::category *b)->bool{return a->title().compare(b->title())<0;});
        for(const plugin::category *category:categories){
            this->_addButton(category->title(),category->description(),category->identifier());
        }
        if(this->_hasAnimation) QMetaObject::invokeMethod(this->_tabcontents,"show");
    }
    void RootTabContents::_set_board(){
        this->_clearButtons();
        std::list<plugin::board *> &&boards=this->_board_hash.values().toStdList();
        boards.sort([](const plugin::board *a,const plugin::board *b)->bool{return a->title().compare(b->title())<0;});
        for(const plugin::board *board:boards){
            this->_addButton(board->title(),board->description(),board->identifier());
        }
        if(this->_hasAnimation) QMetaObject::invokeMethod(this->_tabcontents,"show");
    }
    
    //Error case
    void RootTabContents::_fetch_failed(const QString &type, const QString &err_str){
        QMessageBox::warning(nullptr,tr("%1:Fetch Error").arg(this->_root->title())
                             ,tr("Plugin Name: %1<br />"
                                 "Couldn't fetch list of %2.<br />"
                                 "Reason: %3").arg(this->_root->title(),type,err_str));
    }
    
    void RootTabContents::_get_category_failed(const QNetworkReply::NetworkError err,const QString &err_str){
        this->_fetch_failed(tr("categories"),err_str);
    }
    void RootTabContents::_get_boards_failed(const QNetworkReply::NetworkError err,const QString &err_str){
        this->_fetch_failed(tr("boards"),err_str);
    }
}
