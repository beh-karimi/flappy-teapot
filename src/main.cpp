#include <GL/glut.h>
#include <cmath>
#include <iostream>

#include "drawable_objects.h"

#define PI 3.1415

struct Point{ float x; float y;};

Point player = {-10.0, 0.0};

float player_vspeed = 0.3;
float player_hspeed = 0.05;
const float gravity = 0.01;
float terminal_velocity = -0.4;
bool dead = false;

float camera_preset[3][8] = {
    {0.0, 0.0, 12.0,
        -PI/2, 0.0,
        0.0, 1.0, 0.0},

    {-10.0, 10.0, 0.0,
        -PI/4, -PI/4,
        0.0, 1.0, 0.0},

    {0.5, 0.0, -10.0,
        0.0, 0.0,
        0.0, 1.0, 0.0},
};

float camera[8];
int camera_state = 0;
int render_mode = 0;

Point pillars[10];

void reshape(int w, int h) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    float aspect = (float)w / (float) h;
    switch(render_mode) {
        case 0:
            gluPerspective(70, aspect, 1.0, 1000);
            break;
        case 1:
            glOrtho( -10*aspect, 10*aspect, -10.0, 10.0, 1.0, 1000.0);
            break;
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void display(){
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    float temp_camera[8];
    for(int i=0; i<8; i++) temp_camera[i] = camera[i];

    if(camera_state>0)
        temp_camera[1] += player.y;

    double looking_at[3] = {player.x + temp_camera[0]+cos(temp_camera[3]), temp_camera[1]+sin(temp_camera[4]), temp_camera[2]+sin(temp_camera[3])};
    gluLookAt(player.x + temp_camera[0], temp_camera[1], temp_camera[2],
            looking_at[0], looking_at[1], looking_at[2], 
            temp_camera[5], temp_camera[6], temp_camera[7]);

    draw_player(player_vspeed, player.x, player.y);

    for(Point p : pillars)
        draw_pillar(p.x, p.y);

    glutSwapBuffers();
    //glFlush();
}
void generate_pillars() {
    for(int i = 0; i<10; i++) {
        pillars[i].x = i*10.0 + 10.0;
        pillars[i].y = (float)(rand()%200-100)/10;
        std::cout << pillars[i].y << " init\n";
    }
    std::cout << "==============\n"; 
}

void init() {
    generate_pillars();
    camera_state = 0;
    for(int i=0; i<8; i++)
        camera[i] = camera_preset[0][i];
    dead = false;
    player.x = -10.0;
    player.y = 0.0;
    player_hspeed = 0.05;
    player_vspeed = 0.3;
    terminal_velocity = -0.4;

    glEnable(GL_DEPTH_TEST);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3ub(0, 255, 255);

    reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}

void keyboard(unsigned char k, int x, int y) {
    switch(k) {
        case 'w':
            camera[0] += cos(camera[3]) * 0.1;
            camera[1] += sin(camera[4]) * 0.1;
            camera[2] += sin(camera[3]) * 0.1;
            break;
        case 's':
            camera[0] -= cos(camera[3]) * 0.1;
            camera[1] -= sin(camera[4]) * 0.1;
            camera[2] -= sin(camera[3]) * 0.1;
            break;
        case 'd':
            camera[0] += cos(camera[3]+PI/2) * 0.1;
            camera[2] += sin(camera[3]+PI/2) * 0.1;
            break;
        case 'a':
            camera[0] -= cos(camera[3]+PI/2) * 0.1;
            camera[2] -= sin(camera[3]+PI/2) * 0.1;
            break;
        case 'x':
            camera[1] += 0.1;
            break;
        case 'z':
            camera[1] -= 0.1;
            break;
        case 't':
            if(camera[4] < PI/2)
                camera[4] += 0.05;
            break;
        case 'g':
            if(camera[4] > -PI/2)
                camera[4] -= 0.05;
            break;
        case 'h':
            camera[3] += 0.05;
            break;
        case 'f':
            camera[3] -= 0.05;
            break;
        case ' ':
            if(!dead)
                player_vspeed = 0.2;
            break;
        case 'r':
            init();
            break;
        case 'm':
            camera_state = (camera_state+1)%3;
            for(int i=0; i<8; i++) camera[i] = camera_preset[camera_state][i];
            break;
        case 'c':
            render_mode = (render_mode+1)%2;
            int width = glutGet(GLUT_WINDOW_WIDTH);
            int height = glutGet(GLUT_WINDOW_HEIGHT);
            reshape(width, height);
            break;
        }
}

int check_death() {
    int i = (player.x>=20.0);
    if(player.x < pillars[i].x+1.0 && player.x > pillars[i].x-1.0
            && (player.y < pillars[i].y-2.125 || player.y > pillars[i].y+2.125))
        return 1;
    return 0;
}

void logicLoop(int v) {
    if(!dead){
        if(player_vspeed > terminal_velocity)
            player_vspeed -= gravity;
        player.y += player_vspeed;
        player.x += player_hspeed;
        
        if(pillars[1].x < player.x-9.0) {
            for(int i=0; i<9; i++) {
                pillars[i] = pillars[i+1];
                std::cout << i+1 << ": " << pillars[i].y << "\n";
            }
            pillars[9] = {pillars[8].x+15, (float)(rand()%200-100)/10};
            std::cout << "10: " << pillars[9].y << "\n==============\n"; 
        }

        if(check_death()) {
            player_hspeed = 0.0;
            player_vspeed = 0.0;
            dead = true;
        }
    }
    glutPostRedisplay();
    glutTimerFunc(1000/60, logicLoop, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    //glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(900,900);
    glutCreateWindow("Flappy");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, logicLoop, 0);
    init();
    glutMainLoop();
}
