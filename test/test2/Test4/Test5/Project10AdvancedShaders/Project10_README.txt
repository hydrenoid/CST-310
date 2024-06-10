Project10.cpp is a program that display a checkerboard with three different objects on it. Each object has a texture mapped onto it showing different pictures from the Humus website and two pictures procided by the assignment. This code was written by Connor Seimears and Ty Gehrke. To run correctly, openGL needs to be installed on your machine, along with assimp, soil, glew, and glfw.

To run the code, download the folder and use this command in the ubuntu terminal:

g++ -I include/ src/* -lglfw -lGL -lGLEW -lSOIL -lassimp && ./a.out

Make sure you are in the Project10 folder, which you can do with:

cd ~/Project10