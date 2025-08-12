# Program name
NAME = so_long

# Colors
GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m
CHECK = \033[0;34m✔\033[0m

# Compiler
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Detect OS
OS := $(shell uname)

# Directories
SRC_DIR = src
BUILD_DIR = build
INCLUDE_DIR = include

# Custom libraries
CUSTOM_LIBS_DIR = custom_libs
LIBFT_DIR = $(CUSTOM_LIBS_DIR)/libft
GNL_DIR = $(CUSTOM_LIBS_DIR)/get_next_line

LIBFT = $(LIBFT_DIR)/libft.a
GNL   = $(GNL_DIR)/libgnl.a

# MiniLibX (seleciona automaticamente a certa)
MLX_DIR_MAC   = lib/mlx_mac
MLX_DIR_LINUX = lib/mlx_linux

ifeq ($(OS), Darwin)  # macOS
	MLX_DIR   = $(MLX_DIR_MAC)
	MLX_INC   = -I$(MLX_DIR)
	MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
	CFLAGS   += -DGL_SILENCE_DEPRECATION
else  # Linux
	MLX_DIR   = $(MLX_DIR_LINUX)
	MLX_INC   = -I$(MLX_DIR)
	MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
endif

MLX_LIB := $(MLX_DIR)/libmlx.a

# Include paths (for compilation only)
INCLUDES = -I$(INCLUDE_DIR) -I$(LIBFT_DIR) -I$(GNL_DIR) $(MLX_INC)

# Sources
SRCS = \
	src/main.c \
	src/map_parser.c \
	src/map_utils.c \
	src/map_validator.c \
	src/map_path.c \
	src/init_game.c \
	src/mlx_setup.c \
	src/render_map.c \
	src/sprites.c \
	src/moves.c \
	src/exit_game.c \
	src/hud.c \

# Object files in build/
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# Default rule
all: $(BUILD_DIR) $(NAME)

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

# Link final
$(NAME): $(LIBFT) $(GNL) $(MLX_LIB) $(OBJS)
	@echo "$(GREEN)[Linking]$(RESET) $(NAME)"
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) $(GNL) $(LIBFT) -o $(NAME)
	@echo "$(CHECK) Executable built successfully ✅"

# Build MiniLibX (para o OS detectado)
$(MLX_LIB):
	@echo "$(GREEN)[Building]$(RESET) MiniLibX for $(OS) in $(MLX_DIR)"
	@$(MAKE) -C $(MLX_DIR)

# Compile each object file
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "$(GREEN)[Compiling]$(RESET) $<"
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Build custom libraries
$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) OBJ_DIR=obj

$(GNL):
	@$(MAKE) -C $(GNL_DIR) OBJ_DIR=obj

# Cleaning rules
clean:
	@rm -rf $(BUILD_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean OBJ_DIR=obj
	@$(MAKE) -C $(GNL_DIR) clean OBJ_DIR=obj
	@echo "$(RED)Object files cleaned.$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean OBJ_DIR=obj
	@$(MAKE) -C $(GNL_DIR) fclean OBJ_DIR=obj
	@echo "$(RED)Binary $(NAME) removed.$(RESET)"

re: fclean all

# Docker commands
valgrind:
	@echo "$(GREEN)[Running]$(RESET) Valgrind check in Docker"
	@docker build -t so_long_valgrind .
	@docker run --rm so_long_valgrind

docker-clean:
	@echo "$(RED)[Docker]$(RESET) Removing Docker image"
	@docker rmi so_long_valgrind 2>/dev/null || true

.PHONY: all clean fclean re valgrind docker-clean
