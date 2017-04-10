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

t_environ	*create_maillon(void)
{
	t_environ	*new;

	if ((new = (t_environ *)malloc(sizeof(t_environ))) == NULL)
		ft_critical_error(MALLOC_ERROR);
	ft_memset(new, 0, sizeof(t_environ));
	return (new);
}

void	add_tail(t_ctrl *ctrl, char *str)
{
	t_environ	*new;
	t_environ	*tmp;

	tmp = ctrl->first;
	new = create_maillon();
	if (ctrl->first == NULL)
		ctrl->first = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	if ((new->env = ft_strdup(str)) == NULL)
		ft_critical_error(MALLOC_ERROR);
	new->next = NULL;
}

void	print_lst(t_ctrl *ctrl)
{
	t_environ	*tmp;

	tmp = ctrl->first;
	while (tmp)
	{
		ft_dprintf(1, PURPLE"%s\n"END, tmp->env);
		tmp = tmp->next;
	}
}
