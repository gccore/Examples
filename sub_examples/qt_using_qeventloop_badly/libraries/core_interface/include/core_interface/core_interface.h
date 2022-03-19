#ifndef CORE_PLUGINS_INTERFACE_H
#define CORE_PLUGINS_INTERFACE_H

#include <QPointer>
#include <QVariant>
#include <QObject>
#include <QWidget>
#include <QString>

namespace core::plugins::interface {
class Plugin {
public:
  virtual QPointer<QWidget> init_plugin() = 0;
  virtual QString get_plugin_name() const = 0;

  Q_SIGNAL void plugin_data_available(QVariant const& data);
};
}  // namespace core::plugins::interface

#define CORE_PLUGINS_INTERFACE "core.plugins.interface.plugin"
Q_DECLARE_INTERFACE(core::plugins::interface::Plugin, CORE_PLUGINS_INTERFACE)

#endif  // CORE_PLUGINS_INTERFACE_H
