NAME	= cub3D
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
HEADER	= includes/
LIBFT	= libft/
LIBCC	= -L$(LIBFT) -lft
LIBMLX	= minilibx-linux/
MLXCC	= -L$(LIBMLX) -lmlx -lXext -lX11 -lm
HEADERS = -I $(HEADER) -I $(LIBFT) -I $(LIBMLX)


MAIN    = main.c exit_err.c utils.c
PARSER	= file.c elements.c map.c

SRCS	= $(addprefix srcs/main/, $(MAIN)) \
       $(addprefix srcs/parser/, $(PARSER)) \

OBJS	= $(SRCS:.c=.o)


# Color definitions
RED			= \e[1;31m
NO_COLOR	= \e[0m

all: $(LIBMLX)/libmlx.a $(NAME)

$(LIBMLX)/libmlx.a:
	@echo "🔧 Making minilibx library..."
	@$(MAKE) -C $(LIBMLX) > /dev/null 2>&1
	@echo "✅ Minilibx library compiled successfully!"


$(NAME): $(LIBFT)/libft.a $(OBJS) $(HEADER)/cub3d.h Makefile
	@echo "${RED}"
	@echo "                       _/        _/_/_/    _/_/_/"
	@echo "    _/_/_/  _/    _/  _/_/_/          _/  _/    _/"
	@echo " _/        _/    _/  _/    _/    _/_/    _/    _/"
	@echo "_/        _/    _/  _/    _/        _/  _/    _/"
	@echo " _/_/_/    _/_/_/  _/_/_/    _/_/_/    _/_/_/"
	@echo ""
	@echo "${NO_COLOR}"
	@$(CC) $(CFLAGS) $(HEADERS) $(OBJS) -o $(NAME) $(LIBCC) $(MLXCC)
	@echo "🪄  \e[1;34mDone!\e[0m"

$(LIBFT)/libft.a:
	@echo "🔧 Making libft..."
	@$(MAKE) -C $(LIBFT) > /dev/null 2>&1
	@echo "✅ libft compiled successfully!"

%.o: %.c
	@echo "✔️  \e[0;34mCompiling $<...\e[0m"
	@$(CC) $(CFLAGS) $(HEADERS) -c -o $@ $<

clean:
	@echo "🧹 \e[1;34mCleaning..."
	@rm -f $(OBJS)
	@$(MAKE) clean -C $(LIBFT) > /dev/null 2>&1
	@echo "✨ Done!\e[0m"

fclean: clean
	@echo "🧹 \e[1;34mCleaning all..."
	@rm -f $(NAME)
	@$(MAKE) fclean -C $(LIBFT) > /dev/null 2>&1
	@echo "✨ Done!\e[0m"

re: fclean all

.PHONY: all clean fclean re