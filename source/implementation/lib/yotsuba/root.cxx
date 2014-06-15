#include <QObject>
#include <QVector>
#include <QIcon>

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkDiskCache>

#include <array>

// The version is the same version of watcher
#include <version>

#include "category.h"
#include "root.h"
namespace yotsuba {
    root::root() {
        this->_ver = ::version;
        std::random_device rd;
        std::array<quint32, 4> randomnumbers;
        for (quint32 &randomnumber : randomnumbers) randomnumber = rd();
        std::seed_seq seq(randomnumbers.begin(), randomnumbers.end());
        this->_mt = new std::mt19937(seq);
        this->setDescription(tr("A 4chan plugin for watcher."));
        this->setAuthor("Hiroaki Yamamoto");
        this->setTitle(tr("Yotsuba"));
        this->setIdentifier("a4522fb3-d22d-4fe0-8d1e-8d072410a64b");
        this->_accessManager = new QNetworkAccessManager(this);
        // TODO: The file path must be specified by user.
        this->_cache = new QNetworkDiskCache(this);
        this->_cache->setCacheDirectory("/tmp/watcher/yotsuba/cache");
        this->_accessManager->setCache(this->_cache);
    }
    root::~root() { delete this->_mt; }

    bool root::enable_option() const { return false; }
    const QString &root::version() const { return this->_ver; }
    const QIcon &root::icon() const { return this->_icon; }
    const quint32 root::random_number() { return (*this->_mt)(); }
    void root::get_categories() {
        QVector<plugin::category *> category_list;
        int random_number;
        yotsuba::category *ws_board = new yotsuba::category(
                              this->_mt, this->_accessManager, this),
                          *wus_board = new yotsuba::category(
                              this->_mt, this->_accessManager, this);
        random_number = this->random_number();
        ws_board->setTitle(tr("Safe Boards for Work"));
        ws_board->setDescription(
            tr("They are safe boards when you watch them at working time."));
        ws_board->setIdentifier(QUuid::createUuidV5(
            this->identifier(),
            QByteArray((char *)&random_number, sizeof(random_number))));
        random_number = this->random_number();
        wus_board->setTitle(tr("Unsafe Boards for Work"));
        wus_board->setDescription(
            tr("BE CAREFUL; You'll be FIRED when you watch these boards at "
               "working time."));
        wus_board->setIdentifier(QUuid::createUuidV5(
            this->identifier(),
            QByteArray((char *)&random_number, sizeof(random_number))));
        ws_board->setWorkSafe(true);
        wus_board->setWorkSafe(false);
        category_list << ws_board << wus_board;
        emit this->get_categories_finished(category_list);
    }
}
