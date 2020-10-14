# FilaWinder calculations

_This firmware is written by Simon Tillema for a mechanism to spool filaments on empty rolls. You can use this firmware without any restriction, but note that using it is at your own risk. I do not take any responsibility for any harm caused by my code or the self-fabricated mechanism._

Let's first introduce a few variables:
- ![](https://github.com/Tillema/FilaWinder/blob/master/Documentation/Firmware/EquationImages/sf.png?raw=true) = Steps per revolution
- ![](https://github.com/Tillema/FilaWinder/blob/master/Documentation/Firmware/EquationImages/m.png?raw=true) = number of microsteps
- ![](https://github.com/Tillema/FilaWinder/blob/master/Documentation/Firmware/EquationImages/sr.png?raw=true) = steps per full rotation
- ![](https://github.com/Tillema/FilaWinder/blob/master/Documentation/Firmware/EquationImages/df.png?raw=true) = diameter of the filament
- ![](https://github.com/Tillema/FilaWinder/blob/master/Documentation/Firmware/EquationImages/db.png?raw=true) = diameter of the barrel
- ![](https://github.com/Tillema/FilaWinder/blob/master/Documentation/Firmware/EquationImages/n.png?raw=true) = layer number

### Calculations
>Depending on how much RAM the processor has, either straight or skewed windings could be used for calculating the distance. For a 1kg spool (1.75mm filament), the difference is roughly 2 meters or 5 grams.

#### Total length
Total length of 1 winding on the any layer ($n$) _without_ sideward displacement:

![1](https://github.com/Tillema/FilaWinder/blob/master/Documentation/Firmware/EquationImages/eq1.png?raw=true)

Total length of 1 winding on the any layer ($n$) _with_ sideward displacement:

![2](https://github.com/Tillema/FilaWinder/blob/master/Documentation/Firmware/EquationImages/eq2.png?raw=true)

#### Steps per mm
Steps for a full rotation:

![3](https://github.com/Tillema/FilaWinder/blob/master/Documentation/Firmware/EquationImages/eq3.png?raw=true)

Distance per step on any layer ($n$) _without_ sideward displacement:

![4](https://github.com/Tillema/FilaWinder/blob/master/Documentation/Firmware/EquationImages/eq4.png?raw=true)

Distance per step on any layer ($n$) _with_ sideward displacement:

![5](https://github.com/Tillema/FilaWinder/blob/master/Documentation/Firmware/EquationImages/eq5.png?raw=true)
