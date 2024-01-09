NAME := philo

SRC_DIR := src
OBJ_DIR	:= obj

SRCS := \
	main.c			\
	utils.c	\
	# utils/check_input.c	\
	# utils/found_error.c	\
	# utils/print_message.c \
	# utils/time_and_sleep.c \
	# utils/free_threads.c \
	# brain/init_data.c \
	# brain/threading.c \
	# brain/etsd.c \

SRCS := $(SRCS:%=$(SRC_DIR)/%)
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC := cc

CFLAGS := -g -pthread -Wall -Wextra -Werror
CPPFLAGS := -I include

RM := rm -f
MAKEFLAGS += --no-print-directory
DIR_DUP = mkdir -p $(@D)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)
	$(info CREATED $(NAME))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c Makefile
	$(DIR_DUP)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
	$(info CREATED $@)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: clean fclean re
.SILENT: