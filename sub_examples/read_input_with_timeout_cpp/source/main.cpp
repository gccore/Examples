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
#include <atomic>
#include <string>
#include <thread>
#include <chrono>

struct input_value_t {
        char value;
        std::atomic_bool read_flag;
};

void read_input_function(input_value_t& value)
{
        value.value = std::cin.get();
        value.read_flag = true;
}

auto elapsed_time_from(std::chrono::steady_clock::time_point const& start)
{
        using namespace std::chrono;
        return duration_cast<seconds>(steady_clock::now() - start).count();
}

int main()
{
        auto constexpr time_limit_s = 2;
        input_value_t value = {' ', false};

        auto const start_time = std::chrono::steady_clock::now();
        std::thread read_input_thread(read_input_function, std::ref(value));

        while (!value.read_flag && elapsed_time_from(start_time) < time_limit_s) {
                std::this_thread::yield();
        }

        if (!value.read_flag) {
                std::cout <<  "Timeout" << std::endl;
        } else {
                std::cout <<  "Your value: " << value.value << std::endl;
        }

        read_input_thread.detach();
}

