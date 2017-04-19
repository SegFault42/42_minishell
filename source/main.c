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

int	main(int argc, char **argv, char **environ)
{
	t_ctrl	ctrl;
	char	*line;
	char	**env;
	char	dir[PATH_LENGHT];

	(void)argv;
	(void)argc;
	ft_memset(&ctrl, 0, sizeof(t_ctrl));
	create_env(&ctrl, environ);
	while (0xDEADBEEF)
	{
		env = lst_to_2d_tab(&ctrl);
		getcwd(dir, PATH_LENGHT);
		ft_dprintf(1, CYAN"{%s}=> "END, dir);
		signal(SIGINT, (void*)prompt);
		get_next_line(STDERR_FILENO, &line);
		if (line != NULL && ft_strlen(line) > 0)
			if (built_in(line, &ctrl, env) == EXIT_SUCCESS)
				quit_shell(&line, &env, &ctrl);
		write_history(line);
		ft_strdel(&line);
		free(env);
	}
}
