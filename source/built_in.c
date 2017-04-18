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

void		built_in_echo(char *line, char **env)
{
	int		j;
	char	**split;
	char	**split_env;

	j = 0;
	if ((split = ft_strsplit_blank(line)) == NULL)
		ft_critical_error(MALLOC_ERROR);
	if (split[1] != NULL && split[1][0] == '$')
	{
		while (j < ft_count_2d_tab(env))
		{
			split_env = ft_strsplit(env[j], '=');
			if (ft_strcmp(split_env[0], &split[1][1]) == 0)
			{
				ft_dprintf(1, "%s\n", env[j]);
				ft_2d_tab_free(split_env);
				break ;
			}
			ft_2d_tab_free(split_env);
			++j;
		}
	}
	else if (ft_count_2d_tab(split) > 1)
		ft_print_2d_tab_no_nl(&split[1]);
	ft_2d_tab_free(split);
}

void		built_in_cd(char *line, t_ctrl *ctrl)
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

static bool	check_trim(char **trim, char ***multi_cmd)
{
	if (*trim[0] == '\0')
	{
		ft_strdel(trim);
		ft_2d_tab_free(*multi_cmd);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static bool	if_forest(char ***env, char **trim, t_ctrl *ctrl)
{
	char	**split;

	if ((split = ft_strsplit_blank(*trim)) == NULL)
		ft_critical_error(MALLOC_ERROR);
	if (ft_strcmp("exit", split[0]) == 0)
	{
		ft_2d_tab_free(split);
		return (EXIT_SUCCESS);
	}
	else if (ft_strcmp("echo", split[0]) == 0)
		built_in_echo(*trim, *env);
	else if (ft_strcmp("cd", split[0]) == 0)
		built_in_cd(*trim, ctrl);
	else if (ft_strcmp("env", split[0]) == 0)
		print_lst(ctrl);
	else if (ft_strcmp("setenv", split[0]) == 0)
		built_in_setenv(*trim, ctrl);
	else if (ft_strcmp("unsetenv", split[0]) == 0)
		built_in_unsetenv(*trim, ctrl);
	else
		execute(*env, *trim);
	ft_2d_tab_free(split);
	return (EXIT_FAILURE);
}

bool		built_in(char *line, t_ctrl *ctrl, char **env)
{
	char	*trim;
	char	**multi_cmd;
	int		i;

	i = 0;
	if ((multi_cmd = ft_strsplit(line, ';')) == NULL)
		ft_critical_error(MALLOC_ERROR);
	while (multi_cmd[i])
	{
		if ((trim = ft_strtrim(multi_cmd[i])) == NULL)
			ft_critical_error(MALLOC_ERROR);
		if (check_trim(&trim, &multi_cmd) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (if_forest(&env, &trim, ctrl) == EXIT_SUCCESS)
		{
			ft_strdel(&trim);
			ft_2d_tab_free(multi_cmd);
			return (EXIT_SUCCESS);
		}
		ft_strdel(&trim);
		++i;
	}
	ft_2d_tab_free(multi_cmd);
	return (EXIT_FAILURE);
}
