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

#include <QRegularExpressionValidator>
#include <QRegularExpression>
#include <QApplication>
#include <QLineEdit>

struct postfix_validator final: QValidator {
  QString const postfix;
  explicit postfix_validator(QString const& postfix_) : postfix(postfix_) {}

  QValidator::State validate(QString& text, int& position) const override {
    if (!text.startsWith(postfix)) {
      text.remove(0, postfix.size());
      text.insert(0, postfix);
      position = postfix.size();
    }
    return QValidator::State::Acceptable;
  }
};

int main(int argc, char* argv[]) {
  QApplication application(argc, argv);
  QLineEdit lineedit;

  constexpr auto postfix = "http://";
  lineedit.setValidator(new postfix_validator(postfix));
  lineedit.setText(postfix);
  lineedit.show();

  return application.exec();
}
