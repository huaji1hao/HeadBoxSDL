#include "header.h"
#include "State.h"
#include "Scyjz14Engine.h"
#include "ObjectIndexes.h"
#include "Zombie.h"

void State::copyAllBackgroundBuffer() {
	m_pEngine->BaseEngine::copyAllBackgroundBuffer(); 
};

int State::getLevelIdentifier() {
	return -1; 
}

inline int countAppearedZombies(Scyjz14Engine *m_pEngine) {
    int zbNum = 0;
    for (auto& id : ObjectIndexes::getZombieIndexes()) {
        Zombie* zb = dynamic_cast<Zombie*>(m_pEngine->getDisplayableObject(id));
        if (zb && (zb->isVisible() || zb->isDied())) zbNum++;
    }
    return zbNum;
}

void State::saveGameState(const std::string& filename, int LevelIdentifier) {
    std::ofstream outFile(filename);
    if (!outFile) {
        std::cerr << "Unable to open file for saving game state." << std::endl;
        return;
    }

    outFile << LevelIdentifier << " " << m_pEngine->getScore() << " " << countAppearedZombies(m_pEngine) << std::endl;

    // Save player state
    auto playerIndex = ObjectIndexes::getPlayerIndexes()[0];
    Player* player = dynamic_cast<Player*>(m_pEngine->getDisplayableObject(playerIndex));
    if (player) {
        outFile << "Player " << player->getDrawingRegionLeft() << " " << player->getDrawingRegionTop() << " " << player->getLifeValue() << std::endl;
    }

    // Save each zombie's state
    for (auto& id : ObjectIndexes::getZombieIndexes()) {
        Zombie* zb = dynamic_cast<Zombie*>(m_pEngine->getDisplayableObject(id));
        if (zb && (zb->isVisible() || zb->isDied())) {
            outFile << "Zombie " << zb->getDrawingRegionLeft() << " " << zb->getDrawingRegionTop() << " " << zb->getLifeValue() << std::endl;
        }
    }

    outFile.close();
}

int State::determineLevelFromSaveFile(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "Unable to open file to load game state." << std::endl;
        return -1;
    }

    int level, score;
    inFile >> level >> score;
    inFile.close();

    return level;
}

void State::loadGameState(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "Unable to open file to load game state." << std::endl;
        return;
    }

    int level, score, zbNum;
    inFile >> level >> score >> zbNum;

    m_pEngine->clearScore();
    m_pEngine->increaseScore(score);

    std::string type;
    int x, y, life;

    inFile >> type >> x >> y >> life;
    if (type == "Player") {
        // Assuming you have a method to set player's state
        Player* player = dynamic_cast<Player*>(m_pEngine->getDisplayableObject(ObjectIndexes::getPlayerIndexes()[0]));
        if (player) {
            player->setPosition(x, y);
            player->setLifeValue(life);
        }
    }

    int totalZbNum = ObjectIndexes::countZombies();

    for (int i = 0; i < zbNum; ++i) {
        inFile >> type >> x >> y >> life;
        if (type == "Zombie") {
            int zbIndex = i <= level - 1 ? i + 1 : totalZbNum - zbNum + i + 1;
            Zombie* zb = dynamic_cast<Zombie*>(m_pEngine->getDisplayableObject(zbIndex));
            zb->setRevealingTime(0);
            zb->setPosition(x, y);
            if (i <= level - 1)zb->setBoss(true);
            zb->setLifeValue(life);
            if (zb->isDied()) {
                zb->checkIsLive();
                zb->drawBody();
            }
        }
    }


    inFile.close();
}