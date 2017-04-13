/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/09 05:08:03 by rabougue          #+#    #+#             */
/*   Updated: 2017/04/10 05:17:30 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	quit(t_ctrl *ctrl)
{
	t_environ	*tmp;

	tmp = ctrl->first;
	if (ctrl->first != NULL)
		while (ctrl->first->next)
		{
			while (tmp->next->next)
				tmp = tmp->next;
			ft_strdel(&tmp->next->env);
			free(tmp->next);
			tmp->next = NULL;
			tmp = ctrl->first;
		}
	ft_strdel(&tmp->env);
	free(tmp);
	tmp = NULL;
}

static void	prompt()
{
	char	path[PATH_LENGHT];

	getcwd(path, PATH_LENGHT);
	ft_dprintf(1, CYAN"\n%s => "END, path);
}

void	write_history(char *line)
{
	int	fd;

	if ((fd = (open("/Users/rabougue/.minishell_history", O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR))) > 0)
	{
		ft_dprintf(fd, "%d : %s\n", time(0), line);
		close(fd);
	}
}

int	main(int argc, char **argv, char **environ)
{
	char	*line;
	t_ctrl	ctrl;
	char	**env;
	char	dir[PATH_LENGHT];

			signal(SIGINT, prompt);
	line = NULL;
	ft_memset(&ctrl, 0, sizeof(t_ctrl));
	create_env(&ctrl, environ);
	if (argc != 1)
	{
		ft_dprintf(2, "Too many arguments");
		return (EXIT_FAILURE);
	}
	else
	{
		while (0xDEADBEEF)
		{
			getcwd(dir, PATH_LENGHT);
			env = lst_to_2d_tab(&ctrl);
			ft_dprintf(1, CYAN"%s => "END, dir);
			get_next_line(STDERR_FILENO, &line);
			if (line != NULL && ft_strlen(line) > 0)
			{
				if (built_in(line, &ctrl, env) == EXIT_SUCCESS)
				{
					write_history("exit");
					ft_strdel(&line);
					free(env);
					break ;
				}
			}
			write_history(line);
			ft_strdel(&line);
			free(env);
		}
	}
	quit(&ctrl);
	return (0);
}
