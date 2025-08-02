/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 03:34:48 by migarrid          #+#    #+#             */
/*   Updated: 2025/08/02 16:32:12 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	take_forks(t_philo *philosopher)
{
	t_philo	*left_neighbor;
	int		total;

	total = philosopher->dinner->total;
	if (philosopher->id == 1)
		left_neighbor = &philosopher->dinner->philosophers[total - 1];
	else
		left_neighbor = &philosopher->dinner->philosophers[philosopher->id - 2];
	if (philosopher->id % 2 == 0)
	{
		pthread_mutex_lock(&left_neighbor->fork_mutex);
		pthread_mutex_lock(&philosopher->fork_mutex);
		safe_print(philosopher, TAKE_FORK);
		safe_print(philosopher, TAKE_FORK);
	}
	else
	{
		usleep(400);
		pthread_mutex_lock(&philosopher->fork_mutex);
		pthread_mutex_lock(&left_neighbor->fork_mutex);
		safe_print(philosopher, TAKE_FORK);
		safe_print(philosopher, TAKE_FORK);
	}
}

void	eats(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	philo->starvation = get_timestamp(philo->dinner->start);
	philo->meals++;
	pthread_mutex_unlock(&philo->meal_mutex);
	safe_print(philo, EATING);
	msleep(philo->dinner->eat);
}

void	drop_forks(t_philo *philosopher)
{
	t_philo	*left_neighbor;
	int		total;

	total = philosopher->dinner->total;
	if (philosopher->id == 1)
		left_neighbor = &philosopher->dinner->philosophers[total - 1];
	else
		left_neighbor = &philosopher->dinner->philosophers[philosopher->id - 2];
	if (philosopher->id % 2 == 0)
	{
		pthread_mutex_unlock(&philosopher->fork_mutex);
		pthread_mutex_unlock(&left_neighbor->fork_mutex);
	}
	else
	{
		pthread_mutex_unlock(&left_neighbor->fork_mutex);
		pthread_mutex_unlock(&philosopher->fork_mutex);
	}
}

void	sleeps(t_philo *philosopher)
{
	safe_print(philosopher, SLEEPING);
	msleep(philosopher->dinner->sleep);
}

void	death(t_philo *philo)
{
	pthread_mutex_lock(&philo->dinner->end_mutex);
	pthread_mutex_lock(&philo->dinner->print_mutex);
	philo->dinner->stop = TRUE;
	printf("%u	%d	%s", get_timestamp(philo->dinner->start), philo->id, DIED);
	put_str_fd(STDOUT, DINNER_ENDED);
	pthread_mutex_unlock(&philo->dinner->print_mutex);
	pthread_mutex_unlock(&philo->dinner->end_mutex);
}
