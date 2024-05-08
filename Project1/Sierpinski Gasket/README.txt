Jonathon Moore
CST-310
Professor Citro

Objective:
The objective of this assignment is to learn and understand basic use cases of 2D and 3D objects using OpenGL.Specifically this projects uses Sierpinskis Gasket and its relatables to connect coding knowledge with graphic display.

Files:
SierpinskiDocument.docx $ contains the report and analysis of the project as a whole.

SierpinskiTriangle2D.cpp # source code for displaying a 2D representation of a Sierpinski Triangle.
SierpinskiTriangle3D.cpp # source code for displaying a 3D representation of a Sierpinski Triangle.
KochSnowflake2D.cpp # source code for displaying a 2D representation of a Koch Snowflake.

SierpinskiTriangle2D # executable that runs the 2D triangle
SierpinskiTriangle3D # executable that runs the 3D triangle
KochSnowflake2D # executable that runs the koch snowflake

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
g++ -o <name_of_executable> <name_of_source_code>.cpp -lGLEW -lGL -lGLU -lglut

Then you can run it like this:
./<name_of_executable>

