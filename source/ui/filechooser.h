#pragma once
#include <QtWidgets/QWidget>
#include <QFileInfo>
class QLineEdit;
class QPushButton;
namespace ui{
    class FileChooser:public QWidget{
            Q_OBJECT
            Q_PROPERTY(QString filter READ filter WRITE setFilter)
            Q_PROPERTY(ChooseMode mode READ mode WRITE setMode)
            Q_PROPERTY(QFileInfo fileInfo READ fileinfo)
        public:
            enum ChooseMode{File,Dir};
            FileChooser(const QString &objName=QString(),QWidget *parent=nullptr);
            FileChooser(const QFileInfo &file_path=QFileInfo(),const ChooseMode mode=FileChooser::File,const QString &objName=QString(),QWidget *parent=nullptr);
            QFileInfo fileinfo() const;
            ChooseMode mode() const;
            QString filter() const;
        signals:
            void filePathChanged(const QFileInfo &previous,const QFileInfo &now,bool &cancel);
        public slots:
            void setMode(const ChooseMode mode);
            void setFilter(const QString &filter);
            void setPath(const QString &path);
        private slots:
            void _refbutton_clicked();
        private:
            QLineEdit *_filepath;
            QPushButton *_refbutton;
            QFileInfo _info;
            ChooseMode _mode;
            QString _filter;
    };
}
