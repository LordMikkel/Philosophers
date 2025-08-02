/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 18:02:51 by migarrid          #+#    #+#             */
/*   Updated: 2025/08/02 19:53:48 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	start_simulation(t_dinner *dinner)
{
	int	i;

	i = 0;
	put_str_fd(STDOUT, DINNER_START);
	while (i < dinner->total)
	{
		dinner->philosophers[i].pid = fork();
		if (dinner->philosophers[i].pid == ERROR)
			return (put_str_fd(STDERR, ERR_FORK), 0);
		if (dinner->philosophers[i].pid == 0)
		{
			philosopher_routine(&dinner->philosophers[i]);
			return (0);
		}
		i++;
	}
	monitor_routine(dinner);
	return (1);
}
