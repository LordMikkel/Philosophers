/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 21:49:54 by migarrid          #+#    #+#             */
/*   Updated: 2025/07/29 21:30:39 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	safe_print(t_philo *philo, char *msg)
{
	unsigned int	start_time;

	start_time = philo->dinner->start;
	pthread_mutex_lock(&philo->dinner->print_mutex);
	if (!philo->dinner->stop)
		printf("%u	%d	%s", get_timestamp(start_time), philo->id, msg);
	pthread_mutex_unlock(&philo->dinner->print_mutex);
}
