CC = g++
CFLAGS = -c -O3 -Wall 
LDFLAGS = 

SOURCES = record.cpp aceleracion.cpp inicializa.cpp main.cpp velocidades.cpp paredes.cpp posiciones.cpp posiciones_old.cpp neighbours.cpp

OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = d_v4

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE) : $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean

clean:
	rm -f *.o *~ $(EXECUTABLE)


