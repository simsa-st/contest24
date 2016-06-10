# Contest24
This library provides useful tools for 24-hour programming competitions like
Marathon24, Deadline24 and others.

## Installing dependencies
This library has four dependencies:
* [SFML2.x](https://github.com/SFML/SFML) &ndash; Networking, visualization,
  event handling
* [SFGUI](https://github.com/TankOs/SFGUI) &ndash; User interface
* [Gflags](https://github.com/gflags/gflags) &ndash; Flags parsing
* [Easylogging++](https://github.com/easylogging/easyloggingpp) &ndash; Logging

You need to install just the first one, other three are in the project and are compiled together with this library (and `Easylogging++` is header only).

To install `SFML`, you can use your system package manager. For example on
ubuntu, you can run:
```bash
$ sudo apt-get install libsfml-dev
```

You can install `SFGUI` and `Gflags` as well, if you don't want to compile them with every new project. Just follow the instructions of the individual libraries.

## Compiling
Make sure everything is installed properly by compiling the library together
with the provided examples. To compile this library you will need *cmake*
(or you can write your own Makefile or edit the one that is in
`templates/light/`).

Go to the project root directory and run:
```bash
$ mkdir build && cd build
$ cmake ..
$ make
```

In the `build/bin/` directory you will find compiled examples. Try
to run `examples_tcp_server` and then (while the first binary is
still running) `examples_tcp_client` -- these programs should send
each other a message over TCP. You can also try the Candy Eaters example with
the visualizer by running:
```bash
$ ./candy_eaters_server --ports=5500,5600 --visualizer
$ ./candy_eaters --port=5500 --visualizer --toolbar
```

*Notice: In-source build is disabled (i.e. running `cmake .` in the
root directory), so you really need to create the build directory and run
`cmake ..` from there.*

## Using this library
When you are participating in 24-hour format contests you can write the code
for it on three different occasions.
* First there is code you can share between all these contests -- in this
  project this code lives under `c24/` subdirectory.
* Then there is code that you prepare before the contest itself, which is
  specific to this contest (implements the exact communication protocol, etc.).
  Examples of these can be found under `templates/` subdirectory.
* Finally there is code that you write on the contest itself. Such an example
  can be found under `examples/candy_eaters/`.

Here is a tutorial to get you started:
* [Quick start, a.k.a. from the template light to a working
  example](tutorials/QuickStart.md)
