#pragma once
#include<QHash>
#include<QPair>
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
            virtual QQuickItem *addTab(const QString &title,const QUuid &uuid);
            virtual void removeTab(const QString &title,const QUuid &uuid);
            void setTitle(const QString &title);
            void setUUID(const QUuid &uuid);
            void deleteLater();
            virtual void _closeButtonClicked(const QVariant &title,const QVariant &uuid);
        protected:
            virtual TabContentsBase *_getCurrentTabContents();
            QHash<QPair<QString,QUuid>,TabContentsBase *> _childrenTabs;
            TabWindowBase *_parentWindow;
            TabContentsBase *_parentTab;
            QQuickItem *_tabcontents;
    };
}
