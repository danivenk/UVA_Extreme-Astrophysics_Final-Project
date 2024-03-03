// Dani van Enk, 11823526

// used library and header
#include "obj_stellar_obj.h"
#include <iostream>

// define copy constructor
Stellar_Obj::Stellar_Obj(Stellar_Obj &other) {

    // check if the object to copy isn't this
    if (this == &other) {
        return;
    }

    // check if the dimensions of the vectors in object are the same
    if (other.get_pos().size() != DIM || other.get_vel().size() != DIM ||
            other.get_pos_old().size() != DIM ||
            other.get_vel_old().size() != DIM) {
        return;
    }

    // create a vector iterator
    std::vector<double>::iterator it;

    // copy over the vectors
    it = other.get_pos().begin();
    _pos.assign(it, other.get_pos().end());
    it = other.get_pos_old().begin();
    _pos_old.assign(it, other.get_pos_old().end());
    it = other.get_vel().begin();
    _vel.assign(it, other.get_vel().end());
    it = other.get_vel_old().begin();
    _vel_old.assign(it, other.get_vel_old().end());

    // copy over the mass
    _mass = other.get_mass();

}

// class initialization fucntion
void Stellar_Obj::init(std::vector<double> pos, std::vector<double> vel,
        double mass) {

    // check if the position and velocity vectors are the global dimension size
    if (pos.size() != DIM || vel.size() != DIM) {
            return;
    }

    // create a vector iterator
    std::vector<double>::iterator it;

    // set the vectors
    it = pos.begin();
    _pos.assign(it, pos.end());
    it = pos.begin();
    _pos_old.assign(it, pos.end());
    it = vel.begin();
    _vel.assign(it, vel.end());
    it = vel.begin();
    _vel_old.assign(it, vel.end());

    // set the mass
    _mass = mass;

}
