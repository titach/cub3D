NAME	= cub3D
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
HEADER	= cub3d.h
LIBFT	= ./libft
LIBCC	= -L$(LIBFT) -lft
LIBMLX	= ./minilibx-linux
MLXCC	= -L$(LIBMLX) -lXext -lX11 -lm


# MAIN    = main.c
SRCS	= main.c exit_err.c

OBJS	= $(SRCS:.c=.o)


# Color definitions
RED			= \e[1;31m
NO_COLOR	= \e[0m

all: $(LIBMLX)/libmlx.a $(NAME)

$(LIBMLX)/libmlx.a:
	@echo "🔧 Making minilibx library..."
	@make -C $(LIBMLX) > /dev/null 2>&1
	@echo "✅ Minilibx library compiled successfully!"


$(NAME): $(LIBFT)/libft.a $(OBJS) $(HEADER) Makefile
	@echo "${RED}"
	@echo "                       _/        _/_/_/    _/_/_/"
	@echo "    _/_/_/  _/    _/  _/_/_/          _/  _/    _/"
	@echo " _/        _/    _/  _/    _/    _/_/    _/    _/"
	@echo "_/        _/    _/  _/    _/        _/  _/    _/"
	@echo " _/_/_/    _/_/_/  _/_/_/    _/_/_/    _/_/_/"
	@echo ""
	@echo "${NO_COLOR}"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBCC) $(MLXCC)
	@echo "🪄  \e[1;34mDone!\e[0m"

$(LIBFT)/libft.a:
	@echo "🔧 Making libft..."
	@make -C $(LIBFT) > /dev/null 2>&1
	@echo "✅ libft compiled successfully!"

%.o: %.c
	@echo "✔️  \e[0;34mCompiling $<...\e[0m"
	@$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@echo "🧹 \e[1;34mCleaning..."
	@rm -f $(OBJS)
	@make clean -C $(LIBFT) > /dev/null 2>&1
	@echo "✨ Done!\e[0m"

fclean: clean
	@echo "🧹 \e[1;34mCleaning all..."
	@rm -f $(NAME)
	@make fclean -C $(LIBFT) > /dev/null 2>&1
	@echo "✨ Done!\e[0m"

re: fclean all

.PHONY: all clean fclean re