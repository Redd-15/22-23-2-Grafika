#include "car.h"

#include <obj/load.h>
#include <obj/draw.h>
#include <stdio.h>
#include <math.h>

#define MIN_SPEED -3
#define MAX_SPEED 10
#define MAX_TURN 0.5
#define CAR_LEN 1

void init_car(Car* car)
{
    load_model(&(car->model), "assets/models/cat.obj");
    car->texture_id = load_texture("assets/textures/cube.png");

    car->x=0.0; 
    car->y=0.0; 
    car->psi=0.0; 
    car->v=0.0;
    car->w=0.0; 
    car->delta=0.0; 
    car->timer = 0.0;
    //srand((unsigned) time(car->timer));

    glBindTexture(GL_TEXTURE_2D, car->texture_id);

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

/*void set_car_lighting(Car * car)
{
    float ambient_light[] = { 1.0, 1.0, 1.0, 1.0f };
    float diffuse_light[] = { (float)230/255, (float)230/255, (float)255/255, 1.0f };
    float specular_light[] = { (float)230/255, (float)230/255, (float)255/255, 1.0f };
    float position[] = { 0.0f, 0.0f, 10.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}*/

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
    float w = 0.0;
    w = car->v * tan(car->delta) / CAR_LEN;

    car->x += car->v * time * cos(car->psi + w * time/2);
    car->y += car->v * time * sin(car->psi + w * time/2);
    
    car->psi += w * time; 
    car->timer += time;

    printf("%f || %f || %f\n", car->x, car->y, car->delta);
}

void render_car(const Car* car)
{
    set_car_material(&(car->material));
    //set_car_lighting(car);

    glTranslatef((car->x), (car->y), 0.0);
    glRotatef(90.0, 1.0 ,0.0 ,0.0);
    glRotatef((radian_to_degree(car->psi))+90.0, 0.0 ,1.0 ,0.0);
    printf("%f \n", radian_to_degree(car->psi));
    //glRotatef(car->psi, 0.0 ,0.0 ,1.0);
    glDisable(GL_TEXTURE_2D);
    draw_model(&(car->model));
    glEnable(GL_TEXTURE_2D);
}



void set_car_velocity(Car* car, float vel)
{
    car->v += vel;
    if (car->v < MIN_SPEED){car->v = MIN_SPEED;}
    else if (car->v > MAX_SPEED){car->v = MAX_SPEED;}
}

void set_car_turning(Car* car, float delta)
{
    car->delta += delta;
    if (car->delta > MAX_TURN){car->delta = MAX_TURN;}
    else if (car->delta < -MAX_TURN){car->delta = -MAX_TURN;}
}


