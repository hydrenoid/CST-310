Jonathon Moore
CST-310
Professor Citro

Public GitHub Link: https://github.com/hydrenoid/CST-310

Objective:
The objective of this assignment is to create a 3D animation.

Files:
Project8.docx $ contains the report and analysis of the project as a whole.

LorenzAttractor.cpp # source code for the animated cube.

lorenz_attractor # executable that runs the animation program.

Environment:
These programs were developed using Parallels Desktop off a 2022 Macbook Pro M2, running Ubuntu 22.04.

For installation of the libraries these were the series of commands used:

--sudo apt install libglu1-mesa-dev freeglut3-dev mesa-common-dev

--sudo apt install g++

--sudo apt install libglew-dev

Dependencies:
OpenGL 4.0
GLEW 2.2.0
freeglut 2.8.1-6

Execution: 
First you must compile the source code using this command:
g++ -o <name_of_executable> <name_of_source_code>.cpp -lglfw -lGLEW -lGL -lGLU

Then you can run it like this:
./<name_of_executable>

