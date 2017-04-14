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

char	**lst_to_2d_tab(t_ctrl *ctrl)
{
	size_t		i;
	char		**environ;
	size_t		len_lst;
	t_environ	*tmp;

	i = 0;
	tmp = ctrl->first;
	len_lst = count_nb_node(ctrl);
	environ = NULL;
	if (len_lst > 0)
	{
		if ((environ = (char **)malloc(sizeof(char *) * len_lst + 1)) ==
		NULL)
			ft_critical_error(MALLOC_ERROR);
		while (tmp)
		{
			environ[i] = tmp->env;
			tmp = tmp->next;
			++i;
		}
		environ[i] = NULL;
	}
	return (environ);
}

void	create_env(t_ctrl *ctrl, char **environ)
{
	int	i;

	i = 0;
	if (environ[0] != NULL)
	{
		while (environ[i])
		{
			add_tail(ctrl, environ[i]);
			++i;
		}
	}
	else
	{
		add_tail(ctrl, "PATH=/usr/bin:/bin:/usr/sbin:/sbin");
		add_tail(ctrl, "HOME=/Users/rabougue");
	}
}

void	built_in_unsetenv(char *cmd, t_ctrl *ctrl)
{
	t_environ	*tmp;
	char		**split;
	char		**split_env = NULL;
	size_t		i;

	i = 1;
	tmp = ctrl->first;
	if ((split = ft_strsplit_blank(cmd)) == NULL)
		ft_critical_error(MALLOC_ERROR);
	if (ft_count_2d_tab(split) > 1)
		while (tmp)
		{
			if ((split_env = ft_strsplit(tmp->env, '=')) == NULL)
				ft_critical_error(MALLOC_ERROR);
			if (ft_strcmp(split[1], split_env[0]) == 0)
				break ;
			ft_2d_tab_free(split_env);
			tmp = tmp->next;
			++i;
			if (tmp == NULL)
				ft_dprintf(2, RED"Environement variable not exist\n"END);
		}
	destroy_node(ctrl, i);
	ft_2d_tab_free(split_env);
	ft_2d_tab_free(split);
}

static bool	replace_if_var_exist(t_ctrl *ctrl, char *key, char *var)
{
	size_t		i;
	size_t		len_key;
	size_t		len_tmp;
	t_environ	*tmp;

	i = 0;
	len_key = ft_strlen(key);
	tmp = ctrl->first;
	while (tmp)
	{
		len_tmp = ft_strclen(tmp->env, '=');
		if (len_tmp == len_key && ft_strncmp(tmp->env, key, len_key) == 0)
		{
			ft_strdel(&tmp->env);
			if ((tmp->env = ft_strdup(var)) == NULL)
				ft_critical_error(MALLOC_ERROR);
			return (true);
		}
		tmp = tmp->next;
	}
	return (false);
}

void	built_in_setenv(char *cmd, t_ctrl *ctrl)
{
	char	**split;
	size_t	i;

	i = 0;
	while (cmd[i] && cmd[i] != ' ' && cmd[i] != '\t')
		++i;
	while (cmd[i] == ' ' || cmd[i] == '\t')
		++i;
	if (ft_str_isspace(&cmd[i]) == true)
		ft_dprintf(2, RED"No space allowed. Usage : setenv foo=bar\n"END);
	else
	{
		if ((split = ft_strsplit(&cmd[i], '=')) == NULL)
			ft_critical_error(MALLOC_ERROR);
		if (ft_count_2d_tab(split) == 2 && ft_str_isalpha(split[0]) == true)
		{
			if (replace_if_var_exist(ctrl, split[0], &cmd[i]) == false)
				add_tail(ctrl, &cmd[i]);
		}
		else
			ft_dprintf(2, RED"Bad formmating. Usage : setenv foo=bar\n"END);
		ft_2d_tab_free(split);
	}
}
