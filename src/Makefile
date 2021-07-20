CC = g++
CFLAGS = -c -Wall

src = $(wildcard *.cpp)
obj = $(src:.cpp=.o)
LDFLAGS = -I.

PsEmu: $(obj)
	$(CC) -o $@ $^ 

.PHONY: clean
clean:
	rm -f $(obj) PsEmu