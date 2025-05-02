NAME = cub3D

CC = gcc

# Compiler flags include our project's includes and the MLX42 include directory.
CFLAGS = -Wall -Wextra -Werror -I includes/ -I libft/includes/ -I $(MLX42_DIR)/include

# MLX42 library variables.
MLX42_DIR = ./lib/MLX42
MLX42_LIB = $(MLX42_DIR)/build/libmlx42.a

# Additional libraries.
# Added -L/opt/homebrew/lib for Homebrew on macOS.
# Change -lglfw to -lglfw3 if your installation uses that naming.
GLFW = -ldl -lglfw -pthread -lm

LIBFT = -L libft -lft -lreadline

HEADER = cub3d.h

MAIN = main

PARSER = read_file free_parser 

ID = check_identifiers check_identifiers_utils validate_identifiers validate_identifiers_utils validate_characters validate_characters_utils check_valid_scene

GNL = get_next_line get_next_line_utils

MAP = valid_map extract_map format_map flood_fill flood_fill_utils valid_map_utils

PARSING = parse_textures parse_colors parse_player parsing

EXEC = execution movement raycasting_core raycasting_intersect_h raycasting_intersect_v raycasting_render render_utils minimap textures

SRC = $(addsuffix .c, $(addprefix srcs/main/, $(MAIN))) \
	$(addsuffix .c, $(addprefix srcs/parser/, $(PARSER))) \
	$(addsuffix .c, $(addprefix srcs/execution/, $(EXEC))) \
	$(addsuffix .c, $(addprefix srcs/parser/valid_identifiers/, $(ID))) \
	$(addsuffix .c, $(addprefix srcs/parser/valid_map/, $(MAP))) \
	$(addsuffix .c, $(addprefix srcs/parser/parsing/, $(PARSING))) \
	$(addsuffix .c, $(addprefix srcs/get_next_line/, $(GNL)))

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "\n"
	@make -C libft/
	@echo "\033[0;32mCOMPILING CUB3D..."
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(MLX42_LIB) -L/opt/homebrew/lib $(GLFW)
	@echo "\n\033[0;32mDONE...\n\033[0m"

%.o: %.c
	@printf "\033[0;33mGENERATING CUB3D OBJECTS... %-33.33s\r" $@
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "\033[0;31mCLEANING LIBFT..."
	@make clean -C libft/
	@echo "\nREMOVING CUB3D BINARIES..."
	@rm -f $(OBJ)
	@echo "\033[0m"

fclean: clean
	@echo "\033[0;31mCLEANING LIBFT..."
	@make fclean -C libft/
	@echo "\nDELETING OBJECTS..."
	@rm -f $(OBJ)
	@echo "\nDELETING EXECUTABLE..."
	@rm -f $(NAME)
	@echo "\033[0m"

re: fclean all

test: all
	./cub3D

norm:
	norminette $(SRC) includes/$(HEADER)

.PHONY: all clean fclean re test norm
