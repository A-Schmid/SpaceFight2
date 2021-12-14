# SpaceFight2

## History

When I learned programming back in the days, I often implemented small 2D games to learn new graphics frameworks.
*SpaceFight* is a game I have written about four times.
This here is version 2 written in C++ and SDL using DevC++.
This version dates back to august 2010 when I was 17 years old.
I updated it slightly to compile with a modern GCC.
A simple *make* should build it on Linux, for Windows there are binaries in *windows/SF2.zip*.

![Space Fight Main Menu](doc/SF_menu.png "Space Fight Main Menu")

## Gameplay

Two space ships face each other.
Each player has to shoot its enemy until their lives drop to zero.
Ammunition is limited, but new weapons, as well as buffs (e.g. for healing) spawn on the battlefield.
You may enter your enemy's side, but you will lose life over time.

![Space Fight Gameplay](doc/SF_gameplay.png "Space Fight Gameplay")

### Controls

Left player: WASD to move, Space to shoot

Right player: Arrow keys to move, numpad 0 to shoot

### Muliplayer

Yes, you can play *SpaceFight 2* over the network.
The host has to choose to start the game as a server.
The client has to enter the host's IP in 'config.txt' and start the game as a client.

## Wait, what about SpaceFight 1?

The code of the original SpaceFight game (from december 2008) can be found in the "archive_SpaceFight_1" directory.
I did not touch anything and can't compile it on Linux due to Win32 dependencies.
However, there is an exe file that kind of works with Wine, however in my case the background is white and the window is too big.
You can also see my innovative workaround to not having heard of version control as there are like 12 copies of the source code.

## Acknowledgements

The code might still contain some snippets from C++ tutorials found all over the internet.
Special thanks to [Lazy Foo](https://lazyfoo.net/tutorials/SDL/) and [NeHe](https://nehe.gamedev.net/) who taught me like everything.
