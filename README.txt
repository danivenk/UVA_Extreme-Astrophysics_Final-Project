This is the Gravitational Project solution for the Extreme Astrophysics course

xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
made by Dani van Enk 11823526
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

This solution contains a python script to plot and a C++ script to generate the datapoints from the Newtonian and Post-Newtonian models
To get the plots the C++ code needs to be compiled and the python file needs to be run (which in turn will try to run the compiled code)
For the C++ code 3 parameter datafiles are needed, with names formated as follows 〇〇〇_pars.dat
The observational data needed for the plots is in the files formated as 〇〇〇_data.dat
Once you are certain that there are 3 parameter files and 3 data files you can run the bash-script which will
compile the C++ code and run the python for the stars S2, S38 and S0-102/S55. In the bash-script you can also see the names as which the plots
will be saved as.

################################

The used libraries are:

    for python:
        sys
        os
        subprocess
        matplotlib

    for C++:
        <vector>
        <ctgmath>
        <fstream>
        <iostream>
        <string>

This project uses python3 (!)

################################

To run the bash script, make sure it is executable and run it using
    
    ./run.sh

 in the commandline.
If this won't work, you can also use the lines mentioned in the script as commandline commandos, which are
    
    g++ -o main -g *.cpp

 to compile the code and

    python main.py Newtonian_paper_values.png Post-Newtonian_paper_values.png S2 S38 S0-102/S55

to run the python code.

Once the code is running, it should mention that the parameter files are being read and once that's done,
 the Least Squares value for the newtonian (N) and post-newtonian (PN) should be printed. The code should have also created 2 plot images as
 well as the positional data with the filename formated as 〇〇〇_PN_pos.dat and 〇〇〇_N_pos.dat for
 the post-newtonian and newtonian models respectively

All the files and code should be put in the same directory. The files that will be generated will also be generated in the same location.

################################

A possible error will be that the positional data file can't be found, to fix this restart the terminal and make sure nothing else is
reading the directory and then rerun the script.

################################

The data in the observational data files is all in arcseconds, starting with an header.

The parameter files have the following parameters in this order:
    e - eccentricity
    i - inclination (degrees); is converted to rad in code; i ∈ [0, 180]
    Omega - longitude of the ascending node (degrees); is converted to rad in code; Ω ∈ [0, 360]
    omega - argument of periapsis (degrees); is converted to rad in code; ω ∈ [0, 360]
    distance - distance to source in parsec; is converted to meters in code
    mass - mass of source in M_sun; is converted to kg in code
    pos_center - start position of the center object in arcsec; is converted to meters in code
    pos_satellite - start position of the satellite object in arcsec; is converted to meters in code
    h - time step in years; is converted to seconds in code
    max_t - max time in years; is converted to seconds in code
    pos_satellite2 - second position of the satellite object in arcsec (used for direction of speed); is converted to meters in code
    vel_mult - speed multiplier constant to get better fit; has no physical meaning whatsoever

################################
