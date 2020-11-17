SRC_FILES = $(wildcard *.c)
NAME = libLD_PRELOAD_NOP.so

$(NAME): $(SRC_FILES)
	gcc -Wall -fPIC -shared -o $(NAME) $(SRC_FILES)