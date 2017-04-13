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
	int		i;
	char	path[PATH_LENGHT];
	char	**split;
	char	*concat;

	i = 0;
	ft_memset(&path, 0, sizeof(char) * PATH_LENGHT);
	concat = NULL;
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
	split = ft_strsplit(path, ':');
	i = 0;
	while (split[i])
	{
		concat = (char *)ft_memalloc(sizeof(char) * (ft_strlen(split[i]) + ft_strlen(cmd)) + 2);
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

static void	execute(char **env, char *trim)
{
	pid_t	father;
	char	**split;
	int		status;
	char	*path;

	if ((split = ft_strsplit_blank(trim)) == NULL)
		ft_critical_error(MALLOC_ERROR);
	if (trim[0] != '/' && trim[0] != '.')
	{
		if ((path = check_path_env(split[0], env)) != NULL)
		{
			ft_strdel(&split[0]);
			split[0] = ft_strdup(path);
			ft_strdel(&path);
		}
		else
		{
			ft_2d_tab_free(split);
			return ;
		}
	}
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
				ft_dprintf(1, RED"Error !\n"END);
			exit(EXIT_FAILURE);
		}
	}
	else
		ft_dprintf(2, RED"Permission denied !\n"END);
	ft_2d_tab_free(split);
}

bool	built_in(char *line, t_ctrl *ctrl, char **env)
{
	char	*trim;
	char	**split;
	char	**multi_cmd;
	int		i;

	i = 0;
	split = NULL;
	multi_cmd = ft_strsplit(line, ';');
	while (multi_cmd[i])
	{
		if ((trim = ft_strtrim(multi_cmd[i])) == NULL)
			ft_critical_error(MALLOC_ERROR);
		if (trim[0] == '\0')
		{
			ft_strdel(&trim);
			ft_2d_tab_free(multi_cmd);
			return (EXIT_FAILURE);
		}
		if ((split = ft_strsplit_blank(trim)) == NULL)
			ft_critical_error(MALLOC_ERROR);
		if (ft_strcmp("exit", split[0]) == 0)
		{
			ft_strdel(&trim);
			ft_2d_tab_free(split);
			ft_2d_tab_free(multi_cmd);
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
		else if (env != NULL)
			execute(env, trim);
		else
			ft_dprintf(2, RED"PATH variable not set in environment\n"END);
		ft_strdel(&trim);
		ft_2d_tab_free(split);
		++i;
	}
	ft_2d_tab_free(multi_cmd);
	return (EXIT_FAILURE);
}
