//
//  Sound.h
//  webcam-piano
//
//  Created by Sam Ludford on 23/01/2018.
//

#include "ofMain.h"
#include "ofxMaxim.h"

class Sound {
    
    public:
    
        Sound(double _freq, double _modSpeed);
        double signal();
        void trigger(double cutoff, double _freq);
    
    protected :
    
        int trig;
        double freq;
        double cutoff;
        maxiOsc osc;
        maxiFilter filter;
        maxiFilter filter_glide;
        maxiEnv env;
        maxiOsc filterMod;
        double modSpeed;
    
};
