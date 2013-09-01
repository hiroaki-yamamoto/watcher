#pragma once
#include "multiple_scroll_area.h"
#include <QDir>

template<class T> class QVector;
namespace ui{
    class ThemePanel;
    class ThemeScrollArea:public MultipleScrollArea{
            Q_OBJECT
            Q_PROPERTY(QVector<QDir> ThemeRootDirs READ themeRootDirs WRITE setThemeRootDirs)
        public:
            ThemeScrollArea(QWidget *parent=nullptr);
            ThemeScrollArea(const QVector<QDir> &theme_root_dirs=QVector<QDir>(),QWidget *parent=nullptr);
            ~ThemeScrollArea();
            QVector<QDir> themeRootDirs() const;
        public slots:
            void setThemeRootDirs(const QVector<QDir> &theme_root_dirs);
            void selectDir(const QDir &dir);
        signals:
            void themeSelected(const ThemePanel *theme);
        private:
            void checkEntry();
            QVector<QDir> *_theme_root_dirs;
            ThemePanel *_previous_selected;
        private slots:
            void selectionChanged(bool selected);
    };
}
