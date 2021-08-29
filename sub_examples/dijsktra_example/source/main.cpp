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
#include <numeric>
#include <limits>
#include <vector>

namespace core
{
std::ostream& operator<<(std::ostream& out, std::vector<std::size_t> const& input)
{
        std::cout << "Vertex \t Distance From Source" << std::endl;
        for (std::size_t i = 0; i < input.size(); ++i) {
                std::cout << i << "\t\t" << input[i] << std::endl;
        }
        return out;
}
} // namespace core

namespace core::algorithm
{
static std::size_t minimum_distance(std::vector<std::size_t> const& distance,
                                    std::vector<bool> const& spt_set)
{
        std::size_t min = std::numeric_limits<std::size_t>::max();
        std::size_t min_index = -1;

        for (std::size_t v = 0; v < distance.size(); v++) {
                if ((false == spt_set[v]) && (min >= distance[v])) {
                        min = distance[v];
                        min_index = v;
                }
        }

        return min_index;
}
} // namespace core::algorithm

namespace core::graph
{
static void dijkstra(std::vector<std::vector<std::size_t>> const& graph,
                     std::size_t const src)
{
        std::vector<std::size_t> dist(graph.size());
        std::vector<bool> sptSet(graph.size());

        for (std::size_t i = 0; i < graph.size(); ++i) {
                dist[i] = std::numeric_limits<std::size_t>::max();
                sptSet[i] = false;
        }

        dist[src] = 0;
        for (std::size_t count = 0; count < graph.size() - 1; ++count) {
                auto const u = algorithm::minimum_distance(dist, sptSet);
                sptSet[u] = true;

                for (std::size_t v = 0; v < graph.size(); ++v) {
                        if (!sptSet[v] && graph[u][v]
                            && dist[u] != std::numeric_limits<int>::max()
                            && (dist[u] + graph[u][v]) < dist[v]) {
                                dist[v] = dist[u] + graph[u][v];
                        }
                }
        }

        std::cout << dist << std::endl;
}
} // namespace core::graph

int main()
{
        std::vector<std::vector<std::size_t>> const graph = {
                { 0, 4, 0, 0, 0, 0, 0, 8, 0 },
                { 4, 0, 8, 0, 0, 0, 0, 11, 0 },
                { 0, 8, 0, 7, 0, 4, 0, 0, 2 },
                { 0, 0, 7, 0, 9, 14, 0, 0, 0 },
                { 0, 0, 0, 9, 0, 10, 0, 0, 0 },
                { 0, 0, 4, 14, 10, 0, 2, 0, 0 },
                { 0, 0, 0, 0, 0, 2, 0, 1, 6 },
                { 8, 11, 0, 0, 0, 0, 1, 0, 7 },
                { 0, 0, 2, 0, 0, 0, 6, 7, 0 }
        };

        core::graph::dijkstra(graph, 0);
}
