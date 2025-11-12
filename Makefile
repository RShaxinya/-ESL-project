CC = gcc
CFLAGS = -std=c99 -Wall
TARGET = rgb_app.exe
SOURCES = main.c

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

clean:
	del $(TARGET)
