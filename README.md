# TclBattleBots

======================================================================
                  NMSU CS Virtual Battlebots
======================================================================

The spring 2002 programming contest is a virtual battlebots contest,
where each entry is a program that implements the behavior of a
virtual robot whose goal is to defeat another robot. All robots
must be programmed in Java, C, or C++, and must be 100% original
source code, other than being allowed to use standard libraries
included with the languages.

Robots operate over a simple stdin/stdout textual interface.
One important point is that every write by the robot to stdout should 
be followed by a flush operation (in C, an fflush(stdout) call).

The game is turn-based. Each robot gets a single turn in round
robin fashion, with a random choice of who goes first.

Each turn involves the game server sending two lines to the robot's
stdin, and the robot responding with two lines to stdout. Lines 
must end with a newline character, in C represented by a '\n'.

Battlebot Input
===============

The first input line per turn is the server telling the robot its
current state.

A robot has the following state:

 - position (x,y)
 - direction
 - velocity
 - remaining fuel
 - damage

This first line contains 7 positive integers (in textual form), in 
the order:

x y dir vel fuel damage damagetype

A robot is free to remember its own state, but since there are
outside influences (i.e., getting hit might change your direction),
the robot should read this state vector to find out what it is
currently doing before this turn. The damagetype flag is 0 if no
damage just occurred, 1 if damage is due to hitting a wall, 2 if
damage is due to hitting an object, 3 if damage is due to hitting
another battlebot, and 4 if damage is due to being fired upon.
(the damagetype flag is not yet implemented. It is currently always 0)

The second input line contains "0 no scan" if the previous turn did 
NOT issue a scan command OR if the scan detected no objects; otherwise,
if a scan was issued and it did detect an object, then this 
line has the scan results. A scan result lines looks like

1 <object-id> <pos-angle> <distance> <dir-angle> 

where <object-id> is the id of the object type (0=wall, 1=obstacle,
2=battlebot), <pos-angle> is the angle off center that the object is at 
in front of your robot. I.e., an angle of 0 means the scan indicates 
the object is directly in front of you, a negative angle is to the left
and a positive angle is to the right. <distance> is the distance the
object is away from you, and <dir-angle> is the direction the object
is facing (absolute, not relative to you). For obstacles, the <dir-angle>
is always 0, and for walls, all three parameters are 0. (We may try
to compute the distance and make that available). Only one object is
returned in the scan, and the priority order is: battlebots, obstacles,
and finally walls.

Battlebot Output
================

A robot produces two lines of output. The first contains two integers:

<direction-change> <speed-change>

These are positive and negative and indicate degrees of change in direction
and unit speed changes. Speed can only change +/- 1 or 2 units on each
turn (or 0). Any higher value will be capped at +/- 2. Direction can 
only change up to +/- 5 degrees, and higher values will be capped.
(I am not sure we cap them right now, but they will be)

The second line is a command line, consisting of one word: "none", "scan",
or "fire". They produce the corresponding action, and a scan produces
input on the next turn as described above. The fire command fires an
energy bolt in the current direction of travel. This bolt of energy has
a range of 100 units and covers a 5 degree arc, but it is more effective 
the shorter and more accurate the hit is. There is no feedback as to
whether or not a hit is accomplished. 

Battlebot Operation
===================

A battlebot uses fuel and incurs damage. The game ends when one battlebot
has incurred maximum damage. (currently it also ends when one runs out
of fuel, but maybe we should elminate that and just not allow it to scan
or fire).

Travelling a constant velocity does not use fuel, but changing speed
up or down does use 1 unit of fuel. Scans cost 1 unit of fuel, and 
firing an energy bolt costs 3 units.

Damage is incurred when a wall, obstacle, or battlebot is run in to.
Collisions like those incur a small (1 unit) amount of damage, but
they also cause the battle battlebot to bounce back and spin to a new
(random) direction.

All directions are measured in degrees, with 0 degrees being horizontally
right (or east). 

Robots start at a random position with a random (non-zero) velocity.
(we may change that to make them start with a 0 velocity).

Starting the System
===================

The "playbots" script is the game controller, and is a Tcl/Tk script.
Thus, it needs the command "wish" to be installed on your system in
order to run. Wish is standard with most Linux distributions, and is
on the NMSU CS machines as well (you have to do 
"source /local/config/cshrc.tcltk8.0" to get access to it). Both the
playbots script and a sample battlebot called "mostlyrandom" are
both text files, so feel free to look at them.

You can run a sample game with the command

      playbots -blue ./mostlyrandom -red ./mostlyrandom

Once you develop your own battlebot, replace one or both of the
"./mostlyrandom" with the path to your executable.

If you get an error such as "command not found", then either "wish"
or "tclsh" is not being found in your search path or on your machine.

