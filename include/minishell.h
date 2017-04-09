/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/09 03:34:39 by rabougue          #+#    #+#             */
/*   Updated: 2017/04/09 09:15:05 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "../libft/includes/libft.h"


typedef struct	s_list
{
	char		*env;
	s_list		*next;
}				t_list;

typedef struct	s_ctrl
{
	t_list		*first;
}				t_ctrl;

/*
**===================================built_in.c================================
*/
void	built_in(char *line, char **environ);


#endif
