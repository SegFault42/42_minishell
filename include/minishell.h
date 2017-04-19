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
# include <sys/stat.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <errno.h>
# include <time.h>

# define PATH_LENGHT	1024
# define HOME			0
# define PATH			1

typedef struct			s_environ
{
	char				*env;
	struct s_environ	*next;
}						t_environ;

typedef struct			s_ctrl
{
	t_environ			*first;
}						t_ctrl;

/*
**===================================built_in.c================================
*/
bool					built_in(char *line, t_ctrl *ctrl, char **envrion);
void					built_in_cd_and_echo(char *l, t_ctrl *ctrl, uint8_t id);
/*
**==============================built_in_get_path.c============================
*/
char					*get_path(char *line);
void					change_path(char *new_dir, t_ctrl *ctrl);
/*
**===================================env.c=====================================
*/
/*
**=================================tools.c=====================================
*/
void					write_history(char *line);
bool					quit_shell(char **line, char ***env, t_ctrl *ctrl);
void					prompt(void);
void					destroy_lst(t_ctrl *ctrl);
char					*get_path(char *line);
/*
**=================================execute.c===================================
*/
void					execute(char **env, char *trim);
/*
**=================================unsetenv.c==================================
*/
void					built_in_unsetenv(char *cmd, t_ctrl *ctrl);
/*
**====================================lst_2.c==================================
*/
void					destroy_node(t_ctrl *ctrl, size_t i);
void					add_tail(t_ctrl *ctrl, char *str);
void					print_lst(t_ctrl *ctrl);
void					built_in_setenv(char *cmd, t_ctrl *ctrl);
void					built_in_unsetenv(char *cmd, t_ctrl *ctrl);
void					destroy_node(t_ctrl *ctrl, size_t i);
void					create_env(t_ctrl *ctrl, char **envrion);
size_t					count_nb_node(t_ctrl *ctrl);
char					**lst_to_2d_tab(t_ctrl *ctrl);

#endif
