//
//  ColorHelper.cpp
//  webcam-piano
//
//  Created by Sam Ludford on 25/01/2018.
//

#include "ColorHelper.h"

ofColor ColorHelper::randomColor() {
    ofColor c1 = ofColor::indigo;
    ofColor c2 = ofColor::deepSkyBlue;
    ofColor c3 = ofColor::cyan;
    
    ofColor f = c1.getLerped(c2, ofRandom(1.0));
    ofColor s = f.getLerped(c3, ofRandom(1.0));
    return s;
}

