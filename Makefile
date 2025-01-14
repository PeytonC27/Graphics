CXX = g++
CXXFLAGS = -std=c++17 -Wall
INCLUDE = -ISDL2/include -Iinclude
LIBS = -L./SDL2/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
SRCDIR = ./src
INCDIR = ./include
SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(SRCS:$(SRCDIR)/%.cpp=%.o)
TARGET = main.exe

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) $(CXXFLAGS) $(INCLUDE) $(LIBS) -o $(TARGET)
	

%.o: $(SRCDIR)/%.cpp $(INCDIR)/%.h
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

main.o: ./src/main.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

clean:
	del /q $(OBJS) $(TARGET)

rebuild:
	mingw32-make clean
	mingw32-make

