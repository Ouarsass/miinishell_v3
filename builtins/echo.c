/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouarsas <mouarsas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 23:33:36 by mouarsas          #+#    #+#             */
/*   Updated: 2022/11/02 22:01:26 by mouarsas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_newline(char *s)
{
	int	i;

	i = 0;
	while (s[++i])
		if (s[i] != 'n')
			return (0);
	return (1);
}

int	ft_get_sig(int sig)
{
	if (sig == 0 || sig == -2)
		return (-2);
	else
		return (-1);
}

int	ft_echo(char **av, t_pi pi)
{
	int	i;
	int	sig;

	i = 0;
	sig = 1;
	while (av[++i])
	{
		if (sig >= 0 && av[i][0] && av[i][0] == '-' && av[i][1])
		{
			if (ft_newline(av[i]))
			{
				sig = 0;
				continue ;
			}
		}
		else
			sig = ft_get_sig(sig);
			ft_putstr_fd(av[i], pi.pipe[1][1]);
		if (av[i + 1])
			ft_putstr_fd(" ", pi.pipe[1][1]);		
	}
	if (sig != -2)
		ft_putstr_fd("\n", pi.pipe[1][1]);
	g_variable.status = 0;
	return (1);
}
