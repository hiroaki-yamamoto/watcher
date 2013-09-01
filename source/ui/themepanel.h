#pragma once
#include <QtWidgets/QWidget>
#include <QDir>
#include "ui_themepanel.h"
class QString;
namespace ui{
    class ThemePanel:public QWidget,private Ui::themepanel{
            Q_OBJECT
            Q_PROPERTY(QDir dir READ dir)
            Q_PROPERTY(bool selected READ selected WRITE setSelected)
            Q_PROPERTY(QString theme_title READ theme_title WRITE setThemeTitle)
            Q_PROPERTY(QString theme_desc READ theme_desc WRITE setThemeDesc)
            Q_PROPERTY(QString theme_version READ theme_version WRITE setThemeVersion)
            Q_PROPERTY(QString theme_author READ theme_author WRITE setThemeAuthor)
        public:
            ThemePanel(const QDir &dir,QWidget *parent=nullptr);
            bool selected() const;
            QDir dir() const;
            QString theme_title() const;
            QString theme_desc() const;
            QString theme_version() const;
            QString theme_author() const;
        signals:
            void selectionChanged(bool selected);
        public slots:
            void setSelected(const bool selected) const;
            void setThemeTitle(const QString &title);
            void setThemeDesc(const QString &desc);
            void setThemeVersion(const QString &version);
            void setThemeAuthor(const QString &author);
        private:
            void setEmptyTitleAndDesc();
            void setEmptyTitle();
            void setEmptyDesc();
            QDir _dir;
    };
}
