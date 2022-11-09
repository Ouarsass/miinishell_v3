/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouarsas <mouarsas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 23:34:02 by mouarsas          #+#    #+#             */
/*   Updated: 2022/11/09 01:58:46 by mouarsas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exit_check(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		if (!(s[i] >= 48 && s[i] <= 57))
			exit(255);
	return (ft_atoi(s));
}

int	is_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
			return (0);
	}
	return (1);
}

t_list	*free_to_exit(char **av, t_list *list, t_pi *pi, t_norme2 *norme)
{
	free_my_pi(pi);
	free_mylist(list);
	ft_fresh(av);
	free_2d(norme->tab);
	free_2d(norme->andand);
	free_2d(norme->oror);
	free(norme->str);
	exit(norme->status);
	return (NULL);
}

t_list	*free_to_not_exit(t_norme2 *norme, char **av, t_list *list)
{
	free(norme->str);
	norme->status = 0;
	ft_fresh(av);
	return (list);
}

t_list	*ft_my_exit(char **av, t_list *list, t_pi *pi, t_norme2 *norme)
{
	int	i;

	i = 1;
	if (av[1])
	{
		if (is_number(av[1]) == 1)
		{
			if (av[2])
			{
				ft_putstr_fd("exit: too many arguments\n", pi->pipe[2][1]);
				return (free_to_not_exit(&norme[0], av, list));
			}
			return (free_to_exit(av, list, pi, &norme[0]));
		}
		else
		{
			ft_putstr_fd("exit: numeric argument required\n", pi->pipe[2][1]);
			return (free_to_exit(av, list, pi, &norme[0]));
		}
	}
	return (free_to_exit(av, list, pi, &norme[0]));
}
