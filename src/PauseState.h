#pragma once
#include "Scyjz14Engine.h"
#include "State.h"

class PauseState :
    public State
{
public:
    PauseState(Scyjz14Engine* engine, std::shared_ptr<State> rtState) : State(engine),
    returnState(rtState) {
        if (!eg->isPaused()) eg->pause();
    };

    ~PauseState() {}

    void virtKeyDown(int iKeyCode) override;

    void virtDrawStringsUnderneath() override;

	void PauseState::virtMouseWheel(int x, int y, int which, int timestamp) {
		// We grab the position of the centre of the screen before the zoom
		int iOldCentreX = eg->convertClickedToVirtualPixelXPosition(eg->getWindowWidth() / 2);
		int iOldCentreY = eg->convertClickedToVirtualPixelYPosition(eg->getWindowHeight() / 2);

		if (y < 0)
			eg->getFilterPointScaling()->compress();
		else if (y > 0)
			eg->getFilterPointScaling()->stretch();

		// Now we grab the position after the zoom
		int iNewCentreX = eg->convertClickedToVirtualPixelXPosition(eg->getWindowWidth() / 2);
		int iNewCentreY = eg->convertClickedToVirtualPixelYPosition(eg->getWindowHeight() / 2);

		// Apply a translation to offset so it appears to have zoomed on the centre by moving the old centre back to the centre of the screen
		//eg->getFilterPointsTranslation()->changeOffset(iNewCentreX - iOldCentreX, iNewCentreY - iOldCentreY);
		// Uncomment the above line to zoom in on centre rather than top left

		
		// Redraw the background
		eg->redrawDisplay(); // Force total redraw
	}

	void PauseState::initialise() {
		/*eg->getBackgroundSurface()->setDrawPointsFilter(eg->getFilterPointsTranslation());
		eg->getForegroundSurface()->setDrawPointsFilter(eg->getFilterPointsTranslation());*/

	}

protected:
    std::shared_ptr<State> returnState;
};

