/* This is an example of how to integrate maximilain into openFrameworks,
 including using audio received for input and audio requested for output.
 
 
 You can copy and paste this and use it as a starting example.
 
 */

#include "ofApp.h"

#define OFFSET 0.0



//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetVerticalSync(true);
    
    // audio setup
    sampleRate 	= 44100; /* Sampling Rate */
    bufferSize	= 512; /* Buffer Size. you have to fill this buffer with sound using the for loop in the audioOut method */
    
    ofxMaxiSettings::setup(sampleRate, 2, bufferSize);
    
    ofSetVerticalSync(true);
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    
    ofSoundStreamSetup(2,2,this, sampleRate, bufferSize, 4);
    
    ofBackground(125);
    video.setDeviceID(0);
    video.setDesiredFrameRate(60);
    video.initGrabber(640, 480);
    debug = false;
    
    system.setupAsGrid(40, 2, 150);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    system.update();
    
    video.update();        //Decode the new frame if needed
    //Do computing only if the new frame was obtained
    if ( video.isFrameNew() ) {
        //Store the previous frame, if it exists till now
        if ( grayImage.bAllocated ) {
            grayImagePrev = grayImage;
        }
        
        //Getting a new frame
        image.setFromPixels( video.getPixels() );
        image.mirror(false, true);
        grayImage = image; //Convert to grayscale image
        
        //Do processing if grayImagePrev is inited
        if ( grayImagePrev.bAllocated ) {
            //Get absolute difference
            diff.absDiff( grayImage, grayImagePrev );
            
            //We want to amplify the difference to obtain
            //better visibility of motion
            //We do it by multiplication. But to do it, we
            //need to convert diff to float image first
            diffFloat = diff;    //Convert to float image
            diffFloat *= 2.0;    //Amplify the pixel values (original = 5.0)
            
            //Update the accumulation buffer
            if ( !bufferFloat.bAllocated ) {
                //If the buffer is not initialized, then
                //just set it equal to diffFloat
                bufferFloat = diffFloat;
            }
            else {
                //Slow damping the buffer to zero
                bufferFloat *= 0.65; //original = 0.85
                //Add current difference image to the buffer
                
                bufferFloat += diffFloat;
                bufferFloat.erode(); //helps get rid of noise (remove if not needed)
            }
        }
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground( 255, 255, 255 );    //Set the background color
    
    //Draw only if diffFloat image is ready.
    //It happens when the second frame from the video is obtained
    if ( diffFloat.bAllocated ) {
        //Get image dimensions
        int w = grayImage.width;
        int h = grayImage.height;
        
        //Set color for images drawing
        ofSetColor( 255, 255, 255 );
        
        //Draw images grayImage,  diffFloat, bufferFloat
        if (debug)
        {
            grayImage.draw( 0, 0, w/2, h/2 );
            diffFloat.draw( w/2, 0, w/2, h/2 );
            bufferFloat.draw( 0, h/2, w/2, h/2 );
        }
        else {
//            diffFloat.draw( 0, 0, ofGetWidth(), ofGetHeight() );
            bufferFloat.draw( 0, 0, ofGetWidth(), ofGetHeight() );
        }
        
        //Draw the image motion areas
        if (debug)
        {
            //Shift and scale the coordinate system
            ofPushMatrix();
            ofTranslate( w/2, h/2);
            ofScale( 0.5, 0.5 );
            //Draw bounding rectangle
            ofSetColor(0, 0, 0);
            ofNoFill();
        }
        
        //Get bufferFloat pixels
        float *pixels = bufferFloat.getPixelsAsFloats();
        
        //Scan all pixels
        for (int y=0; y<h; y+=1)
        {
            for (int x=0; x<w; x+=1)
            {
                //Get the pixel value
                float value = pixels[ x + w * y ];
                //If value exceed threshold, then draw pixel
                if ( value >= 1.4 ) {                           //original was 0.9
                    
                    if (debug) ofDrawRectangle( x, y, 1, 1 );
                    
                    system.activateParticle(x + OFFSET, y + OFFSET);
                    soundManager.trigger_at(x + OFFSET, y + OFFSET);
                }
            }
        }
    }
    
    system.draw();
    
}

//--------------------------------------------------------------
void ofApp::audioOut(float * output, int bufferSize, int nChannels) {
    for (int i = 0; i < bufferSize; i++){
        double mix = soundManager.signal();
        output[i*nChannels    ] = mix;
        output[i*nChannels + 1] = mix;
    }
}

//--------------------------------------------------------------
void ofApp::audioIn(float * input, int bufferSize, int nChannels){
    
    for(int i = 0; i < bufferSize; i++){
        /* you can also grab the data out of the arrays*/
        
    }
    
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
   
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    debug = !debug;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
