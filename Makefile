# Compiler to use

CC=g++
CFLAGS=-std=c++11 -fno-exceptions -Wall -Wextra

all: SiConf.lib
#$(CC)  $(CFLAGS) -c reader.o -o SiConf.lib

test: SiConf.lib
	$(CC) -DCONF_TEST $(CFLAGS) SiConf.lib reader_test.cpp -o tests.o

SiConf.lib: reader.cpp
	$(CC) $(CFLAGS) -c reader.cpp -o SiConf.lib


clean:
	rm -rf *.o
	rm -rf *.lib
