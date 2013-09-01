#pragma once
#include <QString>
namespace storage{
    class property_storage;
}
namespace default_value{
    class setting_default;
}
namespace loader{
    class setting_loader{
        public:
            setting_loader(const QString &file,const int element_size=10,const QString &objName=QString());
            ~setting_loader();
            storage::property_storage &storage() const;
            QString filePath() const;
            bool read();
            bool write();
        private:
            storage::property_storage *_storage;
            QString _file;
            default_value::setting_default *_default;
    };
}
