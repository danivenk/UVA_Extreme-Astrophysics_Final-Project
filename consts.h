// Dani van Enk, 11823526

#ifndef CONST_H
#define CONST_H

// used library
#include <vector>

// define pi
#define PI 3.14159265358979323846264338327950288

// dimensions and null_vector
static int DIM(3); // No. of dimensions
static std::vector<double> null_vect(DIM, 0);

// constants and conversion constants
static double G(6.67408E-11); // gravitational constant (m3kg-1s-2)
static double c(299792458); // light speed (m/s)
static double M_sun(1.98847E30); // solar mass (kg)
static double year(31556952); // year (s)
static double AU(1.496E11); // astronomical unit (m)
static double pc(3.08567758E16); // parsec (m)

#endif