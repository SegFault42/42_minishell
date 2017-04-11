/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 03:41:00 by rabougue          #+#    #+#             */
/*   Updated: 2017/04/10 04:15:59 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	create_env(t_ctrl *ctrl)
{
	add_tail(ctrl, "PATH=/usr/bin:/bin:/usr/sbin:/sbin");
	add_tail(ctrl, "HOME=/Users/rabougue");
}

void	built_in_setenv(char *cmd, t_ctrl *ctrl)
{
	char	**split;
	size_t	i;

	i = 0;
	while (cmd[i] && cmd[i] != ' ' && cmd[i] != '\t')
		++i;
	while (cmd[i] == ' ' || cmd[i] == '\t')
		++i;
	if (ft_str_isspace(&cmd[i]) == true)
		ft_dprintf(2, RED"No space allowed. Usage : setenv foo=bar\n"END);
	else
	{
		split = ft_strsplit(&cmd[i], '=');
		if (ft_count_2d_tab(split) == 2 && ft_str_isalpha(split[0]) == true)
			add_tail(ctrl, &cmd[i]);
		else
			ft_dprintf(2, RED"Bad formmating. Usage : setenv foo=bar\n"END);
		ft_2d_tab_free(split);
	}
}
