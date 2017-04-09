/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 00:05:35 by rabougue          #+#    #+#             */
/*   Updated: 2017/04/10 01:21:17 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

#include <errno.h>

void	absolute_path(char *new_dir)
{
	if (chdir(new_dir) < 0)
		ft_dprintf(2, "cd: no such file or directory: %s\n", new_dir);
}

char	*get_path(char *line)
{
	size_t	i;
	char	**split;

	i = 0;
	split = NULL;
	while (line[i] != ' ')
		++i;
	while (line[i] == ' ' || line[i] == '\t')
		++i;
	split = ft_strsplit(&line[i], ' ');
	if (ft_count_2d_tab(split) > 1)
		ft_dprintf(2, "cd: too many arguments\n");
	ft_2d_tab_free(split);
	return (&line[i]);
}
