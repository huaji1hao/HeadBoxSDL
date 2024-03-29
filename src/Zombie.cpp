#include "header.h"
#include "Zombie.h"
#include "ObjectIndexes.h"
#include "UtilCollisionDetection.h"


void Zombie::virtDoUpdate(int iCurrentTime) {
	levyFlight();
	attackPlayer();
	fixPosition();
}

void Zombie::virtDraw() {
	Scyjz14ImageObject::virtDraw();
	// If there is a label then draw the text
	if ((m_szLabel != NULL) && (strlen(m_szLabel) > 0))
	{
		getEngine()->drawForegroundString(getXCentre() + m_iXLabelOffset, getYCentre() + m_iYLabelOffset, m_szLabel, 0xffffff);
	}
}

void Zombie::levyFlight() {
	double alpha = 1.5; 
	double u = ((double)rand() / RAND_MAX) * M_PI / 2; 
	double v = ((double)rand() / RAND_MAX) * 10 + 1; 
	double step = sin(alpha * u) / pow(cos(u), 1 / alpha) * pow(cos((1 - alpha) * u) / v, (1 - alpha) / alpha);

	// A constant to scale the step size
	double k = 1.2;
	double stepSize = step * k;
	double angle = (double)(rand() % 360) * M_PI / 180.0;

	m_iCurrentScreenX += (int)(stepSize * cos(angle));
	m_iCurrentScreenY += (int)(stepSize * sin(angle));
}

void Zombie::attackPlayer() {
	for (auto& playerid : ObjectIndexes::getPlayerIndexes()) {
		// Get the player object
		Player* player = dynamic_cast<Player*>(getEngine()->getDisplayableObject(playerid));
		if (player == nullptr) return;
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

void Zombie::setLabel(char* label, int xOffset, int yOffset) {
	m_szLabel = label;
	m_iXLabelOffset = xOffset;
	m_iYLabelOffset = yOffset;
}