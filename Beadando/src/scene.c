#include "scene.h"

#include <obj/load.h>
#include <obj/draw.h>
#include <stdio.h>
#include <math.h>

void init_scene(Scene* scene)
{
    load_model(&(scene->cube), "assets/models/cube.obj");
    load_model(&(scene->model), "assets/models/cat.obj");
    scene->texture_id = load_texture("assets/textures/cube.png");

    scene->x=0.0; 
    scene->y=2.0; 
    scene->psi=0.0; 
    scene->v=0.0;
    scene->w=0.0; 
    scene->delta=0.0; 
    scene->r = 1.0;
    scene->g = 1.0;
    scene->b = 1.0;
    scene->timer = 0.0;
    srand((unsigned) time(scene->timer));

    glBindTexture(GL_TEXTURE_2D, scene->texture_id);

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
}

void set_lighting(Scene * scene)
{
    float ambient_light[] = { scene->r, scene->g, scene->b, 1.0f };
    float diffuse_light[] = { (float)230/255, (float)230/255, (float)255/255, 1.0f };
    float specular_light[] = { (float)230/255, (float)230/255, (float)255/255, 1.0f };
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



scene->timer += time;
if (scene->timer > 1.0){
    scene->timer = 0.0;
    scene->r = (float)rand()/45520.0;
    scene->g = (float)rand()/45520.0;
    scene->b = (float)rand()/45520.0;
}

}

void render_scene(const Scene* scene)
{
    set_material(&(scene->material));
    set_lighting(scene);
    draw_origin();

    glTranslatef((scene->x), (scene->y), 0.0);
    glRotatef(90.0, 1.0 ,0.0 ,0.0);
    glDisable(GL_TEXTURE_2D);
    draw_model(&(scene->model));
    glEnable(GL_TEXTURE_2D);
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
