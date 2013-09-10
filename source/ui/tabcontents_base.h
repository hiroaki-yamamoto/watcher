#pragma once
#include<QObject>
class QQuickItem;
class QString;
class QUuid;
namespace ui{
    class QMLWindowBase;
    class TabContentsBase:public QObject{
            Q_OBJECT
            Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
            Q_PROPERTY(QUuid   uuid  READ title WRITE setUUID  NOTIFY uuidChanged)
        public:
            TabContentsBase(const QString &title,const QUuid &uuid,QMLWindowBase *parent=nullptr);
            QString title() const;
            QUuid UUID() const;
        signals:
            void titleChanged();
            void uuidChanged();
        public slots:
            void setTitle(const QString &title);
            void setUUID(const QUuid &uuid);
            virtual void deleteLater();
        protected:
            QMLWindowBase *_parent;
            QQuickItem *_tabcontents;
    };
}
