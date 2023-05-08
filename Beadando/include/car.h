#ifndef CAR_H
#define CAR_H

#include "texture.h"
#include "utils.h"

#include <obj/model.h>

typedef struct Car
{
    Model model, steering_wheel, wheels;
    float x;            //x coordinate
    float y;            //y coordinate
    float psi;          //orientation
    float v;            //velocity
    float w;            //angular velocity
    float delta;        //wheel angle
    float turn_speed;
    float wheel_angle;
    float timer;
    Material material;
    GLuint SWheel_texture, Car_texture, Wheel_texture;
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
 * Set the car lighting.
 */
void set_car_lighting();

/**
 * Update the car parameters.
 */
void update_car(Car* car, double time);

/**
 * Render the car objects.
 */
void render_car(const Car* car);

/**
 * Setting car velocity.
 */
void set_car_velocity(Car* car, float vel);

/**
 * Setting car steering wheel angular speed.
 */
void set_car_turning_speed(Car* car, float speed);


#endif /* CAR_H */
