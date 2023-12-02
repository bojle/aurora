all: asm.c
	gcc -g asm.c -o a && ./a file.asm

test: test.c
	gcc test.c -o a && ./a
