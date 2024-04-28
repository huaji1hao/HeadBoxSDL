#pragma once
#include "DrawingSurface.h"
#include "ImagePixelMapping.h"
#include "Scyjz14Image.h"

class ImagePixelMappingFlip :
    public ImagePixelMapping
{
public:
    enum FlipMode {
        HORIZONTAL,
        VERTICAL,
        BOTH // horizontal and vertical flip at the same time
    };

    // set the flip mode when initializing
    ImagePixelMappingFlip(FlipMode mode) : m_flipMode(mode) {}

    // set the flip mode
    void setFlipMode(FlipMode mode) { m_flipMode = mode; }

    // map the coordinates based on the flip mode
    bool mapCoordinates(double& x, double& y, const Scyjz14Image& image);

    // Fake function to warn the user that they are using the wrong function
    bool mapCoordinates(double& x, double& y, const SimpleImage& image) override;

protected:
    FlipMode m_flipMode;
};



