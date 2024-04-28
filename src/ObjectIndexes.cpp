#include "header.h"
#include "ObjectIndexes.h"

// Define the static variables
std::unique_ptr<std::vector<int>> ObjectIndexes::zombieIndexes;
std::unique_ptr<std::vector<int>> ObjectIndexes::playerIndexes;

const std::vector<int>& ObjectIndexes::getZombieIndexes() {
    return *zombieIndexes;
}

const std::vector<int>& ObjectIndexes::getPlayerIndexes() {
    return *playerIndexes;
}

void ObjectIndexes::initialize() {
    zombieIndexes = std::make_unique<std::vector<int>>();
    playerIndexes = std::make_unique<std::vector<int>>();
}

void ObjectIndexes::cleanup() {
    zombieIndexes.reset();
    playerIndexes.reset();
}


void ObjectIndexes::addZombieIndex(int index) {
    zombieIndexes->push_back(index);
}


void ObjectIndexes::removeZombieIndex(int index) {
    for (auto it = zombieIndexes->begin(); it != zombieIndexes->end(); ++it) {
        if (*it == index) {
            zombieIndexes->erase(it);
            break;
        }
    }
}

int ObjectIndexes::countZombies() {
    return zombieIndexes->size();
}


void ObjectIndexes::addPlayerIndex(int index) {
    playerIndexes->push_back(index);
}