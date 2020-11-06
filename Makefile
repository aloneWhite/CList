CROSS_COMPILE ?=

CC = $(CROSS_COMPILE)gcc
AR = $(CROSS_COMPILE)ar
RM = rm

#CFLAGS += -g

SRCS = ./src/clist.c

OBJS = $(SRCS:.c=.o)

all : shared static test

shared : $(OBJS)
	$(CC) $(CFLAGS) -shared -o libclist.so $(OBJS)

static : $(OBJS)
	$(AR) -r libclist.a $(OBJS)

test : shared
	$(CC) $(CFLAGS) -I./src -o clist-demo ./test/clist-demo.c -L. -lclist

clean :
	$(RM) -rf *.p src/*.o test/*.o
	$(RM) -rf libclist.*
