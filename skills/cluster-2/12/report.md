# Skill Name

Author: Hussain Valiuddin
Date: 2020-10-08

---

## Summary

In this skill, we create a voltage monitor to find the voltage at a certain point. Due to the linmitation of the ESP to only read up to 3V, we use a voltage divider circuit to reduce the voltage at the ADC pin on the ESP to below 3V. The voltage divider we use has an R1 or 330Ohms and an R2 of 660Ohms to power down the V_source to below 3V.

## Sketches and Photos

![skill12](images/skill12.JPG)
![console](images/console.JPG)

## Modules, Tools, Source Used Including Attribution

https://github.com/espressif/esp-idf/tree/39f090a4f1dee4e325f8109d880bf3627034d839/examples/peripherals/adc

## Supporting Artifacts

https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/adc.html

---
