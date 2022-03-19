#ifndef CORE_PLUGINS_PLOT_PLUGIN_H
#define CORE_PLUGINS_PLOT_PLUGIN_H

#include "core_interface/core_interface.h"

#include <QPointer>
#include <QString>
#include <QWidget>

class QCustomPlot;

namespace core::plugins::plot {
class Plot final : public QObject, public interface::Plugin {
  Q_OBJECT
  Q_PLUGIN_METADATA(IID CORE_PLUGINS_INTERFACE FILE "meta.json")
  Q_INTERFACES(core::plugins::interface::Plugin)

public:
  QPointer<QWidget> init_plugin() override;
  QString get_plugin_name() const override;

private:
  QPointer<QCustomPlot> widget_;
};
}  // namespace core::plugins::plot

#endif  // CORE_PLUGINS_PLOT_PLUGIN_H
