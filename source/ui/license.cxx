#include <QString>
#include <QtWidgets/QApplication>
const QString short_license(){
    return (
            "<p>Commit version:"+qApp->applicationVersion()+"<br />"
            "Author :Hiroaki Yamamoto"
            "(<a href=\"mailto:admin @ hysoftware.net\">Mail</a> <a href=\'http://hysoftware.net'>Web site</a>)"
            "</p>"
            "<p>License:"
            "<table>"
            "<tr><td>libloader</td><td %1>LGPL3</td></tr>"
            "<tr><td>libstorage</td><td %1>GPL3</td></tr>"
            "<tr><td>libwatcher_ui</td><td %1>GPL3</td></tr>"
            "<tr><td>liblogging</td><td %1>GPL3</td></tr>"
            "<tr><td>Watcher Executable</td><td %1>GPL3</td></tr>"
            "</table>"
            "</p>"
            "<p>This program is free software: you can redistribute it and/or modify "
            "it under the terms of the GNU General Public License as published by "
            "the Free Software Foundation, either version 3 of the License, or "
            "(at your option) any later version.</p>"
            "<p>This program is distributed in the hope that it will be useful, "
            "but WITHOUT ANY WARRANTY; without even the implied warranty of "
            "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the "
            "GNU General Public License for more details.</p>"
            "<p>You should have received a copy of the GNU General Public License "
            "along with this program.  If not, see <a href='http://www.gnu.org/licenses/'> here </a>.</p>"
            );
}
