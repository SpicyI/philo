
CC = cc
CFLAGS = -Wall -Werror -Wextra 
TH_FLAGS = -pthread 

NAME = philo
EXT = .c
SRCDIR = src
OBJDIR = obj


SRC = $(wildcard $(SRCDIR)/*$(EXT))
OBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)/%.o)

RM = rm -rf
DELOBJ = $(OBJ)

all: $(NAME)


$(NAME): $(SRC) $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(SRC) $(TH_FLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%$(EXT)
	$(CC) $(CFLAGS) -o $@ -c $<


.PHONY: clean
clean: 
	$(RM) $(DELOBJ)
.PHONY: fclean
fclean: clean 
	$(RM) $(NAME)
.PHONY: re
re: fclean all