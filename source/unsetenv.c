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

static size_t	loop(char **split, t_environ *tmp, char **split_env)
{
	size_t	i;

	i = 1;
	if (split != NULL && ft_count_2d_tab(split) > 1)
		while (tmp)
		{
			if ((split_env = ft_strsplit(tmp->env, '=')) == NULL)
				ft_critical_error(MALLOC_ERROR);
			if (ft_strcmp(split[1], split_env[0]) == 0)
			{
				ft_2d_tab_free(split_env);
				return (i);
			}
			ft_2d_tab_free(split_env);
			tmp = tmp->next;
			++i;
		}
	if (tmp == NULL)
		ft_dprintf(2, RED"Environement variable not exist\n"END);
	return (i);
}

void			built_in_unsetenv(char *cmd, t_ctrl *ctrl)
{
	t_environ	*tmp;
	char		**split;
	char		**split_env = NULL;
	size_t		i;

	i = 1;
	tmp = ctrl->first;
	if ((split = ft_strsplit_blank(cmd)) == NULL)
		ft_critical_error(MALLOC_ERROR);
	if (split[1] != NULL)
	{
		i = loop(split, tmp, split_env);
		if (tmp != NULL && i <= count_nb_node(ctrl))
			destroy_node(ctrl, i);
	}
	if (split != NULL)
		ft_2d_tab_free(split);
}

