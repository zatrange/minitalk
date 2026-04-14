NAME_C = client
NAME_S = server
NAME_C_B = client_bonus
NAME_S_B = server_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC_SC_D = mandatory
SRC_SC_D_B = bonus
INCLUDES = mandatory/minitalk.h
INCLUDES_B = bonus/minitalk_bonus.h

SRC_C = $(SRC_SC_D)/client.c \
	$(SRC_SC_D)/ft_atoi.c \
	$(SRC_SC_D)/ft_strlen.c \

SRC_S = $(SRC_SC_D)/server.c \
		$(SRC_SC_D)/ft_putnbr.c

OBJ_C = $(SRC_C:$(SRC_SC_D)/%.c=$(SRC_SC_D)/%.o)
OBJ_S = $(SRC_S:$(SRC_SC_D)/%.c=$(SRC_SC_D)/%.o)

SRC_C_B = $(SRC_SC_D_B)/client_bonus.c \
	$(SRC_SC_D_B)/ft_atoi_bonus.c \
	$(SRC_SC_D_B)/ft_strlen_bonus.c 

SRC_S_B = $(SRC_SC_D_B)/server_bonus.c \
	$(SRC_SC_D_B)/ft_putnbr_bonus.c

OBJ_C_B = $(SRC_C_B:$(SRC_SC_D_B)/%.c=$(SRC_SC_D_B)/%.o)
OBJ_S_B = $(SRC_S_B:$(SRC_SC_D_B)/%.c=$(SRC_SC_D_B)/%.o)

all: $(NAME_C) $(NAME_S)
bonus: $(NAME_C_B) $(NAME_S_B)

$(SRC_SC_D)/%.o: $(SRC_SC_D)/%.c $(INCLUDES)
	$(CC) $(CFLAGS) -c $< -o $@
$(SRC_SC_D_B)/%.o: $(SRC_SC_D_B)/%.c $(INCLUDES_B)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME_C): $(OBJ_C)
	$(CC) $(CFLAGS) -o $@ $(OBJ_C)
$(NAME_S): $(OBJ_S)
	$(CC) $(CFLAGS) -o $@ $(OBJ_S)

$(NAME_C_B): $(OBJ_C_B)
	$(CC) $(CFLAGS) -o $@ $(OBJ_C_B)
$(NAME_S_B): $(OBJ_S_B)
	$(CC) $(CFLAGS) -o $@ $(OBJ_S_B)

clean:
	rm -f $(OBJ_C) $(OBJ_S) $(OBJ_C_B) $(OBJ_S_B)

fclean: clean
	rm -f $(NAME_C) $(NAME_S) $(NAME_C_B) $(NAME_S_B)

re: fclean all

.PHONY: clean