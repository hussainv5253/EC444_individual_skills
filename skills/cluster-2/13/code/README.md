# Code Readme

The main folder contains skill13.c which needs to be flashed onto the ESP32. While in the code folder, run idf.py build and then idf.py flash monitor to get the output.

The skill13.c read the ADC value and converts it into a voltage. The voltage is used to calculate the resistence of the Thermistor using the voltage divider formula. The resistence is then converted into temperature using the second set of assignments to get the temperature. The temperature is then output to the console.
