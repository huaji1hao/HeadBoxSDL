#include "header.h"
#include "Zombie.h"
#include "AStar.h"
#include "ObjectIndexes.h"
#include "UtilCollisionDetection.h"


void Zombie::virtDoUpdate(int iCurrentTime) {
	updateAnimationFrame(iCurrentTime);
	fixPosition();
}

void Zombie::updateAnimationFrame(int iCurrentTime){
	// Calculate the time elapsed since the last frame update
	int iElapsedTime = iCurrentTime - m_iLastUpdateTime;

	// Check if it is time to update the frame
	if (iElapsedTime >= m_iTimeBetweenFrames) {
		// Update the frame index
		m_iCurrentFrameX = (m_iCurrentFrameX + 1) % getFrameCount();
		// Reset the last update time
		m_iLastUpdateTime = iCurrentTime;

		attackPlayer();
	}
}

void Zombie::updateDirection(int dx, int dy) {
	// Normalize dx and dy to -1, 0, or 1
	int normDx = (dx > 0) - (dx < 0);
	int normDy = (dy > 0) - (dy < 0);

	for (const auto& dirVec : directionVectors) {
		if (dirVec.dx == normDx && dirVec.dy == normDy) {
			m_direction = dirVec.dir;
			break;
		}
	}
}

void Zombie::updateDirectionTowardsPlayer(Player* player) {
	if (player == nullptr || m_pTileManager == nullptr) return;

	//// Calculate direction vector from zombie to player
	//int dx = player->getXCentre() - this->getXCentre();
	//int dy = player->getYCentre() - this->getYCentre();

	//// Normalize the direction vector
	//double length = std::sqrt(dx * dx + dy * dy);
	//double dirX = dx / length;
	//double dirY = dy / length;

	//// Make sure the smallest step is 1 pixel for either x or y by rounding
	//int stepX = static_cast<int>((dirX > 0) ? std::ceil(dirX) : std::floor(dirX));
	//int stepY = static_cast<int>((dirY > 0) ? std::ceil(dirY) : std::floor(dirY));

	//// Ensure there's at least 1 pixel movement in any direction
	//if (stepX == 0 && stepY == 0) {
	//	stepX = (dirX > 0) ? 1 : -1;
	//	stepY = (dirY > 0) ? 1 : -1;
	//}

	//// Apply the calculated step, ensuring at least 1 pixel movement
	//m_iCurrentScreenX += stepX * moving_speed;
	//m_iCurrentScreenY += stepY * moving_speed;

	//// Update the direction of the zombie based on movement
	//updateDirection(stepX, stepY);
	Point zombiePos = {getXCentre(), getYCentre() };
	Point playerPos = {player->getXCentre(), player->getYCentre() };

	Point zombieMapPos = { 
		m_pTileManager->getMapXForScreenX(getXCentre()),
		m_pTileManager->getMapYForScreenY(getYCentre()) };
	Point playerMapPos = { 
		m_pTileManager->getMapXForScreenX(player->getXCentre()),
		m_pTileManager->getMapYForScreenY(player->getYCentre()) };

	Graph graph(m_pTileManager);
	AStar astar;
	std::pair<int, int> step = astar.a_star_search(graph, zombieMapPos, playerMapPos);

	// Now apply the step to your zombie's position
	m_iCurrentScreenX += step.first * moving_speed;
	m_iCurrentScreenY += step.second * moving_speed;

	updateDirection(step.first, step.second);

}

void Zombie::attackPlayer() {
	for (auto& playerid : ObjectIndexes::getPlayerIndexes()) {
		// Get the player object
		Player* player = dynamic_cast<Player*>(getEngine()->getDisplayableObject(playerid));
		if (player == nullptr) return;

		updateDirectionTowardsPlayer(player);

		// Check if the zombie is colliding with the player
		if (CollisionDetection::checkRectangles(getDrawingRegionLeft(), getDrawingRegionRight(),
			getDrawingRegionTop(), getDrawingRegionBottom(),
			player->getDrawingRegionLeft(), player->getDrawingRegionRight(),
			player->getDrawingRegionTop(), player->getDrawingRegionBottom())) 
		{
			// If the zombie is colliding with the player, knock the player away
			player->knockedAway(getXCentre(), getYCentre());
		}
	}
}

void Zombie::fixPosition() {
	AgentBaseObject::fixPosition();

	// check overlapping between zombies
	for (auto& i : ObjectIndexes::getZombieIndexes()) {
		DisplayableObject* pObject = m_pEngine->getDisplayableObject(i);
		Zombie* pOtherZombie = dynamic_cast<Zombie*>(pObject);

		if (pOtherZombie && pOtherZombie != this) {
			// check whether this zombie is overlapping with the other
			if (CollisionDetection::checkRectangles(
				getDrawingRegionLeft(), getDrawingRegionRight(),
				getDrawingRegionTop(), getDrawingRegionBottom(),
				pOtherZombie->getDrawingRegionLeft(), pOtherZombie->getDrawingRegionRight(),
				pOtherZombie->getDrawingRegionTop(), pOtherZombie->getDrawingRegionBottom())) {
				// if overlapping, then roll back
				m_iCurrentScreenX = m_iPrevScreenX;
				m_iCurrentScreenY = m_iPrevScreenY;
				break; // if roll back, then return
			}
		}
	}
}