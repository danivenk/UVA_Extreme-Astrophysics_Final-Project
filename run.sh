#!/bin/bash
# Dani van Enk, 11823526

# compiles the model generator
g++ -o main -g *.cpp

# runs the plotting code
python main.py Newtonian_paper_values.png Post-Newtonian_paper_values.png S2 S38 S0-102/S55
