/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 18:53:20 by migarrid          #+#    #+#             */
/*   Updated: 2025/08/04 19:10:55 by migarrid         ###   ########.fr       */
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
	if (dinner->total > 200)
		return (put_str_fd(STDERR, ERR_TOTAL), 0);
	if (dinner->dead < 60 || dinner->eat < 60 || dinner->sleep < 60)
		return (put_str_fd(STDERR, ERR_MS), 0);
	if (!allocate_philosophers(dinner))
		return (0);
	if (!init_monitor(&dinner->monitor, dinner))
		return (0);
	return (1);
}

int	allocate_philosophers(t_dinner *dinner)
{
	int	i;

	dinner->philosophers = ft_calloc(dinner->total, sizeof(t_philo));
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
	philo->pid = 0;
	philo->dinner = dinner;
	philo->monitor = &dinner->monitor;
	return (1);
}

int	init_monitor(t_monitor *monitor, t_dinner *dinner)
{
	monitor->dinner = dinner;
	monitor->philosophers = dinner->philosophers;
	monitor->threads = ft_calloc(dinner->total, sizeof(pthread_t));
	if (!monitor->threads)
		return (put_str_fd(STDERR, ERR_MEM), 0);
	if (!init_semaphores(monitor, dinner->total))
		return (put_str_fd(STDERR, ERR_SEM_INIT), 0);
	return (1);
}

int	init_semaphores(t_monitor *monitor, int total)
{
	int	meals;

	meals = monitor->dinner->meals;
	unlink_semaphores();
	monitor->forks = sem_open(SEM_FORKS, O_CREAT | O_EXCL, 0644, total);
	if (monitor->forks == SEM_FAILED)
		return (0);
	monitor->print = sem_open(SEM_PRINT, O_CREAT | O_EXCL, 0644, 1);
	if (monitor->print == SEM_FAILED)
		return (0);
	monitor->death = sem_open(SEM_DEATH, O_CREAT | O_EXCL, 0644, 1);
	if (monitor->death == SEM_FAILED)
		return (0);
	monitor->end = sem_open(SEM_END, O_CREAT | O_EXCL, 0644, 1);
	if (monitor->end == SEM_FAILED)
		return (0);
	if (meals > 0)
	{
		monitor->meals = sem_open(SEM_MEALS, O_CREAT | O_EXCL, 0644, 1);
		if (monitor->meals == SEM_FAILED)
			return (0);
	}
	return (1);
}
