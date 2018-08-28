# Project: 003
# Makefile created by Dev-C++ 4.9.9.2

CPP  = E:\Dev-Cpp\bin\g++.exe
CC   = gcc.exe
WINDRES = windres.exe
RES  = 
OBJ  = main.o $(RES)
LINKOBJ  = main.o $(RES)
LIBS =  -lmingw32 ../../bin/SDL_Config.a -lSDLmain -lSDL -mwindows
INCS =  
CXXINCS =  -I"E:\NewLibraries\SDL-1.2.11\include" -I"E:/SDL_Config/src" 
BIN  = ../../bin/test_003.exe
CXXFLAGS = $(CXXINCS)   -mwindows
CFLAGS = $(INCS)   
RM = rm -f

.PHONY: all all-before all-after clean clean-custom

all: ../../bin/test_003.exe


clean: 
	${RM} $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CPP) $(LINKOBJ) -o "..\..\bin\test_003.exe" $(LIBS)

main.o: main.cpp
	$(CPP) -c main.cpp -o main.o $(CXXFLAGS)
