NAME = ft_container

SRC_DIR = srcs/
INC_PARAMS=$(foreach d, $(INCLUDE_DIR), -I$d)
INCLUDE_DIR = includes/
OBJDIR = bin/

SRCS = main.cpp\
	   RBT_test.cpp\
	   vector_stack_test.cpp\
	   mli_bounds.cpp\
	   mli_empty.cpp\
	   mli_erase.cpp\
	   mli_erase2.cpp\
	   mli_find.cpp

OBJS = $(addprefix $(OBJDIR),$(SRCS:.cpp=.o))

NS = ft

CC = c++
CFLAGS = -Wall -Werror -Wextra -std=c++98 -g -DNS=$(NS)
LFLAGS = $(INC_PARAMS)

$(OBJDIR)%.o : $(SRC_DIR)%.cpp
	$(CC) $(CFLAGS) $(INC_PARAMS) -o $@ -c $<

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
