#include "header.h"
#include "Zombie.h"
#include "AStar.h"
#include "ObjectIndexes.h"
#include "UtilCollisionDetection.h"
#include "Scyjz14CollisionDetection.h"

void Zombie::drawBody() {
	Scyjz14Image body = Scyjz14ImageManager::loadImage("resources/game/zombie_die/zombie_died_with_blood.png", true);

	DrawingSurface* surface = m_pEngine->getBackgroundSurface();

	Direction bodyDir = m_direction;
	if (bodyDir == UPLEFT) bodyDir = UP;
	else if (bodyDir == UPRIGHT) bodyDir = RIGHT;
	else if (bodyDir == DOWNLEFT) bodyDir = DOWN;
	else if (bodyDir == DOWNRIGHT) bodyDir = LEFT;

	m_pEngine->lockBackgroundForDrawing();
	int bottomY = getDrawingRegionBottom();
	if (!m_pTileManager->isPassableByObjectCentre(getXCentre(), bottomY, widthOffset)) {
		// Draw the image covered by the wall
		body.renderImageWithAlphaAndOverlay(surface,
			bodyDir * getDrawWidth(), 0,
			getDrawingRegionLeft(),
			getDrawingRegionTop(),
			m_iDrawWidth, m_iDrawHeight, 0xEBDCC7);
	}
	else {
		// Draw the current frame with transparency
		body.renderImageWithAlpha(surface,
			bodyDir * getDrawWidth(), 0,
			getDrawingRegionLeft(),
			getDrawingRegionTop(),
			m_iDrawWidth, m_iDrawHeight);
	}

	m_pEngine->unlockBackgroundForDrawing();
}

void Zombie::virtDoUpdate(int iCurrentTime) {
	checkIsLife();
	if (isDied()) return;
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

	Point zombieMapPos = {
		m_pTileManager->getMapXForScreenX(getXCentre()),
		m_pTileManager->getMapYForScreenY(getYCentre()) };
	Point zombieMapPosLeft = { 
		m_pTileManager->getMapXForScreenX(getXCentre() - widthOffset),
		m_pTileManager->getMapYForScreenY(getYCentre()) };
	Point zombieMapPosRight = {
		m_pTileManager->getMapXForScreenX(getXCentre() + widthOffset),
		m_pTileManager->getMapYForScreenY(getYCentre()) };

	Point playerMapPos = { 
		m_pTileManager->getMapXForScreenX(player->getXCentre()),
		m_pTileManager->getMapYForScreenY(player->getYCentre()) };

	Graph graph(m_pTileManager);
	AStar astar;
	std::pair<int, int> step = astar.a_star_search(graph, zombieMapPos, zombieMapPosLeft, zombieMapPosRight, playerMapPos);

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
		if (Scyjz14CollisionDetection::checkPixelWithOffset(3, getImage(), m_iCurrentFrameX * m_iDrawWidth, m_direction * m_iDrawHeight, m_iDrawWidth, m_iDrawHeight, getDrawingRegionLeft(), getDrawingRegionTop(), 
		player->getImage(), player->getCurrentFrameX() * player->getDrawWidth(), player->getDirection() * player->getDrawHeight(), player->getDrawWidth(), player->getDrawHeight(), player->getDrawingRegionLeft(), player->getDrawingRegionTop()))
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