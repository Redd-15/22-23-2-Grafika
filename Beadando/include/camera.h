#ifndef CAMERA_H
#define CAMERA_H

#include "utils.h"
#include "car.h"

#include <stdbool.h>

/**
 * Camera, as a moving point with direction
 */
typedef struct Camera
{
    vec3 position;
    vec3 rotation;
    vec3 speed;
    float turn_speed_x;
    float turn_speed_y;
    bool is_preview_visible;
    int camera_mode;
} Camera;

/**
 * Initialize the camera to the start position.
 */
void init_camera(Camera* camera);

/**
 * Update the position of the camera.
 */
void update_camera(Camera* camera, Car* car, double time);

/**
 * Apply the camera settings to the view transformation.
 */
void set_view(const Camera* camera);

/**
 * Set the horizontal and vertical rotation of the view angle.
 */
void rotate_camera(Camera* camera, double horizontal, double vertical);

/**
 * Set the speed of forward and backward motion.
 */
void set_camera_speed(Camera* camera, double speed);

/**
 * Set the speed of left and right side steps.
 */
void set_camera_side_speed(Camera* camera, double speed);

/**
 * Set the speed of up and down side steps.
 */
void set_camera_vertical_speed(Camera* camera, double speed);

void set_camera_vert_turn_speed(Camera* camera, float speed);

void set_camera_hor_turn_speed(Camera* camera, float speed);

void show_texture_preview();

void switch_camera_mode(Camera* camera, int mode);

#endif /* CAMERA_H */
