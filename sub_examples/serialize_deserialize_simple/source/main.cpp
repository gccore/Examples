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

#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>
#include <deque>

template<typename Container>
void save_to_disk(Container const& container, std::filesystem::path const& path)
{
	std::ofstream output(path);
	if(!output.is_open())
	{
		throw std::runtime_error("Couldn't open file: " + path.string());
	}

	for(auto const& item : container)
	{
		output << item << std::endl;
	}
}

template<typename Container, typename Convertor>
auto read_from_disk(std::filesystem::path const& path, Convertor const conv)
{
	Container result;
	std::ifstream input(path);
	if(!input.is_open())
	{
		throw std::runtime_error("Couldn't open file: " + path.string());
	}

	for(std::string line; std::getline(input, line);)
	{
		result.insert(result.end(), conv(line));
	}

	return result;
}

int main()
{
	std::deque<int> d;
	d.push_back(1);
	d.push_back(2);
	d.push_back(3);
	d.push_back(4);

	save_to_disk(d, "backup");
	auto const d2 = read_from_disk<std::deque<int>>("backup", [](auto const& input) {
		return std::stoi(input);
	});

	for(auto const& item : d2)
	{
		std::cout << item << std::endl;
	}
}
