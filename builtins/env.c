/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouarsas <mouarsas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 23:33:51 by mouarsas          #+#    #+#             */
/*   Updated: 2022/11/02 22:00:07 by mouarsas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(t_list *list, t_pi pi)
{
	if (!list)
		return ;
	else
	{
		list->first = list;
		while (list->first)
		{
			ft_putstr_fd(list->first->str, pi.pipe[1][1]);
			ft_putstr_fd("\n", pi.pipe[1][1]);
			list->first = list->first->next;
		}
	}
}
