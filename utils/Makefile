OBJ_DIR ?= obj/
SRC_DIR ?= src/
INCLUDE_DIR ?= include/

SRC_FILES = $(wildcard $(SRC_DIR)*.c)
NAME ?= utils.a

OBJ = $(SRC_FILES:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

$(NAME): $(OBJ)
	ranlib $(NAME)

$(OBJ_DIR) $(SRC_DIR) $(INCLUDE_DIR):
	mkdir $@

$(OBJ): $(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INCLUDE_DIR) \
	| $(SRC_DIR) $(OBJ_DIR)
	$(CC) $(FLAGS) -I $(INCLUDE_DIR) -c -o $@ $<
	ar -rc $(NAME) $@

clean:
	rm $(OBJ)

fclean: clean
	rm $(NAME)