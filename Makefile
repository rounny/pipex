NAME		= pipex

SRCS_DIR      = ./srcs/
SRCS_B_DIR    = ./srcs_b/
# OBJS_DIR      = ./objs/
# OBJS_B_DIR    = ./objs_b/
LIBFT_DIR		= ./libft/
HEAD_DIR		= ./includes/
HEAD_LIST		= pipex.h
HEAD_B_LIST		= pipex_bonus.h

LIBFT			= $(addprefix $(LIBFT_DIR), libft.a)
HEAD         	= $(addprefix $(HEAD_DIR), $(HEAD_LIST))
HEAD_B			= $(addprefix $(HEAD_DIR), $(HEAD_B_LIST))

SRCS_FILES    	= main.c children.c utils.c
SRCS_B_FILES 	= main_bonus.c utils_bonus.c
SRCS			= $(addprefix $(SRCS_DIR), $(SRCS_FILES))
SRCS_B			= $(addprefix $(SRCS_B_DIR), $(SRCS_B_FILES))
OBJS		  	= $(SRCS:%.c=%.o)
OBJS_B			= $(SRCS_B:%.c=%.o)
# OBJS          = $(addprefix $(OBJS_DIR), $(notdir $(SRCS:.c=.o)))
# OBJS_B        = $(addprefix $(OBJS_B_DIR), $(notdir $(SRCS_B:.c=.o)))

CC		      = cc
CFLAGS		  = -Wall -Wextra -Werror 
LDFLAGS		  =	-L$(LIBFT_DIR)
RM			  =	rm -rf

.PHONY: all clean fclean re

all:  $(LIBFT) $(NAME) 

# $(OBJS_DIR):
# 	mkdir $(OBJS_DIR)

# $(OBJS_B_DIR):
# 	mkdir $(OBJS_B_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@make -C $(LIBFT_DIR)
	@make bonus -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(HEAD)
	$(CC) $(OBJS) $(LIBFT) -o $@ $(LDFLAGS)

bonus: all
		@make OBJS="$(OBJS_B)" OBJS_DIR="$(OBJS_B_DIR)" HEAD="$(HEAD_B)"

clean:
		$(RM) $(OBJS) $(OBJS_B)
		make clean -C ./libft

fclean: clean
		$(RM) $(NAME)
		$(RM) $(LIBFT)

re: clean fclean all bonus 