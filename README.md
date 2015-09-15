# Contest24
This library provides useful tools for 24-hour programming competitions like
Marathon24, Deadline24 and others.

## Installing dependencies
This library has three dependencies:
* [SFML2.x](https://github.com/SFML/SFML) &ndash; Networking, visualization, event handling
* [Gflags](https://github.com/gflags/gflags) &ndash; Flags parsing
* [Glog](https://github.com/google/glog) &ndash; Logging

To install them, you can use your systems package manager. For example on linux, you can run:
<pre><code>sudo apt-get install libsfml-dev libgflags-dev libgoogle-glog-dev</code></pre>
Another possibility is to follow the instructions of individual libraries. You can also compile them from source. You can find the sources in <code>c24/extern/</code> and compile them with cmake. Go to the corresponding directory of the library you want to install and run:
<pre><code>$ mkdir build && cd build
$ cmake ..
$ make
$ sudo make install
</code></pre>
Make sure to install gflags before installing google-glog.

## Compiling
To compile this library you will need cmake.

After that you can just build using cmake (but not in the project root directory!).
From the root directory, run:
<pre>
<code>$ mkdir build && cd build
$ cmake ..
$ make
</code></pre>

In the <code>build/bin/</code> directory you will find compiled examples.

## Using this library
Comming soon...
