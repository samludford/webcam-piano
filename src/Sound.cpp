//
//  Sound.cpp
//  webcam-piano
//
//  Created by Sam Ludford on 23/01/2018.
//

#include "Sound.h"

Sound::Sound(double _freq, double _modSpeed) {
    this->freq = _freq;
    this->cutoff = 1.0;
    this->env.setAttack(40.0);
    this->env.setDecay(20.0);
    this->env.setSustain(0.6);
    this->env.setRelease(2000.0);
    this->modSpeed = _modSpeed;
}

double Sound::signal() {
    double current_amp = env.adsr(1.0, trig);
    if(trig == 1) {
        trig = 0;
    }
    
    double c = cutoff + filterMod.sinewave(modSpeed)*200.0;
    return filter.lores(osc.sawn(freq), c, 9.0) * current_amp;
}

void Sound::trigger(double _cutoff) {
    this->cutoff = _cutoff;
    this->trig = 1;
    this->env.trigger = 1;
}
