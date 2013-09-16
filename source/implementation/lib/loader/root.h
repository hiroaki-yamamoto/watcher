#pragma once
/*
 * Here is a exception about the license.
 * NOTICE: This code is licensed under the terms of the latest version of LGPLv3. Not GPLv3.
 *                                                                        ~~~~~~
 */
#include <QObject>
#include <QtNetwork/QNetworkReply>
#include <loader/content_base.h>

class QWidget;
class QIcon;
class QString;
class QUuid;
namespace plugin{
    class category;
    //Root object
    class root:public content_base{
            Q_OBJECT
            using content_base::content_base;
        public:
            virtual bool enable_option() const=0;
            virtual const QString &version() const=0;
            virtual const QIcon &icon() const=0;
            virtual QObject *this_object();
            virtual void closing();
        public slots:
            virtual void get_categories()=0;
            virtual void open_option(QWidget *sender=nullptr);
        signals:
            void get_categories_finished(const QVector<plugin::category *> &categories);
            void get_categories_failed(const QNetworkReply::NetworkError err,const QString &err_str);
    };
}
Q_DECLARE_INTERFACE(plugin::root,"net.hysoft.watcher.plugin")
