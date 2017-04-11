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
	char		**split_env;
	size_t		i;

	i = 1;
	tmp = ctrl->first;
	split = ft_strsplit_blank(cmd);
	if (ft_count_2d_tab(split) > 1)
	{
		while (tmp)
		{
			split_env = ft_strsplit(tmp->env, '=');
			if (ft_strcmp(split[1], split_env[0]) == 0)
			{
				destroy_node(ctrl, i);
				ft_2d_tab_free(split_env);
				break ;
			}
			ft_2d_tab_free(split_env);
			tmp = tmp->next;
			++i;
			if (tmp == NULL)
				ft_dprintf(1, RED"Environement variable not exist\n"END);
		}
	}
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
			tmp->env = ft_strdup(var);
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
		split = ft_strsplit(&cmd[i], '=');
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
