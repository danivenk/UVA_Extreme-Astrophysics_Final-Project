#!/usr/bin/env python
"""
Dani van Enk, 11823526
"""

# used libraries
import sys
import os
import subprocess as sp
from matplotlib import pyplot as plt

class Model_DataFile:
    """
    model datafile class;

    reads a model datafile and prepairs it for plotting;

    parameters:
        file - file to read from;
    """

    def __init__(self, file):

        # define data list and corrupted bool
        self.data_ = []
        self.corrupted = False

        # try to open file
        try:
        
            # open file
            with open(os.path.abspath(file)) as file:

                # read dimension from file
                self.DIM = int(file.readline().split(" ")[1])

                # read BH data from file
                if file.readline() == "BH_DATA\n":

                    # save BH position
                    self.BH_pos = file.readline().split(" ")

                    # loop over the position elements to make them floats
                    for i in range(len(self.BH_pos)):
                        self.BH_pos[i] = float(self.BH_pos[i])

                # read evolution data
                if file.readline() == "EVOLUTION_DATA\n":

                    # loop over all lines
                    while True:

                        # read line
                        line = file.readline()

                        # once at the end of the file stop
                        if not line:
                            break

                        # save data to object
                        self.data_.append(line.split(" "))

        # if file could not be read print error and set object to corrupted
        except FileNotFoundError:
            print(f"FileNotFoundError: {file}")
            self.corrupted = True
            return
        
        # define ordered data dict and pointdata list
        self.data = {"t": [], "x": [], "y": [], "z": []}
        self.pointdata = []

        # loop over all the data
        for j, row in enumerate(self.data_):

            # add the time to the data dict as float
            self.data["t"].append(float(row[0]))

            # add the x-pos to the data dict as float
            if self.DIM >= 1:
                self.data["x"].append(float(row[1]))

            # add the y-pos to the data dict as float
            if self.DIM >= 2:
                self.data["y"].append(float(row[2]))

            # add the z-pos to the data dict as float
            if self.DIM >= 3:
                self.data["z"].append(float(row[3]))

            # add a list to pointdata
            self.pointdata.append([])

            # loop over the items in a row and add position vector to pointdata
            for i in range(len(row)):
                if i != 0:
                    self.pointdata[j].append(float(row[i]))
                    

class Observation_DataFile:
    """
    observation datafile;

    reads out the observation data and prepairs it for plotting;

    parameters:
        file - file to read from;
    """

    def __init__(self, file):

        # define data list and corrupted bool
        self.data_ = []
        self.corrupted = False

        # try to open file
        try:
        
            # open file
            with open(os.path.abspath(file)) as file:

                # read & save headers
                self.headers = file.readline().split(" ")

                # loop over all the lines
                while True:

                    # read line
                    line = file.readline()

                    # once at end of file stop
                    if not line:
                        break

                    # save data to object
                    self.data_.append(line.split(" "))

        # if file could not be read print error and set object to corrupted
        except FileNotFoundError:
            print(f"FileNotFoundError: {file}")
            self.corrupted = True
            return
        
        # define data dict and pointdata list
        self.data = {header: [] for header in self.headers}
        self.pointdata = []

        # loop over the data
        for j, row in enumerate(self.data_):

            # add list to pointdata
            self.pointdata.append([])

            # loop over the elements in a row
            for i, header in enumerate(self.headers):

                # add data to the data dict as a float
                self.data[header].append(float(row[i]))

                # add the points as vectors to the pointdata
                if "err" not in header and i != 0:
                    self.pointdata[j].append(float(row[i]))
                

