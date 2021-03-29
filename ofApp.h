#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "Sprite.h"

typedef enum { MoveStop, MoveLeft, MoveRight, MoveUp, MoveDown } MoveDir;
    
class Emitter;

class ofApp : public ofBaseApp{
    
public:
    ofSoundPlayer radio, radio2;
    void setup();
    void update();
    void draw();
    void checkCollisions();
    
    void scoreAdd(int x);
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y) {}
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button) {}
    void mouseEntered(int x, int y) {}
    void mouseExited(int x, int y) {}
    void windowResized(int w, int h) {}
    void dragEvent(ofDragInfo dragInfo) {}
    void gotMessage(ofMessage msg) {}
    void moveSprite(MoveDir x);
    float move(float x);
    void SpawnRandomize(Emitter *x);
    
    Emitter *invaders,*invaders2, *ship;
    int score;
    int oldScore;
    float gameStartTime;
    bool gameOver = false;
    bool swing = false;
    ofVec3f mouseLast;
    ofImage shipImg,face,ammo,face2;
    MoveDir dir;
};
