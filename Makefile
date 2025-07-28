
# Program name
NAME = so_long

# Colors
GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m
CHECK = \033[0;34m\xe2\x9c\x94\033[0m

# Compiler
CC = cc
CFLAGS = -Wall -Wextra -Werror

# MLX42
MLX_DIR = lib/MLX42
MLX_BUILD = $(MLX_DIR)/build
MLX_INC = -I$(MLX_DIR)/include
MLX_LIB = -L$(MLX_BUILD) -lmlx42 -ldl -lglfw -lm
MLX_LIBFILE = $(MLX_BUILD)/libmlx42.a

# LIBFT
LIBFT_DIR	= ./libft
LIBFT		= $(LIBFT_DIR)/libft.a

# Include
INCLUDES = -Iinclude $(MLX_INC) -I$(LIBFT_DIR)

# Directories
SRC_DIR = src
BUILD_DIR = build

# Sources
SRCS = \
	src/main.c \
	src/parse_map.c \
	src/init_game.c \
	src/render_map.c \
	src/move.c \
	src/error.c \
	

# Object files in build/
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# Default rule
all: $(NAME)

$(LIBFT):
	@echo "$(GREY)📦 Compiling libft and ft_printf...$(RESET)"
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(MLX_LIBFILE) $(OBJS)
	@echo "$(GREEN)[Linking]$(RESET) $(NAME)"
	$(CC) $(CFLAGS) $(OBJS) $(MLX_LIB) -o $(NAME)
	@echo "$(CHECK) Executable built successfully ✅"

# Build object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "$(GREEN)[Compiling]$(RESET) $<"
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# MLX Compilation Rule with auto clone
$(MLX_LIBFILE):
	@if [ ! -d "$(MLX_DIR)" ]; then \
		echo "$(GREEN)[Cloning]$(RESET) MLX42"; \
		git clone https://github.com/codam-coding-college/MLX42.git $(MLX_DIR) >/dev/null 2>&1; \
	fi
	@echo "$(GREEN)[Building]$(RESET) MLX42"
	@i=1; \
	while [ $$i -le 20 ]; do \
		BAR=\"\"; \
		J=1; \
		while [ $$J -le $$i ]; do BAR=$${BAR}\#; J=`expr $$J + 1`; done; \
		while [ $$J -le 20 ]; do BAR=$${BAR}-; J=`expr $$J + 1`; done; \
		echo "MLX42: [$${BAR}] $$(( $$i * 5 ))%"; \
		sleep 0.05; \
		i=`expr $$i + 1`; \
	done
	@cmake -S $(MLX_DIR) -B $(MLX_BUILD) > /dev/null
	@cmake --build $(MLX_BUILD) -j4 > /dev/null
	@echo "$(CHECK) MLX42 built successfully"

clean:
	@rm -rf $(BUILD_DIR)
	@rm -rf $(MLX_BUILD)
	@echo "$(RED)Object files cleaned.$(RESET)"
	@$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) fclean -C $(LIBFT_DIR)
	@echo "$(RED)Binary $(NAME) removed.$(RESET)"

re: fclean all

norm:
	norminette include src

.PHONY: all clean fclean re norm