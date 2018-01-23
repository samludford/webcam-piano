//
//  SoundManager.cpp
//  webcam-piano
//
//  Created by Sam Ludford on 23/01/2018.
//

#include "SoundManager.h"

double speeds[] = { 0.5, 0.75, 1.0, 1.25, 1.5, 2.0 };

SoundManager::SoundManager() {
    
    // setup scale - a minor pentatonic
    scale.resize(16);
    scale[0] = 110.0;
    scale[1] = 130.81;
    scale[2] = 146.83;
    scale[3] = 164.81;
    scale[4] = 196.00;
    scale[5] = 220.00;
    scale[6] = 261.63;
    scale[7] = 293.66;
    scale[8] = 329.63;
    scale[9] = 392.00;
    scale[10] = 440.00;
    scale[11] = 523.25;
    scale[12] = 587.33;
    scale[13] = 659.25;
    scale[14] = 783.99;
    scale[15] = 880.00;
    
    for(int i=0 ; i < scale.size() ; i++) {
        Sound *s = new Sound(scale[i*5%scale.size()], speeds[i*4%6]);
        sounds.push_back(s);
    }
}

void SoundManager::trigger_at(float x, float y) {

    int xBox = x/40.0;
    int yBox = y/40.0;
    assert(xBox < 16 && yBox < 12);
    double cutoff = ofMap(yBox, 0, 12, 100.0, 4000.0);
    sounds[xBox]->trigger(cutoff);
}

double SoundManager::signal() {
    double s;
    for(int i=0 ; i<sounds.size() ; i++) {
        s += sounds[i]->signal();
    }
    return s * 0.0625;
}
