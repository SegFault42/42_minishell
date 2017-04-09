/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/09 06:17:58 by rabougue          #+#    #+#             */
/*   Updated: 2017/04/09 09:15:07 by rabougue         ###   ########.fr       */
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

void	built_in(char *line, char **environ)
{
	if (ft_strcmp("exit", line) == 0)
		exit(EXIT_SUCCESS);
	else if (ft_strcmp("env", line) == 0)
		ft_print_2d_tab(environ);
	else if (ft_strncmp("echo", line, 4) == 0)
		built_in_echo(line);
	else
		ft_dprintf(2, RED"%s : Command not found!\n"END, line);
}
