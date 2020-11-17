SRC_FILES = $(wildcard *.c)
NAME = LD_PRELOAD.so

$(NAME): $(SRC_FILES)
	gcc -Wall -fPIC -shared -o $(NAME) $(SRC_FILES) -ldl -nostartfiles
	#cd NOP; $(MAKE)
	#gcc -Wall -fPIC -shared -o $(NAME) $(SRC_FILES) NOP/*.so -ldl -nostartfiles