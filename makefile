PNAME := image

PCXXSRC := $(wildcard src/*.cpp)

PCXXOBJS := $(PCXXSRC:src/%.cpp=build/%.o)

CC := g++

CXXFLAGS += -std=c++17 -O2 -g
LDLIBS += 
LDFLAGS += -lSDL2

.PHONY: all make_build_dirs clean

all: make_build_dirs $(PCXXOBJS)
	$(CC) $(LDFLAGS) $(PCXXOBJS) -o $(PNAME) $(LDLIBS)

$(PCXXOBJS): build/%.o: src/%.cpp
	$(CC) $(CXXFLAGS) -c $< -o $@

make_build_dirs:
	mkdir -p build/

clean:
	$(RM) -r build/
	$(RM) $(PNAME)