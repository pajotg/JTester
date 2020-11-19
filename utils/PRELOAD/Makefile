SRC_FILES = $(wildcard *.c)

DEVICE = $(shell uname -s)

NAME = PRELOAD.so

ifeq ($(shell echo $(DEVICE) | cut -c 1-5),Linux)
LINUX=true
#NAME = PRELOAD.so
else
#NAME = PRELOAD.dylib
endif

.PHONY: $(NAME)
$(NAME): $(SRC_FILES)
ifdef LINUX
	gcc -Wall -Wextra -fPIC -shared -o $(NAME) $(SRC_FILES) -ldl -nostartfiles
else
	cd NOP; $(MAKE)
	gcc -Wall -Wextra -fPIC -shared -o $(NAME) $(SRC_FILES) -ldl -nostartfiles -LNOP -lPRELOAD_NOP
endif


#ifdef LINUX
#	gcc -Wall -Wextra -fPIC -shared -o $(NAME) $(SRC_FILES) -ldl -nostartfiles
#else
#	cd NOP; $(MAKE)
#	GCC -Wall -Wextra -dynamiclib -o $(NAME) $(SRC_FILES) -LNOP -lPRELOAD_NOP
#endif

#cd NOP; $(MAKE)
#gcc -Wall -fPIC -shared -o $(NAME) $(SRC_FILES) NOP/*.so -ldl -nostartfiles