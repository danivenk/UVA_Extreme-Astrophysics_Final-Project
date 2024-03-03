// Dani van Enk, 11823526

#ifndef STELLAR_OBJ_H
#define STELLAR_OBJ_H

// used header
#include "consts.h"

// define a stellar object
class Stellar_Obj {
    public:

        // constructor and copoy constructor
        Stellar_Obj(std::vector<double> pos = null_vect,
            std::vector<double> vel = null_vect,
            double mass = 0) { init(pos, vel, mass); };
        Stellar_Obj(Stellar_Obj &other);

    private:

        // define the position velocity, both old vectors as well as the mass
        std::vector<double> _pos;
        std::vector<double> _pos_old;
        std::vector<double> _vel;
        std::vector<double> _vel_old;
        double _mass;

        // declare the initialization function
        void init(std::vector<double> pos, std::vector<double> vel,
            double mass);

    public:

        // vector getters and mass getter
        std::vector<double> &get_pos() { return _pos; };
        std::vector<double> &get_pos_old() { return _pos_old; };
        std::vector<double> &get_vel() { return _vel; };
        std::vector<double> &get_vel_old() { return _vel_old; };
        double get_mass() { return _mass; };
};

#endif
