main.exe: main.c
	gcc -Wall -Wextra main.c -o main.exe -I./ -L./ -lraylib -lopengl32 -lgdi32 -lwinmm