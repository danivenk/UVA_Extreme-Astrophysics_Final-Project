// Dani van Enk, 11823526

#ifndef SYSTEM_H
#define SYSTEM_H

// used headers
#include "obj_stellar_obj.h"
#include "help_functions.h"
#include "runge_kutta.h"
#include "models.h"
#include "consts.h"

// define a system class which contains a massive object and a satellite object
class System {
    public:

        // define the class constructor
        System(Stellar_Obj obj, Stellar_Obj massive_obj):
            _obj(obj), _massive_obj(massive_obj) {};

    private:

        // declare the massive and satellite classes
        Stellar_Obj _obj;
        Stellar_Obj _massive_obj;

    public:
        // get the direction to evolve in
        int direction = 0;

    public:

        // massive and satellite class getters
        Stellar_Obj &get_obj() { return _obj; };
        Stellar_Obj &get_massive_obj() { return _massive_obj; };

        // evolve the system according to a model
        template<class T>
        void evolve(double t, double h, double (*model)(double, double, T*)) {

            // save the old position and velocity
            _obj.get_pos_old() = _obj.get_pos();
            _obj.get_vel_old() = _obj.get_vel();

            // loop over the dimensions
            for (int i = 0; i < DIM; i++) {
                
                // evolve the system and get the new position and velocity
                _obj.get_vel().at(i) = next<System>(
                    model, t, _obj.get_vel_old().at(i), h, this);
                _obj.get_pos().at(i) += _obj.get_vel().at(i) * h;

                // increase the system evolve direction
                direction++;
            }

            // reset it to 0
            direction = 0;
        }
};

#endif