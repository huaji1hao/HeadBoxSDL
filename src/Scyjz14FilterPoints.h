#pragma once
#include "ExampleFilterPointClasses.h"
class Scyjz14FilterPoints :
    public FilterPointsScaling
{
public:
	Scyjz14FilterPoints(int xFactor, int yFactor, FilterPoints* pNextFilter);

	// Restore the scaling size to the original size
	void resetScalingSize();

	// Get a reference to the FilterPoints Translation object
	FilterPointsTranslation* getFilterPointsTranslation();

protected:
	FilterPointsTranslation m_translationFilter;
};

