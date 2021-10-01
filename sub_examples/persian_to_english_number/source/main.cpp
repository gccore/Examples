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
#include <QVBoxLayout>
#include <QLineEdit>
#include <QDialog>
#include <QDebug>

inline QChar constexpr pctoe(QChar const pchar)
{
	std::array<QChar, 20> constexpr p =
	{
		QChar(L'\u06F0'), QChar(L'\u06F1'),
		QChar(L'\u06F2'), QChar(L'\u06F3'),
		QChar(L'\u06F4'), QChar(L'\u06F5'),
		QChar(L'\u06F6'), QChar(L'\u06F7'),
		QChar(L'\u06F8'), QChar(L'\u06F9'),
		'0', '1', '2', '3',
		'4', '5', '6', '7',
		'8', '9'
	};
	for (std::size_t i = 0; i < 10; ++i)
	{
		if (p[i] == pchar)
		{
			return p[i + 10];
		}
	}
	return pchar;
}

inline QString pstrtoe(QString pstr)
{
	std::transform(pstr.begin(), pstr.end(), pstr.begin(), pctoe);
	return pstr;
}

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	QLineEdit lineedit;
	QLineEdit lineedit2;
	QVBoxLayout layout;
	layout.addWidget(&lineedit);
	layout.addWidget(&lineedit2);
	QObject::connect(&lineedit, &QLineEdit::textChanged,
			 &app, [&](QString const & text)
	{
		lineedit2.setText(pstrtoe(text));
	});

	QDialog main_widget;
	main_widget.setLayout(&layout);
	main_widget.exec();

	return app.exec();
}
