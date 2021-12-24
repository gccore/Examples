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

enum class InitState
{
	kInitialized,
	kUninitialized
};
} // namespace Core

namespace Map
{
auto constexpr kEntitySymbol = 'X';
auto constexpr kMaxInitSleepSec = 10ULL;

struct Tile
{
	static auto constexpr kDefaultSymbol = '0';

	std::size_t row = 0;
	std::size_t column = 0;

	inline bool operator==(Tile const other) const
	{
		return (row == other.row) && (column == other.column);
	}
	inline bool operator!=(Tile const other) const
	{
		return (row != other.row) || (column != other.column);
	}
};

class SpecialTile : public Tile
{
public:
	virtual void generatePoint() = 0;
	virtual char getSymbol() const = 0;

	bool isInitialized() const
	{
		return init_state_ == Core::InitState::kInitialized;
	}

protected:
	auto getState() const
	{
		return init_state_;
	}
	void setState(Core::InitState const state)
	{
		init_state_ = state;
	}
	void generateRandomPoint()
	{
		row = std::rand() % Core::kRowLength;
		column = std::rand() % Core::kColumnLength;
	}

private:
	Core::InitState init_state_ = Core::InitState::kUninitialized;
};

class BadTile final : public SpecialTile
{
public:
	void generatePoint() override
	{
		setState(Core::InitState::kInitialized);
		generateRandomPoint();
	}
	char getSymbol() const override
	{
		return 'B';
	}
};
class ExitTile final : public SpecialTile
{
public:
	void generatePoint() override
	{
		setState(Core::InitState::kInitialized);
		generateRandomPoint();
	}
	char getSymbol() const override
	{
		return 'E';
	}
};

BadTile badTile;
ExitTile exitTile;
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
				std::cout << Map::kEntitySymbol << ' ';
			}
			else if(Map::exitTile == point)
			{
				std::cout << (Map::exitTile.isInitialized() ? Map::exitTile.getSymbol() :
																Map::Tile::kDefaultSymbol)
						  << ' ';
			}
			else if(Map::badTile == point)
			{
				std::cout << (Map::badTile.isInitialized() ? Map::badTile.getSymbol() :
															   Map::Tile::kDefaultSymbol)
						  << ' ';
			}
			else
			{
				std::cout << Map::Tile::kDefaultSymbol << ' ';
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
	auto const init_time = std::time(nullptr);
	auto const time_for_bad_tile_init = std::time_t(std::rand() % Map::kMaxInitSleepSec);
	auto const time_for_exit_tile_init = std::time_t(std::rand() % Map::kMaxInitSleepSec);

	do
	{
		if(!Map::badTile.isInitialized() || !Map::exitTile.isInitialized())
		{
			auto const current_time = std::time(nullptr);
			if(!Map::badTile.isInitialized() &&
			   (init_time + time_for_bad_tile_init) < current_time)
			{
				Map::badTile.generatePoint();
			}
			if(!Map::exitTile.isInitialized() &&
			   (init_time + time_for_exit_tile_init) < current_time)
			{
				Map::exitTile.generatePoint();
			}
		}

		steps += 1ULL;
		Utility::MoveCurrentPosition(current_pos);
		Utility::PrintMap(map, current_pos);

		std::this_thread::sleep_for(100ms);
	} while(((!Map::exitTile.isInitialized() || !Map::badTile.isInitialized())) ||
			((current_pos != Map::exitTile) && (current_pos != Map::badTile)));

	std::cout << std::endl;
	if(current_pos == Map::exitTile)
	{
		std::cout << "You Win After: " << steps << " Steps." << std::endl;
	}
	else if(current_pos == Map::badTile)
	{
		std::cout << "You Died After: " << steps << " Steps." << std::endl;
	}

	return EXIT_SUCCESS;
}
