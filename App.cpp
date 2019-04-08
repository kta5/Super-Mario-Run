#include "App.h"
#include <iostream>

using namespace std;

static App* singleton;

void app_timer(int value){

    if (singleton->game_over){
        singleton->gameOver->advance();
    }
    /*
    if (singleton->start->contains(singleton->mx,singleton->my)){
        delete singleton->mainmenu;
        delete singleton->start;
        delete singleton->end;
        singleton->moving = true;
        singleton->redraw();
        glutTimerFunc(100, app_timer, value);
    }
    if (singleton->end->contains(singleton->mx,singleton->my)){

        delete deadgame;
        delete mario;
        delete obstacle;
        delete obstacle2;
        delete gameOver;
        delete background;
        delete background2;
        delete mainmenu;
        delete start;
        delete end;

        delete this;


        exit(0);
    }*/

    if (singleton->moving){
        singleton->points++;
        singleton->mario->jump();
        singleton->background->cycle(0.1, 0.01);
        singleton->background2->cycle(0.1, 0.01);
        singleton->obstacle->cycle(0.1, 0.01);
        singleton->obstacle2->cycle(0.1, 0.01);
        singleton->thwomp->cycle(0.1, 0.01);
        singleton->thwomp2->cycle(0.1, 0.01);
        //singleton->bullet->cycle(0.1, 0.01);
        //singleton->bullet2->cycle(0.1, 0.01);

        if (singleton->mario->contains(singleton->obstacle)){
            singleton->moving = false;
            singleton->game_over = true;
            singleton->gameOver->animate();
            cout<< singleton->points << endl;
        }
        if (singleton->mario->contains(singleton->obstacle2)){
            singleton->moving = false;
            singleton->game_over = true;
            singleton->gameOver->animate();
            cout<< singleton->points <<endl;
        }
        if (singleton->mario->contains(singleton->thwomp)){
            singleton->moving = false;
            singleton->game_over = true;
            singleton->gameOver->animate();
            cout<< singleton->points << endl;
        }
        if (singleton->mario->contains(singleton->thwomp2)){
            singleton->moving = false;
            singleton->game_over = true;
            singleton->gameOver->animate();
            cout<< singleton->points << endl;
        }
        /*
        if (singleton->mario->contains(singleton->bullet)){
            singleton->moving = false;
            singleton->game_over = true;
            singleton->gameOver->animate();
            cout<< singleton->points << endl;
        }
        if (singleton->mario->contains(singleton->bullet2)){
            singleton->moving = false;
            singleton->game_over = true;
            singleton->gameOver->animate();
            cout<< singleton->points << endl;
        }
        */
  }
    if (singleton->up){
        if(singleton->mario->y <= -0.324){
          singleton->mario->rising = true;
          singleton->mario->jump();
        }
    }
    if (singleton->down){
        singleton->mario->moveDown(0.025);
    }
    if (singleton->left){
        singleton->mario->moveLeft(0.025);
    }
    if (singleton->right){
        singleton->mario->moveRight(0.025);
    }

    if (singleton->game_over){
        singleton->redraw();
        glutTimerFunc(100, app_timer, value);
    }
    else{
        if (singleton->up || singleton->down || singleton->left || singleton->right || singleton->moving && !singleton->game_over){
            singleton->redraw();
            glutTimerFunc(16, app_timer, value);
        }
    }
  }




App::App(const char* label, int x, int y, int w, int h): GlutApp(label, x, y, w, h){
    // Initialize state variables

    singleton = this;
    mx = 2.0;
    my = 2.0;
    points = 0;

    mainmenu = new TexRect("images/menu.png", -1, 1, 2, 2);
    start = new TexRect("images/start.jpg", -0.5, 0.25, 1, 0.2);
    end = new TexRect("images/end.jpg", -0.5, -0.1, 1, 0.2);

    background = new TexRect("images/background.png", -1, 1, 2, 2);
    background2 = new TexRect("images/background.png", 1, 1, 2, 2);

    mario = new TexRect("images/mario1.png", -0.8, -0.325, 0.15, 0.2);

    obstacle = new TexRect("images/spike.png", 3.3, -0.325, 0.15, 0.2);
    obstacle2 = new TexRect("images/spike.png", 3.15, -0.325, 0.15, 0.2);
    thwomp = new TexRect("images/thwomp1.png", 3, -0.3, 0.15, 0.25);
    thwomp2 = new TexRect("images/thwomp1.png", 6, -0.3, 0.15, 0.25);
    //bullet = new TexRect("../images/bullet1.png", 7.5, 0.6, 0.2, 0.1);
    //bullet2 = new TexRect("../images/bullet1.png", 8.75, 0.3, 0.2, 0.1);

    deadgame = new AnimatedRect("images/gameover.jpg", 2, 1, -1.0, 0.8, 2, 1.2);

    gameOver = new AnimatedRect("images/game_over.png", 7, 1, -1.0, 0.8, 2, 1.2);

    up = down = left = right = false;

    moving = true;
    game_over = false;

    app_timer(1);

}

void App::specialKeyPress(int key){
    if (!game_over){
        if (key == 100){
            left = true;
        }
        if (key == 101){
            up = true;
        }
        if (key == 102){
            right = true;
        }
        if (key == 103){
            //down = true;
        }
    }
}

void App::specialKeyUp(int key){
    if (key == 100) {
        left = false;
    }
    if (key == 101) {
        up = false;
    }
    if (key == 102) {
        right = false;
    }
    if (key == 103) {
        down = false;
    }
}

void App::draw() {

    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set background color to black
    glClearColor(0.0, 0.0, 0.0, 1.0);

    // Set up the transformations stack
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    background->draw(0.1);
    background2->draw(0.1);

	glColor3f(1,1,1);
  obstacle->draw(-0.3);
  obstacle2->draw(-0.3);
  thwomp->draw(-0.3);
  thwomp2->draw(-0.3);
  //bullet->draw(-0.3);
  //bullet2->draw(-0.3);
  mario->draw(-0.5);
/*
    start->draw(-0.4);
    end->draw(-0.4);
    mainmenu->draw(-0.4);
*/
  deadgame->draw();
	gameOver->draw();

    // We have been drawing everything to the back buffer
    // Swap the buffers to see the result of what we drew
    glFlush();
    glutSwapBuffers();
}

void App::mouseDown(float x, float y){
    // Update app state
    singleton->mx = x;
    singleton->my = y;

}

void App::mouseDrag(float x, float y){
    // Update app state
    mx = x;
    my = y;

}

void App::idle(){

}

void App::keyPress(unsigned char key) {
    if (key == 27){
        // Exit the app when Esc key is pressed
        delete deadgame;
        delete mario;
        delete obstacle;
        delete obstacle2;
        delete thwomp;
        delete thwomp2;
        delete gameOver;
        delete background;
        delete background2;
        delete mainmenu;
        delete start;
        delete end;

        delete this;

        exit(0);
    }


    if (key == 'r'){
        mario->x = -0.8;
        mario->y = -0.325;
        mario->rising = false;
        obstacle->x = 1.5;
        obstacle2->x = 2.5;
        thwomp->x = 3;
        thwomp2->x = 6;
        game_over = false;
        gameOver->stop();
        moving = true;
    }

    if (key == 'p'){

    }
    if (key == 'u'){

    }
}
