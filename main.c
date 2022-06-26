/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnappa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 22:43:01 by jnappa            #+#    #+#             */
/*   Updated: 2022/03/05 22:43:02 by jnappa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int sig)
{
	if (sig == SIGINT)
		sig_int();
	else if (sig == SIGQUIT)
	{
		if (g_kost == 2)
		{
			printf("Quit: 3\n");
			g_kost = 1;
		}
		else
		{
			rl_on_new_line();
			rl_redisplay();
		}
	}
}

t_com	*com_init(char *str, int i)
{
	t_com	*new;

	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->line = ft_strdup(str);
	new->command = NULL;
	new->arg = NULL;
	new->options = NULL;
	new->in_file = NULL;
	new->out_file = NULL;
	new->in_in_file = NULL;
	new->heredoc = NULL;
	new->flag_heredoc = 0;
	new->flag = 0;
	new->index = i;
	new->fd_in = 0;
	new->fd_out = 0;
	return (new);
}

void	ft_add_next(t_com **com, char *line, int i)
{
	t_com	*new;
	t_com	*tmp;

	new = com_init(line, i);
	free(line);
	tmp = (*com);
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}

void	shell_init(t_mini **new)
{
	(*new) = malloc(sizeof(t_mini));
	if (!(*new))
		exit(EXIT_FAILURE);
	(*new)->com = com_init(NULL, 0);
	(*new)->quote = 0;
	(*new)->pipes = 0;
	(*new)->flag = 0;
	(*new)->minus = 0;
	(*new)->arrow = -1;
	(*new)->exit = 0;
}

int	main(int ac, char **av, char **env)
{
	t_enpv	*my_enpv;
	t_enpv	*declare;

	(void)ac;
	(void)av;
	g_kost = 0;
	my_enpv = enpv_init(env);
	declare = init_declare();
	if (ac == 1)
	{
		signal(SIGTERM, SIG_IGN);
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, signal_handler);
		ft_minishell(&my_enpv, &declare);
	}
	else
		ft_error(ERR1);
	return (0);
}
