/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 00:05:35 by rabougue          #+#    #+#             */
/*   Updated: 2017/04/19 17:45:23 by rabougue         ###   ########.fr       */
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
	if (tmp == NULL)
	{
		ft_dprintf(2, RED"HOME variable not set in environment\n"END);
		return ;
	}
	while (ft_strncmp(tmp->env, "HOME", 4) != 0)
	{
		if (tmp->next == NULL)
		{
			ft_dprintf(2, RED"HOME variable not set in environment\n"END);
			return ;
		}
		tmp = tmp->next;
	}
	if (chdir(&tmp->env[5]) < 0)
		ft_dprintf(2, RED"cd: no such file or directory: %s\n"END, tmp->env);
}

static void	split_change_path(size_t l, char **new_dir, char *old_dir, char *t)
{
	static char	current_dir[PATH_LENGHT] = {0};

	if (l == 1 && *new_dir[0] == '-')
	{
		if (chdir(t) < 0)
			ft_dprintf(2, RED"cd: no such file or directory: %s\n"END, t);
		ft_strcpy(t, old_dir);
	}
	else
	{
		getcwd(current_dir, PATH_LENGHT);
		relative_path(*new_dir);
		ft_strcpy(t, old_dir);
	}
}

void		change_path(char *new_dir, t_ctrl *ctrl)
{
	size_t		len_new_dir;
	static char	current_dir[PATH_LENGHT] = {0};
	static char	tmp[PATH_LENGHT] = {0};
	static char	old_dir[PATH_LENGHT] = {0};

	getcwd(old_dir, PATH_LENGHT);
	len_new_dir = ft_strlen(new_dir);
	if (tmp[0] == '\0')
		getcwd(tmp, PATH_LENGHT);
	if (len_new_dir == 0 || (len_new_dir == 1 && new_dir[0] == '~'))
	{
		getcwd(current_dir, PATH_LENGHT);
		home_path(ctrl);
		ft_strcpy(tmp, old_dir);
	}
	else if (new_dir[0] == '/')
	{
		getcwd(current_dir, PATH_LENGHT);
		absolute_path(new_dir);
		ft_strcpy(tmp, old_dir);
	}
	else
		split_change_path(len_new_dir, &new_dir, old_dir, tmp);
}
