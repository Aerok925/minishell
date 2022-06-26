NAME = minishell

SRCS =	main.c enpv_init.c free_lst_enpv.c ft_minishell.c ft_parsing.c\
		ft_utils_1.c ft_utils_2.c ft_utils_3.c ft_utils_4.c ft_parsing_redirect.c\
		ft_pars_dollar.c ft_pars_quote.c ft_pars_slesh.c ft_heredoc.c\
		ft_cmp.c found_info_in_elements.c ft_add_commands.c ft_error_redirect_1.c\
		add_elen_lst.c init_shlvl.c init_pwd.c get_adrees_info.c\
		init_old_pwd.c exec_pwd.c ft_pre_parsing.c ft_error_redirect_0.c\
		ft_strcon.c distribution_command.c declare.c init_last_command.c \
		small_letter.c exec_exit.c int_to_str.c free_arr.c ft_open_fd.c\
		free_command_lst.c exec_env.c sorted_ascii.c fd_put_str.c cp_arr.c \
		export_branch.c del_elem_lst.c check_arg_for_unset.c add_to_.c \
		exec_cd.c execve/init_ready__command.c  execve/create_path.c \
		execve/create_options.c arr_len.c add_arr_in_arr.c \
		execve/env_in_arr.c execve/free_ready_command.c \
		execve/execve_on.c execve/redirect.c init_redir.c \
		exec_echo.c execve/error_redir.c execve/redir_help_in_file.c \
		print_env.c free_exit.c help_shlvl.c help_sort_ascii.c \
		distrib_for_pipe.c dis_command.c help_multipipe.c \
		signal.c

CC = gcc

FLAGS =  -lreadline

WWW = -g -Wall -Wextra -Werror

INCLUDES = minishell.h

OBJS = ${SRCS:.c=.o}

UNAME := $(shell uname)
ifeq ($(UNAME),Darwin)
	UNAME_M := $(shell uname -m)
	ifeq ($(UNAME_M),x86_64)
		FLAGS	+= -I${HOME}/.brew/opt/readline/include
		LDLIBS	+= -L${HOME}/.brew/opt/readline/lib
	endif
	ifeq ($(UNAME_M),arm64)
		FLAGS	+= -I/opt/homebrew/opt/readline/include
		LDLIBS	+= -L/opt/homebrew/opt/readline/lib
	endif
endif

.PHONY: all clean fclean re

.c.o:
	$(CC) $(WWW) -c $< -o $@

$(NAME): $(SRCS) $(OBJS) $(INCLUDES)
	$(CC) $(OBJS) $(FLAGS) $(LDLIBS) -I$(INCLUDES) -o $(NAME)

all : $(NAME)

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all