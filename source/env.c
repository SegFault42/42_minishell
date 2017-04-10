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

