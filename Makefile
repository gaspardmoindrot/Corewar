# =========== Colors =========== #
CLEAR			:= "\033[2K"
UP				:= "\033[A"
EOC				:= "\033[0;0m"
BLACK			:= "\033[0;30m"
RED				:= "\033[0;31m"
GREEN			:= "\033[0;32m"
YELLOW			:= "\033[0;33m"
BLUE			:= "\033[0;34m"
PURPLE			:= "\033[0;35m"
CYAN			:= "\033[0;36m"
WHITE			:= "\033[0;37m"
# ============================== #

# ========== Editable ========== #
ASM				:= asm
DASM				:= dasm
COREWAR				:= corewar
# ============================== #

# ========== Standard ========== #
#
CC				:= gcc
FLAGS			:= -g -fsanitize=address -Wall -Wextra -Werror
# ============================== #

# =========== Files ============ #
#
ASM_SRCS_FILES		:=	asm.c \
				op.c \
				change_file.c \
				first_turn.c \
				utils.c \
				check_instruction.c \
				utils_2.c \
				second_turn.c \
				third_turn.c \
				utils_3.c \
				ft_printf_binaire.c

DASM_SRCS_FILES		:=	dasm.c

CORE_SRCS_FILES		:=	corewar.c

ASM_HEADERS_FILES	:=	asm.h \
				op.h

DASM_HEADERS_FILE	:=	dasm.h

CORE_HEADERS_FILES	:=	corewar.h

# ============================== #

# ========== Sources =========== #
ASM_PATH		:= srcs/asm/
DASM_PATH		:= srcs/dasm/
CORE_PATH		:= srcs/corewar/
ASM_SRCS		:= $(addprefix $(ASM_PATH), $(ASM_SRCS_FILES))
DASM_SRCS		:= $(addprefix $(DASM_PATH), $(DASM_SRCS_FILES))
CORE_SRCS		:= $(addprefix $(CORE_PATH), $(CORE_SRCS_FILES))
# ============================== #

# ========== Objects =========== #
OBJS_PATH			:= objs/
ASM_OBJS_PATH		:= objs/asm/
DASM_OBJS_PATH		:= objs/dasm/
CORE_OBJS_PATH		:= objs/corewar/
ASM_OBJS		:= $(addprefix $(ASM_OBJS_PATH), $(ASM_SRCS_FILES:.c=.o))
DASM_OBJS                := $(addprefix $(DASM_OBJS_PATH), $(DASM_SRCS_FILES:.c=.o))
CORE_OBJS 		:= $(addprefix $(CORE_OBJS_PATH), $(CORE_SRCS_FILES:.c=.o))
# ============================== #

# ========== Includes ========== #
INCLUDES_PATH	:= includes/
INCLUDES		:= -I $(INCLUDES_PATH)
ASM_HEADERS		:= $(addprefix $(INCLUDES_PATH), $(ASM_HEADERS_FILES))
DASM_HEADERS		:= $(addprefix $(INCLUDES_PATH), $(DASM_HEADERS_FILES))
CORE_HEADERS	:= $(addprefix $(INCLUDES_PATH), $(CORE_HEADERS_FILES))
# ============================== #

# ========== Libraries ========= #
LIBFT_PATH		:= libft/
LIBFT_INCLUDES	:= -I libft/includes
LIBFT			:= -L $(LIBFT_PATH) -lft -lncurses -lpthread
# ============================== #

.PHONY: all libft clean fclean re

all: libft $(ASM) $(DASM) $(COREWAR)

libft:
	@make -C $(LIBFT_PATH)

$(ASM_OBJS_PATH)%.o: $(ASM_PATH)%.c $(ASM_HEADERS) $(LIBFT_PATH)libft.a
	@mkdir $(OBJS_PATH) 2> /dev/null || true
	@mkdir $(ASM_OBJS_PATH) 2> /dev/null || true
	$(CC) $(FLAGS) $(INCLUDES) $(LIBFT_INCLUDES) -o $@ -c $<

$(DASM_OBJS_PATH)%.o: $(DASM_PATH)%.c $(DASM_HEADERS) $(LIBFT_PATH)libft.a
	@mkdir $(OBJS_PATH) 2> /dev/null || true
	@mkdir $(DASM_OBJS_PATH) 2> /dev/null || true
	$(CC) $(FLAGS) $(INCLUDES) $(LIBFT_INCLUDES) -o $@ -c $<

$(CORE_OBJS_PATH)%.o: $(CORE_PATH)%.c $(CORE_HEADERS) $(LIBFT_PATH)libft.a
	@mkdir $(OBJS_PATH) 2> /dev/null || true
	@mkdir $(CORE_OBJS_PATH) 2> /dev/null || true
	$(CC) $(FLAGS) $(INCLUDES) $(LIBFT_INCLUDES) -o $@ -c $<

$(ASM): $(ASM_OBJS)
	$(CC) $(FLAGS) $(LIBFT) $(ASM_OBJS) -o $@

$(DASM): $(DASM_OBJS)
	$(CC) $(FLAGS) $(LIBFT) $(DASM_OBJS) -o $@

$(COREWAR): $(CORE_OBJS)
	$(CC) $(FLAGS) $(LIBFT) $(CORE_OBJS) -o $@

clean:
	@make -C $(LIBFT_PATH) clean &> /dev/null
	@rm -fv $(ASM_OBJS) $(DASM_OBJS) $(CORE_OBJS)
	@rmdir $(OBJS_PATH) 2> /dev/null || true

fclean: clean
	@make -C $(LIBFT_PATH) fclean &> /dev/null
	@rm -fv $(ASM) $(DASM) $(COREWAR)

re: fclean all

.PHONY: clean fclean re all
