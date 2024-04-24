#include "header.h"
#include "ImagePixelMappingFlip.h"

bool ImagePixelMappingFlip::mapCoordinates(double& x, double& y, const Scyjz14Image& image) {
    if (x < 0 || y < 0 || x >= image.getWidth() || y >= image.getHeight()) {
        return false;
    }

    // Apply the flip based on the mode specified
    switch (flipMode) {
    case HORIZONTAL:
        x = image.getWidth() - x - 1; // Flip horizontally
        break;
    case VERTICAL:
        y = image.getHeight() - y - 1; // Flip vertically
        break;
    case BOTH:
        x = image.getWidth() - x - 1; // first flip horizontally
        y = image.getHeight() - y - 1; // then flip vertically
        break;
    }

    return true; // Successfully mapped the coordinates
}