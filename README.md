# Huaca

This project is part of Global Game Jam 2016 (a game creation contest) a game about an inca woman who must activate interrupters in the right order to complete the ritual and get to the next level of the temple. She can use keys to open doors and portals to get to said interrupters.


A Huaca (wak'a) is an object that represents something revered, typically a monument. Some of them have been associated with veneration and ritual. (Source Wikipedia : https://en.wikipedia.org/wiki/Huaca)

## Requirements

`Huaca` is written in C++11 so you need a C++11 compiler like [Clang](http://clang.llvm.org/) or [GCC](http://gcc.gnu.org/).

`Huaca` also needs external libraries:

* [SFML2](http://www.sfml-dev.org/)
* [Boost.Filesystem](http://www.boost.org/libs/filesystem/)


## Build and install

You can download the sources directly from github:

    git clone https://github.com/Hatunruna/huaca.git
Then you have to use [CMake](http://www.cmake.org/) to build the project:

    cd huaca
    mkdir build
    cd build
    cmake ..
    make

Finally, you can install the files (you may need root permissions):

    make install

## How to use

The best way to use this skel is to copy the game directory in your tree. Or to copy the whole skeleton.

## Authors

- Arthur Hugeat, arthur dot hugeat at univ dash fcomte dot fr
- Benjamin Goodwin, benjamin.d.goodwin@gmail.com
- Célia Dehors, celia.dehors@gmail.com
- Julien Bernard, julien dot bernard at univ dash fcomte dot fr
- Gérard Taiclet (Noctilucas),
- Roxanne Herbstmeyer,
- Sophie Teixeira.


## Copyright

This library is open source and is distributed under the [MIT license](http://opensource.org/licenses/MIT).
