#pragma once
#include<QObject>
#include<QString>
#include<QUuid>
class QQuickItem;
namespace ui{
    class TabWindowBase;
    class TabContentsBase:public QObject{
            Q_OBJECT
            Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
            Q_PROPERTY(QUuid   uuid  READ title WRITE setUUID  NOTIFY uuidChanged)
        public:
            TabContentsBase(const QString &title,const QUuid &uuid,TabWindowBase *parent=nullptr);
            TabContentsBase(const QString &title,const QUuid &uuid,TabContentsBase *parent=nullptr);
            QString title() const;
            QUuid UUID() const;
        signals:
            void titleChanged();
            void uuidChanged();
        public slots:
            //By default, this function does nothing and always returns nulltpr.
            virtual QQuickItem *addTab(const QString &title,const QUuid &uuid);
            void setTitle(const QString &title);
            void setUUID(const QUuid &uuid);
            virtual void deleteLater();
        protected:
            TabWindowBase *_parentWindow;
            TabContentsBase *_parentTab;
            QQuickItem *_tabcontents;
    };
}
