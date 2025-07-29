/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 04:10:32 by migarrid          #+#    #+#             */
/*   Updated: 2025/07/29 21:33:48 by migarrid         ###   ########.fr       */
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
		if (pthread_create(&dinner->philosophers[i].thread, NO_ATRIBUTE,
				philosopher_routine, &dinner->philosophers[i]))
			return (put_str_fd(STDERR, ERR_THREAD), 0);
		i++;
	}
	if (pthread_create(&dinner->monitor.thread, NO_ATRIBUTE,
			monitor_routine, &dinner->monitor))
		return (put_str_fd(STDERR, ERR_THREAD), 0);
	return (1);
}
