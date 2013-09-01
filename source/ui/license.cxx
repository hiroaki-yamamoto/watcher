#include <QString>
#include <QtWidgets/QApplication>
const QString short_license(){
    return
            "<p>Commit version:"+qApp->applicationVersion()+"<br />"
            "Author :Hiroaki Yamamoto"
            "(<a href=\"mailto:admin @ hysoftware.net\">Mail</a> <a href=\'http://hysoftware.net'>Web site</a>)<br />"
            "License:Core Software:GPL3, libloader.so:LGPL3 \n\n</p>"
            "<p>This program is free software: you can redistribute it and/or modify "
            "it under the terms of the GNU General Public License as published by "
            "the Free Software Foundation, either version 3 of the License, or "
            "(at your option) any later version.</p>"
            "<p>This program is distributed in the hope that it will be useful, "
            "but WITHOUT ANY WARRANTY; without even the implied warranty of "
            "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the "
            "GNU General Public License for more details.\n\n"
            "You should have received a copy of the GNU General Public License "
            "along with this program.  If not, see <a href='http://www.gnu.org/licenses/'> here </a>.</p>";
}
