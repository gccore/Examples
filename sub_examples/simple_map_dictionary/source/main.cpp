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
 * g1999raemzani@gmail.com
 */

#include <string_view>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

using namespace std::string_literals;

namespace core {
struct word_t final {
  using vec = std::vector<word_t>;

  std::string in;
  std::string out;

  bool match(std::string_view const string) const {
    return in == string;
  }

  friend word_t operator>>(std::istream& input, word_t output) {
    input >> output.in >> output.out;
    return output;
  }
};
} // namespace core

class dictionary final {
 private:
  core::word_t::vec words_;

 public:
  std::string translator(std::string const& word) const {
    for (auto const& i : words_) {
      if (i.match(word)) {
        return i.out;
      }
    }
    return {};
  }

  std::string translator(std::vector<std::string> const& words) const {
    std::string result;
    for (auto const& i : words) {
      auto const translate = translator(i);
      result += translate.empty() ? std::string() : translate + " ";
    }
    return result;
  }

  friend void operator>>(std::istream& input, dictionary& output) {
    output.words_.push_back(input >> core::word_t());
  }
};

int main() {
  std::size_t n = 0;
  std::cin >> n;

  dictionary dic;
  for (std::size_t i = 0; i < n; ++i) {
    std::cin >> dic;
  }

  std::cout << dic.translator("ghasem") << std::endl;
  std::cout << dic.translator({"ghasem"s, "ramezani"s}) << std::endl;
}
