NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=thread -o3 $(DEBUG)
DEBUG = -g3

ifeq ($(d),1)
	CFLAGS += -fsanitize=thread 
endif

red			= /bin/echo -e "\x1b[31m\#\# $1\x1b[0m"
green		= /bin/echo -e "\x1b[32m\#\# $1\x1b[0m"
yellow		= /bin/echo -e "\x1b[33m\#\# $1\x1b[0m"
blue		= /bin/echo -e "\x1b[34m\#\# $1\x1b[0m"
purple		= /bin/echo -e "\x1b[35m\#\# $1\x1b[0m"

SRC = main.c\
      utils.c\
      philosopher.c\
	  philosopher2.c\
      table.c\
	  routine.c\
	  routine2.c\
	  join.c\
	  death.c\
	  time.c

OBJ = $(SRC:.c=.o)

# ---------------------------------- RULES ----------------------------------- #

all: $(LIBFT) $(NAME)

$(NAME) : $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) -Ihdr -o $(NAME) $(OBJ)
	@$(call blue,"✅ $@ build successful!")

%.o: %.c hdr/philosopher.h
	@$(CC) $(CFLAGS) -Ihdr -c $< -o $@
	@$(call blue,"✅ $< compiled!")

clean   :
	@rm -rf $(OBJ)
	@$(call blue,"🗑️ $(NAME) cleaned")

fclean  : clean
	@rm -rf $(OBJ) $(NAME)
	@$(call blue,"🗑️ $(NAME) fcleaned")

re      : fclean all

.PHONY : all bonus clean fclean re run val fun

# ---------------------------------------------------------------------------- #
