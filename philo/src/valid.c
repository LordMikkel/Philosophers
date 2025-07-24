/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 17:07:40 by migarrid          #+#    #+#             */
/*   Updated: 2025/07/22 22:44:44 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	is_valid_args(int ac, char **av)
{
	int	i;

	if (ac < 5 || ac > 6)
		return (FALSE);
	i = 0;
	while (i < ac)
	{
		if (!ft_atoi_range(av[i++]) || (ft_atoi(av[i++]) <= 0))
			return (put_str_fd(STDERR, ERR_INT), FALSE);
	}
	return (TRUE);
}
