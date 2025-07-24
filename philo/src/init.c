/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 18:53:20 by migarrid          #+#    #+#             */
/*   Updated: 2025/07/24 21:40:09 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	init_dinner(t_dinner *dinner, int ac, char **av)
{
	dinner->total = ft_atoi(av[1]);
	dinner->dead = ft_atoi(av[2]);
	dinner->eat = ft_atoi(av[3]);
	dinner->sleep = ft_atoi(av[4]);
	if (ac == 6)
		dinner->meals = ft_atoi(av[5]);
	else
		dinner->meals = FALSE;
	dinner->stop = 0;
	dinner->start = get_current_time();
	if (pthread_mutex_init(&dinner->print_mutex, NO_ATRIBUTE))
		return (put_str_fd(STDERR, ERR_MUTEX), 0);
	if (allocate_philosophers(dinner))
		return (0);
	if (init_monitor(&dinner->monitor, dinner))
		return (0);
	return (1);
}

int	allocate_philosophers(t_dinner *dinner)
{
	int	i;

	dinner->philosophers = malloc(sizeof(t_philo) * dinner->total);
	if (!dinner->philosophers)
		return (put_str_fd(STDERR, ERR_MEM), 0);
	i = 0;
	while (i < dinner->total)
	{
		if (!init_philosopher(&dinner->philosophers[i], i + 1, dinner))
			return (0);
		i++;
	}
	return (1);
}

int	init_philosopher(t_philo *philo, int id, t_dinner *dinner)
{
	philo->id = id;
	philo->meals = 0;
	philo->starvation = 0;
	philo->dinner = dinner;
	if (pthread_mutex_init(&philo->meal_mutex, NO_ATRIBUTE))
		return (put_str_fd(STDERR, ERR_MUTEX), 0);
	return (1);
}

int	init_monitor(t_monitor *monitor, t_dinner *dinner)
{
	monitor->dinner = dinner;
	if (pthread_mutex_init(&monitor->service_mutex, NO_ATRIBUTE))
		return (0);
	monitor->forks_available = malloc(sizeof(int) * dinner->total);
	if (!monitor->forks_available)
		return (0);
	init_forks(monitor);
	return (1);
}

void	init_forks(t_monitor *monitor)
{
	int	i;

	i = 0;
	while (i < monitor->dinner->total)
	{
		monitor->forks_available[i] = FREE;
		i++;
	}
}
