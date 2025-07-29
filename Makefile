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

# MLX42
MLX_DIR = lib/MLX42
MLX_BUILD = $(MLX_DIR)/build
MLX_INC = -I$(MLX_DIR)/include
MLX_LIB = -L$(MLX_BUILD) -lmlx42 -L/opt/homebrew/opt/glfw/lib -lglfw -ldl -lm
# MLX_LIB = -L$(MLX_BUILD) -lmlx42 -ldl -lglfw -lm 
MLX_LIBFILE = $(MLX_BUILD)/libmlx42.a

# Include paths
INCLUDES = -I$(INCLUDE_DIR) \
		   -I$(LIBFT_DIR) \
		   -I$(GNL_DIR) \
		   $(MLX_INC)

# Sources
SRCS = \
	src/main.c \
	src/map_parser.c \
	src/map_utils.c \
	src/map_validator.c \
	# src/init_game.c \
	# src/render_map.c \
	# src/move.c \
	# src/error.c \

# Object files in build/
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# Default rule
all: $(BUILD_DIR) $(NAME)

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(NAME): $(MLX_LIBFILE) $(LIBFT) $(GNL) $(OBJS)
	@echo "$(GREEN)[Linking]$(RESET) $(NAME)"
	$(CC) $(CFLAGS) $(OBJS) $(MLX_LIB) $(GNL) $(LIBFT) -o $(NAME)
	@echo "$(CHECK) Executable built successfully ✅"

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

# MLX Compilation Rule with progress bar
$(MLX_LIBFILE):
	@if [ ! -d "$(MLX_DIR)" ]; then \
		echo "$(GREEN)[Cloning]$(RESET) MLX42"; \
		git clone https://github.com/codam-coding-college/MLX42.git $(MLX_DIR) >/dev/null 2>&1; \
	fi
	@echo "$(GREEN)[Building]$(RESET) MLX42"
	@i=1; \
	while [ $$i -le 20 ]; do \
		BAR=""; \
		J=1; \
		while [ $$J -le $$i ]; do BAR=$${BAR}\#; J=`expr $$J + 1`; done; \
		while [ $$J -le 20 ]; do BAR=$${BAR}-; J=`expr $$J + 1`; done; \
		echo "MLX42: [\"\"$${BAR}] $$(( $$i * 5 ))%"; \
		sleep 0.05; \
		i=`expr $$i + 1`; \
	done
	@cmake -S $(MLX_DIR) -B $(MLX_BUILD) > /dev/null
	@cmake --build $(MLX_BUILD) -j4 > /dev/null
	@echo "$(CHECK) MLX42 built successfully"

# Cleaning rules
clean:
	@rm -rf $(BUILD_DIR)
	@rm -rf $(MLX_BUILD)
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
