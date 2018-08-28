# Project: SDL_Config
# Makefile created by Dev-C++ 4.9.9.2

CPP  = E:\MinGW\bin\g++.exe
CC   = E:\MinGW\bin\gcc.exe
WINDRES = E:\MinGW\bin\windres.exe
RES  = 
OBJ  = ../bin/obj/SDL_config.o $(RES)
LINKOBJ  = ../bin/obj/SDL_config.o $(RES)
LIBS =   
INCS =  
CXXINCS =  -I"E:\Libs\SDL-1.2.11 - mingw\include"
BIN  = ../bin/SDL_Config.a
CXXFLAGS = $(CXXINCS) -fexpensive-optimizations -O3
CFLAGS = $(INCS)    
RM = rm -f


.PHONY: all all-before all-after clean clean-custom

all: ../bin/SDL_Config.a


clean:
	${RM} $(OBJ) $(BIN)

$(BIN): $(LINKOBJ)
	ar r $(BIN) $(LINKOBJ)
	ranlib $(BIN)

../bin/obj/SDL_config.o: SDL_config.c
	$(CPP) -c SDL_config.c -o ../bin/obj/SDL_config.o $(CXXFLAGS)
