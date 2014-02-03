Prey Modifications:
--------

Unlink Kernels (gamma)


Predator ideas:
--------

Not 100% eff.
Lower with high density predator.

Follow distance weighted prey density instead of nearest neighbor
Velocity Alignment B(v^* - v)/| v^* - v |


Utility Functions:
--------

Change from Predator selection to:

\[ \int_t^T |v_bar - v|^2
|d - min_j (d_j) |^2 + \frac{1}{d_{i,j}} \]

Select on this and remove a percentile.


Runtime length and Evo Parameters:
--------

Switch to max runtime.
Calculate runtime curve for LD50 (50% death time)