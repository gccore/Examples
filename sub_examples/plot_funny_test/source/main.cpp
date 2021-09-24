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
	return x * x;
}

int main(int argc, char* argv[])
{
	QApplication application(argc, argv);
	QCustomPlot plot;
	plot.setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iMultiSelect |
			     QCP::iSelectPlottables | QCP::iSelectAxes | QCP::iSelectLegend |
			     QCP::iSelectItems | QCP::iSelectOther |
			     QCP::iSelectPlottablesBeyondAxisRect);
	plot.legend->setVisible(true);
	plot.addGraph();
	QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
	timeTicker->setTimeFormat("%h:%m:%s");
	plot.xAxis->setTicker(timeTicker);
	plot.axisRect()->setupFullAxesBox();
	for(double i = -1000; i < 1000; ++i)
	{
		plot.graph()->addData(i, get_y(i));
	}
	plot.rescaleAxes();
	plot.replot(QCustomPlot::rpQueuedReplot);
	plot.show();
	return application.exec();
}
