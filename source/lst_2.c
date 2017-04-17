/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 03:41:00 by rabougue          #+#    #+#             */
/*   Updated: 2017/04/10 04:15:59 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	one_node(t_ctrl *ctrl, t_environ *tmp_rm)
{
	if (ctrl->first->next != NULL)
	{
		ctrl->first = ctrl->first->next;
		ft_strdel(&tmp_rm->env);
		free(tmp_rm);
	}
	else
	{
		ft_strdel(&ctrl->first->env);
		free(ctrl->first);
		ctrl->first = NULL;
	}
}

void		destroy_node(t_ctrl *ctrl, size_t i)
{
	t_environ	*tmp_rm;
	t_ctrl		tmp_save;
	size_t		j;

	j = 1;
	tmp_rm = ctrl->first;
	if (i > 1)
	{
		while (j < i)
		{
			if (j == (i -1))
				tmp_save.first = tmp_rm;
			tmp_rm = tmp_rm->next;;
			++j;
		}
		tmp_save.first->next = tmp_rm->next;
		ft_strdel(&tmp_rm->env);
		free(tmp_rm);
	}
	else
		one_node(ctrl, tmp_rm);
}

