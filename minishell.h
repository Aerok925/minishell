/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnappa <jnappa@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:47:20 by jnappa            #+#    #+#             */
/*   Updated: 2022/02/18 19:38:14 by jnappa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <limits.h>
# include <fcntl.h>

# define ERR1 "minishell: ./minishell: The program must not have arguments\n"
# define ERR_PIPE "minishell: syntax error near unexpected token `|'\n"
# define ERR_CTRL_D "minishell: warning: document at line delimit by endoffile"
# define ERR_QUOTES "Error, not a pair of quotes\n"
# define ISSPACE "\r\f\t\v\n "
# define O_W O_WRONLY
# define O_C O_CREAT
# define O_T O_TRUNC
# define O_A O_APPEND
# define O_R O_RDONLY

typedef struct s_ready_command
{
	char	*path_comand;
	char	**options;
	char	**env;
}	t_ready_command;

typedef struct s_enpv
{
	struct s_enpv	*next;
	char			*name;
	char			*info;
	int				exp;
}	t_enpv;

//options and arg - равна NULL если аргументов нет
//in_file -  файл в дискриптор которого мы бдуем записывать
//out_file - файл из дискриптора которого мы будем брать инфу
//in_in_file - файл дискриптор которого дополнять
//по дефолту они все должны адресовать на нулл
//flag - 0 ничего нет 1 обычный ред 2 двойной ред

typedef struct s_command
{
	struct s_command	*next;
	char				*line;
	char				*command;
	char				**arg;
	char				*options;
	char				**in_file;
	char				**out_file;
	char				**in_in_file;
	char				**heredoc;
	int					flag;
	int					flag_heredoc;
	int					index;
	int					fd_in;
	int					fd_out;
	pid_t				pidor;
}	t_com;

typedef struct s_mini
{
	t_com	*com;
	int		quote;
	int		flag;
	int		pipes;
	int		minus;
	int		arrow;
	int		exit;
}	t_mini;

typedef struct s_redir
{
	int	main_in;
	int	main_out;
	int	my_out;
	int	my_in;
}	t_redir;

//функции для структуры команды execve
void	init_struct(t_enpv *env, t_enpv *declare, t_com *command);
void	free_struct_ready_command(t_ready_command *ready_command);
void	create_path(t_enpv *env, t_ready_command *ready_com, t_com *command);
void	create_options_for_command(t_com *com, t_ready_command *rd_com);
void	execve_on(t_ready_command *rd_com, t_enpv *declare);
void	error_path(t_enpv *declare, t_com *com, t_ready_command *ready);
void	redirect_main(t_redir *rc, t_com *com, t_enpv *declare);
t_redir	*init_redirect(t_com *com, t_enpv *declare, int flag);

//multipipehelp
void	child_process(t_enpv *lst, t_mini *mini, t_enpv *declare, char *line);
void	pipe_multipipe(int	*fdout, int *fdin);
void	refresh_fd(int tmpin, int tmpout, int fdin, int fdout);
void	wait_multipipe(t_mini *mini);
void	close_fd_multipipe(t_mini *mini);

//залупень по листам enpv
void	init_shlvl(t_enpv *lst);
int		help_shlvl(int number, t_enpv *shlvl_lst);
void	lst_add_back(t_enpv *lst, char *name, char *info);

//signal
void	sig_int(void);

t_enpv	*enpv_init(char **enpv);
int		ft_cmp(char *str_one, char *str_two);
void	init_pwd(t_enpv *lst); // принимает полный список enpv
void	init_old_pwd(t_enpv *ls);
t_enpv	*init_declare(void);
void	init_last_command(t_enpv *lst);
void	env_in_arr(t_enpv *env, t_ready_command *rd_com);
t_enpv	*dis_command_for_pipe(t_enpv *lst, t_mini *mini, t_enpv *declare,
			char *line);
t_enpv	*dis_command(t_enpv *lst, t_mini *mini, t_enpv *declare, char *line);

t_enpv	*del_elem_lst(t_enpv *lst, char *str);
void	print_env(t_enpv *lst);

void	exec_cd(t_enpv *lst, t_enpv *declare, t_com *command); //cd

void	check_arg_for_unset(char **arr, t_enpv *declare);
void	add_to_(t_enpv *declare, t_com *command);
char	**add_str_in_arr(char **arr, char *str);

//очистка
void	free_arr(char **arr);
void	free_lst_command(t_com *lst);
void	free_lst(t_enpv *lst);
void	free_exit(t_enpv *my_envp, t_enpv *declare, char *line, t_mini *mini);
char	**add_to_array(char **opt, char **arg);
char	**exit_help(t_com *command);

//распределение команд для export
void	out_export_lst(t_enpv *lst);
void	exec_branch(t_enpv *lst, t_com	*com, t_enpv *declare);
void	help_sort_ascii(char **max, t_enpv *next, char **arr, int y);

//конкатинация 3 строк
char	*ft_str_con_three(char *str_one, char *str_two, char *str_three);
//поиск команды по env
void	found_path(t_enpv *lst, t_com *com, t_enpv *declare);
//разветвление по командам
t_enpv	*distribution_command(t_enpv *lst, t_mini *mini,
			t_enpv *declare, char *line);
void	small_letter(t_com *com); //все символы в команде станут мелкими

char	*int_to_str(int number);

//всякие приколы с массивом
int		size_of_array_char(char **arr);
char	**copy_arr(char **arr);
int		arr_len(char **arr);
char	**add_arr_in_arr(char **arr, char **arr2);

//файлы для запуска ручных команд
void	exec_exit(t_enpv *my_envp, t_enpv *declare, char *line, t_mini *mini);
void	exec_pwd(t_enpv *declare);
void	exec_env(t_enpv *lst, t_com *command, t_enpv *declare);
void	exec_echo(t_com *com, t_enpv *declare);

char	*copy_str(char *str, int begin, int end);
char	*ft_get_info(t_enpv *lst, char *found);
t_enpv	*get_adress_info(t_enpv *lst, char *str);

//erreor redirect
void	error_no_file(char *file_name, t_enpv *declare);
void	error_permisson_denaid(char *file_name, t_enpv *declare);

//help_redir_in_file
int		redir_out_mini_part_one(t_redir *rc, t_com *com, t_enpv *declare);
int		redir_out_mini_part_two(t_redir *rc, t_com *com, t_enpv *declare);

void	fd_putstr(char *str, int fd);

//main
void	signal_handler(int sig);
t_com	*com_init(char *str, int i);
void	ft_add_next(t_com **com, char *line, int i);
void	shell_init(t_mini **new);
t_com	*ft_com_next(t_com **com);

int	g_kost;

//ft_utils_1
int		ft_strcmp(const char *s1, const char *s2);
int		ft_search(char const *set, char c);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strjoin(char *s1, char *s2);

//ft_utils_2
int		ft_isspace(char c);
char	*ft_strstr(char *big, char *little);
char	*ft_strdup(char *s);
char	*ft_charjoin(char *s1, char c);

//ft_utils_3
size_t	ft_strlen(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);

//ft_utils_4
int		ft_isdigit(int c);
int		ft_islower(int c);
int		ft_isupper(int c);
int		ft_isalpha(int c);
int		ft_isalnum(int c);

//ft_minishell
void	ft_minishell(t_enpv **my_envp, t_enpv **decl);

//ft_pre_parsing
void	ft_pre_parsing(t_mini **mini, t_enpv **env, t_enpv **decl, char *line);

//ft_parsing
int		ft_key(char c);
int		ft_open_quote(char *line, char c, int i, int flag);
char	*ft_parsing(t_enpv **env, t_enpv **decl, char *line);

//ft_pars_quote
char	*ft_pars_quote_1(char *line, int *i);
char	*ft_pars_quote_2(t_enpv **env, t_enpv **my_envp, char *line, int *i);

//ft_pars_slesh
char	*ft_pars_slesh(char *line, int *i);

//ft_pars_dollar
char	*ft_pars_dollar(t_enpv **env, t_enpv **my_envp, char *line, int *i);

//ft_add_commands
void	ft_add_commands(t_com **com, char **line);
void	ft_pars_files(t_enpv **env, t_enpv **decl, t_com **com);

//ft_parsing_redirect
void	ft_while_redirect(char *line, int *i);
char	*ft_redirect_out(t_com **com, char *line, int *i);
char	*ft_redirect_in(t_com **com, char *line, int *i);
char	*ft_redirect_in_in(t_com **com, char *line, int *i);
char	*ft_pars_redirect(t_mini **mini, t_com **com, char *str);

//ft_error_redirect_0
int		ft_error(char *error);
char	*ft_print_error_redirect(char *line);
char	*ft_error_redirect(char *s, int i);
void	ft_add_file(t_com **com, char *tmp, int k);

//ft_error_redirect_1
int		ft_marker_redirect(char *s, int *i, char c);
char	*ft_found_error_red(char *s, int *i, char c);

//ft_heredoc
char	*ft_redirect_heredoc(t_com **com, char *line, int *i);
void	ft_heredoc(char *name);
void	ft_heredoc_add(t_enpv **env, t_enpv **decl, t_com **com);

//ft_open_fd
void	ft_open_in(t_com **com);
void	ft_open_in_in(t_com **com);
void	ft_open_out(t_com **com);

#endif
