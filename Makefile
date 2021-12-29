CFILES = $(wildcard src/*.cpp)
OBJFILES = $(CFILES:.cpp=.o)

CC = g++
OUT = PEX

$(OUT): $(OBJFILES)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) -c -o $@ $^

clean:
	find . -path "*/*.o"  -delete
