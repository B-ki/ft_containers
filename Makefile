NAME = ft_container

SRC_DIR = srcs/
INCLUDE_DIR = includes/
OBJDIR = bin/

SRCS = main.cpp

OBJS = $(addprefix $(OBJDIR),$(SRCS:.cpp=.o))

CC = c++
CFLAGS = -Wall -Werror -Wextra -std=c++98 -g
LFLAGS = -I includes
INCPATH = -I$(INCLUDE_DIR)

$(OBJDIR)%.o : $(SRC_DIR)%.cpp
	$(CC) $(CFLAGS) $(INCPATH) -o $@ -c $<

$(NAME): $(OBJDIR) $(OBJS)
	$(CC) $(OBJS) $(LFLAGS) -o $(NAME)

all: $(NAME)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

clean: 
	rm -rf $(OBJDIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY:	all re clean fclean
