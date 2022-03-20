/*
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * @another_ghasem
 * g1999ramezani@gmail.com
 */

#include "core_interface/core_interface.h"

#include <QPluginLoader>
#include <QApplication>
#include <QPointer>
#include <QWidget>
#include <QDebug>
#include <QDir>

#include <map>

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);

  std::map<QString, core::plugins::interface::Plugin*> plugins;

  auto plugins_dir = QDir(QCoreApplication::applicationDirPath());
  plugins_dir.cd("plugins");
  for (auto const& dir_name : plugins_dir.entryList(QDir::Dirs)) {
    auto plugin_dir = QDir(plugins_dir.path() + QDir::separator() + dir_name);
    for (auto const& file_name : plugin_dir.entryList(QDir::Files)) {
      if (QLibrary::isLibrary(file_name)) {
        auto* const loader = new QPluginLoader(plugin_dir.absoluteFilePath(file_name), &app);
        auto* const object = qobject_cast<core::plugins::interface::Plugin*>(loader->instance());
        plugins[object->get_plugin_name()] = object;
        QObject::connect(object, &core::plugins::interface::Plugin::request_for_plugin, &app,
                         [&plugins, object](QString const& name) {
                           auto const plugin = plugins.find(name);
                           if (plugin != plugins.end()) {
                             core::Result<core::plugins::interface::Plugin*> result;
                             result.data = plugin->second;
                             result.state = true;
                             object->on_recived_plugin(result);
                           }
                         });

        if (nullptr != object) {
          auto const widget = object->init_plugin();
          if (nullptr != widget) {
            widget->show();
          }
        } else {
          qDebug() << loader->errorString();
        }
      }
    }
  }

  return app.exec();
}
