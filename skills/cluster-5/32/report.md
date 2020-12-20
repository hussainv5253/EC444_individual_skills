# Skill Name: Speed Sensor

Author: Hussain Valiuddin

## Date: 2020-12-01

## Summary

The sensor was wired according to the arduino guide. The data is read as analog and read through pin A3. The encoder image was printed and stuck to the inside of the wheel using tape and the sensor was kept close to it. The sensor utputs a distict voltage when looking at black or white parts of the encoder, and I used 2500 as the middle value between them. This code counted the number of times a unique black reading was measured. black reading was measured if the voltage was above 2500mV and that the reading before it was white i.e below 2500mV.

We know that there are 6 black sections in one rotation. We count the number of black sections measured during 1 second, divide by 6 to find the number of rotations and using the circumference of the wheel that is 24cm, the speed is calulated by ufinding the distance travveled in 1 second.

## Sketches and Photos

![decoder](./images/board.JPG)
![sensor](./images/board.JPG)

## Modules, Tools, Source Used Including Attribution

## Supporting Artifacts

---
