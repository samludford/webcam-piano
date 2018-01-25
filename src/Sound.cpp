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
    this->env.setAttack(80.0);
    this->env.setDecay(20.0);
    this->env.setSustain(0.5);
    this->env.setRelease(3000.0);
    this->modSpeed = _modSpeed;
}

double Sound::signal() {
    
    double current_amp = env.adsr(0.8, trig);
    if(trig == 1) {
        trig = 0;
    }
    
    double c = cutoff + filterMod.sinewave(modSpeed)*100.0;
    double c_glid = filter_glide.lopass(c, 0.01);
    return filter.lores(osc.sawn(freq), c_glid, 2.0) * current_amp;
}

void Sound::trigger(double _cutoff, double _freq) {
    this->freq = _freq;
    this->cutoff = _cutoff;
    this->trig = 1;
}
