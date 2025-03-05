# Nombre del ejecutable
NAME = minishell

# Compilador y banderas
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

# Directorios
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj

# Archivos fuente
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Librería Libft (si la usas)
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

# Comando para limpiar
RM = rm -f

# Regla principal
all: $(NAME)

CLR_RMV		:= \033[0m
RED		    := \033[1;31m
GREEN		:= \033[1;32m
YELLOW		:= \033[1;33m
BLUE		:= \033[1;34m
CYAN 		:= \033[1;36m

# Crear el ejecutable
$(NAME): $(OBJ_FILES) $(LIBFT)
	@echo "$(GREEN)Compilation ${CLR_RMV}of ${YELLOW}$(NAME) ${CLR_RMV}..."
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ_FILES) -L$(LIBFT_DIR) -lft -lreadline
	@echo "$(GREEN)$(NAME) created[0m ✔️"

# Compilar la librería libft
$(LIBFT):
	@echo "$(GREEN)Compilation ${CLR_RMV}of ${YELLOW}libft.a ${CLR_RMV}..."
	@make -C $(LIBFT_DIR)
	@echo "$(GREEN)libft.a created[0m ✔️"

# Compilar archivos objeto
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -I$(LIBFT_DIR) -c $< -o $@

# Limpiar archivos objeto
clean:
	$(RM) $(OBJ_FILES)
	@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)objs ✔️"
	@make clean -C $(LIBFT_DIR)

# Limpiar todo
fclean: clean
	$(RM) $(NAME)
	@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)binary ✔️"
	@make fclean -C $(LIBFT_DIR)

# Recompilar todo
re: fclean all

# Evitar conflictos con archivos
.PHONY: all clean fclean re
