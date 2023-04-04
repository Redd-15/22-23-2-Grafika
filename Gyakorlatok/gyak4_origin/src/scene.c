#include "scene.h"

#include <GL/gl.h>
#include <math.h>

void init_scene(Scene* scene)
{
}

void update_scene(Scene* scene)
{
}

void render_scene(const Scene* scene)
{
    draw_origin();
    draw_triangle();
    draw_chess_board();
    draw_cylinder();
}

void draw_origin()
{
    glBegin(GL_LINES);

    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);

    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);

    glEnd();

}
void draw_triangle(){

    glBegin(GL_TRIANGLE_FAN);

    glColor3f(0.5, 0.5, 0.0);
    glVertex3f(1.0, 1.0, 0);

    glColor3f(0.0, 0.5, 0.5);
    glVertex3f(0.0, 1.0, 1.0);

    glColor3f(0.5, 0.0, 0.5);
    glVertex3f(1.0, 0.0, 1.0);

    glEnd();
}

void draw_chess_board(){

    glBegin(GL_QUADS);

    
    int blck = 0;

    for(float x = 0; x<1.0; x=x+0.1){
        if(blck == 0){blck = 1;}
        else{blck = 0;}
        for(float y = 0; y<1.0; y=y+0.1){

            if(blck == 0){glColor3f(1.0, 1.0, 1.0); blck = 1;}
            else{glColor3f(0.0, 0.0, 0.0); blck = 0;}
            
            glVertex3f(x+0.1, y, 0);
            glVertex3f(x, y, 0);
            glVertex3f(x, y+0.1, 0);
            glVertex3f(x+0.1, y+0.1, 0);

            
        }
    }


    glEnd();


}
void draw_cylinder(){

    glBegin(GL_QUAD_STRIP);

    

    float height = 0.5;
    float step = 10.0;
    float r = 0.1;
    float x = 0.5;
    float y = 0.5;

    for(float deg = 0; deg<=360; deg=deg+step){
            
        glColor3f(0.1, 0.2, 0.3);
        glVertex3f(x+r*cos(degree_to_radian(deg)), y+r*sin(degree_to_radian(deg)), height);
        glVertex3f(x+r*cos(degree_to_radian(deg)), y+r*sin(degree_to_radian(deg)), 0);
        
        glColor3f(0.4, 0.5, 0.6);
        glVertex3f(x+r*cos(degree_to_radian(deg+step/2)), y+r*sin(degree_to_radian(deg+step/2)), height);
        glVertex3f(x+r*cos(degree_to_radian(deg+step/2)), y+r*sin(degree_to_radian(deg+step/2)), 0);              
        
    }


    glEnd();


}
