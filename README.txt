README
----

Daniel Moyer
203 901 770
dcmoyer@gmail.com

CS 174A Project 1

1. OS:

Mac OS X 10.8.5
Compiled using g++ i686-apple-darwin11-llvm-g++-4.2 (GCC) 4.2.1 (Based on Apple Inc. build 5658) (LLVM build 2336.11.00)

2.Code Structure
----------

All work was done in anim.cpp or the makefile. New functions include:

set_colour_special(float r, float g, float b, float a, float ambient, float diffuse, float specular )
drawWing()
drawWings()
drawLeg()
drawLegs()
drawBody()
drawBee()
drawGround()

Unused:

drawCompass()

The unused function, when called, draws 3 ellipsoids used for identifying cardinal directions in the original frame of reference.

To compile, type "make" in the cli in the directory. The output executable is B.exe. This has only been tested on my own personal computer.

3. Evaluation
---------

(a) 5/5 points (The bee and the tree/ground are not on the same hierarchy except at a very base level).
(b) 1/1 point
(c) 2/2 points (has more than 8 parts, assumably ok).
(d) 2/2 points
(e) 4/4 points
(f) 5/5 points (rotated in Y for placement, not actual animation)
(g) 3/3 points
(h) 2/2 points
