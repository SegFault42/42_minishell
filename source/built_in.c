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

	i = 0;
	while (line[i] != ' ')
		++i;
	while (line[i] == ' ')
		++i;
	ft_dprintf(1, "%s\n", &line[i]);
}

static void	built_in_cd(char *line, t_env *env)
{
	char	new_dir[ft_strlen(line)];
	char	*ptr;

	ptr = get_path(line);
	if (ptr == NULL)
		return ;
	ft_memset(&new_dir, 0, ft_strlen(line));
	ft_strcpy(new_dir, ptr);
	change_path(new_dir, env);
}

bool	built_in(char *line, t_env *env)
{
	char	*trim;

	trim = ft_strtrim(line);
	if (ft_strlen(trim) == 0)
		return (EXIT_FAILURE);
	if (ft_strncmp("exit", trim, 4) == 0)
	{
		ft_strdel(&trim);
		return(EXIT_SUCCESS);
	}
	else if (ft_strncmp("echo", trim, 4) == 0)
		built_in_echo(trim);
	else if (ft_strncmp("cd", trim, 2) == 0)
		built_in_cd(trim, env);
	else if (ft_strcmp("env", trim) == 0)
		ft_print_2d_tab(env->environnement);
	else if (ft_strcmp(trim, "pwd") == 0)
		system("pwd");
	else
		ft_dprintf(2, RED"%s : Command not found!\n"END, trim);
	ft_strdel(&trim);
	return (EXIT_FAILURE);
}
