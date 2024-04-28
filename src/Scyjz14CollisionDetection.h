#pragma once
#include "header.h"
#include "Scyjz14Image.h"
#include "UtilCollisionDetection.h"

class Scyjz14CollisionDetection :
    public CollisionDetection
{
public:
    // Check if two images collide by checking the pixels
    static bool checkPixel(
        Scyjz14Image image1, int iSourceX1, int iSourceY1, int width1, int height1, int iScreenX1, int iScreenY1,
        Scyjz14Image image2, int iSourceX2, int iSourceY2, int width2, int height2, int iScreenX2, int iScreenY2);
    
    // Expand the opaque part of image1 by `offset` pixels
    // and detect whether it collides with image2.
    static bool checkPixelWithOffset(int offSet,
        const Scyjz14Image& image1, int iSourceX1, int iSourceY1, int width1, int height1, int iScreenX1, int iScreenY1,
        const Scyjz14Image& image2, int iSourceX2, int iSourceY2, int width2, int height2, int iScreenX2, int iScreenY2);

    // Check if a image collides with a straight line
    static bool checkPixelWithStraightLine(
        Scyjz14Image image, int iSourceX, int iSourceY, int width, int height, int iScreenX, int iScreenY,
        int startX, int startY, int endX, int endY);

    // Check is a image is contained in another image by quickly calculating the bounding box
    static bool isImageContained(
        int iScreenX1, int iScreenY1, int width1, int height1,
        int iScreenX2, int iScreenY2, int width2, int height2);

    // Check if image2 is in image1
    static bool checkPixelIsImg2InImg1(
        Scyjz14Image image1, int iSourceX1, int iSourceY1, int width1, int height1, int iScreenX1, int iScreenY1,
        Scyjz14Image image2, int iSourceX2, int iSourceY2, int width2, int height2, int iScreenX2, int iScreenY2);
};