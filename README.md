# SmartAss IRC bot

This is an attempt to create an IRC bot, which can talk back to users when they mention it's name.

At the moment it's in a very early stage of development, and main focus is to adhere to the IRC-protocol and to implement some features here and there.

What language engine it'll interface is yet to be decided, but it has to be MIT-licensed (or similar to the MIT license) and written in C++, preferably modern C++.

Project homepage is [https://studiofreya.com/smartass](https://studiofreya.com/smartass).

## Building it

For the time being, only Visual Studio 2013 solution file is available. When the time is right, CMakeLists.txt will be added to enable building on Linux and similar systems.

Boost 1.58 is required, and it's expected to be placed in boost_1_58_0. Build Boost by running build_boost_1_58_vs2013.bat.