# Project: 003
# Makefile created by Dev-C++ 4.9.9.2

CPP  = E:\Dev-Cpp\bin\g++.exe
CC   = gcc.exe
WINDRES = windres.exe
RES  = 
OBJ  = main.o $(RES)
LINKOBJ  = main.o $(RES)
LIBS      = -L"E:/Dev-Cpp/Lib" -lmingw32 "E:\Libs\SDL-1.2.11 - mingw\lib\libSDL.dll.a" "E:\Libs\SDL-1.2.11 - mingw\lib\libSDLmain.a"  ../../bin/SDL_Config.a  -mwindows 
INCS =  
CXXINCS   = -I"E:/Dev-Cpp/lib/gcc/mingw32/3.4.2/include" -I"E:/Dev-Cpp/include/c++/3.4.2/backward" -I"E:/Dev-Cpp/include/c++/3.4.2/mingw32" -I"E:/Dev-Cpp/include/c++/3.4.2" -I"E:/Dev-Cpp/include" -I"E:/Dev-Cpp/" -I"E:/Dev-Cpp/include/common/wx/msw" -I"E:/Dev-Cpp/include/common/wx/generic" -I"E:/Dev-Cpp/include/common/wx/fl" -I"E:/Dev-Cpp/include/common/wx/gizmos" -I"E:/Dev-Cpp/include/common/wx/html" -I"E:/Dev-Cpp/include/common/wx/mmedia" -I"E:/Dev-Cpp/include/common/wx/net" -I"E:/Dev-Cpp/include/common/wx/ogl" -I"E:/Dev-Cpp/include/common/wx/plot" -I"E:/Dev-Cpp/include/common/wx/protocol" -I"E:/Dev-Cpp/include/common/wx/stc" -I"E:/Dev-Cpp/include/common/wx/svg" -I"E:/Dev-Cpp/include/common/wx/xml" -I"E:/Dev-Cpp/include/common/wx/xrc" -I"E:/Dev-Cpp/include/common/wx" -I"E:/Dev-Cpp/include/common" -I"E:/Libs/SDL-1.2.11 - mingw/include" -I"E:/Projects/SDL_Config/src"
RCINCS    = --include-dir "E:/Dev-Cpp/include/common"
BIN  = ../../bin/test_001.exe
CXXFLAGS = $(CXXINCS)  -g
CFLAGS = $(INCS)   
RM = rm -f

.PHONY: all all-before all-after clean clean-custom

all: ../../bin/test_001.exe


clean: 
	${RM} $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CPP) $(LINKOBJ) -o "..\..\bin\test_001.exe" $(LIBS)

main.o: main.cpp
	$(CPP) -c main.cpp -o main.o $(CXXFLAGS)
