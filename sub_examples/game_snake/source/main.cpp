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

namespace core
{
namespace color
{
auto constexpr kGreen = "\033[42m";
auto constexpr kBlack = "\033[40m";
auto constexpr kBlue = "\033[0;94m";
auto constexpr kRed = "\033[41m";
auto constexpr kNul = "\033[0m";
} // namespace color

auto constexpr kRowLength = 16ULL;
auto constexpr kColumnLength = kRowLength + kRowLength;

template<typename T, std::size_t Length>
using TileArray = std::array<T, Length>;
using Matrix = TileArray<TileArray<std::size_t, kColumnLength>, kRowLength>;

enum class InitState
{
	kInitialized,
	kUninitialized
};
} // namespace core

namespace map
{
auto constexpr kEntitySymbol = 'X';
auto constexpr kMaxInitSleepSec = 10ULL;

auto GetEntitySymbol()
{
	using namespace core::color;
	return std::string(kBlue) + kEntitySymbol + kNul;
}

struct Tile
{
	static auto constexpr kDefaultSymbol = ' ';

	static auto getDefaultSymbol()
	{
		using namespace core::color;
		return std::string(kBlack) + kDefaultSymbol + kNul;
	}

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
		return init_state_ == core::InitState::kInitialized;
	}

protected:
	auto getState() const
	{
		return init_state_;
	}
	void setState(core::InitState const state)
	{
		init_state_ = state;
	}
	void generateRandomPoint()
	{
		row = std::rand() % core::kRowLength;
		column = std::rand() % core::kColumnLength;
	}

private:
	core::InitState init_state_ = core::InitState::kUninitialized;
};

class BadTile final : public SpecialTile
{
public:
	void generatePoint() override
	{
		setState(core::InitState::kInitialized);
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
		setState(core::InitState::kInitialized);
		generateRandomPoint();
	}
	char getSymbol() const override
	{
		return 'E';
	}
};

static BadTile badTile;
static ExitTile exitTile;

auto GetBadTileChar()
{
	std::string result;
	result = Tile::getDefaultSymbol();

	if(badTile.isInitialized())
	{
		result = core::color::kRed;
		result += badTile.getSymbol();
		result += core::color::kNul;
	}

	return result;
}
auto GetExitTileChar()
{
	std::string result;
	result = Tile::getDefaultSymbol();

	if(exitTile.isInitialized())
	{
		result = core::color::kGreen;
		result += exitTile.getSymbol();
		result += core::color::kNul;
	}

	return result;
}

} // namespace map

namespace utility
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
void MoveCurrentPosition(map::Tile& pos)
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
		if(pos.row < core::kRowLength - 1)
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
		if(pos.column < core::kColumnLength - 1)
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
void PrintMap(core::Matrix const& map_mat, map::Tile const& pos)
{
	ClearConsoleScreen();
	for(std::size_t i = 0; i < map_mat.size(); ++i)
	{
		for(std::size_t j = 0; j < map_mat[i].size(); ++j)
		{
			auto const point = map::Tile{i, j};
			if(point == pos)
			{
				std::cout << map::GetEntitySymbol();
			}
			else if(map::exitTile == point)
			{
				std::cout << map::GetExitTileChar();
			}
			else if(map::badTile == point)
			{
				std::cout << map::GetBadTileChar();
			}
			else
			{
				std::cout << map::Tile::getDefaultSymbol();
			}
		}
		std::cout << std::endl;
	}
}
} // namespace utility

int main()
{
	core::Matrix map = {{{0ULL}}};
	map::Tile current_pos = {0ULL, 0ULL};
	std::size_t steps = 0ULL;

	std::srand(std::time(nullptr));
	auto const init_time = std::time(nullptr);
	auto const time_for_bad_tile_init =
		std::time_t(std::rand() % map::kMaxInitSleepSec);
	auto const time_for_exit_tile_init =
		std::time_t(std::rand() % map::kMaxInitSleepSec);

	do
	{
		if(!map::badTile.isInitialized() || !map::exitTile.isInitialized())
		{
			auto const current_time = std::time(nullptr);
			if(!map::badTile.isInitialized() &&
			   (init_time + time_for_bad_tile_init) < current_time)
			{
				map::badTile.generatePoint();
			}
			if(!map::exitTile.isInitialized() &&
			   (init_time + time_for_exit_tile_init) < current_time)
			{
				map::exitTile.generatePoint();
			}
		}

		steps += 1ULL;
		utility::MoveCurrentPosition(current_pos);
		utility::PrintMap(map, current_pos);

		std::this_thread::sleep_for(100ms);
	} while(((!map::exitTile.isInitialized() || !map::badTile.isInitialized())) ||
			((current_pos != map::exitTile) && (current_pos != map::badTile)));

	std::cout << std::endl;
	if(current_pos == map::exitTile)
	{
		std::cout << "You Win After: " << steps << " Steps." << std::endl;
	}
	else if(current_pos == map::badTile)
	{
		std::cout << "You Died After: " << steps << " Steps." << std::endl;
	}

	return EXIT_SUCCESS;
}
