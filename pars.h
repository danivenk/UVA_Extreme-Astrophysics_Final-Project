// Dani van Enk, 118223526

#ifndef PARS_H
#define PARS_H

// used library and header
#include <fstream>
#include "consts.h"

// define a parameter class
class Pars {
    private:

        // parameter file infilestream
        std::ifstream ifs;

        // bool to see if file could be opened
        bool corrupted = false;

    public:

        // constructor and destructor for the parameter class
        Pars(char* filename){ init(filename); };
        ~Pars() { if(ifs) ifs.close(); };

        // declare parameters in this class
        double e; // eccentricity;
        double i; // inclination; i ∈ [0, 180]
        double Omega; // longitude of the ascending node; Ω ∈ [0, 360]
        double omega; // argument of periapsis; ω ∈ [0, 360]
        double distance; // distance to the BH from Earth (pc);
        double mass; // mass of center object (M_sun);
        std::vector<double> pos_center_obj; // position in arcsec;
        std::vector<double> pos_satellite; // position in arcsec;
        double h; // delta t in years;
        double t_max; // max t in years;
        std::vector<double> pos_satellite2; // 2nd position in arcsec for
                                            // velocity direction;
        double vel_mult; // velocity multiplier;

    private:

        // declare the initialization function
        void init(char* filename);

    public:

        // check if parameter file could be opened
        bool is_corrupted() { return corrupted; };
};

#endif