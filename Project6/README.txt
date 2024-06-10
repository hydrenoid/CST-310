Jonathon Moore
CST-310
Professor Citro

Public GitHub Link: https://github.com/hydrenoid/CST-310

Objective:
The objective of this assignment is to implement shaders for different kinds of light, specifically specular lighting.

Files:
Project6.docx $ contains the report and analysis of the project as a whole.

main.cpp # source code for displaying the scene.

main # executable that runs the scene.


Environment:
These programs were developed using Parallels Desktop off a 2022 Macbook Pro M2, running Ubuntu 22.04.

For installation of the libraries these were the series of commands used:

--sudo apt-get install libfreetype-dev libfreetype6 libfreetype6-dev

Dependencies:
OpenGL 4.0
GLEW 2.2.0
GLFW
libdl
SOIL
freetype

Execution: 
First you must compile the source code using this command:
-- g++ -I/usr/include/freetype2 main.cpp glad.c -o main -lglfw -lGLU -lGL -ldl -lSOIL -lfreetype

Then you can run it like this:
./<name_of_executable>

