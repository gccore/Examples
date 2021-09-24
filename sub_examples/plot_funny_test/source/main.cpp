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

#include <QApplication>
#include <QTimer>

#include "qcustomplot.h"

double get_y(double const x)
{
	return x * 2 + 1;
}

int main(int argc, char* argv[])
{
	QApplication application(argc, argv);
	QCustomPlot plot;
	plot.setMaximumSize(800, 500);
	plot.setMinimumSize(800, 500);
	plot.legend->setVisible(true);
	plot.addGraph();
	QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
	timeTicker->setTimeFormat("%h:%m:%s");
	plot.xAxis->setTicker(timeTicker);
	plot.axisRect()->setupFullAxesBox();
	QTimer generator;
	QObject::connect(&generator, &QTimer::timeout, &application, [&plot] {
		static auto const begin = QTime::currentTime();
		double x_key = begin.msecsTo(QTime::currentTime());
		plot.graph()->addData(x_key, get_y(x_key));
		auto data = plot.graph()->data();
		if(data->size() > 100)
		{
			data->remove(data->begin()[0].key);
		}
		plot.rescaleAxes();
		plot.replot(QCustomPlot::rpQueuedReplot);
	});
	generator.start(100);
	plot.show();
	return application.exec();
}
