#include "../include/minishell.h"

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

