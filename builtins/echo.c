/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouarsas <mouarsas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 23:33:36 by mouarsas          #+#    #+#             */
/*   Updated: 2022/11/09 01:57:54 by mouarsas         ###   ########.fr       */
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

int	laarebi_help_us_please(int sig, t_pi pi, char *str)
{
	ft_putstr_fd(str, pi.pipe[1][1]);
	return (sig);
}

int	check_n(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-')
	{
		i = 1;
		while (str[i])
		{
			if (str[i] != 'n')
				return (1);
			i++;
		}
		return (-2);
	}
	return (1);
}

char	*switch_to_old_status(char *str)
{
	int		i;
	char	*join;
	char	*tmp;
	int		len;

	join = NULL;
	i = 0;
	len = ft_strlen(str);
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (str[i + 1] == '?')
			{
				tmp = ft_strjoin(ft_substr(str, 0, i), \
					ft_itoa(g_isexecuting.old_status));
				join = ft_strjoin(tmp, ft_substr(str, i + 2, len - (i + 2)));
				free(tmp);
				free(str);
				str = join;
			}
		}
		i++;
	}
	return (str);
}

int	ft_echo(char **av, t_pi pi, int i)
{
	int	sig;
	int	check;

	while (av[i])
	{
		check = check_n(av[i]);
		if (check == -2)
		{
			i++;
			sig = -2;
		}
		else
			break ;
	}
	while (av[i])
	{
		av[i] = switch_to_old_status(av[i]);
		ft_putstr_fd(av[i], pi.pipe[1][1]);
		if (av[i + 1])
			ft_putstr_fd(" ", pi.pipe[1][1]);
		i++;
	}
	if (sig != -2)
		ft_putstr_fd("\n", pi.pipe[1][1]);
	return (1);
}
