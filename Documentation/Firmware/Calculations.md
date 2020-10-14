## FilaWinder calculations

_This firmware is written by Simon Tillema for a mechanism to spool filaments on empty rolls. You can use this firmware without any restriction, but note that using it is at your own risk. I do not take any responsibility for any harm caused by my code or the self-fabricated mechanism._

Let's first introduce a few variables:
- $s_f$ = Steps per revolution
- $m$ = number of microsteps
- $s_r$ = steps per full rotation
- $d_f$ = diameter of the filament
- $d_b$ = diameter of the barrel
- $n$ = layer number

### Calculations
>Depending on how much RAM the processor has, either straight or skewed windings could be used for calculating the distance. For a 1kg spool (1.75mm filament), the difference is roughly 2 meters or 5 grams.

#### Total length
Total length of 1 winding on the any layer ($n$) _without_ sideward displacement:

<img src="https://latex.codecogs.com/gif.latex?l=\pi&space;(d_b&plus;nd_f)" title="l=\pi (d_b+nd_f)" />

Total length of 1 winding on the any layer ($n$) _with_ sideward displacement:

$l=\sqrt{d_n^2+(\pi(d_b+nd_f))^2}$

#### Steps per mm
Steps for a full rotation:

$s_r=s_mm$

Distance per step on any layer ($n$) _without_ sideward displacement:

$s_r=\frac{\pi(d_b+nd_f)}{s_mm}$

Distance per step on any layer ($n$) _with_ sideward displacement:

$s_r=\frac{\sqrt{d_n^2+(\pi(d_b+nd_f))^2})}{s_mm}$