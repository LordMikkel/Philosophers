/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 04:10:02 by migarrid          #+#    #+#             */
/*   Updated: 2025/07/29 04:45:38 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	*philosopher_routine(void *arg)
{
	t_philo	*philosopher;

	philosopher = (t_philo *)arg;
	if (philosopher->dinner->total == 1)
		return (one_philosopher(philosopher), NULL);
	while (!philosopher->dinner->stop)
	{
		thinks(philosopher);
		if (!request_for_forks(&philosopher->dinner->monitor))
				return (NULL);
		eats(philosopher);
		if (has_eaten_enough(philosopher))
			break ;
		sleeps(philosopher);
	}
	return (NULL);
}

void	one_philosopher(t_philo *philosopher)
{
	safe_print(philosopher, TAKE_L_FORK);
	msleep(philosopher->dinner->dead);
	safe_print(philosopher, DIED);
}

int	has_eaten_enough(t_philo *philosopher)
{
	int eaten;

	pthread_mutex_lock(&philosopher->meal_mutex);
	eaten = philosopher->meals;
	pthread_mutex_unlock(&philosopher->meal_mutex);
	if (philosopher->dinner->meals > 0 && eaten >= philosopher->dinner->meals)
		return (TRUE);
	return (FALSE);
}
