/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 03:34:48 by migarrid          #+#    #+#             */
/*   Updated: 2025/07/29 04:42:22 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	thinks(t_philo *philosopher)
{
		safe_print(philosopher, THINKING);
}

void	eats(t_philo *philo)
{
	int left_fork;
	int right_fork;

	safe_print(philo, TAKE_L_FORK);
	safe_print(philo, TAKE_R_FORK);
	safe_print(philo, EATING);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->starvation = get_timestamp(philo->dinner->start);
	philo->meals++;
	pthread_mutex_unlock(&philo->meal_mutex);
	msleep(philo->dinner->eat);
	left_fork = calculate_fork_id(philo->id, philo->dinner->total, 0);
	right_fork = calculate_fork_id(philo->id, philo->dinner->total, 1);
	pthread_mutex_lock(&philo->dinner->monitor.service_mutex);
	philo->dinner->monitor.forks_available[left_fork] == FREE;
	philo->dinner->monitor.forks_available[left_fork] == FREE;
	pthread_mutex_unlock(&philo->dinner->monitor.service_mutex);
}

void	sleeps(t_philo *philosopher)
{
	safe_print(philosopher, SLEEPING);
	msleep(philosopher->dinner->sleep);
}

void	death(t_philo *philo)
{
		pthread_mutex_lock(&philo->dinner->print_mutex);
		pthread_mutex_lock(&philo->dinner->end_mutex);
		philo->dinner->stop = TRUE;
		printf("%u	%d	%s", get_timestamp(philo->dinner->start), philo->id, DIED);
		pthread_mutex_unlock(&philo->dinner->end_mutex);
		pthread_mutex_unlock(&philo->dinner->print_mutex);
}
