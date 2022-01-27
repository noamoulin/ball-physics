#include <math.h>

class Vect2D {

    public :

    float x;
    float y;

    Vect2D() = default;
    
    Vect2D(float x, float y) {
        this->x = x;
        this->y = y;
    }

    float magnitude(void) { // cf. ----------------
        return sqrtf(x*x+y*y); //                 |
    } //                                          v

    float dot(const Vect2D &vector) { //Ce serait mieux que ce soit l'espace qui gere le produit scalaire mais pour l'instant on ce contetera de cette implementation en depit des geometries exotiques.
        return vector.x*x + vector.y*y;
    }

    Vect2D operator+(const Vect2D &vector) {
        return Vect2D(vector.x+x,vector.y+y);
    }

    Vect2D operator-(const Vect2D &vector) {
        return Vect2D(x-vector.x,y-vector.y);
    }

    Vect2D operator*(const float scalaire) {
        return Vect2D(x*scalaire,y*scalaire);
    }

    Vect2D operator/(const float scalaire) {
        return Vect2D(x/scalaire,y/scalaire);
    }

    void operator+=(const Vect2D &vector) {
        this->x+=vector.x;
        this->y+=vector.y;
    }

    void operator-=(const Vect2D &vector) {
        this->x-=vector.x;
        this->y-=vector.y;
    }

    void operator*=(const float scalaire) {
        this->x*=scalaire;
        this->y*=scalaire;
    }

    void operator/=(const float scalaire) {
        this->x/=scalaire;
        this->y/=scalaire;
    }

    bool operator==(const Vect2D &vector) {
        return(x == vector.x && y == vector.y);
    }

    bool operator!=(const Vect2D &vector) {
        return(x != vector.x && y != vector.y);
    }
};