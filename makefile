default:
	gcc main.c -o tetris -lraylib -L/opt/homebrew/lib -I/opt/homebrew/include -framework CoreVideo -framework IOKit -framework Cocoa -framework OpenGL