//
//  Sound.cpp
//  webcam-piano
//
//  Created by Sam Ludford on 23/01/2018.
//

#include "Sound.h"

Sound::Sound(double _freq) {
    this->freq = _freq;
    this->cutoff = 1.0;
    this->env.setAttack(0);
    this->env.setDecay(1);
    this->env.setSustain(1);
    this->env.setRelease(2000.0);
}

double Sound::signal() {
    double current_amp = env.adsr(1.0, trig);
    if(trig == 1) {
        trig = 0;
    }
//    double c = ofMap(current_amp,0,1,80.0,c*4);
    return filter.lores(osc.sawn(freq), cutoff, 1.0) * current_amp;
}

void Sound::trigger(double _cutoff) {
    this->cutoff = _cutoff;
    this->trig = 1;
    this->env.trigger = 1;
}
