/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 21:48:55 by migarrid          #+#    #+#             */
/*   Updated: 2025/07/24 21:56:36 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	wait_for_threads(t_dinner *dinner)
{
	int	i;

	pthread_join(dinner->monitor.thread, NO_RETURN_VALUE);
	i = 0;
	while (i < dinner->total)
	{
		pthread_join(dinner->philosophers[i].thread, NO_RETURN_VALUE);
		i++;
	}
}
