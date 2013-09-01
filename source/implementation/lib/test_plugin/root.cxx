#include "root.h"
#include "category.h"
#include <QVector>
#include <array>

namespace test{
    root::root(QObject *parent):plugin::root(parent){
        std::random_device rd;
        std::array<unsigned int,8> numbers;
        for(unsigned int &number:numbers) number=rd();
        std::seed_seq sq(numbers.begin(),numbers.end());
        this->_mt=new std::mt19937(sq);
        this->setDescription(tr("Test Plugin for Core Developer."));
        this->setTitle(tr("Test Plugin"));
        this->setAuthor("Hiroaki Yamamoto");
        this->setIdentifier("7f4a04b3-9827-4782-8e38-142831fcba0a");
    }
    root::~root(){delete this->_mt;}

    void root::get_categories(){
        QVector<plugin::category *> categories;
        for(qint32 i=1;i<129;i++){
            unsigned int random_number=(*this->_mt)();
            categories<<new test::category(
                        this->_mt,
                        QString("Category Test:")+QString::number(i),
                        QUuid::createUuidV5(this->identifier(),QByteArray((const char *)&random_number,sizeof(random_number))),this
                        );
        }
        emit this->get_categories_finished(categories);
    }
    bool root::enable_option() const{return false;}
    const QString &root::version() const{return this->_ver;}
    const QIcon &root::icon() const{return this->_icon;}
}
