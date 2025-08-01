/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 23:27:59 by migarrid          #+#    #+#             */
/*   Updated: 2025/07/31 23:39:39 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	safe_print(t_philo *philo, char *msg)
{
	unsigned int	start_time;
	int				end;

	start_time = philo->dinner->start;
	end = safe_read_end(philo->dinner);
	pthread_mutex_lock(&philo->dinner->print_mutex);
	if (!end)
		printf("%u	%d	%s", get_timestamp(start_time), philo->id, msg);
	pthread_mutex_unlock(&philo->dinner->print_mutex);
}
