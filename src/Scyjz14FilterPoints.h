#pragma once
#include "ExampleFilterPointClasses.h"
class Scyjz14FilterPoints :
    public FilterPointsScaling
{
public:
	Scyjz14FilterPoints(int xFactor, int yFactor, FilterPoints* pNextFilter);

	void resetScalingSize();

	FilterPointsTranslation* getFilterPointsTranslation();

protected:
	FilterPointsTranslation translationFilter;
};

