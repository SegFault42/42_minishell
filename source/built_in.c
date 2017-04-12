/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/09 06:17:58 by rabougue          #+#    #+#             */
/*   Updated: 2017/04/10 05:18:48 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


static void	built_in_echo(char *line)
{
	size_t	i;
	char	**split;

	i = 0;
	if ((split = ft_strsplit_blank(line)) == NULL)
		ft_critical_error(MALLOC_ERROR);
	if (ft_count_2d_tab(split) > 1)
		ft_print_2d_tab(&split[1]);
	ft_2d_tab_free(split);
}

static void	built_in_cd(char *line, t_ctrl *ctrl)
{
	char	new_dir[ft_strlen(line)];
	char	*ptr;

	ptr = get_path(line);
	if (ptr == NULL)
		return ;
	ft_memset(&new_dir, 0, ft_strlen(line));
	ft_strcpy(new_dir, ptr);
	change_path(new_dir, ctrl);
}

static void	execute(t_ctrl *ctrl)
{
	pid_t	father;
	char	*env[] = {"/bin/zsh", NULL};

	father = fork();
	if (father > 0)
	{
		wait(NULL);
		kill(father, SIGTERM);
	}
	else if (father == 0)
	{
		execve(env[0], env, NULL);
	}
	else
		ft_dprintf(2, RED"Execution failed !\n"END);
}

bool	built_in(char *line, t_ctrl *ctrl)
{
	char	*trim;
	char	**split;

	if ((trim = ft_strtrim(line)) == NULL)
		ft_critical_error(MALLOC_ERROR);
	if (trim[0] == '\0')
	{
		ft_strdel(&trim);
		return (EXIT_FAILURE);
	}
	if ((split = ft_strsplit_blank(trim)) == NULL)
		ft_critical_error(MALLOC_ERROR);
	if (ft_strcmp("exit", split[0]) == 0)
	{
		ft_strdel(&trim);
		ft_2d_tab_free(split);
		return (EXIT_SUCCESS);
	}
	else if (ft_strcmp("echo", split[0]) == 0)
		built_in_echo(trim);
	else if (ft_strcmp("cd", split[0]) == 0)
		built_in_cd(trim, ctrl);
	else if (ft_strcmp("env", split[0]) == 0)
		print_lst(ctrl);
	else if (ft_strcmp("setenv", split[0]) == 0)
		built_in_setenv(trim, ctrl);
	else if (ft_strcmp("unsetenv", split[0]) == 0)
		built_in_unsetenv(trim, ctrl);
	else if (ft_strcmp("pwd", split[0]) == 0)
		system("pwd");
	else if (ft_strcmp("/", split[0]) == 0)
		execute(ctrl);
	else
		ft_dprintf(2, RED"%s : Command not found!\n"END, trim);
	ft_2d_tab_free(split);
	ft_strdel(&trim);
	return (EXIT_FAILURE);
}
