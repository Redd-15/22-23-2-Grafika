#ifndef CAR_H
#define CAR_H

#include "camera.h"
#include "texture.h"

#include <obj/model.h>

typedef struct Car
{
    Model model;
    float x;        //x coordinate
    float y;        //y coordinate
    float psi;      //orientation
    float v;        //velocity
    float w;        //angular velocity
    float delta;    //wheel angle
    float turn_speed;
    float timer;
    Material material;
    GLuint texture_id;
} Car;

/**
 * Initialize the car by loading model and parameters.
 */
void init_car(Car* car);

/**
 * Set the current material.
 */
void set_car_material(const Material* material);

/**
 * Update the car.
 */
void update_car(Car* car, double time);

/**
 * Render the car objects.
 */
void render_car(const Car* car);

void set_car_velocity(Car* car, float vel);

void set_car_turning_speed(Car* car, float speed);


#endif /* CAR_H */
