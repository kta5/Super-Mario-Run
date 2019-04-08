#include "TexRect.h"


TexRect::TexRect (const char* filename, float x=0, float y=0, float w=0.5, float h=0.5){

    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);

    texture_id = SOIL_load_OGL_texture (
     filename,
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
     );

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;

    rising = false;
    movingLeft = true;

    xinc = 0.01;
    yinc = 0.025;

}

void TexRect::moveUp(float rate){
    y += rate;
}
void TexRect::moveDown(float rate){
    y -= rate;
}
void TexRect::moveLeft(float rate){
    x -= rate;
    if (x < -0.99){
        x = -0.99;
    }
}
void TexRect::moveRight(float rate){
    x += rate;
    if (x + w > 0.99){
        x = 0.99 - w;
    }
}

void TexRect::jump(){
    if(rising){
        y+=yinc;
    }
    else {
        y -= yinc;
    }
    if (y > 0.5){
        rising = false;
    }
    if ((y-h) < -0.525){
      y = -0.325;
    }
}



void TexRect::draw(float z){
    glBindTexture( GL_TEXTURE_2D, texture_id );
    glEnable(GL_TEXTURE_2D);

    glBegin(GL_QUADS);
    glColor4f(1, 1, 1, 1);
    glTexCoord2f(0, 0);
    glVertex3f(x, y - h, z);

    glTexCoord2f(0, 1);
    glVertex3f(x, y, z);

    glTexCoord2f(1, 1);
    glVertex3f(x+w, y, z);

    glTexCoord2f(1, 0);
    glVertex3f(x+w, y - h, z);

    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void TexRect::cycle(float z, float rate){
    x -= rate;
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glEnable(GL_TEXTURE_2D);

    glBegin(GL_QUADS);
    glColor4f(1, 1, 1, 1);

    if (x+w < -0.99){
      x = 1.0;
      if (x < -1.0){
        x = 1.0;
      }
    }

    glTexCoord2f(0, 0);
    glVertex3f(x, y-h, z);

    glTexCoord2f(0, 1);
    glVertex3f(x, y, z);

    glTexCoord2f(1, 1);
    glVertex3f(x+w, y, z);

    glTexCoord2f(1, 0);
    glVertex3f(x+w, y - h, z);

    glEnd();

    glDisable(GL_TEXTURE_2D);
}


bool TexRect::contains(TexRect* object){
    if (x+w >= object->x && object->x + object->w >= x && object->y >= y - h){
      return true;
    }
    else{
      return false;
    }
}
