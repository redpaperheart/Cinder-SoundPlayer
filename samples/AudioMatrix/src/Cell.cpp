//
//  Cell.cpp
//  AudioMatrix
//
//  Created by Eric Jiang on 7/14/15.
//
//

#include "Cell.h"


void Cell::cellOn(){
    
    mAudioOn = true;
}

void Cell::cellOff(){
    mAudioOn = false;
}

void Cell::sliderOn(){
    bSlider = true;
}

void Cell::sliderOff(){
    bSlider = false;
}

void Cell::draw(int colWidth, int rowHeight, int gridTop, int gridLeft)
{
    
    Rectf rect( colWidth*mX + gridLeft, rowHeight*mY + gridTop, colWidth*mX + gridLeft+colWidth-15,  rowHeight*mY + gridTop+rowHeight-15 );
    
    if (mSelected) {
        gl::color(1.0f, 184.0f/255.0f, 95.0f/255.0f);
        gl::drawSolidRect(rect);
        
        gl::color(1.0f, 184.0f/255.0f, 95.0f/255.0f);
        gl::drawStrokedRect(rect);
    }
    
    if (bSlider) {
        gl::color(249.0f/255.0f, 246.0f/255.0f, 244.0f/255.0f);
        gl::drawSolidRect(rect);
    }
    
    if (mAudioOn){
        gl::color(1.0f, 153.0f/255.0f, 0.0f);
        
        gl::drawSolidRect (rect);
    }
    else {
        gl::color(1.0f, 184.0f/255.0f, 95.0f/255.0f, 0.1f);
        gl::drawStrokedRect (rect);
        
    }
}
