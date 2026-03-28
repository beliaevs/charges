charges
=======

Build system of charges on a unit sphere that will be in static equilibrium.
It's so called [Thompson problem](https://en.wikipedia.org/wiki/Thomson_problem).

build
-----

Build app with cmake:

cmake -S . -B build

cd build

cmake --build . --config=release

run
---

charges.exe 10

The app will give answer for number of charges not greater than 300-400.