def main(argv):
    """
    mainfunction

    parameters:
        argv - commandline arguments;
    """

    # make sure that the arguments at least have one object and both filenames
    if len(argv) < 4:
        print(f"Usage python {argv[0]} <newtonian-filename> "
              "<post-newtonian-filename> <object>")
        return

    # define the colors and legend list
    colors = ["red", "blue", "green"]
    legend = []

    # create 2 figures
    fig_N = plt.figure(1)
    fig_PN = plt.figure(2)

    # loop over the objects
    for i in range(3, len(argv)):
    
        # add object name to legend
        legend.append(argv[i])
        
        # change slash to .. for the files
        if "/" in argv[i]:
            argv[i] = argv[i].replace("/", "..")

        # run the model generation code (Newtonian)
        code_N = sp.run(["./main", f"{argv[i]}_N_pos.dat",
                         f"{argv[i]}_pars.dat"], capture_output=True,
                        text=True)

        # print out the commandline output and errors
        print(code_N.stdout, end="")
        print(code_N.stderr, end="")

        # run the model generation code (Post-Newtonian)
        code_PN = sp.run(["./main", f"{argv[i]}_PN_pos.dat",
                          f"{argv[i]}_pars.dat", "post_newtonian"],
                         capture_output=True, text=True)

        # print out the commandline output and errors
        print(code_PN.stdout, end="")
        print(code_PN.stderr, end="")

        # make sure the files are created
        if code_N.returncode == 5 or code_PN.returncode == 5:
            continue

        # create objects form the positional data and observational data
        datafile1 = Model_DataFile(f"{argv[i]}_N_pos.dat")
        datafile2 = Model_DataFile(f"{argv[i]}_PN_pos.dat")
        obsfile = Observation_DataFile(f"{argv[i]}_data.dat")

        # print the least squares fit for both models
        print(f"{legend[i - 3]}-N: R^2 = "
              f"{least_sq(obsfile.pointdata, datafile1.pointdata)}")
        print(f"{legend[i - 3]}-PN: R^2 = "
              f"{least_sq(obsfile.pointdata, datafile2.pointdata)}")

        # plot the data if not corrupted to their respective figures
        if not datafile1.corrupted:
            fig_N.gca().plot(datafile1.BH_pos[0], datafile1.BH_pos[1], "ko")
            fig_N.gca().plot(datafile1.data["x"], datafile1.data["y"],
                             color=colors[i - 3], linestyle="-", linewidth=1,
                             label=legend[i - 3])
        if not datafile2.corrupted:
            fig_PN.gca().plot(datafile2.BH_pos[0], datafile2.BH_pos[1], "ko")
            fig_PN.gca().plot(datafile2.data["x"], datafile2.data["y"],
                              color=colors[i - 3], linestyle="-", linewidth=1,
                              label=legend[i - 3])
        if not obsfile.corrupted:
            fig_N.gca().errorbar(obsfile.data[obsfile.headers[1]],
                                 obsfile.data[obsfile.headers[2]],
                                 xerr=obsfile.data[obsfile.headers[3]],
                                 yerr=obsfile.data[obsfile.headers[4]],
                                 fmt="None", ecolor="black", elinewidth=.5)
            fig_PN.gca().errorbar(obsfile.data[obsfile.headers[1]],
                                  obsfile.data[obsfile.headers[2]],
                                  xerr=obsfile.data[obsfile.headers[3]],
                                  yerr=obsfile.data[obsfile.headers[4]],
                                  fmt="None", ecolor="black", elinewidth=.5)
            fig_N.gca().plot(obsfile.data[obsfile.headers[1]],
                             obsfile.data[obsfile.headers[2]], marker="o",
                             linestyle="none", markersize=3,
                             color=colors[i - 3])
            fig_PN.gca().plot(obsfile.data[obsfile.headers[1]],
                              obsfile.data[obsfile.headers[2]], marker="o",
                              linestyle="none", markersize=3,
                              color=colors[i - 3])

    # set the title, labels, legend and aspect ratio of the figures
    fig_N.gca().set_title("Newtonian model around Sag A*")
    fig_PN.gca().set_title("Post-Newtonian model around Sag A*")
    fig_N.gca().set_xlabel("ΔR.A.(\")")
    fig_PN.gca().set_xlabel("ΔR.A.(\")")
    fig_N.gca().set_ylabel("ΔDec.(\")")
    fig_PN.gca().set_ylabel("ΔDec.(\")")
    fig_N.gca().legend()
    fig_PN.gca().legend()
    fig_N.gca().invert_xaxis()
    fig_PN.gca().invert_xaxis()
    fig_N.gca().set_aspect("equal")
    fig_PN.gca().set_aspect("equal")

    # save the figures as files
    fig_N.savefig(argv[1])
    fig_PN.savefig(argv[2])


def distance(r1, r2):
    """
    calculate the distance between two points;

    parameters:
        r1 - point 1;
        r2 - point 2;

    return the shortest distance
    """

    # make sure both points are the same dimensions
    assert len(r1) == len(r2)

    # set the length to 0
    length = 0

    # loop over the points and add their square elements
    for i in range(len(r1)):
        length += abs(r1[i] - r2[i])**2

    return length**(1/2)


def find_shortest_distance(r, data):
    """
    find the shortest distance from point to data;

    parameters:
        r       - point to find closest distance to;
        data    - data to compare distances to;

    returns the shortest distance and the points between it is
    """

    # define empty lengths list
    lengths = []

    # loop over the data
    for point in data:

        # add distance and points the distance is caluclated for to the list
        lengths.append((distance(r, point[:2]), r, point[:2]))

    return sorted(lengths, key=lambda x: x[0])[0]


def least_sq(obsdata, modeldata):
    """
    find the least squares between observational data and model data;

    parameters:
        obsdata     - observational data;
        modeldata   - model data;

    returns the least squares
    """
    
    # set the total to 0
    tot = 0

    # loop over the observational data
    for point in obsdata:

        # find the shortest distance
        find = find_shortest_distance(point, modeldata)

        # set area to 1
        area = 1

        # find the rectangle area between the data and model
        for i in range(len(find[1])):
            area *= abs(find[1][i] - find[2][i])

        # add to the total
        tot += area
    
    return tot


if __name__ == "__main__":
    main(sys.argv)