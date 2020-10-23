This firmware is written by Simon Tillema for a mechanism to spool filaments on empty rolls. You can use this firmware without any restriction, but note that using it is at your own risk. I do not take any responsibility for any harm caused by my code or the self-fabricated mechanism.

# Calculation of step frequency
Given are the variable quantities 'winding speed', 'diameter at layer' and the fixed quantities 'number of steps per revolution'.

The total number of steps per revolutions can be calculated, if the motor steps and the microsteps are known, with the following formula:

***total_steps = motor_steps * microsteps***

In case the frequency is known, the number of revolutions per second can be calculated with:

***rotary_speed [rev/s] = frequency [1/s] / total_steps***

Given the diameter, the speed can be calculated with:

***winding_speed [mm/s] = diameter [mm] * pi * rotary_speed [rev/s]***

If the previous two formulas are substituted, the formula becomes:

***winding_speed [mm/s] = diameter [mm] * pi * frequency [rev/s] / total_steps***

Because the frequency is relevant to drive the stepper motor, this need to be converted:

***frequency [rev/s] = winding_speed [mm/s] * total_steps / (diameter [mm] * pi)***

The pulse interval is the inverse of the frequency, so, the formula can be inversed:

***interval [s] = diameter [mm] * pi / (winding_speed [mm/s] * total_steps)***