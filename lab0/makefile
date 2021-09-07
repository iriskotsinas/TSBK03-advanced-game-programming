all :  lab0

lab0: lab0.c ../common/GL_utilities.c ../common/VectorUtils3.c ../common/LoadTGA.c ../common/LittleOBJLoader.c ../common/Mac/MicroGlut.m
	gcc -Wall -o lab0 -DGL_GLEXT_PROTOTYPES lab0.c ../common/GL_utilities.c ../common/VectorUtils3.c ../common/LoadTGA.c ../common/LittleOBJLoader.c ../common/Mac/MicroGlut.m -I../common -I../common/Mac -lm -framework OpenGL -framework Cocoa

clean :
	rm lab0

