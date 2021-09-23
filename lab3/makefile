# set this variable to the director in which you saved the common files
commondir = ../common/

all : lab3

lab3 : lab3.c $(commondir)GL_utilities.c $(commondir)VectorUtils3.c $(commondir)LittleOBJLoader.c $(commondir)LoadTGA.c $(commondir)Mac/MicroGlut.m
	gcc -Wall -o lab3 -I$(commondir) -I../common/Mac -DGL_GLEXT_PROTOTYPES lab3.c $(commondir)GL_utilities.c $(commondir)LittleOBJLoader.c $(commondir)VectorUtils3.c $(commondir)LoadTGA.c $(commondir)Mac/MicroGlut.m -lm -framework OpenGL -framework Cocoa

clean :
	rm lab3

