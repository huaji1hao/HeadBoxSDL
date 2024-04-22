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
    Graph(Scyjz14TileManager* tm) {
        this->tm = tm;
        getData();
        
    }

    char data[127][127] = { 0 };

    // Directly adjacent neighbors (4-directional)
    std::vector<Point> directions = {
        {1, 0}, {-1, 0}, {0, 1}, {0, -1}
    };

    // Diagonal neighbors
    std::vector<Point> diagonals = {
        {1, 1}, {1, -1}, {-1, 1}, {-1, -1}
    };

    bool isPassable(Point point) const;

    std::vector<Point> getNeighbors(Point point) const;

    double cost(Point from, Point to) const;

    void getData();

private:
    Scyjz14TileManager* tm = nullptr;
};


class AStar
{
public:
    // Function to reconstruct the path from the came_from map
    std::vector<Point> reconstruct_path(Point start, Point goal, std::unordered_map<Point, Point> came_from);

    /*
      A* algorithm adaptation. 
      During initialization, 
      only nodes that are both neighbors of startLeft and startRight 
      will be added to the search queue.
    */
    std::pair<int, int> a_star_search(Graph& graph, Point start, Point startLeft, Point startRight, Point goal);

};

