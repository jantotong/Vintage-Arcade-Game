#include "ofApp.h"
#include "Emitter.h"

void ofApp::setup(){
    radio.load("audio/shoot.mp3");
    radio2.load("audio/explode.mp3");
    shipImg.load("images/j.png");
    face.load("images/angryFace.png");
    face2.load("images/angryFace2.png");
    ammo.load("images/ammo.png");
    
    
    ofSetVerticalSync(true);
    ofBackground(0, 0, 0);
    score = 0;
    
    // Record when the game starts - game will run for 10 sec
    //
    gameStartTime = ofGetElapsedTimeMillis();
    
    ship = new Emitter( new SpriteSystem() );
    invaders = new Emitter(new SpriteSystem());
    invaders2 = new Emitter(new SpriteSystem());
    
    ship->setPosition(ofVec3f(ofGetWindowWidth()/2, ofGetWindowHeight()-10, 0));
    ship->setVelocity(ofVec3f(0, -1000, 0));
    ship->setRate(0);
    ship->setLifespan(500);
    ship->setImage(shipImg);
    ship->setChildImage(ammo);
    
    invaders->setPosition(ofVec3f((3*ofGetWindowWidth())/4, 10, 0));
    invaders->velocity.set(0, 400, 0);
    invaders->setLifespan(5000);
    invaders->setRate(1);
    invaders->setChildImage(face);
    
    invaders2->setPosition(ofVec3f(ofGetWindowWidth()/4, 10, 0));
    invaders2->velocity.set(0, 400, 0);
    invaders2->setLifespan(5000);
    invaders2->setRate(0.5);
    invaders2->setChildImage(face2);
    
    //Stop until Key 's'
    invaders->stop();
    invaders2->stop();
    ship->stop();
    
}

//--------------------------------------------------------------
//  ofApp::update() is called every frame by the OF mainloop. 
//  If the frame rate is 60 fps (frames per second) it gets called 
//  every 1/60 sec
//
void ofApp::update() {
    
    ship->update();
    invaders->update();
    invaders2->update();
    
    
    checkCollisions();
    ship->setRate(0);
    //Modulate velocity
    SpawnRandomize(invaders);
    SpawnRandomize(invaders2);
    
    if(ship->moving){
        switch(dir){
            case MoveUp:{
                ship->trans.y = (ship->trans.y)-10.0;
            }
            case MoveDown:{
                ship->trans.y = (ship->trans.y)+10.0;
            }
            case MoveRight:{
                ship->trans.x = (ship->trans.x)+10.0;
            }
            case MoveLeft:{
                ship->trans.x = (ship->trans.x)-10.0;
            }
        }
    }
    
    ofVec3f v = invaders->velocity;
    ofVec3f v2 = invaders2->velocity;
    
    invaders->setVelocity(ofVec3f(move(v.x), v.y, v.z));
    invaders2->setVelocity(ofVec3f(ofRandom(-v2.y /2, v2.y /2), v2.y, v2.z));
    
    float t = ofGetElapsedTimeMillis();
    //    if ((t - gameStartTime > (20 * 1000))) {
    //        gameOver = true;
    //        ship->stop();
    //        invaders->stop();
    //        invaders2->stop();
    //    }
}

void ofApp::draw(){
    
    ship->draw();
    invaders->draw();
    invaders2->draw();
    
    // draw current score
    //
    string scoreText;
    scoreText += "Score: " + std::to_string(score);
    ofDrawBitmapString(scoreText, ofPoint(10, 20));
}

//  This is a simple O(M x N) collision check
//  For each missle check to see which invaders you hit and remove them
//
void ofApp::checkCollisions() {
    
    // find the distance at which the two sprites (missles and invaders) will collide
    // detect a collision when we are within that distance.
    //
    float collisionDist = ship->childHeight / 2 + invaders->childHeight / 2;
    float collisionDist2 = ship->childHeight / 2 + invaders2->childHeight / 2;
    
    // Loop through all the missiles, then remove any invaders that are within
    // "collisionDist" of the missiles.  the removeNear() function returns the
    // number of missiles removed.
    //
    for (int i = 0; i < ship->sys->sprites.size(); i++){
        score += invaders->sys->removeNear(ship->sys->sprites[i].trans, collisionDist);
        score += invaders2->sys->removeNear(ship->sys->sprites[i].trans, collisionDist);
        if(score!=oldScore){
            radio2.play();
            oldScore = oldScore+1;
        }
    }
}


void ofApp::mouseDragged(int x, int y, int button){
    ofPoint mouse_cur = ofPoint(x, y);
    ofVec3f delta = mouse_cur - mouseLast;
    
    // ship half of screen only
    //
    if ((ship->trans.y + delta.y) > ofGetWindowHeight() / 2) {
        ship->trans += delta;
        mouseLast = mouse_cur;
    }
    //
}

void ofApp::mousePressed(int x, int y, int button){
    if (!ship->started) {
        gameStartTime = ofGetElapsedTimeMillis();
        gameOver = false;
        ship->start();
        invaders->start();
        invaders2->start();
        score = 0;
        oldScore = 0;
    }
    mouseLast = ofPoint(x, y);
}


void ofApp::keyPressed(int key) {
    switch (key) {
        case 'F':
        case 'f':
            ofToggleFullscreen();
            break;
        case 'H':
        case 'h':
            break;
        case 'r':
            break;
        case 's':
            invaders->start();
            invaders2->start();
            ship->start();
            break;
        case 'u':
            break;
        case ' ':
            radio.play();
            ship->setRate(5);
            break;
        case '.':
            break;
        case ',':
            break;
        case OF_KEY_RIGHT:
            ship->moving = true;
            moveSprite(MoveRight);
            ship->trans.x = (ship->trans.x)+30.0;
            break;
        case OF_KEY_LEFT:
            ship->moving = true;
            moveSprite(MoveLeft);
            break;
        case OF_KEY_UP:
            ship->moving = true;
            moveSprite(MoveUp);
            ship->trans.y = (ship->trans.y)-30.0;
            break;
        case OF_KEY_DOWN:
            ship->moving = true;
            moveSprite(MoveDown);
            break;
        case OF_KEY_ALT:
            break;
        case OF_KEY_CONTROL:
            break;
        case OF_KEY_SHIFT:
            break;
        case OF_KEY_DEL:
            break;
    }
}

void ofApp::keyReleased(int key){
    switch (key) {
        case OF_KEY_RIGHT:
            ship->moving = false;
            break;
        case OF_KEY_LEFT:
            ship->moving = false;
            break;
        case OF_KEY_UP:
            ship->moving = false;
            break;
        case OF_KEY_DOWN:
            ship->moving = false;
            break;
    }
}

void ofApp::moveSprite(MoveDir x) {
    dir = x;
}

//Modulate velocity
void ofApp::SpawnRandomize(Emitter *x){
    
    x->rate = (ofRandom(0.1, 1.2));
    
    //Invaders Special Double Output Case
    if(x->rate == 0.3){
        x->rate = 10;
    }
}

//for swining motiong
float ofApp::move(float x){
    if(swing){
        x = x - 20;
    }
    else{
        x = x + 20;
    }
    if(x < -400){
        swing = false;
    }
    else if(x > 400){
        swing = true;
    }
    return x;
}
