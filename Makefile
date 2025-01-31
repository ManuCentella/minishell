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

# Crear el ejecutable
$(NAME): $(OBJ_FILES) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ_FILES) -L$(LIBFT_DIR) -lft -lreadline

# Compilar archivos objeto
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -I$(LIBFT_DIR) -c $< -o $@

# Compilar la librería libft
$(LIBFT):
	@make -C $(LIBFT_DIR)

# Limpiar archivos objeto
clean:
	$(RM) $(OBJ_FILES)
	@make clean -C $(LIBFT_DIR)

# Limpiar todo
fclean: clean
	$(RM) $(NAME)
	@make fclean -C $(LIBFT_DIR)

# Recompilar todo
re: fclean all

# Evitar conflictos con archivos
.PHONY: all clean fclean re
