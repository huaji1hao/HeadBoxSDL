#include "header.h"
#include "AStar.h"

bool Graph::isPassable(Point point) const {
    // Check if the location at point is passable or not
    // If the point is out of bounds, return false
    if (point.x < 0 || point.x >= tm->getMapWidth() || point.y < 0 || point.y >= tm->getMapHeight()) {
        return false;
    }

    // Otherwise, return true if the tile is passable
    return data[point.y][point.x] == '0';
}

std::vector<Point> Graph::getNeighbors(Point point) const {
    std::vector<Point> neighbors;

    for (const auto& dir : directions) {
        Point newPoint = { point.x + dir.x, point.y + dir.y };
        if (isPassable(newPoint)) {
            neighbors.push_back(newPoint);

        }
    }

    for (const auto& diag : diagonals) {
        Point newPoint = { point.x + diag.x, point.y + diag.y };
        Point side1 = { point.x + diag.x, point.y };
        Point side2 = { point.x, point.y + diag.y };

        // Add diagonal neighbor only if both adjacent sides are passable (no wall)
        if (isPassable(newPoint) && isPassable(side1) && isPassable(side2)) {
            neighbors.push_back(newPoint);
        }
    }

    return neighbors;
}

double Graph::cost(Point from, Point to) const {
    // The cost from one point to another, use Euclidean distance
    return heuristic(from, to);

}

void Graph::getData() {
    for (int y = 0; y < tm->getMapHeight(); y++)
        for (int x = 0; x < tm->getMapWidth(); x++) {
            data[y][x] = tm->getMapValue(x, y) + '0';
        }
}

std::vector<Point> AStar::reconstruct_path(Point start, Point goal, std::unordered_map<Point, Point> came_from) {
    std::vector<Point> path;
    Point current = goal;

    // If there is no available path
    if (!came_from.count(current)) {
        return path;
    }

    // else reconstruct the path
    while (current != start) {
        path.push_back(current);
        current = came_from[current];
    }
    path.push_back(start); // optional
    std::reverse(path.begin(), path.end());
    return path;
}

std::pair<int, int> AStar::a_star_search(Graph& graph, Point start, Point startLeft, Point startRight, Point goal) {
    std::priority_queue<Node> frontier;
    std::unordered_map<Point, Point> came_from;
    std::unordered_map<Point, double> cost_so_far;

    // Add unique neighbors to the frontier if passable
    auto addIfPassable = [&](const Point& neighbor, Point startLR) {
        if (graph.isPassable(neighbor)) {
            came_from[neighbor] = start; // Start is the same for left and right in this context
            cost_so_far[neighbor] = graph.cost(startLR, neighbor);
            double priority = cost_so_far[neighbor] + heuristic(neighbor, goal);
            frontier.push(Node{ neighbor, priority });
        }
    };

    // Left unique neighbor
    addIfPassable({ startLeft.x - 1, startLeft.y }, startLeft);
    // Right unique neighbor
    addIfPassable({ startRight.x + 1, startRight.y }, startRight);

    // Add common neighbors to the priority queue
    for (auto& nLeft : graph.getNeighbors(startLeft)) {
        for (auto& nRight : graph.getNeighbors(startRight)) {
            if (nLeft == nRight) {
                addIfPassable(nLeft, start);
            }
        }
    }

    // Continue with the A* algorithm
    while (!frontier.empty()) {
        Point current = frontier.top().point;
        frontier.pop();

        if (current == goal) break; // Goal reached, stop search

        for (Point next : graph.getNeighbors(current)) {
            if (!graph.isPassable(next)) continue; // Skip impassable

            double new_cost = cost_so_far[current] + graph.cost(current, next);
            if (!cost_so_far.count(next) || new_cost < cost_so_far[next]) {
                cost_so_far[next] = new_cost;
                double priority = new_cost + heuristic(next, goal);
                frontier.push(Node{ next, priority });
                came_from[next] = current;
            }
        }
    }

    // Reconstruct the path and find the next step
    std::vector<Point> path = reconstruct_path(start, goal, came_from);
    if (path.size() > 1) {
        Point next_step = path[1];
        return std::make_pair(next_step.x - start.x, next_step.y - start.y); // Return movement vector
    }

    return std::make_pair(0, 0); // No valid path found, no movement
}
