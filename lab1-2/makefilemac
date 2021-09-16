all :  lab1-2

lab1-2: lab1-2.c ../common/GL_utilities.c ../common/VectorUtils3.c ../common/LoadTGA.c ../common/LittleOBJLoader.c ../common/Mac/MicroGlut.m
	gcc -Wall -o lab1-2 -DGL_GLEXT_PROTOTYPES lab1-2.c ../common/GL_utilities.c ../common/VectorUtils3.c ../common/LoadTGA.c ../common/LittleOBJLoader.c ../common/Mac/MicroGlut.m -I../common -I../common/Mac -lm -framework OpenGL -framework Cocoa

clean :
	rm lab1-2

