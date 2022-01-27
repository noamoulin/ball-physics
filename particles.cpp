#include <math.h>
#include <iostream>

#include "vectors.cpp"

using namespace std;

class Particle {
    
public :

    float mass;
    float radius;
    float kinetic_energy;
    int id;
    Vect2D applied_forces;
    Vect2D velocity;
    Vect2D position;
    Vect2D acceleration;
    Vect2D kinetic_momentum;

    Particle(Vect2D pos0, Vect2D V0, float mass_, float radius, int id) {

        this->id = id;
        this->mass = mass_;
        this->radius = radius;
        this->velocity = V0;
        this->position = pos0;
        this->kinetic_momentum = velocity * mass;
        this->kinetic_energy = (mass*(velocity.magnitude()*velocity.magnitude()))/2;
        this->applied_forces = Vect2D(0.0f,0.0f);
        this->acceleration = applied_forces/mass_;
    }

    void applyForce(Vect2D force) {

        this->applied_forces += force;
    }

    void update(float dt) {

        this->acceleration = applied_forces/mass;
        this->velocity += acceleration*dt;
        this->position += velocity*dt;
        this->applied_forces = Vect2D(0.0f,0.0f);
    }

    bool operator!=(Particle &p2) {
        return (id != p2.id);
    }
};