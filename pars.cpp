// Dani van Enk, 11823526

// used header and libraries
#include "pars.h"
#include <iostream>
#include <string>

// define the initialization function
void Pars::init(char* filename) {

    // open the parameterfile
    ifs.open(filename, std::ifstream::in);

    // check if file could be opened
    if (!ifs) {

        // if not set object to corrupted and close file
        corrupted = true;
        ifs.close();
        return;
    }

    // declare parameter string
    std::string parameter;

    // set position parameter vectors to 0
    pos_center_obj.assign(DIM, 0);
    pos_satellite.assign(DIM, 0);
    pos_satellite2.assign(DIM, 0);

    // print file reading to commandline
    std::cout << "Reading Parameters from " << filename << std::endl;

    // readout paramters
    ifs >> parameter >> e;
    ifs >> parameter >> i;
    ifs >> parameter >> Omega;
    ifs >> parameter >> omega;
    ifs >> parameter >> distance;
    ifs >> parameter >> mass;
    ifs >> parameter;
    for (int i = 0; i < DIM; i++) {
        ifs >> pos_center_obj.at(i);
    }
    ifs >> parameter;
    for (int i = 0; i < DIM; i++) {
        ifs >> pos_satellite.at(i);
    }
    ifs >> parameter >> h;
    ifs >> parameter >> t_max;
    ifs >> parameter;
    for (int i = 0; i < DIM; i++) {
        ifs >> pos_satellite2.at(i);
    }
    ifs >> parameter >> vel_mult;

    // close file when done
    ifs.close();
}