#include "content_base.h"
namespace plugin {
    QObject *content_base::this_object() { return this; }
    const QString &content_base::description() const { return this->_desc; }
    void content_base::setDescription(const QString &desc) {
        this->_desc = desc;
    }
    const QUuid &content_base::identifier() const { return this->_id; }
    void content_base::setIdentifier(const QUuid &id) { this->_id = id; }
    const QString &content_base::title() const { return this->_title; }
    void content_base::setTitle(const QString &title) { this->_title = title; }
    const QString &content_base::author() const { return this->_author; }
    void content_base::setAuthor(const QString &author) {
        this->_author = author;
    }
}
