/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouarsas <mouarsas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 23:33:36 by mouarsas          #+#    #+#             */
/*   Updated: 2022/11/07 19:46:34 by mouarsas         ###   ########.fr       */
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

int	laarebi_help_us_please(int sig, t_pi pi, char *str)
{
	sig = ft_get_sig(sig);
	ft_putstr_fd(str, pi.pipe[1][1]);
	return (sig);
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
			sig = laarebi_help_us_please(sig, pi, av[i]);
		if (av[i + 1])
			ft_putstr_fd(" ", pi.pipe[1][1]);
	}
	if (sig != -2)
		ft_putstr_fd("\n", pi.pipe[1][1]);
	return (1);
}
