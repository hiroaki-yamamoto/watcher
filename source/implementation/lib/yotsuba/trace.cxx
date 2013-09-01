#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QtDebug>
#include "trace.h"
namespace yotsuba{
    void traceRequest(const QNetworkRequest &request){
        qDebug()<<"Request Header:";
        for(const QByteArray &header:request.rawHeaderList()) qDebug()<<"    "<<header<<":"<<request.rawHeader(header);
    }
    void traceReply(const QNetworkReply &reply){
        qDebug()<<"Reply Header:";
        for(const QByteArray &headerName:reply.rawHeaderList()) qDebug()<<"    "<<headerName<<":"<<reply.rawHeader(headerName);
    }
}
