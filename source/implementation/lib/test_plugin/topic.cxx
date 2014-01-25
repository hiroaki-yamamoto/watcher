#include <QtDebug>
#include <QImage>
#include <QUrl>
#include <QUuid>
#include <QtGlobal>
#include <random>
#include <logging/logging.h>
#include "root.h"
#include "category.h"
#include "board.h"
#include "topic.h"
#include "response.h"
using namespace std;
namespace test{
    topic::topic(const QString &title, const QString &author, const QUuid &id,const QUrl &topicURL, QObject *parent):plugin::topic(parent){
        this->setTitle(title);
        this->setAuthor(author);
        this->setIdentifier(id);
        this->_topicURL=topicURL;
    }
    bool topic::readonly() const{return false;}

    const QUrl &topic::topic_url() const{return this->_topicURL;}
    void topic::get_responses(){
        QString responseTitle=tr("Test Response %1"),
                responseAuthor=tr("Anonymouse %1"),
                responseEmail=tr("anonymouse%1@example.com"),
                /*
                 *%1: Type
                 *%2: Name
                 *%3: Author
                 *%4: Desc.
                 *%5: Uuid
                 *%6: Link
                 */
                informationTable=tr("<p>%1 information:"
                                    "<table>"
                                    "<tr><td>Name</td><td>%2</td></tr>"
                                    "<tr><td>Author</td><td>%3</td></tr>"
                                    "<tr><td>Desc.</td><td>%4</td></tr>"
                                    "<tr><td>Identifier</td><td>%5</td></tr>"
                                    "<tr><td>Address</td><td><a href=\"%6\">%6</a></td></tr>"
                                    "</table></p>"),
                responseBody=tr("<p>This is a test.</p>");
        QVector<QImage> images={QImage(":/images/aghi"),    QImage(":/images/air"),
                                QImage(":/images/atra_dot"),QImage(":/images/auros"),
                                QImage(":/images/autumn")};
        //Initialize mt19937 with upper 32bit of UUID as seed value.
        mt19937 random(((quint32 *)this->identifier().toByteArray().data())[0]);
        for(quint32 count=0;count<512;count++){
            QUuid id=QUuid::createUuidV5(this->identifier(),QString::number(count));
            quint32 num_images=(qAbs(random()))%(images.size()+1);
            
            QUrl responseURL=this->_topicURL.resolved("res/"+QString::number(count));
            QString response_info=informationTable.arg("Response",responseAuthor.arg(QString::number(count)),
                                                       responseTitle.arg(QString::number(count)),
                                                       responseBody,id.toString(),responseURL.toString()),
                    topic_info=informationTable.arg("Topic",this->title(),this->author(),
                                                    this->description(),this->identifier().toString(),
                                                    this->_topicURL.toString()),
                    board_info,category_info,plugin_info;
            //Board Info
            if(this->parent()!=nullptr){
                test::board *parent=qobject_cast<test::board *>(this->parent());
                board_info=informationTable.arg("Board",parent->title(),parent->author(),parent->description(),
                                                parent->identifier().toString(),parent->board_url().toString());
                //Category Info
                if(parent->parent()!=nullptr){
                    test::category *board_parent=qobject_cast<test::category *>(parent->parent());
                    category_info=informationTable.arg("Category",board_parent->title(),board_parent->author(),
                                                       board_parent->description(),board_parent->identifier().toString(),
                                                       QString());
                    //Plugin info
                    if(board_parent->parent()!=nullptr){
                        test::root *cat_parent=qobject_cast<test::root *>(board_parent->parent());
                        plugin_info=informationTable.arg("Plugin",
                                                         cat_parent->title(),cat_parent->author(),
                                                         cat_parent->description(),cat_parent->identifier().toString(),
                                                         QString());
                    }
                }
            }
            test::response *res=new test::response(responseTitle.arg(QString::number(count)),
                                                  responseBody+plugin_info+category_info+board_info+topic_info+response_info,
                                                  responseAuthor.arg(QString::number(count)),responseEmail,QDateTime::currentDateTime(),
                                                  responseURL,id,this);
            for(quint32 count_2=0;count_2<num_images;count_2++)
                res->fetchImage(responseURL.resolved(QUrl(QString("images/%1.jpg").arg(QString::number(count_2)))),
                                     images[(qAbs(random()))%images.size()]);
            this->_resposes<<res;
        }
        emit this->get_responses_finished(this->_resposes);
    }

    void topic::post(){
        //TODO:Create and Open posting UI(UI includes input fields of title,email, images and body)
    }
}
