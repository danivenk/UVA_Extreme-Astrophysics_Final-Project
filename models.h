// Dani van Enk, 11823526

#ifndef MODELS_H
#define MODELS_H

// used header
#include "obj_system.h"

// define a newtonian model
template<class T>
double newtonian_model(double t, double y, T *obj_C) {

    return -G * obj_C->get_massive_obj().get_mass() / std::pow(vect_size(
        obj_C->get_obj().get_pos_old(),
        obj_C->get_massive_obj().get_pos_old()), 2) * r_direction(
        obj_C->direction, obj_C->get_massive_obj().get_pos_old(),
        obj_C->get_obj().get_pos_old());
}

// define a post newtonian model
template<class T>
double post_newtonian_model(double t, double y, T *obj_C) {
    return -G * obj_C->get_massive_obj().get_mass() / (std::pow(c, 2) *
        std::pow(vect_size(obj_C->get_obj().get_pos_old(),
        obj_C->get_massive_obj().get_pos_old()), 3)) * (
        obj_C->get_obj().get_pos_old().at(obj_C->direction) * (std::pow(c, 2)
        - 4 * G * obj_C->get_massive_obj().get_mass()/vect_size(
        obj_C->get_obj().get_pos_old(), obj_C->get_massive_obj().get_pos_old())
        + std::pow(vect_size(obj_C->get_obj().get_vel_old()), 2)) - 4 *
        obj_C->get_obj().get_vel_old().at(obj_C->direction) * dot(
        obj_C->get_obj().get_vel_old(), obj_C->get_obj().get_pos_old()));
}

#endif