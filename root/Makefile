CC = gcc
CFLAGS = -Wall
LDFLAGS = -lws2_32
SRCS = merl_main.c shell.c kernel.c user.c utils.c tetra.c color-and-test.c
OBJS = $(SRCS:.c=.o)
TARGET = MERL.exe

all: $(TARGET)

$(TARGET): $(SRCS)
    $(CC) $(CFLAGS) -o $(TARGET) $(SRCS) $(LDFLAGS)

clean:
    del /Q *.o *.exe 2>nul || true

.PHONY: all clean