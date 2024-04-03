#pragma once
#include "header.h"
#include <vector>
#include <queue>
#include <unordered_map>
#include <cmath>
#include <limits>
#include "Scyjz14TileManager.h"

// A simple structure to represent a point on the grid
struct Point {

    int x, y;

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Point& other) const {
        return !(*this == other);
    }
};

// Necessary to use Point as key in unordered_map
namespace std {
    template <>
    struct hash<Point> {
        size_t operator()(const Point& point) const {
            return hash<int>()(point.x) ^ hash<int>()(point.y);
        }
    };
}

// Heuristic function: a simple Euclidean distance (you can change to Manhattan if it's only 4 directions allowed)
inline double heuristic(Point a, Point b) {
    return std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2));
}


// A structure to represent a node in the priority queue
struct Node {
    Point point;
    double priority;

    bool operator<(const Node& other) const {
        // In C++, the priority queue is a max heap, so we need to reverse the comparisons
        return priority > other.priority;
    }
};

// A structure to represent the map or graph
class Graph {
public:
    //const char* data[14] = {
    //    // Your map data...
    //};
    Graph(Scyjz14TileManager* tm) {
        getData(tm);
        m_pTileManager = tm;
    }

    char data[25][25] = { 0 };

    // Directly adjacent neighbors (4-directional)
    std::vector<Point> directions = {
        {1, 0}, {-1, 0}, {0, 1}, {0, -1}
    };

    // Diagonal neighbors
    std::vector<Point> diagonals = {
        {1, 1}, {1, -1}, {-1, 1}, {-1, -1}
    };

    int getPointCentreScreenX(Point p) const {
        int tileWidth = m_pTileManager->getTileWidth();
        int x = p.x * tileWidth + tileWidth / 2;
        return x;
    }

    int getPointCentreScreenY(Point p) const{
        int tileHeight = m_pTileManager->getTileHeight();
        int y = p.y * tileHeight + tileHeight / 2;
        return y;
    }

    bool isPassable(Point point) const{
        // Check if the location at point is passable or not
        // If the point is out of bounds, return false
        if(point.x < 0 || point.x >= 24 || point.y < 0 || point.y >= 14) {
            return false;
        }

        /*if (!m_pTileManager->isPassableByObjectCentre(
            getPointCentreScreenX(point), 
            getPointCentreScreenY(point), 15)) {
            return false;

        }*/
        // Otherwise, return true if the tile is passable
        return data[point.y][point.x] == '0';
    }

    std::vector<Point> getNeighbors(Point point) const {
        std::vector<Point> neighbors;

        for (const auto& dir : directions) {
            Point newPoint = { point.x + dir.x, point.y + dir.y };
            if (isPassable(newPoint)) {
                neighbors.push_back(newPoint);
                // For vertical movement, ensure no walls on the sides
                /*if (dir.x == 0) {
                    Point left = { point.x - 1, point.y + dir.y };
                    Point right = { point.x + 1, point.y + dir.y };
                    if (isPassable(left) && isPassable(right)) {
                        neighbors.push_back(newPoint);
                    }
                }
                else {
                    neighbors.push_back(newPoint);
                }*/
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

    double cost(Point from, Point to) const {
        // The cost from one point to another, use Euclidean distance
        return heuristic(from, to);
        
    }

    void getData(Scyjz14TileManager * tm) {
        for (int y = 0; y < 14; y++)
            for (int x = 0; x < 24; x++) {
                data[y][x] = tm->getMapValue(x, y) + '0';
            }
                
    }

private:
    Scyjz14TileManager* m_pTileManager = nullptr;
};


class AStar
{
public:
    // Function to reconstruct the path from the came_from map
    std::vector<Point> reconstruct_path(Point start, Point goal, std::unordered_map<Point, Point> came_from) {
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

    // A* algorithm implementation
    std::pair<int, int> a_star_search(Graph& graph, Point start, Point goal) {
        std::priority_queue<Node> frontier;
        frontier.push(Node{ start, 0 });

        std::unordered_map<Point, Point> came_from;
        std::unordered_map<Point, double> cost_so_far;

        came_from[start] = start;
        cost_so_far[start] = 0;

        while (!frontier.empty()) {
            Point current = frontier.top().point;
            frontier.pop();

            if (current == goal) {
                break;
            }

            for (Point next : graph.getNeighbors(current)) {
                if (!graph.isPassable(next)) continue;

                double new_cost = cost_so_far[current] + graph.cost(current, next);
                if (!cost_so_far.count(next) || new_cost < cost_so_far[next]) {
                    cost_so_far[next] = new_cost;
                    double priority = new_cost + heuristic(next, goal);
                    frontier.push(Node{ next, priority });
                    came_from[next] = current;
                }
            }
        }

        std::vector<Point> path = reconstruct_path(start, goal, came_from);

        // Find next step on the path
        if (path.size() > 1) {
            Point next_step = path[1];
            return std::make_pair(next_step.x - start.x, next_step.y - start.y);
        }
        else {
            return std::make_pair(0, 0);
        }
    }
    

};

