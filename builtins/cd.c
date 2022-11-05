/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouarsas <mouarsas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 23:33:27 by mouarsas          #+#    #+#             */
/*   Updated: 2022/11/03 20:50:38 by mouarsas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_key_env(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (ft_substr(str, 0, i));
		i++;
	}
	return (NULL);
}

t_list	*get_node_env(char *s, t_list *list)
{
	list->first = list;
	while (list->first)
	{
		if (!ft_strcmp(s, get_key_env(list->first->str)))
			return (list->first);
		list->first = list->first->next;
	}
	return (NULL);
}

char	*get_value_env(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (ft_substr(str, i + 1, ft_strlen(str)));
		i++;
	}
	return (NULL);
}

char	*env_value(char *s, t_list *list)
{
	char	*env;

	list->first = list;
	while (list->first)
	{
		env = get_key_env(list->first->str);
		if (ft_strcmp(s, env) == 0)
		{
			free(env);
			return (get_value_env(list->first->str));
		}
		free(env);
		list->first = list->first->next;
	}
	return (NULL);
}

t_list	*change_dir(char **av, t_cd ci, t_list *list, t_pi pi)
{
	if (ci.i < 0)
	{
		ft_putstr_fd("minishell: cd: ", pi.pipe[2][1]);
		ft_putstr_fd(av[1], pi.pipe[2][1]);
		ft_putstr_fd(": No such file or directory\n", pi.pipe[2][1]);
		ci.st[0] = 0;
	}
	else
		change_dir_norm(ci, list, pi);
	return (list);
}

t_list	*ft_cd(char **av, t_list *list, t_pi pi, int *st)
{
	char	path[255];
	char	*home;
	char	*old_cur;
	t_cd	ci;

	ci.st = &st[0];
	getcwd(path, 255);
	old_cur = ft_strdup(path);
	if (!av[1])
	{
		home = env_value("HOME", list);
		if (!home)
		{
			ft_putstr_fd("minishell: cd: HOME not set", pi.pipe[2][1]);
			st[0] = 0;
			free(old_cur);
			return (list);
		}
		free(home);
		list =  cd_norm(list, pi, st);
		free(old_cur);
		return list;
	}
	ci.i = chdir((const char *)av[1]);
	ci.old_cur = old_cur;
	list = change_dir(av, ci, list, pi);
	free(old_cur);
	return (list);
}
