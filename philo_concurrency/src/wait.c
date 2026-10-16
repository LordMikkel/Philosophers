/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 21:48:55 by migarrid          #+#    #+#             */
/*   Updated: 2025/07/29 02:17:28 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	wait_for_threads(t_dinner *dinner)
{
	int	i;

	if (pthread_join(dinner->monitor.thread, NO_RETURN_VALUE))
		return (FAIL);
	i = 0;
	while (i < dinner->total)
	{
		if (pthread_join(dinner->philosophers[i].thread, NO_RETURN_VALUE))
			return (FAIL);
		i++;
	}
	return (SUCCES);
}
