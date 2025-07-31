# Program name
NAME = so_long

# Colors
GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m
CHECK = \033[0;34m✔\033[0m

# Compiler
CC = cc
CFLAGS = -Wall -Wextra -Werror -DGL_SILENCE_DEPRECATION

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

# MiniLibX
MLX_DIR = lib/minilibx
OS := $(shell uname)

# System-specific MLX flags
ifeq ($(OS), Darwin)  # macOS
MLX_INC = -I$(MLX_DIR)
MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
else  # Linux
MLX_INC = -I$(MLX_DIR)
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
endif

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
	# src/error.c \

# Object files in build/
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# Default rule
all: $(BUILD_DIR) $(NAME)

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

# Link final
$(NAME): $(LIBFT) $(GNL) $(MLX_DIR)/libmlx.a $(OBJS)
	@echo "$(GREEN)[Linking]$(RESET) $(NAME)"
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) $(GNL) $(LIBFT) -o $(NAME)
	@echo "$(CHECK) Executable built successfully ✅"

# Build MiniLibX if not already built
$(MLX_DIR)/libmlx.a:
	@echo "$(GREEN)[Building]$(RESET) MiniLibX"
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

.PHONY: all clean fclean re
