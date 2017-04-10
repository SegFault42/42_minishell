/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/09 03:34:39 by rabougue          #+#    #+#             */
/*   Updated: 2017/04/10 04:48:56 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"

# define PATH_LENGHT 1024

# define HOME	0
# define PATH	1

typedef struct	s_env
{
	char		**environnement;
}				t_env;

/*
**===================================built_in.c================================
*/
bool				built_in(char *line, t_env *env);
/*
**==============================built_in_get_path.c============================
*/
char				*get_path(char *line);
void				change_path(char *new_dir, t_env *env);
/*
**===================================env.c=====================================
*/
void	create_env(t_env *env);

#endif
