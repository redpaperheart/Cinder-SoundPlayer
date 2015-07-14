
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

class Cell {
public:
    static ColorA sColorAudioOn;
    static ColorA sColorSelected;
    static ColorA sColorSlider;
    static ColorA sColorNothing;
    
    int mX, mY;
    bool mState;
    bool mAudioOn;
    bool mSelected;
    bool bSlider;
        
    void setup(int x, int y);
    void cellOn();
    void cellOff();
    void sliderOn();
    void sliderOff();
    void draw(int colWidth, int rowHeight, int gridTop, int gridLeft);
    void display();
};
