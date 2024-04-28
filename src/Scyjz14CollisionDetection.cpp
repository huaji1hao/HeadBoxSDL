#include "header.h"
#include "Scyjz14CollisionDetection.h"

bool Scyjz14CollisionDetection::checkPixel(
    Scyjz14Image image1, int iSourceX1, int iSourceY1, int width1, int height1, int iScreenX1, int iScreenY1,
    Scyjz14Image image2, int iSourceX2, int iSourceY2, int width2, int height2, int iScreenX2, int iScreenY2) {

    // First, check the bounding rectangles for overlap
    if (!checkRectangles(iScreenX1, iScreenX1 + width1, iScreenY1, iScreenY1 + height1,
        iScreenX2, iScreenX2 + width2, iScreenY2, iScreenY2 + height2)) {
        // If the bounding rectangles do not overlap, return false
        return false;
    }

    // Calculate the overlap bounds of the two images
    int left = std::max(iScreenX1, iScreenX2);
    int right = std::min(iScreenX1 + width1, iScreenX2 + width2);
    int top = std::max(iScreenY1, iScreenY2);
    int bottom = std::min(iScreenY1 + height1, iScreenY2 + height2);

    // Iterate over each pixel in the overlapping area
    for (int y = top; y < bottom; y++) {
        for (int x = left; x < right; x++) {
            // Calculate the position of the pixel within the source images
            int posX1 = x - iScreenX1 + iSourceX1;
            int posY1 = y - iScreenY1 + iSourceY1;
            int posX2 = x - iScreenX2 + iSourceX2;
            int posY2 = y - iScreenY2 + iSourceY2;

            // Get the pixel data from both images
            unsigned int pixel1 = image1.getPixelColour(posX1, posY1);
            unsigned int pixel2 = image2.getPixelColour(posX2, posY2);

            // Check alpha value
            unsigned int alpha1 = pixel1 >> 24;
            unsigned int alpha2 = pixel2 >> 24;

            // Check for collision where both pixels are fully opaque
            if (alpha1 == 255 && alpha2 == 255) {
                return true;
            }
        }
    }

    // No collision detected
    return false;
}


bool Scyjz14CollisionDetection::checkPixelWithStraightLine(
    Scyjz14Image image, int iSourceX, int iSourceY, int width, int height, int iScreenX, int iScreenY,
    int startX, int startY, int endX, int endY) {

    // Determine if the line is horizontal or vertical
    bool isHorizontal = (startY == endY);
    bool isVertical = (startX == endX);

    if (!isHorizontal && !isVertical) {
        std::cerr << "Error: The line is neither horizontal nor vertical." << std::endl;
        return false;
    }

    // Calculate the intersection of the line with the image's bounding box
    int left = std::max(iScreenX, std::min(startX, endX));
    int right = std::min(iScreenX + width, std::max(startX, endX));
    int top = std::max(iScreenY, std::min(startY, endY));
    int bottom = std::min(iScreenY + height, std::max(startY, endY));

    // Check each pixel along the line within the bounds of the image
    if (isHorizontal) {
        int y = startY - iScreenY + iSourceY; // Y position in the source image
        if (y < iSourceY || y >= iSourceY + height) return false; // Check if y is within image bounds
        for (int x = left; x <= right; x++) {
            int sourceX = x - iScreenX + iSourceX; // X position in the source image
            if (sourceX >= iSourceX && sourceX < iSourceX + width) {
                unsigned int pixel = image.getPixelColour(sourceX, y);
                unsigned int alpha = pixel >> 24;
                if (alpha == 255) { // Fully opaque
                    return true;
                }
            }
        }
    }
    else if (isVertical) {
        int x = startX - iScreenX + iSourceX; // X position in the source image
        if (x < iSourceX || x >= iSourceX + width) return false; // Check if x is within image bounds
        for (int y = top; y <= bottom; y++) {
            int sourceY = y - iScreenY + iSourceY; // Y position in the source image
            if (sourceY >= iSourceY && sourceY < iSourceY + height) {
                unsigned int pixel = image.getPixelColour(x, sourceY);
                unsigned int alpha = pixel >> 24;
                if (alpha == 255) { // Fully opaque
                    return true;
                }
            }
        }
    }

    return false;
}


