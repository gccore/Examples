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

#include <QCoreApplication>
#include <QTimer>
#include <QDebug>

class increment_loop : public QObject
{
	Q_OBJECT

private:
	int counter = 0;
	int const max;

public:
	increment_loop(int const limit = 1000)
		: max(limit)
	{
		connect(this, &increment_loop::increment, this, &increment_loop::on_increment);
	}
	~increment_loop()
	{
		qDebug() << "Counter: " << counter;
	}

public slots:
	void on_increment(int const ratio)
	{
		if ((counter + ratio) < max)
		{
			counter += ratio;
			emit increment(ratio);
		}
	}

signals:
	void increment(int const ratio);

};
#include "main.moc"

int main(int argc, char* argv[])
{
	QCoreApplication a(argc, argv);
	increment_loop obj;
	emit obj.increment(100);
	QTimer::singleShot(1000, &a, [] {QCoreApplication::exit();});
	return a.exec();
}
