/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 00:05:35 by rabougue          #+#    #+#             */
/*   Updated: 2017/04/10 05:10:34 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	relative_path(char *new_dir)
{
	char	current_dir[PATH_LENGHT];

	ft_memset(&current_dir, 0, PATH_LENGHT);
	getcwd(current_dir, PATH_LENGHT);
	ft_strcat(current_dir, "/");
	ft_strcat(current_dir, new_dir);

	if (chdir(current_dir) < 0)
		ft_dprintf(2, RED"cd: no such file or directory: %s\n"END, new_dir);
}

static void	absolute_path(char *new_dir)
{
	if (chdir(new_dir) < 0)
		ft_dprintf(2, RED"cd: no such file or directory: %s\n"END, new_dir);
}

static void	home_path(t_ctrl *ctrl)
{
	t_environ	*tmp;

	tmp = ctrl->first;
	while (ft_strncmp(tmp->env, "HOME", 4) != 0)
	{
		ft_dprintf(1, YELLOW"%s\n"END, tmp->env);
		if (tmp->next == NULL)
		{
			ft_dprintf(2, RED"HOME not set\n"END);
			return ;
		}
		tmp = tmp->next;
	}
	if (chdir(&tmp->env[5]) < 0)
		ft_dprintf(2, RED"cd: no such file or directory: %s\n"END, tmp->env);
}

void	change_path(char *new_dir, t_ctrl *ctrl)
{
	size_t		len_new_dir;
	static char	current_dir[PATH_LENGHT] = {0};

	len_new_dir = ft_strlen(new_dir);
	if (len_new_dir == 0 || (len_new_dir == 1 && new_dir[0] == '~'))
	{
		getcwd(current_dir, PATH_LENGHT);
		home_path(ctrl);
	}
	else if (new_dir[0] == '/')
	{
		getcwd(current_dir, PATH_LENGHT);
		absolute_path(new_dir);
	}
	else if (len_new_dir == 1 && new_dir[0] == '-')
	{
		if (chdir(current_dir) < 0)
			ft_dprintf(2, RED"cd: no such file or directory: %s\n"END, current_dir);
	}
	else
	{
		getcwd(current_dir, PATH_LENGHT);
		relative_path(new_dir);
	}
}

char	*get_path(char *line)
{
	size_t	i;
	char	**split;

	i = 0;
	while (line[i] && line[i] != ' ' && line[i] != '\t')
		++i;
	while (line[i] == ' ' || line[i] == '\t')
		++i;
	split = ft_strsplit(&line[i], ' ');
	if (ft_count_2d_tab(split) > 1)
	{
		ft_dprintf(2, RED"cd: too many arguments\n"END);
		ft_2d_tab_free(split);
		return (NULL);
	}
	ft_2d_tab_free(split);
	return (&line[i]);
}
