CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2
TARGET = student_grade
SRC = student_grade.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)
