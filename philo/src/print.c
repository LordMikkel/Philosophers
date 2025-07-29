/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 21:49:54 by migarrid          #+#    #+#             */
/*   Updated: 2025/07/29 03:40:18 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void safe_print(t_philo *philo, char *message)
{
	pthread_mutex_lock(&philo->dinner->print_mutex);
	if (!philo->dinner->stop)
		printf("%u	%d	%s", get_timestamp(philo->dinner->start), philo->id, message);
	pthread_mutex_unlock(&philo->dinner->print_mutex);
}
