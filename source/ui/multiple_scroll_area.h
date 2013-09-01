#pragma once
#include <QtWidgets/QScrollArea>

class QVBoxLayout;
namespace ui{
    class PluginPanel;
    class MultipleScrollArea:public QScrollArea{
            Q_OBJECT
        public:
            MultipleScrollArea(QWidget *parent=nullptr);
            MultipleScrollArea &operator <<(QWidget *panel);
            QWidget *operator [](const int index) const;
            int children_size() const;
            void clear();
        protected:
            QWidget *_widget;
            QVBoxLayout *_layout;
    };
}
