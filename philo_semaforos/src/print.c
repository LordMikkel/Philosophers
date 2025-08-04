/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 23:38:44 by migarrid          #+#    #+#             */
/*   Updated: 2025/08/03 18:26:07 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	safe_print(t_philo *philo, char *msg)
{
	unsigned int	start_time;

	start_time = philo->dinner->start;
	sem_wait(philo->monitor->print);
	if (!philo->dinner->stop)
		printf("%u	%d	%s", get_timestamp(start_time), philo->id, msg);
	sem_post(philo->monitor->print);
}
