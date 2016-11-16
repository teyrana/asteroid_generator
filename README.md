Procedural Asteroid Terrain Generation Tool
-------

This code is a hobby project to procedure generate terrain. This module could fit into an asset
production pipeline for a video game or other graphical applications.


IO:
====
Terrain is generated from scratch, using internal code seeds, and output in .obj format 
(which can then be viewed in an external viewer, such as OBJ Viewer).  

Generation Methods:
====
Base terrain is either a rectangle or 3d spherical body, and any number of effects are then applied to this terrain in sequence.



Asteroid exmaple:
==== 
Start with a triangle mesh sphere for the base terrain.

Next, apply a simplex noise effect (modified so that opposite edges of the range can be wrapped on a spherical body.)

Next, a bombardment effect, which applies impact craters to the base mesh, resulting in a nice moon-like desolate wasteland.