bool Scyjz14CollisionDetection::checkPixelWithOffset(int offSet,
    const Scyjz14Image& image1, int iSourceX1, int iSourceY1, int width1, int height1, int iScreenX1, int iScreenY1,
    const Scyjz14Image& image2, int iSourceX2, int iSourceY2, int width2, int height2, int iScreenX2, int iScreenY2) {

    if (!checkRectangles(iScreenX1, iScreenX1 + width1, iScreenY1, iScreenY1 + height1,
        iScreenX2, iScreenX2 + width2, iScreenY2, iScreenY2 + height2)) {
        return false;
    }

    int left = std::max(iScreenX1, iScreenX2);
    int right = std::min(iScreenX1 + width1, iScreenX2 + width2);
    int top = std::max(iScreenY1, iScreenY2);
    int bottom = std::min(iScreenY1 + height1, iScreenY2 + height2);

    for (int y = top; y < bottom; y++) {
        for (int x = left; x < right; x++) {
            int posX1 = x - iScreenX1 + iSourceX1;
            int posY1 = y - iScreenY1 + iSourceY1;
            int posX2 = x - iScreenX2 + iSourceX2;
            int posY2 = y - iScreenY2 + iSourceY2;

            unsigned int pixel2 = image2.getPixelColour(posX2, posY2);
            unsigned int alpha2 = pixel2 >> 24;
            if (alpha2 != 255) {
                continue; // Only interested in fully opaque pixels in image2
            }

            // Check the pixel and its surroundings based on the offset
            for (int offsetY = -offSet; offsetY <= offSet; offsetY++) {
                for (int offsetX = -offSet; offsetX <= offSet; offsetX++) {
                    int checkX = posX1 + offsetX;
                    int checkY = posY1 + offsetY;

                    // Make sure we don't check beyond the image boundaries
                    if (checkX >= iSourceX1 && checkX < iSourceX1 + width1 && checkY >= iSourceY1 && checkY < iSourceY1 + height1) {
                        unsigned int pixel1 = image1.getPixelColour(checkX, checkY);
                        unsigned int alpha1 = pixel1 >> 24;
                        if (alpha1 == 255) {
                            return true; // Collision detected
                        }
                    }


                }
            }


        }
    }

    return false; // No collision detected
}


bool Scyjz14CollisionDetection::isImageContained(
    int iScreenX1, int iScreenY1, int width1, int height1,
    int iScreenX2, int iScreenY2, int width2, int height2) {
    // Calculate the boundary of both images
    int right1 = iScreenX1 + width1;
    int bottom1 = iScreenY1 + height1;
    int right2 = iScreenX2 + width2;
    int bottom2 = iScreenY2 + height2;

    // Check if all four sides of image2 are within image1
    return (iScreenX2 >= iScreenX1 && iScreenY2 >= iScreenY1 &&
        right2 <= right1 && bottom2 <= bottom1);
}


bool Scyjz14CollisionDetection::checkPixelIsImg2InImg1(
    Scyjz14Image image1, int iSourceX1, int iSourceY1, int width1, int height1, int iScreenX1, int iScreenY1,
    Scyjz14Image image2, int iSourceX2, int iSourceY2, int width2, int height2, int iScreenX2, int iScreenY2) {

    // First, check if the entire image2 is within the bounds of image1
    if (!isImageContained(iScreenX1, iScreenY1, width1, height1, iScreenX2, iScreenY2, width2, height2))
        return false;

    // Iterate over each pixel in image2 to check containment
    for (int y = 0; y < height2; y++) {
        for (int x = 0; x < width2; x++) {
            int posX2 = x + iSourceX2;
            int posY2 = y + iSourceY2;
            unsigned int pixel2 = image2.getPixelColour(posX2, posY2);
            unsigned int alpha2 = pixel2 >> 24;

            // Only consider non-transparent pixels in image2
            if (alpha2 == 255) {
                // Check corresponding pixel in image1
                int posX1 = iScreenX2 - iScreenX1 + x + iSourceX1;
                int posY1 = iScreenY2 - iScreenY1 + y + iSourceY1;
                unsigned int pixel1 = image1.getPixelColour(posX1, posY1);
                unsigned int alpha1 = pixel1 >> 24;

                // If corresponding pixel in image1 is not opaque, return false
                if (alpha1 != 255) {
                    return false;
                }
            }
        }
    }

    // All non-transparent pixels of image2 are contained within the opaque pixels of image1
    return true;
}

