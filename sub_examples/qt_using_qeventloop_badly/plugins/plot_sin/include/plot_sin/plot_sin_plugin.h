#ifndef CORE_PLUGINS_PLOT_SIN_PLUGIN_H
#define CORE_PLUGINS_PLOT_SIN_PLUGIN_H

#include "core_interface/core_interface.h"
#include "core_common_things/result.h"

#include <QEventLoop>
#include <QPointer>
#include <QThread>
#include <QPointF>
#include <QWidget>

namespace core::plugins::plot_sin {
class PlotSin final : public interface::Plugin {
  Q_OBJECT
  Q_PLUGIN_METADATA(IID CORE_PLUGINS_INTERFACE FILE "meta.json")
  Q_INTERFACES(core::plugins::interface::Plugin)

public:
  QPointer<QWidget> init_plugin() override;
  QString get_plugin_name() const override;

private:
  Q_SLOT void on_recived_plugin(Result<interface::Plugin*> const& plugin) override;
  Q_SIGNAL void on_value_updated(QPointF const& value);

  QPointer<QWidget> widget_;
  QPointer<QThread> thread_;
};
}  // namespace core::plugins::plot_sin

#endif  // CORE_PLUGINS_PLOT_SIN_PLUGIN_H
