#ifndef CORE_PLUGINS_INTERFACE_H
#define CORE_PLUGINS_INTERFACE_H

#include "core_common_things/result.h"

#include <QPointer>
#include <QVariant>
#include <QObject>
#include <QWidget>
#include <QString>

namespace core::plugins::interface {
class Plugin {
public:
  virtual QPointer<QWidget> init_plugin() {
    return nullptr;
  }

  virtual QString get_plugin_name() const = 0;

  Q_SIGNAL void request_for_plugin(QString const& plugin_name);
  Q_SLOT virtual void on_recived_plugin(Result<QPointer<Plugin>> const& plugin) {
    Q_UNUSED(plugin);
  }
};
}  // namespace core::plugins::interface

#define CORE_PLUGINS_INTERFACE "core.plugins.interface.plugin"
Q_DECLARE_INTERFACE(core::plugins::interface::Plugin, CORE_PLUGINS_INTERFACE)

#endif  // CORE_PLUGINS_INTERFACE_H
