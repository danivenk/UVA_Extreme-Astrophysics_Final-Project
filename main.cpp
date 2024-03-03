// Dani van Enk, 11823526

// used headers and library
#include <iostream>
#include "obj_system.h"
#include "pars.h"

// declare streaming function
template<typename T>
std::ostream &operator<<(std::ostream &os, std::vector<T> vect);

// define the main function with commandline arguments
int main(int argc, char* argv[]) {

    // check if the arguments given are the numeber wanted
    if (argc < 3 && argc > 4) {
        std::cout << argv[0] << " <datafile> <parameters file> "
            "<post_newtonian>" << std::endl;
        return 3;
    }

    // create parameter object from file
    Pars p(argv[2]);

    // check if parameterfile has been read correctly
    if (p.is_corrupted()) {
        std::cout << "FileReadError: " << argv[2] << std::endl;
        return 5;
    }

    // create an out filestream
    std::ofstream ofs(argv[1]);

    // check if the filestream has been created correctly
    if (!ofs.is_open()) {
        ofs.close();
        return 10;
    }

    // readout eccentricty, distance and orbital angles from parameter object
    double e(p.e); // eccentricity;
    double inclination(p.i * PI/180); // inclination; i ∈ [0, PI]
    double Omega(p.Omega * PI/180); // longitude of the ascending node;
                                    //  Ω ∈ [0, 2PI]
    double omega(p.omega * PI/180); // argument of periapsis; ω ∈ [0, 2PI]
    double distance(p.distance * pc); // distance to the BH from Earth;

    // create the center object
    Stellar_Obj BH(to_pos(distance, p.pos_center_obj, true), null_vect,
        p.mass * M_sun);

    // write Dimenson and blackhole data to file
    ofs << "DIM " << DIM << std::endl;
    ofs << "BH_DATA" << std::endl;
    ofs << BH.get_pos() << std::endl;

    // get the postion of the satellite object and its direction for speed
    std::vector<double> pos = to_pos(distance, p.pos_satellite, true);
    std::vector<double> pos2 = to_pos(distance, p.pos_satellite2, true);

    // transform position vectors to orbital alignment
    pos = rotate(2, -omega, rotate(0, -inclination, rotate(2, -Omega, pos)));
    pos2 = rotate(2, -omega, rotate(0, -inclination, rotate(2, -Omega, pos2)));

    // declare a velocity vector
    std::vector<double> vel(DIM, 0);

    // set speed to orbital speed in the direction of pos2
    for (int i = 0; i < DIM; i++) {
        vel.at(i) = orbital_speed(BH.get_mass(), vect_size(pos), e)
            * direction(i, pos2, pos);
            // * phi_direction(i, pos, null_vect);

        // this doesn't really make sense but somehow did gave me some
        //  elliptical orbits, conclusion: something's still wrong with the
        //  orbital allignment. At all 0 it works but not at the given angles
        // lets call it a correction constant to get a better fitting orbit
        vel.at(i) *= p.vel_mult;
    }

    // define the satellite object
    Stellar_Obj Star(pos, vel);

    // create a system of the center object and the satellite object
    System S1(Star, BH);

    // begin writing positional data to file
    ofs << "EVOLUTION_DATA" << std::endl;

    // set the start time and timesteps
    double t = 0;
    double h = p.h * year;

    // loop until the max time is reached
    while (t < p.t_max * year) {

        // rotate the positions to the sky plane and convert to angles
        pos = rotate(2, Omega, rotate(0, inclination, rotate(2, omega, S1.get_obj().get_pos_old())));
        pos = to_angle(distance, pos, true);

        // write time and position to file
        ofs << t << " " << pos << std::endl;

        // evolve system accorting to newtonian unless specified by arguments
        if (argv[3]) {
            S1.evolve<System>(t, h, post_newtonian_model);
        } else {
            S1.evolve<System>(t, h, newtonian_model);
        }

        // do a timestep
        t += h;
    }

    // close file
    ofs.close();

    return 0;
}

// define streaming operator for vectors
template<typename T>
std::ostream &operator<<(std::ostream &os, std::vector<T> vect) {

    // loop over the vectors and print the elements to the
    //  steam with spaces in between
    for (int i = 0; i < vect.size(); i++) {
        os << vect.at(i);
        if (i != vect.size() - 1) {
            os << " ";
        }
    }

    return os;
}