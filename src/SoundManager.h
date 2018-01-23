//
//  SoundManager.h
//  webcam-piano
//
//  Created by Sam Ludford on 23/01/2018.
//

#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"
#include "Sound.h"

class SoundManager {
    
    public:
    
        SoundManager();
        double signal();
        void trigger_at(float x, float y);
    
    protected:
    
        vector<double> scale;
        vector<Sound*> sounds;
    
};

