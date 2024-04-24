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

    ImagePixelMappingFlip(FlipMode mode) : flipMode(mode) {}

    bool mapCoordinates(double& x, double& y, const Scyjz14Image& image);

    bool mapCoordinates(double& x, double& y, const SimpleImage& image) {
        std::cout << "You are using worng function! Warning!" << std::endl;
        return false;
    };

protected:
    FlipMode flipMode;
};



