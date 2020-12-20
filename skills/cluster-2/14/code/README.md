# Code Readme

The main folder contains skill14.c which needs to be flashed onto the ESP32. While in the code folder, run idf.py build and then idf.py flash monitor to get the output.

The skill14.c read the ADC value and converts it into a voltage. The voltage is used to calculate the distance using the conversion folrmula in the code. Then there is some calibration done to get more accurate values. The distance is then output to the console.
