#include "camera.h"

#include <GL/gl.h>

#include <math.h>

void init_camera(Camera* camera)
{
    camera->position.x = 0.0;
    camera->position.y = 0.0;
    camera->position.z = 1.0;
    camera->rotation.x = 0.0;
    camera->rotation.y = 0.0;
    camera->rotation.z = 0.0;
    camera->speed.x = 0.0;
    camera->speed.y = 0.0;
    camera->speed.z = 0.0;
    camera->turn_speed_x = 0.0;
    camera->turn_speed_y = 0.0;
    camera->camera_mode = 1;

    camera->is_preview_visible = false;
}

void update_camera(Camera* camera, Car* car, double time)
{
    double angle;
    double side_angle;

    angle = degree_to_radian(camera->rotation.z);
    side_angle = degree_to_radian(camera->rotation.z + 90.0);

    switch (camera->camera_mode)
    {
    case 1:
        camera->position.x += cos(angle) * camera->speed.y * time;
        camera->position.y += sin(angle) * camera->speed.y * time;
        camera->position.x += cos(side_angle) * camera->speed.x * time;
        camera->position.y += sin(side_angle) * camera->speed.x * time;
        camera->position.z += camera->speed.z * time;
        rotate_camera(camera, camera->turn_speed_x * time, camera->turn_speed_y * time);
        break;
    case 2:

        camera->position.x = car->x;
        camera->position.y = car->y;
        camera->position.z = 0.07;
        rotate_camera(camera, (radian_to_degree(car->w)*time), 0);
        rotate_camera(camera, camera->turn_speed_x * time, camera->turn_speed_y * time);
        break;
    
    case 3:

        camera->position.x = car->x;
        camera->position.y = car->y;
        camera->position.z = 0.1;
        rotate_camera(camera, (radian_to_degree(car->w)*time), 0);
        rotate_camera(camera, camera->turn_speed_x * time, camera->turn_speed_y * time);
        break;
    
    default:
        break;
    }
    

    
}

void set_view(const Camera* camera)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotatef(-(camera->rotation.x + 90), 1.0, 0, 0);
    glRotatef(-(camera->rotation.z - 90), 0, 0, 1.0);
    glTranslatef(-camera->position.x, -camera->position.y, -camera->position.z);
}

void rotate_camera(Camera* camera, double horizontal, double vertical)
{
    camera->rotation.z += horizontal;
    camera->rotation.x += vertical;

    if (camera->rotation.z < 0) {
        camera->rotation.z += 360.0;
    }

    if (camera->rotation.z > 360.0) {
        camera->rotation.z -= 360.0;
    }

    if (camera->rotation.x < 0) {
        camera->rotation.x += 360.0;
    }

    if (camera->rotation.x > 360.0) {
        camera->rotation.x -= 360.0;
    }
}

void set_camera_speed(Camera* camera, double speed)
{
    camera->speed.y = speed;
}

void set_camera_side_speed(Camera* camera, double speed)
{
    camera->speed.x = speed;
}

void set_camera_vertical_speed(Camera* camera, double speed)
{
    camera->speed.z = speed;    
}

void set_camera_vert_turn_speed(Camera* camera, float speed)
{
    camera->turn_speed_y = speed;
}

void set_camera_hor_turn_speed(Camera* camera, float speed)
{
    camera->turn_speed_x = speed;
}

void show_texture_preview()
{
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1, 1, 1);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-1, 1, -3);
    glTexCoord2f(1, 0);
    glVertex3f(1, 1, -3);
    glTexCoord2f(1, 1);
    glVertex3f(1, -1, -3);
    glTexCoord2f(0, 1);
    glVertex3f(-1, -1, -3);
    glEnd();

    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
}

void switch_camera_mode(Camera* camera, int mode)
{
    camera->camera_mode = mode;
    //printf("%d\n", mode);
}
