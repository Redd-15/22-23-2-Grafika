#include "scene.h"

#include <obj/load.h>
#include <obj/draw.h>
#include <stdio.h>
#include <math.h>

void init_scene(Scene* scene)
{
    load_model(&(scene->track), "assets/models/Track.obj");
    load_model(&(scene->start_line), "assets/models/StartLine.obj");
    load_model(&(scene->lights), "assets/models/Lights.obj");
    load_model(&(scene->grandstand), "assets/models/GrandStands.obj");
    load_model(&(scene->skybox), "assets/models/skybox.obj");
    scene->texture_track = load_texture("assets/textures/track_img_final.jpg");
    scene->texture_start_line = load_texture("assets/textures/StartLine.jpg");
    scene->texture_grandstand = load_texture("assets/textures/GrandStands.jpg");
    scene->texture_track_side = load_texture("assets/textures/grass.jpg");
    scene->texture_lights[0] = load_texture("assets/textures/0.jpg");
    scene->texture_lights[1] = load_texture("assets/textures/1.jpg");
    scene->texture_lights[2] = load_texture("assets/textures/2.jpg");
    scene->texture_lights[3] = load_texture("assets/textures/3.jpg");
    scene->texture_lights[4] = load_texture("assets/textures/4.jpg");
    scene->texture_lights[5] = load_texture("assets/textures/5.jpg");
    scene->texture_skybox = load_texture("assets/textures/skybox.jpg");

    scene->material.ambient.red = 0.6;
    scene->material.ambient.green = 0.6;
    scene->material.ambient.blue = 0.6;

    scene->material.diffuse.red = 0.8;
    scene->material.diffuse.green = 0.8;
    scene->material.diffuse.blue = 0.8;

    scene->material.specular.red = 1.0;
    scene->material.specular.green = 1.0;
    scene->material.specular.blue = 1.0;

    scene->material.shininess = 1.0;
    scene->timer = 0.0;
    scene->timerRunning = false;

    scene->light_intensity = 0.1f;

    init_car(&(scene->car));
}

void change_light(Scene* scene){

    scene->light_intensity += 0.1f;
    if (scene->light_intensity > 1.0f){
        scene->light_intensity = 0.0f;
    }
} 

void set_lighting(Scene* scene)
{
    float ambient_light[] = {1.0, 1.0, 1.0, 1.0f };
    float diffuse_light[] = { scene->light_intensity, scene->light_intensity, scene->light_intensity, 1.0f };
    float specular_light[] = { scene->light_intensity, scene->light_intensity, scene->light_intensity, 1.0f };
    float position[] = { 0.0f, 0.0f, 10.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void set_material(const Material* material)
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

void update_scene(Scene* scene, double time)
{
    if (scene->timerRunning){
        
        scene->car.v = 0;
        scene->timer += time;
    }

    update_car(&(scene->car), time);
}

void initiateStartSequence(Scene* scene){

    init_car(&(scene->car));
    scene->timerRunning = true;

}

int getLightID(Scene* scene){

    if (scene->timerRunning == false){

        return 0;
    }
    else if (scene->timer > 8.0){
        scene->timer = 0.0;
        scene->timerRunning = false;
    }
    else if (scene->timer > 7.0){

        return 5;
    }
    else if (scene->timer > 6.0){
        return 4;
    }
    else if (scene->timer > 5.0){
        return 3;
    }
    else if (scene->timer > 4.0){
        return 2;
    }
    else if (scene->timer > 3.0){
        return 1;
    }

    return 0;

}

void render_scene(Scene* scene)
{
    set_material(&(scene->material));
    set_lighting(scene);

    glPushMatrix();
    glScalef(0.05,0.05,0.05);

    glBindTexture(GL_TEXTURE_2D, scene->texture_skybox);
    glEnable(GL_TEXTURE_2D);
    draw_model(&(scene->skybox));
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, scene->texture_track);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();

    glRotatef(90, 0.0, 0.0, 1.0);
    glScalef(1.0,-1.0,1.0);
    draw_model(&(scene->track));

    glBindTexture(GL_TEXTURE_2D, scene->texture_track_side);
    glTranslatef(50.0,0.0,-0.01);
    glScalef(10.0,10.0,1.0);
    draw_model(&(scene->track));
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.1,0.0,-0.2);
    glRotatef(90, 0, 0, 1.0);
    glScalef(2,2,2);
    glBindTexture(GL_TEXTURE_2D, scene->texture_lights[getLightID((scene))]);
    glEnable(GL_TEXTURE_2D);
    draw_model(&(scene->lights));
    glPopMatrix();

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene->texture_start_line);
    glEnable(GL_TEXTURE_2D);
    glScalef(20,20,20);
    glRotatef(90, 0, 0, -1.0);
    glTranslatef(0.0,0.09,0.007);
    draw_model(&(scene->start_line));
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-15.0f,0,0);
    glBindTexture(GL_TEXTURE_2D, scene->texture_grandstand);
    glRotatef(90, 0, 0, 1.0);
    glTranslatef(0,0,0.1);
    draw_model(&(scene->grandstand));
    glTranslatef(0.0,-10,0.1);
    draw_model(&(scene->grandstand));
    glTranslatef(0.0,-10,0.1);
    draw_model(&(scene->grandstand));
    glPopMatrix();

    render_car(&(scene->car));
    
}

