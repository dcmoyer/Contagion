Prey Modifications:
--------

Unlink Kernels (gamma)


Predator ideas:
--------

Not 100% eff.
Lower with high density predator.

Follow distance weighted prey density instead of nearest neighbor
Velocity Alignment \[\frac{B(v^* - v)}{| v^* - v |}\]


Utility Functions:
--------

Change from Predator selection to:

\[ \int_t^T |v_{bar} - v|^2\]

and

\[|d - \min_j (d_j) |^2 + \frac{1}{d_{i,j}} \]

First is CS, second is Ber/D'Or. Select on this and remove a percentile.


Runtime length and Evo Parameters:
--------

Switch to max runtime.
Calculate runtime curve for LD50 (50% death time)