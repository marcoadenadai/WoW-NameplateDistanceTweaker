CC=g++
CFLAGS=-c -Wall -I headers
LDFLAGS=-mwindows -lcomctl32 -static -static-libgcc -static-libstdc++
SOURCES=src/main.cpp src/memhacking.cpp
OBJECTS=$(addprefix obj/,$(notdir $(SOURCES:.cpp=.o)))
EXECUTABLE=Tbc243_Tweaks
RESFILE=res/main.res

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) $(RESFILE)
	$(CC) -o $@ $(OBJECTS) $(RESFILE) $(LDFLAGS)

obj/%.o: src/%.cpp | obj
	$(CC) $(CFLAGS) $< -o $@

obj:
	mkdir obj

$(RESFILE): res/Resource.rc
	windres --input res/Resource.rc --output $(RESFILE) --output-format=coff

clean:
	rm -f obj/*.o $(EXECUTABLE) $(RESFILE)
	rmdir obj

.PHONY: all clean