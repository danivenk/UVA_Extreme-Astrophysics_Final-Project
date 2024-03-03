// Dani van Enk, 11823526

#ifndef HELP_H
#define HELP_H

// used libraries and header
#include <ctgmath>
#include "consts.h"

// gives the size of the vector drawn from r1 to r2
double vect_size(std::vector<double> r1, std::vector<double> r2=null_vect) {

    // check both vectors are the same size
    if (r1.size() != r2.size()) {
        throw (r1, r2);
    }

    // set size to 0
    double size = 0;

    // loop over the vectors and add their square differences
    for (int i = 0; i < r1.size(); i++) {
        size += std::pow(std::abs(r1.at(i) - r2.at(i)), 2);
    }

    return std::sqrt(size);
};

// give the r_direction component in one of
//  the cartesian directions (0=x, 1=y, 2=z) for the vector between r1 and r2
double r_direction(int dimension, std::vector<double> r1,
        std::vector<double> r2) {

    // check both vectors are the same size
    if (r1.size() != r2.size()) {
        throw(r1, r2);
    }

    // declare theta
    double theta;
    
    // get the theta angle
    switch (DIM) {
        case 3:
            theta = std::acos((r2.at(2) - r1.at(2)) / vect_size(r1, r2));
            break;
        default:
            theta = std::acos(0 / vect_size(r1, r2));
            break;
    }

    // define the phi angle
    double phi = std::atan2((r2.at(1) - r1.at(1)), (r2.at(0) - r1.at(0)));

    // return the r direction vector elements
    switch (dimension) {
        case 0:
            return std::sin(theta) * std::cos(phi);
        case 1:
            return std::sin(theta) * std::sin(phi);
        case 2:
            return std::cos(theta);
        default:
            return 0;
    }
};

// give the phi_direction component in one of
//  the cartesian directions (0=x, 1=y, 2=z) for the vector between r1 and r2
double phi_direction(int dimension, std::vector<double> r1,
        std::vector<double> r2) {

    // check both vectors are the same size
    if (r1.size() != r2.size()) {
        throw(r1, r2);
    }

    // declare theta
    double theta;

    // get the theta angle
    switch (DIM) {
    case 3:
        theta = std::acos((r2.at(2) - r1.at(2)) / vect_size(r1, r2));
        break;
    default:
        theta = std::acos(0 / vect_size(r1, r2));
        break;
    }

    // get the phi angle
    double phi = std::atan2((r2.at(1) - r1.at(1)), (r2.at(0) - r1.at(0)));

    // return the phi direction vector elements
    switch (dimension) {
    case 0:
        return -std::sin(phi);
    case 1:
        return std::cos(phi);
    default:
        return 0;
    }
};

// find the direction of the vector spanning 2 points in
//  direction (x=0, y=1, z=2)
double direction(int dimension, std::vector<double> r1,
    std::vector<double> r2) {
    
    // check both vectors are the same size
    if (r1.size() != r2.size()) {
        throw(r1, r2);
    }

    return (r1.at(dimension) - r2.at(dimension))/vect_size(r1, r2);
};

// rotate a vector in direction (x=0, y=1 z=2) with an angle
std::vector<double> rotate(int direction, double angle, std::vector<double> x) {

    // define a new vector
    std::vector<double> new_(DIM, 0);

    // define the rotation matrices
    switch (direction) {
        case 0:
            new_.at(0) = DIM == 3 ? x.at(0) : 0;
            new_.at(1) = DIM == 3 ? std::cos(angle) * x.at(1) - std::sin(angle)
                * x.at(2) : 0;
            new_.at(2) = DIM == 3 ? std::sin(angle) * x.at(1) + std::cos(angle)
                * x.at(2) : 0;
            break;
        case 1:
            new_.at(0) = DIM == 3 ? std::cos(angle) * x.at(0) + std::sin(angle)
                * x.at(2) : 0;
            new_.at(1) = DIM == 3 ? x.at(1) : 0;
            new_.at(2) = DIM == 3 ? -std::sin(angle) * x.at(0) +
                std::cos(angle) * x.at(2) : 0;
            break;
        case 2:
            new_.at(0) = DIM == 3 ? std::cos(angle) * x.at(0) - std::sin(angle)
                * x.at(1) : 0;
            new_.at(1) = DIM == 3 ? std::sin(angle) * x.at(0) + std::cos(angle)
                * x.at(1) : 0;
            new_.at(2) = DIM == 3 ? x.at(2) : 0;
            break;
        default:
            return null_vect;
    }

    return new_;
};

// find the orbital speed for an elliptical orbit
double orbital_speed(double M, double R, double e) {
    return std::sqrt(G * M * (2 - (1 - e))/R);
};

// get the sky angle from the position and the distance to the source,
//  convert to arcsec (default false)
std::vector<double> to_angle(double distance, std::vector<double> x,
        bool to_arcsec=false) {

    // define the new vector
    std::vector<double> new_(DIM, 0);

    // loop over the vector elements
    for (int i = 0; i < DIM; i++) {

        // convert to the angle
        new_.at(i) = 2 * x.at(i) / distance;

        // convert to arcsec if defined
        if (to_arcsec) {
            new_.at(i) *= 3600;
        }
    }

    return new_;
}

// convert sky angle to position with the distance,
//  convert from arcsec (default false)
std::vector<double> to_pos(double distance, std::vector<double> x,
        bool from_arcsec = false) {

    // define new vector
    std::vector<double> new_(DIM, 0);

    // loop over vector elements
    for (int i = 0; i < DIM; i++) {

        // convert from arcsec if defined
        if (from_arcsec) {
            x.at(i) /= 3600;
        }

        // convert angle to position
        new_.at(i) = x.at(i) * distance / 2;
    }

    return new_;
}

// calculate the dot product between two vectors
double dot(std::vector<double> r1, std::vector<double> r2) {
    
    // check both vectors are the same size
    if (r1.size() != r2.size()) {
        throw(r1, r2);
    }

    // define tot to 0
    double tot = 0;

    // loop over the vector elements to calculate the dot product
    for (int i = 0; i < DIM; i++) {
        tot += r1.at(i) * r2.at(i);
    }

    return tot;
}

#endif
