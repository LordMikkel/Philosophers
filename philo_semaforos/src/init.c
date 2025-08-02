/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 18:53:20 by migarrid          #+#    #+#             */
/*   Updated: 2025/08/02 20:23:38 by migarrid         ###   ########.fr       */
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
	philo->dinner = dinner;
	philo->monitor = dinner->monitor;
	philo->pid = 0;
	return (1);
}

int	init_monitor(t_monitor *monitor, t_dinner *dinner)
{
	monitor->dinner = dinner;
	monitor->philosophers = dinner->philosophers;
	monitor->pid = 0;
	init_semaphore(monitor, dinner->total);
	if (!monitor->forks || !monitor->service || !monitor->print ||
		!monitor->end || !monitor->death)
		return (0);
	return (1);
}

void	init_semaphore(t_monitor *monitor, int total)
{
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_SERVICE);
	sem_unlink(SEM_DEATH);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_END);
	monitor->forks = sem_open(SEM_FORKS, O_CREAT | O_EXCL, 0644, total);
	monitor->service = sem_open();
	monitor->print = sem_open();
	monitor->end = sem_open();
	monitor->death = sem_open();
}
