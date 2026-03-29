# Compiler și flags
CC = gcc
CFLAGS = -Wall -Wextra -O2 -I/opt/homebrew/include
LDFLAGS = -L/opt/homebrew/lib -lraylib -lm -lpthread -ldl \
          -framework CoreVideo -framework IOKit -framework Cocoa -framework OpenGL

# Fișiere sursă cu calea corectă
SRCS = main.c tetrominos/tetrominos.c drawings/drawings.c clearRows/clearRows.c
OBJS = $(SRCS:.c=.o)

# Executabil
TARGET = tetris

# Regula implicită
all: $(TARGET)

# Linking
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Compilare fișiere .c în .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Curățare
clean:
	rm -f $(OBJS) $(TARGET)

# Rebuild complet
rebuild: clean all

.PHONY: all clean rebuild