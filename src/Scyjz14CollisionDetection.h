#pragma once
#include "header.h"
#include "Scyjz14Image.h"
#include "UtilCollisionDetection.h"

class Scyjz14CollisionDetection :
    public CollisionDetection
{
public:
    static bool checkPixel(
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

    /*
        Expand the opaque part of picture 1 by `offset` pixels 
        and detect whether it collides with picture 2.
    */
    static bool checkPixelWithOffset(int offSet,
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
};

