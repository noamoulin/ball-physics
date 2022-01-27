#include <math.h>
#include <vector>
#include "particles.cpp"
#include <iostream>


class Box {

public : 
    
    float height;
    float width;
    float dt;
    int nb;
    float gravity;
    const float G = 6.6742e-11;
    std::vector <Particle> particles;
    
    Box(float width, float height, float dt,float gravity) {

        this->width = width;
        this->height = height;
        this->dt = dt;
        this->nb = 0;
        this->gravity = gravity;
    }

    void summonParticle(float x0, float y0, float v0x, float v0y, float mass_, float radius) {

        particles.push_back(Particle(Vect2D(x0,y0), Vect2D(v0x,v0y), mass_, radius, nb));
        nb++;
    }

    void applyAttractionForces(void) {

        for(auto &particle : particles) {
            for(auto &part : particles) {

                if(part != particle) { 

                    Vect2D AB = particle.position-part.position;
                    part.applyForce(Vect2D(AB/AB.magnitude())*(G*particle.mass*part.mass)/(particle.position-part.position).magnitude()*(particle.position-part.position).magnitude());
                }
            }
        }
    }

    void checkForCollisions(void) {

        for(auto &p1 : particles) {

            /* PROVISOIRE */ // il faudra definir une classe edge plus tard

            /*if(p1.position.x >= width) {
                p1.velocity.x*=-1.0f;
                p1.position.x = width-p1.radius;
            }

            if(p1.position.x <= 0.0f) {
                p1.velocity.x*=-1.0f;
                p1.position.x = p1.radius;
            }

            if(p1.position.y >= height) {
                p1.velocity.y*=-1.0f;
                p1.position.y=height-p1.radius
            }

            if(p1.position.y <= 0.0f) {
                p1.velocity.y*=-1.0f;
                p1.position.y = p1.radius;
            }*/

            for(auto &p2 : particles) { // A OPTIMISER POUR LIMITER LES INSTRUCTIONS

                if(p1 != p2) {

                    if((p2.position-p1.position).magnitude() < (p1.radius+p2.radius)) { // if collision 

                        // POSITION CORRECTION

                        Vect2D p1p2 = p2.position - p1.position; // A -> B

                        Vect2D correction = (p1p2/p1p2.magnitude()) * ((p1.radius+p2.radius)-p1p2.magnitude());

                        p1.position -= correction/2.0f;
                        p2.position += correction/2.0f;

                        // POSITION CORRECTED 

                        /* COLLISIONS INTER BILLES */

                        Vect2D normale = p1p2/p1p2.magnitude();
                        Vect2D tangente = Vect2D(normale.x,-normale.y);


                        float dptanp1 = tangente.dot(p1.velocity);
                        float dptanp2 = tangente.dot(p2.velocity);      
                                                                     // <--- produits scalaires.
                        float dpnorm1 = normale.dot(p1.velocity);
                        float dpnorm2 = normale.dot(p2.velocity);

                        float kmp1 = (dpnorm1 * (p1.mass - p2.mass) + 2.0f * p2.mass * dpnorm2) / (p1.mass + p2.mass);    // <--- moments cinetiques 
                        float kmp2 = (dpnorm2 * (p2.mass - p1.mass) + 2.0f * p1.mass * dpnorm1) / (p1.mass + p2.mass);    

                        float kx = (p1.velocity.x - p2.velocity.x);
                        float ky = (p1.velocity.y - p2.velocity.y);
                        float p = 2.0 * (normale.x * kx + normale.y * ky) / (p1.mass + p2.mass);

                        p1.velocity.x = p1.velocity.x - p * p2.mass * normale.x;
                        p1.velocity.y = p1.velocity.y - p * p2.mass * normale.y;
                        p2.velocity.x = p2.velocity.x + p * p1.mass * normale.x;
                        p2.velocity.y = p2.velocity.y + p * p1.mass * normale.y;
                    }
                }
            }
        }
    }

    void update() {

        applyAttractionForces();
        checkForCollisions();


        for(auto &particle : particles) {

            particle.applyForce(Vect2D(0.0f, gravity*particle.mass));
            particle.update(dt);
        }
    }
};