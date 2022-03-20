#include "plot/plot_plugin.h"

#include "qcustomplot.h"

#include <QSharedPointer>
#include <QColor>
#include <QTimer>
#include <QPen>

namespace core::plugins::plot {
QPointer<QWidget> Plot::init_plugin() {
  widget_ = new QCustomPlot;

  widget_->setMinimumSize(QSize(300, 300));

  widget_->addGraph();
  widget_->graph(0)->setPen(QPen(QColor(40, 110, 255)));
  QSharedPointer<QCPAxisTickerTime> time_ticker(new QCPAxisTickerTime);
  time_ticker->setTimeFormat("%h:%m:%s");
  widget_->xAxis->setTicker(time_ticker);
  widget_->axisRect()->setupFullAxesBox();
  widget_->yAxis->setRange(-1.2, 1.2);

  QObject::connect(widget_->xAxis, qOverload<QCPRange const &>(&QCPAxis::rangeChanged),
                   widget_->xAxis2, qOverload<QCPRange const &>(&QCPAxis::setRange));
  QObject::connect(widget_->yAxis, qOverload<QCPRange const &>(&QCPAxis::rangeChanged),
                   widget_->yAxis2, qOverload<QCPRange const &>(&QCPAxis::setRange));

  static QTimer timer;
  QObject::connect(&timer, &QTimer::timeout, this, [this] {
    static QTime time(QTime::currentTime());
    // calculate two new data points:
    double key = time.elapsed() / 1000.0;  // time elapsed since start of demo, in seconds
    static double lastPointKey = 0;
    if (key - lastPointKey > 0.002)  // at most add point every 2 ms
    {
      // add data to lines:
      auto const y = qSin(key) + qrand() / (double)RAND_MAX * 1 * qSin(key / 0.3843);
      widget_->graph(0)->addData(key, y);
      Q_EMIT new_data(QPointF(key, y));
      // rescale value (vertical) axis to fit the current data:
      //widget_->graph(0)->rescaleValueAxis();
      //widget_->graph(1)->rescaleValueAxis(true);
      lastPointKey = key;
    }
    // make key axis range scroll with the data (at a constant range size of 8):
    widget_->xAxis->setRange(key, 8, Qt::AlignRight);
    widget_->replot();
  });
  timer.start(0);

  return qobject_cast<QWidget *>(widget_);
}
QString Plot::get_plugin_name() const {
  return "Plot";
}
}  // namespace core::plugins::plot
