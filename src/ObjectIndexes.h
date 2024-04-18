#pragma once
#include <vector>
#include <initializer_list>

class ObjectIndexes {
public:
    // get the zombie indexes as a const reference
    static const std::vector<int>& getZombieIndexes() {
        return *zombieIndexes;
    }
    // get the player indexes as a const reference
    static const std::vector<int>& getPlayerIndexes() {
        return *playerIndexes;
    }

    // initialize the vectors
    static void initialize() {
        zombieIndexes = std::make_unique<std::vector<int>>();
        playerIndexes = std::make_unique<std::vector<int>>();
    }

    // reset the vectors
    static void cleanup() {
        zombieIndexes.reset();
        playerIndexes.reset();
    }

    // add indexes to the zombie vector
    static void addZombieIndex(int index) {
        zombieIndexes->push_back(index);
    }

    //remove indexes from the zombie vector
    static void removeZombieIndex(int index) {
        for (auto it = zombieIndexes->begin(); it != zombieIndexes->end(); ++it) {
            if (*it == index) {
                zombieIndexes->erase(it);
                break;
            }
        }
    }

    // conut the number of zombies
    static int countZombies() {
        return zombieIndexes->size();
    }

    // add indexes to the player vector
    static void addPlayerIndex(int index) {
        playerIndexes->push_back(index);
    }


private:
    // use unique_ptr to avoid memory leaks
    // use static to avoid multiple instances
    // Here are two vectors to store indexes of zombies and players
    static std::unique_ptr<std::vector<int>> zombieIndexes;
    static std::unique_ptr<std::vector<int>> playerIndexes;
};
