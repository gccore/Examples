#ifndef CORE_PLUGINS_PLOT_PLUGIN_H
#define CORE_PLUGINS_PLOT_PLUGIN_H

#include "core_interface/core_interface.h"

#include <QPointer>
#include <QString>
#include <QWidget>
#include <QPointF>

class QCustomPlot;

namespace core::plugins::plot {
class Plot final : public interface::Plugin {
  Q_OBJECT
  Q_PLUGIN_METADATA(IID CORE_PLUGINS_INTERFACE FILE "meta.json")
  Q_INTERFACES(core::plugins::interface::Plugin)

public:
  QPointer<QWidget> init_plugin() override;
  QString get_plugin_name() const override;

  Q_SIGNAL void new_data(QPointF const &data);

private:
  QPointer<QCustomPlot> widget_;
};
}  // namespace core::plugins::plot

#endif  // CORE_PLUGINS_PLOT_PLUGIN_H
