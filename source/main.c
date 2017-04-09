/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/09 05:08:03 by rabougue          #+#    #+#             */
/*   Updated: 2017/04/09 06:34:02 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **environ)
{
	char	*line;

	while (0xDEADBEEF)
	{
		ft_dprintf(1, CYAN"$> "END);
		get_next_line(STDERR_FILENO, &line);
		built_in(line, environ);
	}
}
