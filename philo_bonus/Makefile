
CC = cc
CFLAGS =  -Wall -Werror -Wextra
TH_FLAGS = -pthread 

NAME = philo_bonus
EXT = .c
SRCDIR = src
OBJDIR = obj


SRC = $(wildcard $(SRCDIR)/*$(EXT))
OBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)/%.o)

RM = rm -rf
DELOBJ = $(OBJ)

all: $(NAME)


$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(TH_FLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%$(EXT)
	$(CC) $(CFLAGS) $(TH_FLAGS) -o $@ -c $<


.PHONY: clean
clean: 
	$(RM) $(DELOBJ)
.PHONY: fclean
fclean: clean 
	$(RM) $(NAME)
.PHONY: re
re: fclean all