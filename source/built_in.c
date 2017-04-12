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
		ft_print_2d_tab_no_nl(&split[1]);
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

static	char	*check_path_env(char *cmd, char **env)
{
	char	**split;
	size_t	i;
	char	*path;
	size_t	ret;

	i = 0;
	ret = 0;
	while (env[i] && (ret = ft_strncmp("PATH=", env[i], ft_strclen(env[i], '=')) != 0))
		++i;
	if (ret != 0)
		return (NULL);
	path = (char *)ft_memalloc(sizeof(char) * ft_strlen(env[i]));
	split = ft_strsplit(env[i], ':');
	if (path == NULL || split == NULL)
		ft_critical_error(MALLOC_ERROR);
	i = 0;
	while (split[i])
	{
		ret = ft_strclen(split[i], '/');
		ft_strcpy(path, &split[i][ret]);
		ft_strcat(path, "/");
		ft_strcat(path, cmd);
		if (access(path, X_OK) == 0)
		{
			ft_2d_tab_free(split);
			return (path);
		}
		++i;
	}
	ft_2d_tab_free(split);
	ft_strdel(&path);
	return (NULL);
}

static void	execute(char **env, char *trim)
{
	pid_t	father;
	char	**split;
	int		status;
	char	*path;

	if ((split = ft_strsplit_blank(trim)) == NULL)
		ft_critical_error(MALLOC_ERROR);
	if ((path = check_path_env(split[0], env)) != NULL)
		ft_strcpy(split[0], path);
	ft_strdel(&path);
	if (access(split[0], X_OK) == 0)
	{
		father = fork();
		if (father < 0)
			ft_dprintf(2, RED"Fork failure\n"END);
		else if (father > 0)
		{
			waitpid(father, &status, 0);
			kill(father, SIGTERM);
		}
		else
		{
			if (execve(split[0], &split[0], env) < 0)
				ft_dprintf(1, "Error !\n");
			exit(EXIT_FAILURE);
		}
	}
	else
		ft_dprintf(2, RED"%s: Command not found !\n"END, split[0]);
	ft_2d_tab_free(split);
}

bool	built_in(char *line, t_ctrl *ctrl, char **env)
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
	else
		execute(env, trim);
	ft_2d_tab_free(split);
	ft_strdel(&trim);
	return (EXIT_FAILURE);
}
