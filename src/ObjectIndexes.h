#pragma once
#include <vector>
#include <initializer_list>

class ObjectIndexes {
public:
    // get the zombie indexes as a const reference
    static const std::vector<int>& getZombieIndexes();
    // get the player indexes as a const reference
    static const std::vector<int>& getPlayerIndexes();

    // initialize the vectors
    static void initialize();

    // reset the vectors
    static void cleanup();

    // add indexes to the zombie vector
    static void addZombieIndex(int index);

    //remove indexes from the zombie vector
    static void removeZombieIndex(int index);

    // conut the number of zombies
    static int countZombies();

    // add indexes to the player vector
    static void addPlayerIndex(int index);

private:
    // use unique_ptr to avoid memory leaks
    // use static to avoid multiple instances
    // Here are two vectors to store indexes of zombies and players
    static std::unique_ptr<std::vector<int>> zombieIndexes;
    static std::unique_ptr<std::vector<int>> playerIndexes;
};
