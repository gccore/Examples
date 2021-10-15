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

#include <algorithm>
#include <iostream>
#include <string>

enum class direction_right { };
enum class direction_left { };

template <typename Container>
void shift(Container& data, std::size_t ratio, direction_right)
{
	for (; ratio != 0; --ratio)
	{
		auto const last_value = data[data.size() - 1];
		data.erase(std::remove(data.begin(), data.end(), last_value));
		data.insert(data.begin(), last_value);
	}
}
template <typename Container>
void shift(Container& data, std::size_t ratio, direction_left)
{
	for (; ratio != 0; --ratio)
	{
		auto const first_value = *data.begin();
		data.erase(std::remove(data.begin(), data.end(), first_value));
		data.insert(data.end(), first_value);
	}
}

int main()
{
	std::string string = "hello";
	shift(string, 2, direction_left());
	std::cout << string << std::endl;

	std::vector<std::string> strings = {"_1", "_2", "_3"};
	shift(strings, 2, direction_right());
	for (auto const& item : strings)
	{
		std::cout << item << ", ";
	}
	std::cout << std::endl;
}
