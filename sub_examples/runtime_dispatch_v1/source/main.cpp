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
#include <cassert>

#include <QApplication>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QPushButton>
#include <QWidget>

namespace core
{
struct animal_t
{
	std::string const name;
	explicit animal_t(std::string const& name_)
		: name(name_)
	{
	}
	auto operator()() const
	{
		return name;
	}
};

struct dog_t final : animal_t
{
	using animal_t::animal_t;
};

struct cat_t final : animal_t
{
	using animal_t::animal_t;
};
} // namespace core

/*!
 *
 * Other Programmer(s) interface
 *
 */
template<typename Animal>
auto function(Animal const&)
{
	assert(false);
}

/*!
 *
 * Implementation
 *
 */
template<>
auto function(core::cat_t const& animal)
{
	return animal();
}
template<>
auto function(core::dog_t const& animal)
{
	return animal();
}

/*!
 *
 * End User Interface
 *
 */
void run_ui(int argc, char* argv[])
{
	QApplication application(argc, argv);
	auto const widget = new QWidget;
	auto const layout = new QVBoxLayout;
	auto const button1 = new QPushButton("Cat");
	auto const button2 = new QPushButton("Dog");
	layout->addWidget(button1);
	layout->addWidget(button2);
	QObject::connect(button1, &QPushButton::clicked, &application, [] {
		core::cat_t cat("Some Cat");
		auto const message = QString::fromStdString(function(cat));
		QMessageBox::information(nullptr, " ", message);
	});
	QObject::connect(button2, &QPushButton::clicked, &application, [] {
		core::dog_t dog("Some Dog");
		auto const message = QString::fromStdString(function(dog));
		QMessageBox::information(nullptr, " ", message);
	});
	widget->setLayout(layout);
	widget->show();
	application.exec();
}

int main(int argc, char* argv[])
{
	run_ui(argc, argv);
}
