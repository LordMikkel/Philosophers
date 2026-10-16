/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 03:34:48 by migarrid          #+#    #+#             */
/*   Updated: 2025/08/04 19:03:27 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	take_forks(t_philo *philosopher)
{
	sem_wait(philosopher->monitor->waiter);
	sem_wait(philosopher->monitor->forks);
	safe_print(philosopher, TAKE_FORK);
	sem_wait(philosopher->monitor->forks);
	safe_print(philosopher, TAKE_FORK);
}

void	eats(t_philo *philo)
{
	sem_wait(philo->monitor->death);
	philo->starvation = get_timestamp(philo->dinner->start);
	sem_post(philo->monitor->death);
	if (philo->dinner->meals > 0)
	{
		sem_wait(philo->monitor->meals);
		philo->meals++;
		sem_post(philo->monitor->meals);
	}
	safe_print(philo, EATING);
	msleep(philo->dinner->eat);
}

void	drop_forks(t_philo *philosopher)
{
	sem_post(philosopher->monitor->forks);
	sem_post(philosopher->monitor->forks);
	sem_post(philosopher->monitor->waiter);
}

void	sleeps(t_philo *philosopher)
{
	safe_print(philosopher, SLEEPING);
	msleep(philosopher->dinner->sleep);
}

void	death(t_philo *philo)
{
	sem_wait(philo->monitor->death);
	sem_wait(philo->monitor->print);
	printf("%u	%d	%s", get_timestamp(philo->dinner->start), philo->id, DIED);
	printf("%s", DINNER_ENDED);
	exit(EXIT_FAILURE);
}
