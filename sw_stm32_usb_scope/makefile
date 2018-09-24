

# Set up basic variables:
CC = gcc
CFLAGS = -c -ggdb -Wall -DDEBUG
#-ggdb	Produce debugging information for use by GDB.  dikkat bunsuz debug calismiyor
#-g		Produce debugging information in the operating system's native format
#-c 	gcc -c compiles source files without linking.
#gcc -g generates debug information to be used by GDB debugger.
#gcc -I adds include directory of header files.
#gcc -D defines a macro to be used by the preprocessor.
#gcc -o writes the build output to an output file.
#gcc -O sets the compiler's optimization level.

LDFLAGS =

# List of sources:
SOURCES = main.c gnuplot_i.c
OBJECTS = $(SOURCES:.c=.o)

# Name of executable target:
EXECUTABLE = stm32_usb_scope


CFLAGS += `pkg-config --cflags libhid`
LDFLAGS += `pkg-config --libs libhid`
 
all: $(SOURCES) $(EXECUTABLE)
 
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)
 
.c.o:
	$(CC) $(CFLAGS) $< -o $@
 
clean:
	rm $(OBJECTS) $(EXECUTABLE)



#gcc -Wall -o main main.c $( pkg-config --cflags --libs libhid) 	works...
