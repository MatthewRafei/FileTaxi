main: main.c ftstr.c ftstr.h utils.h
	cc -o main -ggdb --pedantic -Wextra -Wall -O0 main.c ftstr.c

clean:
	rm main
