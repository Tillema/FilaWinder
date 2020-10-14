## FilaWinder calculations

_This firmware is written by Simon Tillema for a mechanism to spool filaments on empty rolls. You can use this firmware without any restriction, but note that using it is at your own risk. I do not take any responsibility for any harm caused by my code or the self-fabricated mechanism._

Let's first introduce a few variables:
- sf = Steps per revolution
- m = number of microsteps
- sr = steps per full rotation
- df = diameter of the filament
- db = diameter of the barrel
- n = layer number

### Calculations
>Depending on how much RAM the processor has, either straight or skewed windings could be used for calculating the distance. For a 1kg spool (1.75mm filament), the difference is roughly 2 meters or 5 grams.

#### Total length
Total length of 1 winding on the any layer (n) _without_ sideward displacement:

_**l=π(db+n\*df)**_

Total length of 1 winding on the any layer (n) _with_ sideward displacement:

_**l=√(df²+(π(db+n\*df))²)**_

#### Steps per mm
Steps for a full rotation:

_**sr=sm\*m**_

Distance per step on any layer (n) _without_ sideward displacement:

_**sr=π(db+n\*df))/(sm\*m)**_

Distance per step on any layer (n) _with_ sideward displacement:

_**sr=√(df²+(π(db+n\*df))²)/(sm*m)**_