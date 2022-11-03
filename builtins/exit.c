/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouarsas <mouarsas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 23:34:02 by mouarsas          #+#    #+#             */
/*   Updated: 2022/11/03 20:39:16 by mouarsas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exit_check(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		if (!(s[i] >= 48 && s[i] <= 57))
			free_and_exit(255);
	return (ft_atoi(s));
}

void	free_and_exit(int status)
{
	//rl_clear_history();
	exit(status);
}

t_list	*ft_my_exit(char **av, t_list *list, t_pi *pi, t_norme2 *norme)
{
	if (av[1])
	{
		free(norme->str);
		ft_putstr_fd("exit: too many arguments\n", pi->pipe[2][1]);
		norme->status = 0;
		ft_fresh(av);
		return (list);
	}
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
