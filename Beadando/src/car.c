#include "car.h"

#include <obj/load.h>
#include <obj/draw.h>
#include <stdio.h>
#include <math.h>

#define MIN_SPEED -1.5
#define MAX_SPEED 5
#define MAX_TURN 0.5
#define CAR_LEN 0.2
#define WHEEL_RADIUS 0.015

void init_car(Car* car)
{
    load_model(&(car->model), "assets/models/Car_assembly.obj");
    load_model(&(car->steering_wheel), "assets/models/SteeringWheel.obj");
    load_model(&(car->wheels), "assets/models/Wheel.obj");
    
    car->SWheel_texture = load_texture("assets/textures/sWheel.jpg");
    car->Car_texture = load_texture("assets/textures/Car.jpg");
    car->Wheel_texture = load_texture("assets/textures/wheels.jpg");

    car->x=0.0; 
    car->y=0.0; 
    car->psi=0.0; 
    car->v=0.0;
    car->a=0.0;
    car->w=0.0; 
    car->delta=0.0; 
    car->delta_a = 0.0f;
    car->turn_speed=0.0;
    car->wheel_angle = 0.0;

    car->material.ambient.red = 0.6;
    car->material.ambient.green = 0.6;
    car->material.ambient.blue = 0.6;

    car->material.diffuse.red = 0.8;
    car->material.diffuse.green = 0.8;
    car->material.diffuse.blue = 0.8;

    car->material.specular.red = 1.0;
    car->material.specular.green = 1.0;
    car->material.specular.blue = 1.0;

    car->material.shininess = 1.0;
}


void set_car_material(const Material* material)
{
    float ambient_material_color[] = {
        material->ambient.red,
        material->ambient.green,
        material->ambient.blue
    };

    float diffuse_material_color[] = {
        material->diffuse.red,
        material->diffuse.green,
        material->diffuse.blue
    };

    float specular_material_color[] = {
        material->specular.red,
        material->specular.green,
        material->specular.blue
    };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
}

void update_car(Car* car, double time)
{              
        if((car->v < 0.000000000001 && car->v > -0.000000000001) || isnan(time)){
            time = 0.05;
        }

        car->v += car->a * time;
        if (car->a == 0){
            car->v += car->v*-0.03;
        }

        if (car->v < MIN_SPEED){car->v = MIN_SPEED;}
        else if (car->v > MAX_SPEED){car->v = MAX_SPEED;}

        if (car->v > 0){
        car->turn_speed = car->delta_a*(MAX_SPEED/car->v*0.1f);
        }
        else if (car->v < 0){
            car->turn_speed = car->delta_a*(MAX_SPEED/car->v*-0.1f);
        }
        else {
            car->turn_speed = car->delta_a/2.0f;
        }

        car->delta += car->turn_speed * time;
        if (car->delta > MAX_TURN){car->delta = MAX_TURN;}
        else if (car->delta < -MAX_TURN){car->delta = -MAX_TURN;}


        car->w = car->v * tan(car->delta) / CAR_LEN;

        car->x += car->v * time * cos(car->psi + car->w * time/2);
        car->y += car->v * time * sin(car->psi + car->w * time/2);
        
        car->psi += car->w * time; 

        car->wheel_angle += (car->v/WHEEL_RADIUS);

        while (car->wheel_angle > 360)
        {
            car->wheel_angle -= 360;
        }

        if (car->delta != 0){car->delta -= car->delta*0.05;}

}

void render_car(const Car* car)
{
    set_car_material(&(car->material));

    glTranslatef((car->x), (car->y), 0.0);
    glRotatef((radian_to_degree(car->psi)), 0.0 ,0.0 ,1.0);
    
    glBindTexture(GL_TEXTURE_2D, car->Car_texture);
    glEnable(GL_TEXTURE_2D);
    draw_model(&(car->model));

    glBindTexture(GL_TEXTURE_2D, car->Wheel_texture);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0.05,0.06,0.0227);
    glRotatef((radian_to_degree(car->delta)/2), 0.0 ,0.0 ,1.0);
    glRotatef(car->wheel_angle, 0.0 ,1.0 ,0.0);
    draw_model(&(car->wheels));
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.05,-0.06,0.0227);
    glRotatef((radian_to_degree(car->delta)/2)+180, 0.0 ,0.0 ,1.0);
    glRotatef(-car->wheel_angle, 0.0 ,1.0 ,0.0);
    draw_model(&(car->wheels));
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.11,0.06,0.0227);
    glRotatef(car->wheel_angle, 0.0 ,1.0 ,0.0);
    draw_model(&(car->wheels));
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.11,-0.06,0.0227);
    glRotatef(180, 0.0 ,0.0 ,1.0);
    glRotatef(-car->wheel_angle, 0.0 ,1.0 ,0.0);
    draw_model(&(car->wheels));
    glPopMatrix();

    glTranslatef(0.018, 0.0, 0.051);
    glRotatef((radian_to_degree(car->delta))*-4, 1.0 ,0.0 ,0.0);
    glBindTexture(GL_TEXTURE_2D, car->SWheel_texture);
    glEnable(GL_TEXTURE_2D);
    draw_model(&(car->steering_wheel));
}



void set_car_acc(Car* car, float vel)
{
    car->a = vel;
}

void set_car_turning_speed(Car* car, float speed)
{
    car->delta_a = speed;
}

