# Contest24
This library provides useful tools for 24-hour programming competitions like
Marathon24, Deadline24 and others.

## Installing dependencies
This library has four dependencies:
* [SFML2.x](https://github.com/SFML/SFML) &ndash; Networking, visualization,
  event handling
* [SFGUI](https://github.com/TankOs/SFGUI) &ndash; User interface
* [Gflags](https://github.com/gflags/gflags) &ndash; Flags parsing
* [Glog](https://github.com/google/glog) &ndash; Logging

To install them, you can use your systems package manager. For example on
linux, you can install all of them but SFGUI by running:
<pre><code>$ sudo apt-get install libsfml-dev libgflags-dev libgoogle-glog-dev</code></pre>
Another possibility is to follow the instructions of individual libraries. You
can also compile them from source. You can find the sources in
<code>c24/extern/</code> and compile them with cmake. Go to the corresponding
directory of the library you want to install and run (on linux):
<pre><code>$ mkdir build && cd build
$ cmake ..
$ make
$ sudo make install
$ sudo ldconfig
</code></pre>
Make sure to install gflags before google-glog and SFML before SFGUI.

## Compiling
Make sure everything is installed properly by compiling the library together
with the provided examples. To compile this library you will need *cmake*
(or you can write your own Makefile or edit the one that is in
<code>templates/light/</code>).

Go to the project root directory and run:
<pre>
<code>$ mkdir build && cd build
$ cmake ..
$ make
</code></pre>

In the <code>build/bin/</code> directory you will find compiled examples. Try
to run <code>examples_tcp_server</code> and then (while the first binary is
still running) <code>examples_tcp_client</code> -- these programs should send
each other a message over TCP. You can also try the Candy Eaters example with
the visualizer by running:
<pre><code>$ ./candy_eaters_server --ports=5500,5600 --visualizer</code>
<code>$ ./candy_eaters --port=5500 --visualizer --toolbar</code></pre>

*Notice: In-source build is disabled (i.e. running <code>cmake .</code> in the
root directory), so you really need to create the build directory and run
<code>cmake ..</code> from there.*

## Using this library
When you are participating in 24-hour format contests you can write the code
for it on three different occasions.
* First there is code you can share between all these contests -- in this
  project this code lives under <code>c24/</code> subdirectory.
* Then there is code that you prepare before the contest itself, which is
  specific to this contest (implements the exact communication protocol, etc.).
  Examples of these can be found under <code>templates/</code> subdirectory.
* Finally there is code that you write on the contest itself. Such an example
  can be found under <code>examples/candy_eaters/</code>.

Here is a tutorial to get you started:
* [Quick start, a.k.a. from the template light to a working
  example](tutorials/QuickStart.md)
