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
    float timer;
    bool timerRunning;

} Scene;

/**
 * Initialize the scene by loading models.
 */
void init_scene(Scene* scene);

/**
 * Set the lighting of the scene.
 */
void set_lighting();

/**
 * Set the current material.
 */
void set_material(const Material* material);

/**
 * Update the scene.
 */
void update_scene(Scene* scene, double time);

void initiateStartSequence(Scene* scene);

int getLightID(Scene* scene);

/**
 * Render the scene objects.
 */
void render_scene(Scene* scene);

/**
 * Draw the origin of the world coordinate system.
 */
void draw_origin();

#endif /* SCENE_H */
