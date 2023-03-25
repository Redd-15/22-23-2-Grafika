#include "pong.h"
#include "pad.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void init_pong(Pong* pong, int width, int height)
{
    pong->width = width;
    pong->height = height;
    
    init_ball(&(pong->ball), width / 2, height / 2);
    init_pad(&(pong->left_pad), 0, height, RED_THEME);
    init_pad(&(pong->right_pad), width - 50, height, GREEN_THEME);
    
    display_points(pong);

}

void display_points(Pong* pong){

    printf(" %d | %d \n", pong->player_L_point, pong->player_R_point);
}

void update_pong(Pong* pong, double time)
{
    update_pad(&(pong->left_pad), time);
    update_pad(&(pong->right_pad), time);
    update_ball(&(pong->ball), time);
    bounce_ball(pong);
}

void render_pong(Pong* pong)
{
    render_pad(&(pong->left_pad));
    render_pad(&(pong->right_pad));
    render_ball(&(pong->ball));
}

void set_left_pad_position(Pong* pong, float position)
{
    set_pad_position(&(pong->left_pad), position);
}

void set_left_pad_speed(Pong* pong, float speed)
{
    set_pad_speed(&(pong->left_pad), speed);
}

void set_right_pad_position(Pong* pong, float position)
{
    set_pad_position(&(pong->right_pad), position);
}

void set_right_pad_speed(Pong* pong, float speed)
{
    set_pad_speed(&(pong->right_pad), speed);
}

float get_right_pad_y(Pong pong)
{
    return pong.right_pad.y;
}

float get_left_pad_y(Pong pong)
{
    return pong.left_pad.y;
}

float get_right_pad_height(Pong pong){

    return pong.right_pad.height;
}

float get_left_pad_height(Pong pong){

    return pong.left_pad.height;
}

void bounce_ball(Pong* pong)
{

    if (pong->ball.x - pong->ball.radius < 50) {
        pong->ball.x = pong->ball.radius + 50;
    
        if (abs(get_left_pad_y(*pong) + get_left_pad_height(*pong) - pong->ball.y) < get_left_pad_height(*pong)){
            pong->ball.speed_x *= -1;
            if (pong->ball.speed_y < 0){pong->ball.rotation_speed -= 0.4;}
            else {pong->ball.rotation_speed += 0.4;}

            }
        else{
            pong->player_R_point += 1;
            init_pong(pong,pong->width,pong->height);
            }
    }
    if (pong->ball.x + pong->ball.radius > pong->width - 50) {
        pong->ball.x = pong->width - pong->ball.radius - 50;
    
        if (abs(get_right_pad_y(*pong) + get_right_pad_height(*pong) - pong->ball.y) < get_right_pad_height(*pong)){
            pong->ball.speed_x *= -1;
            if (pong->ball.speed_y < 0){pong->ball.rotation_speed += 0.4;}
            else {pong->ball.rotation_speed -= 0.4;}

            }
        else{
            pong->player_L_point += 1;
            init_pong(pong,pong->width,pong->height);
            }
    }
    if (pong->ball.y - pong->ball.radius < 0) {
        pong->ball.y = pong->ball.radius;
        pong->ball.speed_y *= -1;
        if (pong->ball.speed_x < 0){pong->ball.rotation_speed += 0.4;}
            else {pong->ball.rotation_speed -= 0.4;}
    }
    if (pong->ball.y + pong->ball.radius > pong->height) {
        pong->ball.y = pong->height - pong->ball.radius;
        pong->ball.speed_y *= -1;
        if (pong->ball.speed_x < 0){pong->ball.rotation_speed -= 0.4;}
            else {pong->ball.rotation_speed += 0.4;}
    }
}
