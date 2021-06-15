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
#include <cstdlib>
#include <vector>
#include <thread>
#include <ctime>

using namespace std::chrono_literals;

struct base {
  enum type_t {
    rock, paper,
    scissors, unknown
  } type;
  std::string hand_name;

  base(type_t const t, std::string const& name) : type(t), hand_name(name) {}
  friend std::ostream& operator<<(std::ostream& out, base const& other) {
    switch (other.type) {
      case base::rock:
        std::clog << other.hand_name << ": rock";
        break;
      case base::paper:
        std::clog << other.hand_name << ": paper";
        break;
      case base::scissors:
        std::clog << other.hand_name << ": scissors";
        break;
      case base::unknown:
        std::clog << "faild.";
    }
    return out;
  }
};

struct rock final: base {
  rock(std::string const& name)
    : base(base::rock, name) {}
};

struct paper final: base {
  paper(std::string const& name)
    : base(base::paper, name) {}
};

struct scissors final: base {
  scissors(std::string const& name)
    : base(base::scissors, name) {}
};

base play(std::string const& hand_name) {
  auto const round = base::type_t(std::rand() % 3);

  switch (round) {
    case base::rock:
      return rock(hand_name);
    case base::paper:
      return paper(hand_name);
    case base::scissors:
      return scissors(hand_name);
  }

  return base(base::unknown, std::string());
}

base check(base const& player_1, base const& player_2) {
  base result(base::unknown, std::string());

  if (player_1.type != player_2.type) {
    switch (player_1.type) {
      case base::rock:
        result = player_2.type == base::scissors ? player_1 : player_2;
        break;
      case base::paper:
        result = player_2.type == base::rock ? player_1 : player_2;
        break;
      case base::scissors:
        result = player_2.type == base::paper ? player_1 : player_2;
        break;
    }
  }

  return result;
}

template <typename... PlayerList>
void fight(PlayerList const& ... list) {
  std::vector<std::string> namelist = {list ... };

  std::clog << "------------------------" << std::endl;

  auto result = play(namelist.front());
  std::clog << result << std::endl;
  for (std::size_t i = 1; i < namelist.size(); ++i) {
    auto const other = play(namelist[i]);
    std::clog << other << std::endl;
    result = check(result, other);
  }

  std::clog << "Winner: " << result << std::endl;
  std::clog << "------------------------" << std::endl;
}

int main() {
  std::srand(std::time(nullptr));

  while (true) {
    fight("ali", "ghasem", "hamid", "reza");
    std::this_thread::sleep_for(1s);
  }
}
