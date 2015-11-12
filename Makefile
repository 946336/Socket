CC = gcc
CXX = g++

FLAGS = -g -Wall -Wextra
CFLAGS = -std=gnu99
NOLINK = -c

sock: sockets.cpp
	${CXX} ${FLAGS} ${NOLINK} $^

send: send.cpp sockets.cpp
	${CXX} ${FLAGS} $^ -o $@

recv: receive.cpp sockets.cpp
	${CXX} ${FLAGS} $^ -o $@

clean:
	rm *.o
