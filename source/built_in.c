/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/09 06:17:58 by rabougue          #+#    #+#             */
/*   Updated: 2017/04/10 01:18:08 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

#define PATH_LENGHT 1024

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

static void	built_in_cd(char *line)
{
	char	current_dir[PATH_LENGHT];
	char	new_dir[ft_strlen(line)];

	ft_memset(&new_dir, 0, ft_strlen(line));
	ft_memset(&current_dir, 0, PATH_LENGHT);
	ft_strcpy(new_dir, get_path(line));
	if (new_dir[0] == '/')
		absolute_path(new_dir);
	/*else*/
		/*relative_path();*/

	getcwd(current_dir, PATH_LENGHT);
	ft_dprintf(1, "current_dir = %s\n", current_dir);
}

bool	built_in(char *line, char **environ)
{
	if (ft_strncmp("exit", line, 4) == 0)
		return(EXIT_SUCCESS);
	else if (ft_strncmp("echo", line, 4) == 0)
		built_in_echo(line);
	else if (ft_strncmp("cd", line, 2) == 0)
		built_in_cd(line);
	else if (ft_strcmp("env", line) == 0)
		ft_print_2d_tab(environ);
	else
		ft_dprintf(2, RED"%s : Command not found!\n"END, line);
	return (EXIT_FAILURE);
}
