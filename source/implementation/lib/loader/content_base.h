#pragma once
/*
 * Here is a exception about the license.
 * NOTICE: This code is licensed under the terms of the latest version of
 * LGPLv3. Not GPLv3.
 *                                                                        ~~~~~~
 */
#include <QObject>
#include <QString>
#include <QUuid>

namespace plugin {
    // This class is inherited by category,board,and topic.
    // You need to implement to their pure-virtual function and the pure-virtual
    // function of this class.
    class content_base : public QObject {
        using QObject::QObject;

       public:
        // Name of the content.
        virtual const QString &title() const final;
        // If description doesn't exist, you don't need to implement this
        // function.
        virtual const QString &description() const final;
        virtual QObject *this_object();
        // The UUID of this class will be generated by the constructor of this
        // class. You cannot override this function.
        virtual const QUuid &identifier() const final;
        // Content author.
        virtual const QString &author() const final;

       protected:
        // However, UUID must be provided from root class of each plugin.
        virtual void setIdentifier(const QUuid &id) final;
        virtual void setDescription(const QString &desc) final;
        virtual void setTitle(const QString &name) final;
        virtual void setAuthor(const QString &author) final;

       private:
        QString _title, _desc, _author;
        QUuid _id;
    };
}
