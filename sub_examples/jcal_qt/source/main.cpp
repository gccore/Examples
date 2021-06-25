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

#include <QCalendarWidget>
#include <QDateTimeEdit>
#include <QApplication>
#include <QVBoxLayout>
#include <QWidget>

int main(int argc, char* argv[]) {
  QApplication application(argc, argv);
  QWidget widget;
  auto const layout = new QVBoxLayout;
  auto const datetime_edit = new QDateTimeEdit;
  auto const calendar_widget = new QCalendarWidget;

  calendar_widget->setCalendar(QCalendar(QCalendar::System::Jalali));
  datetime_edit->setCalendarWidget(calendar_widget);
  datetime_edit->setCalendar(QCalendar(QCalendar::System::Jalali));
  datetime_edit->setDateTime(QDateTime::currentDateTime());
  datetime_edit->setDisplayFormat("yyyy.MM.dd");
  datetime_edit->setAlignment(Qt::AlignCenter);

  QObject::connect(calendar_widget, &QCalendarWidget::clicked, [&](auto const date) {
    datetime_edit->setDate(date);
  });
  QObject::connect(datetime_edit, &QDateTimeEdit::dateChanged, [&](auto const date) {
    calendar_widget->setSelectedDate(date);
  });

  layout->addWidget(calendar_widget);
  layout->addWidget(datetime_edit);
  widget.setLayout(layout);
  widget.show();
  return application.exec();
}
