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

#include <boost/lockfree/queue.hpp>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <thread>
#include <vector>

#define SLEEP()                               \
  auto const sleep_time = std::rand() % 1000; \
  std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));

boost::lockfree::queue<int> queue(10'000'000);

void producer() {
  while (true) {
    while (not queue.push(std::rand()))
      ;
    SLEEP()
  }
}

void consumer() {
  while (true) {
    int data = -1;
    while (queue.pop(data))
      ;
    std::cout << __PRETTY_FUNCTION__ << " " << data << std::endl;
    SLEEP()
  }
}

int main() {
  std::vector<std::thread> threads;
  for (std::size_t i = 0; i <= std::thread::hardware_concurrency(); ++i) {
    threads.emplace_back(producer);
  }

  std::thread(consumer).join();
}
