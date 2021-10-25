#
# N.B. If you're using files with .cc extensions, then you need to search
# and replace cpp with cc.
#

CC = g++
CFLAGS = -Wall -g
#CFLAGS = -std=c++11 -Wall -g
# For this project, you'll have only main.cpp, since we're using
# template classes.
SRCS =  main.cpp
#SRCS = ${wildcard *.cpp}
OBJS = ${SRCS:.cpp=.o}
INCLS = ${SRCS:.cpp=.h} main.h  node.h nosuchobject.h mtfList.h orderedList.h

p1: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o p1

$(OBJS):
	$(CC) $(CFLAGS) -c $*.cpp

depend: Makefile.dep
	$(CC) -MM $(SRCS) > Makefile.dep

Makefile.dep:
	touch Makefile.dep

.PHONY: submit clean

submit:
	rm -f submit.zip
	zip submit.zip $(SRCS) $(INCLS) Makefile Makefile.dep

clean:
	rm -f *.o a.out core

include Makefile.dep

