/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouarsas <mouarsas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 23:34:11 by mouarsas          #+#    #+#             */
/*   Updated: 2022/11/02 21:59:09 by mouarsas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**spliting_export(char *tab)
{
	int		i;
	char	**av;

	i = -1;
	av = ft_split(tab, '=');
	if (av && av[0] && av[1] && av[2])
		return (NULL);
	if (!av || !*av)
		return (NULL);
	if ((av[0][0] >= '0' && av[0][0] <= '9'))
		return (NULL);
	while (av[0][++i])
	{
		if (!(av[0][i] >= 'a' && av[0][i] <= 'z') \
		&& !(av[0][i] >= 'A' && av[0][i] <= 'Z') && \
		!(av[0][i] >= '0' && av[0][i] <= '9') && \
		(av[0][i] != '_'))
			return (NULL);
	}
	return (av);
}

void	affichage_exports(t_list *list, t_pi pi)
{
	list->first = list;
	while (list->first)
	{
		ft_putstr_fd("declare -x ", pi.pipe[1][1]);
		ft_putstr_fd(get_key_env(list->first->str), pi.pipe[1][1]);
		ft_putstr_fd("=\"", pi.pipe[1][1]);
		ft_putstr_fd(get_value_env(list->first->str), pi.pipe[1][1]);
		ft_putstr_fd("\"\n", pi.pipe[1][1]);
		list->first = list->first->next;
	}
	g_variable.status = 0;
}

t_list	*ft_add_to_env(t_list *list, char *str, char *spl)
{
	char	**split;

	list->first = list;
	while (list->first)
	{
		split = ft_split(list->first->str, '=');
		if (ft_strcmp(split[0], spl) == 0)
		{
			free(list->first->str);
			list->first->str = ft_strdup(str);
			return (list);
		}
		if (list->first->next == NULL)
			break;
		else
			list->first = list->first->next;
	}
	list->first->next = new_list(str);
	return (list);
}

t_list	*ft_export(char **av, t_list *list, t_pi pi)
{
	int	i;
	char **split;

	i = 0;
	list->first = list;
	if (!av[1])
	{
		affichage_exports(list, pi);
		return (list);
	}
	while (av[++i])
	{
		if (ft_strchr(av[i], '='))
		{
			split = spliting_export(av[i]);
			if (split)
				list = ft_add_to_env(list, av[i], split[0]);
		}
	}
	return (list);
}

t_list		*new_list(char *tmp)
{
	t_list	*listnew;

	listnew = malloc(sizeof(t_list));
	listnew->str = ft_strdup(tmp);
	listnew->next = NULL;
	return (listnew);
}
