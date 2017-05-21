CC = gcc
CXX = g++

FLAGS = -g -Wall -Wextra -Werror -pedantic
CFLAGS = -std=gnu99
NOLINK = -c

all: send recv

sock: sockets.cpp
	${CXX} ${FLAGS} ${NOLINK} $^

send: send.cpp sockets.cpp
	${CXX} ${FLAGS} $^ -o $@

recv: receive.cpp sockets.cpp
	${CXX} ${FLAGS} $^ -o $@

clean:
	rm *.o

