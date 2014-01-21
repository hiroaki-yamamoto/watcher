#pragma once

#include <QMultiHash>
#include <QVariant>
#include <QList>
class serializer;
class QString;
namespace storage{
    //Recoverable key-value storage
    class property_storage:public QObject{
            Q_OBJECT
            Q_PROPERTY(int ElementSize READ elementSize WRITE setElementSize)
        public:
            property_storage(const int element_size=10,const QString &objName=QString(),QObject *parent=nullptr);
            /*
             * Copies entire elements.
             * Unlike differencial_copy described below, this constructor copies the "entire" elements in other.
             */
            property_storage(const property_storage &other,const int element_size=10,const QString &objName=QString(),QObject *parent=nullptr);
            friend serializer& operator<<(serializer &out,const property_storage &data);
            friend serializer& operator>>(serializer &in,property_storage &data);
            virtual bool readOnly();
            QVariant operator[](const QString &key) const;
            //Take differencial set by operandB.
            property_storage operator-(const property_storage &operandB) const;
            //Substitute operator
            property_storage &operator=(const property_storage &operandB);
            //Take differencial set and substitute in lhs.
            property_storage &operator-=(const property_storage &operandB);
            
            //Existing union must be natural if differencial operator exists...
            property_storage operator+(const property_storage &operandB) const;
            property_storage operator+=(const property_storage &operandB);
            const int &elementSize() const;
        public slots:
            void set(const QString &key,const QVariant &value);
            QVariant get(const QString &key) const;
            bool exists(const QString &key) const;
            void undo(const QString &key);
            void undo();
            bool unset(const QString &key);
            void clear();
            //Copies the most recently registerd element in setting if the key doesn't exist.
            void differencial_copy(const property_storage &setting);
            void copy(const QString &key, const QVariantList &values);
            void setElementSize(const int size);
            void dump();
        signals:
            void propertyChanged(const QString &key,const QVariant &previous,const QVariant &now);
            void propertyRemoved(const QString &key);
            void propertyCleared();
        protected:
            QMultiHash<QString,QVariant> __data;
        protected slots:
            /* Removes values in the specified key until the number of the values equals to _element_size.
             * Note that the values are removed in the chronological order.
             *
             * Moreover, this function is called automatically when set member funciton in this class is called.
             * (i.e. it is NOT always called when the number of elements in __data is changed)
             */
            virtual void shrink(const QString &key);
        private:
            int _element_size;
    };
    serializer& operator<<(serializer &out,const property_storage &data);
    serializer& operator>>(serializer &in,property_storage &data);
}
serializer& operator<<(serializer &out,const QVariant &data);
serializer& operator>>(serializer &in,QVariant &data);
