# source files.
SRC = $(wildcard src/*.cpp)
OBJ = $(patsubst src%, ../buildtemp%.o, $(SRC))
OUT = bin/LSFscene
# include directories
INCLUDES = -I. -I./include/  -I./include/CGF -I/usr/local/include -I./include/TinyXML
# C++ compiler flags (-g -O2 -Wall)
CCFLAGS = -g
# compiler
CCC = g++
# library paths
LIBS = -Llib -L/usr/local/lib -L/usr/lib -lCGF -lTinyXML -lglew32 -lglui32 -lfreeglut -lglu32 -lopengl32
# compile flags
LDFLAGS = -g


default: $(OUT)

../buildtemp/%.o: src/%
	mkdir -p ../buildtemp
	$(CCC) $(INCLUDES) $(CCFLAGS) -c $< -o $@

$(OUT): $(OBJ)
	mkdir -p bin
	$(CCC) $(INCLUDES) $(CCFLAGS) $(OBJ) $(LIBS) -o $(OUT)

clean:
	rm -f $(OBJ) $(OUT)

test:
	echo $(SRC)
	echo $(OBJ)

animation:
	$(CCC) $(INCLUDES) -o animation src/LSFanimation.cpp src/testAnimation.cpp src/LSFvertex.cpp src/LSFprimitive.cpp $(LIBS)