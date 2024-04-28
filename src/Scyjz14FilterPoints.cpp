#include "header.h"
#include "Scyjz14FilterPoints.h"
#include "ExampleFilterPointClasses.h"

Scyjz14FilterPoints::Scyjz14FilterPoints(int xFactor, int yFactor, FilterPoints* pNextFilter = nullptr)
	: FilterPointsScaling(xFactor, yFactor, pNextFilter)
	, m_translationFilter(0, 0, this)
{
}

void Scyjz14FilterPoints::resetScalingSize() {
	setStretch(0, 0); 
}

FilterPointsTranslation* Scyjz14FilterPoints::getFilterPointsTranslation() {
	return &m_translationFilter; 
}