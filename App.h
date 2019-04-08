#ifndef App_hpp
#define App_hpp

#include "GlutApp.h"
#include "TexRect.h"
#include "AnimatedRect.h"

class App: public GlutApp {
    // Maintain app state here


public:
    // Constructor, to initialize state
    App(const char* label, int x, int y, int w, int h);

    float mx;
    float my;
    float increment;
    int points;


    // These are the events we want to handle
    void draw();
    void keyPress(unsigned char key);
    void mouseDown(float x, float y);
    void mouseDrag(float x, float y);

    void specialKeyPress(int key);

    void specialKeyUp(int key);

    void idle();

    TexRect* ball;

    TexRect* platform;

    TexRect* background;
    TexRect* background2;
    TexRect* obstacle;
    TexRect* obstacle2;
    TexRect* thwomp;
    TexRect* thwomp2;
    TexRect* bullet;
    TexRect* bullet2;
    TexRect* mario;


    TexRect* mainmenu;
    TexRect* start;
    TexRect* end;


    AnimatedRect* deadgame;

    AnimatedRect* gameOver;

    bool up;
    bool down;
    bool left;
    bool right;

    bool moving;
    bool game_over;




};

#endif
