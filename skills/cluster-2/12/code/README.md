# Code Readme

The main folder contains skill12.c which needs to be flashed onto the ESP32. while in the code folder, run idf.py build and then idf.py flash monitor to get the output.

The skill12.c code contains i2c communication, alphanumeric display and ADC initiallization funtions.
The program runs 2 tasks simultaneously, one gets the voltage from the ADC and determines voltage source using the voltage divider formula.
The second task prints the voltage onto the alpha-numeric LED display
