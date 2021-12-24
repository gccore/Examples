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
#include <cstdlib>
#include <string>
#include <thread>
#include <chrono>
#include <ctime>
#include <array>

using namespace std::chrono_literals;

namespace Core
{
auto constexpr kRowLength = 10ULL;
auto constexpr kColumnLength = kRowLength;

template<typename T, std::size_t Length>
using TileArray = std::array<T, Length>;
using Matrix = TileArray<TileArray<std::size_t, kColumnLength>, kRowLength>;
} // namespace Core

namespace Map
{
struct Tile final
{
	std::size_t row = 0;
	std::size_t column = 0;

	inline bool operator==(Tile const& other) const
	{
		return (row == other.row) && (column == other.column);
	}
	inline bool operator!=(Tile const& other) const
	{
		return (row != other.row) || (column != other.column);
	}
};
auto constexpr kExitTile = Tile{0ULL, 9ULL};
auto constexpr kBadTile = Tile{9ULL, 9ULL};
} // namespace Map

namespace Utility
{
enum class Direction
{
	Up,
	Down,
	Left,
	Right
};
auto GetRandomPosition()
{
	return static_cast<Direction>(std::rand() % 4);
}
void MoveCurrentPosition(Map::Tile& pos)
{
	switch(GetRandomPosition())
	{
	case Direction::Up:
		if(pos.row > 0ULL)
		{
			pos.row -= 1;
		}
		break;
	case Direction::Down:
		if(pos.row < Core::kRowLength - 1)
		{
			pos.row += 1;
		}
		break;
	case Direction::Left:
		if(pos.column > 0ULL)
		{
			pos.column -= 1;
		}
		break;
	case Direction::Right:
		if(pos.column < Core::kColumnLength - 1)
		{
			pos.column += 1;
		}
		break;
	}
}
void ClearConsoleScreen()
{
#if defined _WIN32
	std::system("cls");
#elif defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
	std::system("clear");
#elif defined(__APPLE__)
	std::system("clear");
#endif
}
void PrintMap(Core::Matrix const& map, Map::Tile const& pos)
{
	ClearConsoleScreen();
	for(std::size_t i = 0; i < map.size(); ++i)
	{
		for(std::size_t j = 0; j < map[i].size(); ++j)
		{
			auto const point = Map::Tile{i, j};
			if(point == pos)
			{
				std::cout << "X ";
			}
			else if(Map::kExitTile == point)
			{
				std::cout << "E ";
			}
			else if(Map::kBadTile == point)
			{
				std::cout << "B ";
			}
			else
			{
				std::cout << "0 ";
			}
		}
		std::cout << std::endl;
	}
}
} // namespace Utility

int main()
{
	Core::Matrix map = {{{0ULL}}};
	Map::Tile current_pos = {0ULL, 0ULL};
	std::size_t steps = 0ULL;

	std::srand(std::time(nullptr));
	do
	{
		steps += 1ULL;
		Utility::MoveCurrentPosition(current_pos);
		Utility::PrintMap(map, current_pos);

		std::this_thread::sleep_for(100ms);
	} while((current_pos != Map::kExitTile) && (current_pos != Map::kBadTile));

	std::cout << std::endl;
	if(current_pos == Map::kExitTile)
	{
		std::cout << "You Win After: " << steps << " Steps." << std::endl;
	}
	else if(current_pos == Map::kBadTile)
	{
		std::cout << "You Died After: " << steps << " Steps." << std::endl;
	}

	return EXIT_SUCCESS;
}
