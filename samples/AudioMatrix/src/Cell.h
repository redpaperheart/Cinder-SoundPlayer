
//
//  Cell.h
//  AudioMatrix
//
//  Created by Eric Jiang on 7/14/15.
//
//

#pragma once

#include "cinder/Color.h"

using namespace ci;
using namespace std;

class Cell {
public:
    static ColorA sColorAudioOn;
    static ColorA sColorCellOn;
    static ColorA sColorPlayhead;
    static ColorA sColorNothing;
    
    void setup(int x, int y);
    void enable(bool on)            { bEnabled = on; }
    void toggle()                   { bEnabled = !bEnabled; }
    void setPlayhead(bool playhead) { bPlayhead = playhead; }
    void setSelected(bool selected) { bSelected = selected; }
    
    bool isEnabled()    { return bEnabled; }
    bool isSelected()   { return bSelected; }
    
    void draw(float side, float padding, vec2 offset);
    
private:
    int mX, mY;
    bool bEnabled;
    bool bPlayhead;
    bool bSelected;
};
