//
//  Cell.cpp
//  AudioMatrix
//
//  Created by Eric Jiang on 7/14/15.
//
//

#include "Cell.h"

ColorA Cell::sColorAudioOn = Color(1.0f, 153.0f/255.0f, 0.0f);
ColorA Cell::sColorSelected = Color(1.0f, 184.0f/255.0f, 95.0f/255.0f);
ColorA Cell::sColorSlider = Color(249.0f/255.0f, 246.0f/255.0f, 244.0f/255.0f);
ColorA Cell::sColorNothing = ColorA(1.0f, 184.0f/255.0f, 95.0f/255.0f, 0.1f);

void Cell::setup(int x, int y)
{
    mX = x;
    mY = y;
    mState = false;
    mAudioOn = false;
    mSelected = false;
    bSlider = false;
}

void Cell::cellOn()
{
    mAudioOn = true;
}

void Cell::cellOff()
{
    mAudioOn = false;
}

void Cell::sliderOn()
{
    bSlider = true;
}

void Cell::sliderOff(){
    bSlider = false;
}

void Cell::draw(int colWidth, int rowHeight, int gridTop, int gridLeft)
{
    Rectf rect( colWidth*mX + gridLeft, rowHeight*mY + gridTop, colWidth*mX + gridLeft+colWidth-15,  rowHeight*mY + gridTop+rowHeight-15 );
    
    if (mAudioOn){
        gl::color(sColorAudioOn);
        gl::drawSolidRect (rect);
    }
    else if (mSelected) {
        gl::color(sColorSelected);
        gl::drawSolidRect(rect);
    }
    else if (bSlider) {
        gl::color(sColorSlider);
        gl::drawSolidRect(rect);
    }
    
    gl::color(sColorNothing);
    gl::drawStrokedRect (rect);
}
