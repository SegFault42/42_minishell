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

#define SIZE_ENV_TAB 2 + 1

void	add_env_varaible(char *variable)
{

}

void	create_env(t_env *env)
{
	env->environnement = (char **)ft_memalloc(sizeof(char *) * SIZE_ENV_TAB);
	env->environnement[0] = ft_strdup("HOME=/Users/rabougue");
	env->environnement[1] = ft_strdup("PATH=/usr/bin:/bin:/usr/sbin:/sbin");
	env->environnement[SIZE_ENV_TAB -1] = NULL;
}

