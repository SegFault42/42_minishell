/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/09 06:17:58 by rabougue          #+#    #+#             */
/*   Updated: 2017/04/19 17:45:05 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	**split_check_path_env(char **env)
{
	char	path[PATH_LENGHT];
	char	**split;
	int		i;

	i = 0;
	ft_memset(&path, 0, sizeof(char) * PATH_LENGHT);
	while (env[i])
	{
		if (ft_strncmp("PATH=", env[i], 5) == 0)
			break ;
		++i;
	}
	if (env[i] == NULL)
	{
		ft_dprintf(2, RED"PATH variable not set in environment\n"END);
		return (NULL);
	}
	ft_strcat(path, &env[i][5]);
	if ((split = ft_strsplit(path, ':')) == NULL)
		ft_critical_error(MALLOC_ERROR);
	return (split);
}

static char	*check_path_env(char *cmd, char **env)
{
	int		i;
	char	**split;
	char	*concat;

	i = 0;
	concat = NULL;
	if ((split = split_check_path_env(env)) == NULL)
		return (NULL);
	while (split[i])
	{
		if ((concat = (char *)ft_memalloc(sizeof(char) * (ft_strlen(split[i]) +
		ft_strlen(cmd)) + 2)) == NULL)
			ft_critical_error(MALLOC_ERROR);
		ft_strcat(concat, split[i]);
		ft_strcat(concat, "/");
		ft_strcat(concat, cmd);
		if (access(concat, F_OK) == 0)
			break ;
		ft_strdel(&concat);
		++i;
		if (split[i] == NULL)
			ft_dprintf(2, RED"%s: Command not found !\n"END, cmd);
	}
	ft_2d_tab_free(split);
	return (concat);
}

static char	**prepare_execution(char *trim, char **env)
{
	char	**split;
	char	*path;

	if ((split = ft_strsplit_blank(trim)) == NULL)
		ft_critical_error(MALLOC_ERROR);
	if (trim[0] != '/' && trim[0] != '.')
	{
		if (env != NULL && (path = check_path_env(split[0], env)) != NULL)
		{
			ft_strdel(&split[0]);
			if ((split[0] = ft_strdup(path)) == NULL)
				ft_critical_error(MALLOC_ERROR);
			ft_strdel(&path);
		}
		else
		{
			ft_2d_tab_free(split);
			return (NULL);
		}
	}
	return (split);
}

void		execute(char **env, char *trim)
{
	pid_t	father;
	char	**split;
	int		status;

	if ((split = prepare_execution(trim, env)) == NULL)
		return ;
	if (access(split[0], X_OK) == 0)
	{
		if ((father = fork()) < 0)
			ft_dprintf(2, RED"Fork failure\n"END);
		else if (father > 0)
		{
			waitpid(father, &status, 0);
			kill(father, SIGTERM);
		}
		else
		{
			if (execve(split[0], &split[0], env) < 0)
				ft_dprintf(2, RED"Error !\n"END);
			exit(EXIT_FAILURE);
		}
	}
	else
		ft_dprintf(2, RED"Permission denied !\n"END);
	ft_2d_tab_free(split);
}
