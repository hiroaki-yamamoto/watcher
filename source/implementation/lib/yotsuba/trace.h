#pragma once
class QNetworkRequest;
class QNetworkReply;
namespace yotsuba {
    void traceRequest(const QNetworkRequest &request);
    void traceReply(const QNetworkReply &reply);
}
