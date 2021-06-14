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
#include <vector>
#include <map>

namespace core {
enum class token_t {
  ope, num, var
};
struct token_pair_t final {
  std::string string;
  token_t token;
};
using token_list_t = std::vector<token_pair_t>;

static token_list_t tokenizer(std::string const& string) {
  token_list_t result;
  for (std::size_t i = 0; i < string.size(); ++i) {
    char const c = string[i];
    token_pair_t t;

    if ((c >= '0') && (c <= '9')) {
      for (; i < string.size(); ++i) {
        if ((string[i] >= '0') && (string[i] <= '9')) {
          t.string += string[i];
        } else { break; }
      } --i;
      t.token = token_t::num;
    } else if (((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z'))) {
      t.string = c; t.token = token_t::var;
    } else {
      switch (c) {
        case '+':
        case '-':
        case '*':
        case '/':
          t.string = c; t.token = token_t::ope;
      }
    }

    result.push_back(t);
  }
  return result;
}
} // namespace core

namespace calculator {
using vars_t = std::map<std::string, std::string>;

static double result_of(std::string const& formula, vars_t const& variables) {
  auto tokens = core::tokenizer(formula);

check_for_var:
  for (std::size_t i = 0; i < tokens.size(); ++i) {
    auto& token = tokens[i];

    if (token.token == core::token_t::var) {
      token.string = variables.at(token.string);
      token.token = core::token_t::num;
      tokens.insert(tokens.begin() + i, core::token_pair_t{"*", core::token_t::ope});
      goto check_for_var;
    }
  }

check_for_mul_div:
  for (std::size_t i = 0; i < tokens.size(); ++i) {
    auto const token = tokens[i];

    if ((token.token == core::token_t::ope) && (token.string == "*" || token.string == "/")) {
      auto& prev = tokens[i - 1];
      auto next = tokens[i + 1];

      if (prev.token == core::token_t::var) { prev.string = variables.at(prev.string); }
      if (next.token == core::token_t::var) { next.string = variables.at(next.string); }

      if (token.string == "*")
      { prev.string = std::to_string(std::stod(prev.string) * std::stod(next.string)); }
      else if (token.string == "/")
      { prev.string = std::to_string(std::stod(prev.string) / std::stod(next.string)); }
      prev.token = core::token_t::num;

      tokens.erase(tokens.begin() + i + 1);
      tokens.erase(tokens.begin() + i);

      goto check_for_mul_div;
    }
  }

check_for_sum_sub:
  for (std::size_t i = 0; i < tokens.size(); ++i) {
    auto const token = tokens[i];

    if ((token.token == core::token_t::ope) && ((token.string == "-") || (token.string == "+"))) {
      auto& prev = tokens[i - 1];
      auto next = tokens[i + 1];

      if (prev.token == core::token_t::var) { prev.string = variables.at(prev.string); }
      if (next.token == core::token_t::var) { next.string = variables.at(next.string); }

      if (token.string == "+")
      { prev.string = std::to_string(std::stod(prev.string) + std::stod(next.string)); }
      else if (token.string == "-")
      { prev.string = std::to_string(std::stod(prev.string) - std::stod(next.string)); }
      prev.token = core::token_t::num;

      tokens.erase(tokens.begin() + i + 1);
      tokens.erase(tokens.begin() + i);

      goto check_for_sum_sub;
    }
  }

  return tokens.size() == 1 ? std::stod(tokens[0].string) : -1;
}
} // namespace calculator


int main() {
  auto const aa = calculator::result_of("2x*9", {{"x", "2"}});
  std::cout << aa << std::endl;
}
