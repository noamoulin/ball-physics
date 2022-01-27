
/********* LIBRARIES *********/

#include <time.h>
#include <math.h>
#include <GL/glut.h>

/********* SEIRARBIL *********/



#include "box.cpp" // <-- Box class



/********* WINDOW SETTINGS *********/

const float FRAME_RATE = 50.0f;
const float DT = 1.0f/50.0f;
const int WIDTH = 1000;
const int HEIGHT = 1000;

/********* SGNITTES WODNIW *********/



Box * box;(1.0f, 1.0f, 0.001f,0.0f); // <-- BOX

int dtpf = static_cast<int>(DT/box.dt);

void boxInit(void);


/********* ROUTINES *********/

void drawParticle(float, float, float);
void display(void);
void idle(int);
float adapt(float,float,float,float,float);

/******** SENITUOR *********/


/********* ENTRY POINT *********/

int main(int argc, char **argv) {

    boxInit();
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(WIDTH,HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Cosmic Marbles");
    glutDisplayFunc(display);
    glutTimerFunc(1000/FRAME_RATE,idle,0);

    glutMainLoop();

    return 0;
}

/********* TNIOP YRTNE *********/



/* ##################################### ROUTINES DEFINITIONS ##################################### */



void idle(int) {

    for(int i = 0; i < dtpf; i++) {
        box.update();
    }

    glutPostRedisplay();
    glutTimerFunc(1000/FRAME_RATE,idle,0);
}


void boxInit(void) {


    box.summonParticle(0.5f,0.5f,0.0f,0.0f, 10000000000.0f,0.05f);
    box.summonParticle(0.8f,0.5f,0.0f,0.5f, 100000000.0f,  0.01f);
    box.summonParticle(0.2f,0.5f,0.0f,-0.5f,100000000.0f,  0.01f);
    box.summonParticle(0.5f,0.8f,-0.5f,0.0f,10000000.0f,   0.01f);
    box.summonParticle(0.5f,0.2f,0.5f,0.0f, 1000000.0f,    0.01f);
    box.summonParticle(0.1f,0.1f,0.0f,0.0f, 1000000.0f,    0.01f);

}

float adapt(float x, float in_min, float in_max, float out_min, float out_max) { return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;}

void drawParticle(float radius, float x, float y) {

    float i = 0.0f;
    
    glBegin(GL_TRIANGLE_FAN);
    
    glVertex2f(x, y); // Center

    for(i = 0.0f; i <= 360; i++) {
        glVertex2f(radius*cos(M_PI * i / 180.0) + x, radius*sin(M_PI * i / 180.0) + y);
    }

    
    glEnd();
    glFlush();
}

void display(void) {

        /* ***** UPDATE THE WINDOW ***** */

        glClear(GL_COLOR_BUFFER_BIT);
    
        for(auto &particle : box.particles) {

            float wnpx = adapt(particle.position.x,0.0f,box.width,-1.0f,1.0f);
            float wnpy = adapt(particle.position.y,0.0f, box.width,-1.0f,1.0f);
            float wnpr = adapt(particle.radius,0.0f, box.width,0.0f, 2.0f);

            drawParticle(wnpr, wnpx, wnpy);
        }
        /* ***** WINDOW UPDATED ***** */
}