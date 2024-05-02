#include <GL/glut.h>
void draw_cube(unsigned int mode) {
    float offset = 0.0;
    switch(mode) {
        case 1:
            offset = 0.01;
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            break;
    }
    glBegin(GL_QUADS);
        glVertex3f(0.5 + offset, 0.0, 0.5 + offset);
        glVertex3f(-0.5 - offset, 0.0, 0.5 + offset);
        glVertex3f(-0.5- offset, 0.0, -0.5- offset);
        glVertex3f(0.5, 0.0, -0.5- offset);

        glVertex3f(0.5, 0.0, 0.5 + offset);
        glVertex3f(-0.5- offset, 0.0, 0.5 + offset);
        glVertex3f(-0.5- offset, 500.0, 0.5 + offset);
        glVertex3f(0.5, 500.0, 0.5 + offset);

        glVertex3f(0.5, 0.0, 0.5 + offset);
        glVertex3f(0.5, 0.0, -0.5- offset);
        glVertex3f(0.5, 500.0, -0.5- offset);
        glVertex3f(0.5, 500.0, 0.5 + offset);

        glVertex3f(-0.5- offset, 0.0, 0.5 + offset);
        glVertex3f(-0.5- offset, 0.0, -0.5- offset);
        glVertex3f(-0.5- offset, 500.0, -0.5- offset);
        glVertex3f(-0.5- offset, 500.0, 0.5 + offset);

        glVertex3f(-0.5- offset, 0.0, -0.5- offset);
        glVertex3f(0.5, 0.0, -0.5- offset);
        glVertex3f(0.5, 500.0, -0.5- offset);
        glVertex3f(-0.5- offset, 500.0, -0.5- offset);

        glVertex3f(0.5, 500.0, 0.5 + offset);
        glVertex3f(-0.5- offset, 500.0, 0.5 + offset);
        glVertex3f(-0.5- offset, 500.0, -0.5- offset);
        glVertex3f(0.5, 500.0, -0.5- offset);
    glEnd();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void draw_pillar(float x, float y) {
    glPushMatrix();
    glTranslatef(x, y+2.5, -10.0);
    draw_cube(0);
    glColor3b(0.0, 0.0, 0.0);
    draw_cube(1);
    glColor3ub(0, 255, 255);

    glTranslatef(0.0, -505.0, 0.0);
    draw_cube(0);
    glColor3b(0.0, 0.0, 0.0);
    draw_cube(1);
    glColor3ub(0, 255, 255);
    glPopMatrix();
}

void draw_player(float vspeed, float x, float y) {
    glPushMatrix();
    glTranslatef(x, y, -10.0);
    glRotatef(vspeed*100, 0.0, 0.0, 1.0);
    glColor3ub(0, 0, 0);
    glutWireTeapot(0.5);
    glColor3ub(0, 255, 180);
    glutSolidTeapot(0.5);
    glColor3ub(0, 255, 255);
    glPopMatrix();
}
