#pragma once
#include <QObject>
#include <QVector>
#include <QHash>
#include <QPair>
#include <QUuid>
#include <QString>
#include <QtNetwork/QNetworkReply>
namespace plugin{
    class root;
    class category;
    class board;
    class topic;
    class response;
}
class QQuickItem;
namespace ui{
    class RootWindow;
    class RootTabContents:public QObject{
            Q_OBJECT
            Q_PROPERTY(QString TabName READ TabName WRITE setTabName)
            Q_PROPERTY(ViewState State READ state NOTIFY stateChanged)
        public:
            RootTabContents(plugin::root *plugin_root,ui::RootWindow *parent=nullptr);
            enum ViewState{Category,Board};
            ViewState state();
            QString TabName() const;
            bool categories_empty() const;
            bool boards_empty() const;
        public slots:
            void setTabName(const QString &name);
            void button_clicked(QVariant button_var);
            void back();
            void forward();
            void reload();
            void deleteLater();
        signals:
            void topicMode(plugin::board *board);
            void stateChanged();
        private slots:
            void _get_category_completed(const QVector<plugin::category *> &categories);
            void _get_boards_completed(const QVector<plugin::board *> &boards);
            void _get_category_failed(const QNetworkReply::NetworkError err,const QString &err_str);
            void _get_boards_failed(const QNetworkReply::NetworkError err,const QString &err_str);
            void _process_switch_instruction();
            void _set_category();
            void _set_board();
            void _switch_contents();
            void _back();
            void _forward();
            void _reload();
            void _addButton(const QString &button_text,const QString &detailed_text=QString(),const QUuid &id=QUuid());
            void _clearButtons();
        private:
            enum SwitchInstruction{Back,Forward,Reload,ContentsSwitch} _sw_inst;
            void _do_switch(const SwitchInstruction sw);
            void _fetch_failed(const QString &type,const QString &err_str);
            bool _hasAnimation;
            QHash<QPair<QUuid,QString>,plugin::category *> _category_hash;
            QHash<QPair<QUuid,QString>,plugin::board *> _board_hash;
            plugin::root *_root;
            RootWindow *_parent;
            QQuickItem *_tabcontent;
            QHash<ui::RootTabContents::ViewState,QPair<QUuid,QString>> _contentsName;
            ViewState _state;
    };
}
