/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/09 05:08:03 by rabougue          #+#    #+#             */
/*   Updated: 2017/04/10 05:17:30 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	quit(t_env *env)
{
	ft_2d_tab_free(env->environnement);
}

int	main(int argc, char **argv)
{
	char	*line;
	t_env	env;

	line = NULL;
	ft_memset(&env, 0, sizeof(t_env));
	create_env(&env);
	if (argc != 1)
	{
		ft_dprintf(2, "Too many arguments");
		return (EXIT_FAILURE);
	}
	else
		while (0xDEADBEEF)
		{
			ft_dprintf(1, CYAN"$> "END);
			get_next_line(STDERR_FILENO, &line);
			if (line != NULL/* && ft_strlen(line) > 0*/)
				if (built_in(line, &env) == EXIT_SUCCESS)
				{
					ft_strdel(&line);
					break ;
				}
			ft_strdel(&line);
		}
	quit(&env);
	return (0);
}
