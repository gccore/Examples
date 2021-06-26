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

#include <QString>
#include <QDebug>
#include <QUuid>
#include <QList>

namespace core {
struct person final {
  using list = QList<core::person>;

  QString name;
  std::uint16_t age;

  person(QString const& name_, std::uint16_t const age_)
    : name(name_), age(age_), m_id(QUuid::createUuid())
  {}
  bool operator==(person const& other_person) const noexcept {
    return (m_id == other_person.m_id) && (name == other_person.name);
  }

 private:
  QUuid m_id;
};
} // namespace core

int main() {
  core::person::list const folks = {
    {"ghasem", 21},
    {"other ghasem", 22},
    {"another ghasem", 23},
    {"someone else", 24},
  };
  auto const another_one = folks[0];

  if (folks.contains(another_one)) {
    qDebug() << "It's work";
  } else {
    qDebug() << "Failed";
  }
}
