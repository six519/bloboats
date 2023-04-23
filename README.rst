Bloboats
========

A Game created by Markus Kettunen and was forked from https://salsa.debian.org/games-team/bloboats.
A few line of codes was updated to be able to compile the game successfully.

Building on FreeBSD 13.1
========================
::

    pkg install libvorbis sdl sdl_mixer sdl_image sdl_net
    make TARGET=FREEBSD
    make install

Building on Ubuntu 22.04 LTS
============================
::

    apt install libsdl1.2-dev libsdl-mixer1.2-dev libsdl-image1.2-dev libsdl-net1.2-dev libvorbis-dev
    make
    make install

Building on macOS
=================
::

    brew install libvorbis sdl12-compat sdl_image sdl_mixer sdl_net
    make TARGET=MACOSX
    make TARGET=MACOSX install

Building on Windows 10 (Cross-Compilation)
==========================================

Please install `Cygwin <https://www.cygwin.com/>`_ to cross-compile the code and make sure to install the following packages below:

* mingw64-i686-SDL
* mingw64-i686-SDL_image
* mingw64-i686-SDL_net
* mingw64-i686-SDL_mixer
* mingw64-i686-gcc-g++
* mingw64-i686-libvorbis 
* make

To build:

::

    make TARGET=CROSS

Screenshot
==========

.. image:: image1.png

.. image:: image2.png