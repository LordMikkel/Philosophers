/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 17:07:40 by migarrid          #+#    #+#             */
/*   Updated: 2025/07/26 15:50:15 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static int	is_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+')
		i++;
	if (!str[i])
		return (FALSE);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	is_valid_args(int ac, char **av)
{
	int	i;

	if (ac < 5 || ac > 6)
		return (put_str_fd(STDERR, ERR_ARGS), FALSE);
	i = 1;
	while (i < ac)
	{
		if (!is_number(av[i]) || !ft_atoi_range(av[i]) || ft_atoi(av[i]) <= 0)
			return (put_str_fd(STDERR, ERR_INT), FALSE);
		i++;
	}
	return (TRUE);
}
