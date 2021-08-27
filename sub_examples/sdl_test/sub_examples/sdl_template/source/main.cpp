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

#include "gc_renderer.h"
#include "gc_screen.h"
#include "gc_game.h"

int main()
{
        core::gc_screen screen("SDL Basics");
        core::gc_renderer renderer(screen);
        core::gc_game game(renderer);

        return core::states::success == game.execute() ? EXIT_SUCCESS : EXIT_FAILURE;
}
