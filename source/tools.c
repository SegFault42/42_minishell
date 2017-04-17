#include "../include/minishell.h"

char	*get_path(char *line)
{
	size_t	i;
	char	**split;

	i = 0;
	while (line[i] && line[i] != ' ' && line[i] != '\t')
		++i;
	while (line[i] == ' ' || line[i] == '\t')
		++i;
	if ((split = ft_strsplit(&line[i], ' ')) == NULL)
		ft_critical_error(MALLOC_ERROR);
	if (ft_count_2d_tab(split) > 1)
	{
		ft_dprintf(2, RED"cd: too many arguments\n"END);
		ft_2d_tab_free(split);
		return (NULL);
	}
	ft_2d_tab_free(split);
	return (&line[i]);
}

void	quit(t_ctrl *ctrl)
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

void	prompt(void)
{
	char	path[PATH_LENGHT];

	getcwd(path, PATH_LENGHT);
	ft_dprintf(1, CYAN"\n%s => "END, path);
}

void	write_history(char *line)
{
	int	fd;

	if ((fd = (open("/Users/rabougue/.minishell_history",
	O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR))) > 0)
	{
		ft_dprintf(fd, "%d : %s\n", time(0), line);
		close(fd);
	}
}

bool	quit_shell(char **line, char ***env, t_ctrl *ctrl)
{
	write_history("exit");
	ft_strdel(line);
	free(*env);
	quit(ctrl);
	exit(EXIT_SUCCESS);
}

