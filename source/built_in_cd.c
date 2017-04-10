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

void	home_path(char *path)
{
	if (chdir(path) < 0)
		ft_dprintf(2, RED"cd: no such file or directory: %s\n"END, path);
}

void	change_path(char *new_dir, t_env *env)
{
	if (ft_strlen(new_dir) == 0)
		home_path(&env->environnement[HOME][5]);
	if (new_dir[0] == '/')
		absolute_path(new_dir);
	else
		relative_path(new_dir);
}

char	*get_path(char *line)
{
	size_t	i;
	char	**split;

	i = 0;
	split = NULL;
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
