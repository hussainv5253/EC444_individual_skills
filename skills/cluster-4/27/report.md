# State Models

Author: Hussain Valiuddin

## Date: 2020-11-13

## Summary

In this skill a FSM for a whack-a-mole game is created. There are 4 states in this FSM:
S0: Wait for user to enter start. If start is entered, start the game timer and move to S1.
S1: run raise one mole function which would randomly pop out a mole. Start timer and move to S2.
S2: If mole is hit, increase score and move back to S1. If the hit timer runs out, move to S1 without increasing score. If the game timer has run out, then move to S3.
S3: Display score and move back to S0.

## Sketches and Photos

## Modules, Tools, Source Used Including Attribution

## Supporting Artifacts

---
