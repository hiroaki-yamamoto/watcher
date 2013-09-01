#include <QDebug>
#include <QUrl>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QSharedPointer>
#include <QUuid>
#include "api_urls.h"
#include "root.h"
#include "category.h"
#include "board.h"
#include "error.h"
#include "trace.h"
namespace yotsuba{
    category::category(std::mt19937 *mt,QObject *parent):plugin::category(parent){
        if(mt==nullptr){
            qWarning()<<"mt must not be nulltpr.";
            this->deleteLater();
            return;
        }
        this->_ws=false;
        this->_mt=mt;
    }
    
    void category::setWorkSafe(const bool ws){this->_ws=ws;}
    void category::get_boards(){
        //Download Board List.
        QNetworkAccessManager *manager=new QNetworkAccessManager(this);
        connect(manager,SIGNAL(finished(QNetworkReply*)),SLOT(getDataFinished(QNetworkReply*)));
        manager->get(create_request(board_list_url()));
    }
    //This slot is called when downloading board list has been finished.
    void category::getDataFinished(QNetworkReply *reply){
        traceReply(*reply);
        if(reply->error()!=QNetworkReply::NoError){
            emit this->get_boards_failed(reply->error(),reply->errorString());
            reply->close();
            return;
        }
        QByteArray raw_data=reply->readAll();
        reply->close();
        QJsonDocument &&data=QJsonDocument::fromJson(raw_data);
        if(data.isNull()){
            emit this->get_boards_failed(QNetworkReply::UnknownContentError,
                                         generate_invalid_document(reply->url(),raw_data));
            return;
        }
        if(!data.object().contains("boards")){
            emit this->get_boards_failed(QNetworkReply::UnknownContentError,generate_key_not_found("boards"));
            return;
        }
        QJsonValue &&boards_value=data.object()["boards"];
        if(!boards_value.isArray()){
            emit this->get_boards_failed(QNetworkReply::UnknownContentError,generate_invalid_type("boards","Array"));
            return;
        }
        QJsonArray &&boards=boards_value.toArray();
        QVector<plugin::board *> board_list;
        for(QJsonArray::const_iterator &&board=boards.constBegin();board<boards.constEnd();board++){
            if(!(*board).isObject()){
                emit this->get_boards_failed(QNetworkReply::UnknownContentError,generate_invalid_type("The element of \"boards\"","Object"));
                return;
            }
            QJsonObject &&board_object=(*board).toObject();
            if(!board_object.contains("board")){
                emit this->get_boards_failed(QNetworkReply::UnknownContentError,generate_key_not_found("board"));
                return;
            }
            if(!board_object.contains("title")){
                emit this->get_boards_failed(QNetworkReply::UnknownContentError,generate_key_not_found("title"));
                return;
            }
            if(!board_object.contains("ws_board")){
                emit this->get_boards_failed(QNetworkReply::UnknownContentError,generate_key_not_found("ws_board"));
                return;
            }
            QJsonValue  &&board_dir=board_object["board"],&&board_title=board_object["title"],
                    &&ws_board=board_object["ws_board"];
            
            if(!board_dir.isString()){
                emit this->get_boards_failed(QNetworkReply::UnknownContentError,generate_invalid_type("board","Object"));
                return;
            }
            if(!board_title.isString()){
                emit this->get_boards_failed(QNetworkReply::UnknownContentError,generate_invalid_type("title","String"));
                return;
            }
            if(!ws_board.isDouble()){
                emit this->get_boards_failed(QNetworkReply::UnknownContentError,generate_invalid_type("ws_board","Double"));
                return;
            }
            if((int)this->_ws==(int)ws_board.toDouble()){
            unsigned int random_number=(*this->_mt)();
                yotsuba::board *yotsuba_board=new yotsuba::board(this->_mt,this);
                yotsuba_board->setBoardURL(QUrl(QString("http://boards.4chan.org/%1/").arg(board_dir.toString())));
                yotsuba_board->setTitle(board_title.toString());
                yotsuba_board->setBoardDirName(board_dir.toString());
                yotsuba_board->setIdentifier(QUuid::createUuidV5(this->identifier(),
                                                                 QByteArray((char *)&random_number,sizeof(random_number))));
                yotsuba_board->setDescription(yotsuba_board->board_url().toString());
                board_list<<yotsuba_board;
            }
        }
        emit this->get_boards_finished(board_list);
        this->sender()->deleteLater();
    }
}
