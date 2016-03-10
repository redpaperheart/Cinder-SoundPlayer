//
//  Cell.cpp
//  AudioMatrix
//
//  Created by Eric Jiang on 7/14/15.
//
//

#include "Cell.h"

ColorA Cell::sColorAudioOn = Color(1.0f, 153.0f/255.0f, 0.0f);
ColorA Cell::sColorCellOn = Color(1.0f, 184.0f/255.0f, 95.0f/255.0f);
ColorA Cell::sColorPlayhead = ColorA(1.0f, 184.0f/255.0f, 95.0f/255.0f, 0.25f);
ColorA Cell::sColorNothing = Color(249.0f/255.0f, 246.0f/255.0f, 244.0f/255.0f);

void Cell::setup(int x, int y)
{
    mX = x;
    mY = y;
    bEnabled = false;
    bPlayhead = false;
    bSelected = false;
}

void Cell::draw(float side, float padding, vec2 offset)
{
    float x = offset.x + mX * side;
    float y = offset.y + mY * side;
    float w = x + side - padding;
    float h = y + side - padding;
    Rectf rect(x, y, w, h);
    
    if (bPlayhead && bEnabled) {
        gl::color(sColorAudioOn);
    }
    else if (bEnabled) {
        gl::color(sColorCellOn);
    }
    else if (bPlayhead) {
        gl::color(sColorPlayhead);
    }
    else if (bSelected) {
        gl::color(sColorPlayhead);
    }
    else {
        gl::color(sColorNothing);
    }
    gl::drawSolidRect(rect);
}