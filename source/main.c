/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/09 05:08:03 by rabougue          #+#    #+#             */
/*   Updated: 2017/04/10 00:53:38 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **environ)
{
	char	*line;

	line = NULL;
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
			if (line != NULL)
				if (built_in(line, environ) == EXIT_SUCCESS)
					break ;
			ft_strdel(&line);
		}
	return (0);
}
