#include "header.h"
#include "LeaderBoardState.h"
#include "Button.h"
#include "Scyjz14Engine.h"
#include "Scyjz14Image.h"
#include "Scyjz14ImageManager.h"
#include <sstream>
#include <vector>

void LeaderBoardState::loadScores() {
	std::ifstream inFile("resources/Score/leaderboard.txt");
	std::string line;

	if (inFile) {
		while (std::getline(inFile, line)) {
			std::istringstream iss(line);
			std::string name;
			int score;
			std::getline(iss, name, '\t'); // Use tab as delimiter
			iss >> score;
			scores.push_back({ name, score });
		}
		inFile.close();

		// Sort the scores in descending order
		std::sort(scores.begin(), scores.end());
	}
	else {
		std::cerr << "Failed to open scores file." << std::endl;
	}
}

void LeaderBoardState::virtSetupBackgroundBuffer() {
	Scyjz14Image background = Scyjz14ImageManager::loadImage("resources/background/menu_background.png", true);

	DrawingSurface* surface = m_pEngine->getBackgroundSurface();
	background.renderImageWithAlpha(surface, 150, 0, 0, 0, 720, 560);

}

void LeaderBoardState::virtDrawStringsUnderneath() {
	int titleY = 50; // Y position for the title
	int startY = 94; // Initial Y position for the first score

	int offsetXName = 120; // X position for the name
	int offsetXScore = 560; // Fixed X position for the score, adjusted to align right
	int gapY = 45; // Vertical gap between each score
	Font* font = m_pEngine->getFont("resources/Arial_Rounded_Bold.ttf", 24);

	// Draw titles above the score entries
	m_pEngine->drawBackgroundString(offsetXName + 10, titleY, "Player Name", 0x000000, font);
	m_pEngine->drawBackgroundString(offsetXScore, titleY, "Score", 0x000000, font);

	for (int i = 0; i < std::min(int(scores.size()), 10); i++) {
		// Draw the rank and name
		char bufName[100];
		sprintf(bufName, "%2d. %s", i + 1, scores[i].name.c_str());
		m_pEngine->drawBackgroundString(offsetXName, startY + i * gapY, bufName, 0x000000, font);

		// Draw the score separately to ensure it aligns right
		char bufScore[24];
		sprintf(bufScore, "%d", scores[i].score);
		m_pEngine->drawBackgroundString(offsetXScore, startY + i * gapY, bufScore, 0x000000, font);
	}
}


void LeaderBoardState::initialiseStateObject() {
	m_pEngine->notifyObjectsAboutMouse(true);
	m_pEngine->drawableObjectsChanged();

	m_pEngine->lockAndSetupBackground();

	// Create array with default size for one object
	m_pEngine->createObjectArray(5);
	Button* button1 = new Button(90, 10, m_pEngine, "resources/UI/GO_BACK_GREY.png");
	button1->useTopCentreFor00();
	button1->setEnterImage("resources/UI/GO_BACK_BLACK.png");

	m_pEngine->storeObjectInArray(0, button1);
}

void LeaderBoardState::virtMouseUp(int iButton, int iX, int iY) {
	Button* backButton = dynamic_cast<Button*> (m_pEngine->getDisplayableObject(0));
	if (backButton->isInClickArea()) {
		m_pEngine->setState(std::make_shared<StartUpState>(m_pEngine));
	}
}

LeaderBoardState::~LeaderBoardState() {
	m_pEngine->destroyOldObjects(true);
	m_pEngine->clearContents();
}