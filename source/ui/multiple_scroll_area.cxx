#include "multiple_scroll_area.h"
#include <QtWidgets/QWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtDebug>
namespace ui {
    MultipleScrollArea::MultipleScrollArea(QWidget *parent)
        : QScrollArea(parent) {
        this->_widget = new QWidget(this->viewport());
        this->_layout = new QVBoxLayout(this);
        this->_layout->setAlignment((this->_layout->alignment() & 0x000F) |
                                    Qt::AlignTop);
        this->_widget->setLayout(this->_layout);
    }
    MultipleScrollArea &ui::MultipleScrollArea::operator<<(QWidget *panel) {
        panel->setParent(this->_widget);
        this->_layout->addWidget(panel);
        this->setWidget(this->_widget);
        panel->raise();
        return (*this);
    }
    QWidget *MultipleScrollArea::operator[](const int index) const {
        if (this->_widget->children().size() > (index + 1))
            return qobject_cast<QWidget *>(
                this->_widget->children()[index + 1]);
        else
            return nullptr;
    }
    int MultipleScrollArea::children_size() const {
        return this->_widget->children().size() - 1;
    }
    void MultipleScrollArea::clear() {
        // I can't stand this implementation, but I don't know how to ignore
        // _layout in this->_widget->children() other than this...
        for (QObject *child : this->_widget->children()) {
            if (child == this->_layout) continue;
            this->_layout->removeWidget(qobject_cast<QWidget *>(child));
            child->setParent(nullptr);
            child->deleteLater();
        }
    }
}
