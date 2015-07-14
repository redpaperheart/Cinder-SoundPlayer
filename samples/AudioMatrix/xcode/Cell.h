//
//  Cell.h
//  AudioMatrix
//
//  Created by Eric Jiang on 7/14/15.
//
//

#pragma once

using namespace ci;
using namespace ci::app;
using namespace std;

class Cell{
public:
    int mX, mY;
    bool mState;
    bool mAudioOn;
    bool mSelected;
    bool bSlider;
    
    Cell(){};
    
    Cell(int x, int y ){
        
        mX = x;
        mY = y;
        mState = false;
        mAudioOn = false;
        mSelected = false;
        bSlider = false;
        
    };
    
    void cellOn();
    void cellOff();
    void sliderOn();
    void sliderOff();
    void draw(int colWidth, int rowHeight, int gridTop, int gridLeft);
    void display();
    
};

