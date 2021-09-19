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

#include <iostream>

#include <QQmlApplicationEngine>
#include <QGuiApplication>
#include <QQmlContext>
#include <QQuickItem>
#include <QDebug>

struct test_item : QQuickItem
{
	void f()
	{
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	}
};

class controller : public QObject
{
	Q_OBJECT
    public slots:
	Q_INVOKABLE void setup_test(test_item* item)
	{
		item->f();
	}
};
#include "main.moc"

int main(int argc, char* argv[])
{
	QGuiApplication app(argc, argv);
	QQmlApplicationEngine engine;
	controller c;
	qmlRegisterType<test_item>("qml.pass.id", 1, 0, "TestItem");

	auto const find_test_item = [&](QObject*, QUrl const&) {
		auto const root = engine.rootObjects();
		if(!root.empty())
		{
			auto const obj = root.first()->findChild<test_item*>("testItem");
			if(obj)
			{
				c.setup_test(obj);
			}
			else
			{
				qDebug() << "Couldn't Cast";
			}
		}
		else
		{
			qDebug() << "Empty";
		}
	};
	QObject::connect(&engine, &QQmlApplicationEngine::objectCreated, &app, find_test_item);
	engine.load("qrc:/qml_pass_objectName_example/main.qml");

	return app.exec();
}
