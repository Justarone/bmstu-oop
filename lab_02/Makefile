CC = g++
INCLUDE_DIR = include/
BINARIES = $(patsubst %.cpp,bin/%.o, $(wildcard *.cpp))
# Remove -g if not in debug mode
#GTK_FLAGS = `pkg-config gtkmm-3.0 --libs --cflags`
COMPILE_FLAGS = -Wall -g -Werror -std=c++17

.PHONY: all test clean
all: app.exe

app.exe: $(BINARIES)
	$(CC) $^ -o $@ $(GTK_FLAGS) 

bin/%.o: %.cpp
	mkdir -p bin
	$(CC) -c -o $@ $(GTK_FLAGS) $(COMPILE_FLAGS) $^ -I$(INCLUDE_DIR)

clean:
	rm -rf bin/ app.exe

# g++ main.cpp -o app.exe `pkg-config gtkmm-3.0 --cflags --libs`
