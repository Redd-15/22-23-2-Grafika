#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"
#include "car.h"

#include <obj/model.h>

typedef struct Scene
{
    Model track, lights, start_line, grandstand, skybox;
    Material material;
    GLuint texture_track, texture_track_side, texture_lights[6], texture_start_line, texture_grandstand, texture_skybox;
    Car car;
    float timer, light_intensity;
    bool timerRunning;


} Scene;

/**
 * Initialize the scene by loading models.
 */
void init_scene(Scene* scene);

/**
 * Changing the sun intensity.
 */
void change_light(Scene* scene);
/**
 * Set the lighting of the scene.
 */
void set_lighting(Scene* scene);

/**
 * Set the current material.
 */
void set_material(const Material* material);

/**
 * Update the scene.
 */
void update_scene(Scene* scene, double time);

/**
 * Initiate the start sequence.
 */
void initiateStartSequence(Scene* scene);

/**
 * Get Light texture for teh start light animation.
 */
int getLightID(Scene* scene);

/**
 * Render the scene objects.
 */
void render_scene(Scene* scene);

#endif /* SCENE_H */
