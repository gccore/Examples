#include "plot_sin/plot_sin_plugin.h"

#include "plot/plot_plugin.h"

#include <QVBoxLayout>
#include <QDebug>
#include <QLabel>

#include <cassert>
#include <cmath>

namespace core::plugins::plot_sin {
QPointer<QWidget> PlotSin::init_plugin() {
  auto* const x_sin_label = new QLabel("X Sin: ");
  auto* const x_sin_value_label = new QLabel;
  auto* const y_sin_label = new QLabel("Y Sin: ");
  auto* const y_sin_value_label = new QLabel;
  auto* const x_layout = new QHBoxLayout;
  auto* const y_layout = new QHBoxLayout;
  x_layout->addWidget(x_sin_label);
  x_layout->addWidget(x_sin_value_label);
  y_layout->addWidget(y_sin_label);
  y_layout->addWidget(y_sin_value_label);
  auto* const main_layout = new QVBoxLayout;
  main_layout->addLayout(x_layout);
  main_layout->addLayout(y_layout);
  widget_ = new QWidget;
  widget_->setLayout(main_layout);
  widget_->setMinimumSize(QSize(200, 100));
  Q_EMIT request_for_plugin("Plot");
  connect(this, &PlotSin::on_value_updated, this, [=](QPointF const& data) {
    x_sin_value_label->setText(QString::number(std::sin(data.x())));
    y_sin_value_label->setText(QString::number(std::sin(data.y())));
  });
  return widget_;
}
QString PlotSin::get_plugin_name() const {
  return "PlotSin";
}

void PlotSin::on_recived_plugin(Result<interface::Plugin*> const& plugin) {
  if (plugin) {
    auto* const plot = dynamic_cast<plot::Plot*>(plugin.data);
    assert(nullptr != plot);
    connect(plot, &plot::Plot::new_data, this, &PlotSin::on_value_updated);
  } else {
    qDebug() << "Failed To Request Plot Plugin: " << plugin.message;
  }
}
}  // namespace core::plugins::plot_sin
