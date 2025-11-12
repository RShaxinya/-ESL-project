CC = gcc
CFLAGS = -std=c99 -Wall
TARGET = workshop3.exe
SOURCES = main.c

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

clean:
	del $(TARGET)
