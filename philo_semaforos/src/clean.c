/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 16:23:41 by migarrid          #+#    #+#             */
/*   Updated: 2025/08/05 18:02:00 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	clean_all(t_dinner *dinner)
{
	clean_philosophers(dinner);
	clean_monitor(&dinner->monitor);
	unlink_semaphores();
}

void	clean_monitor(t_monitor *monitor)
{
	if (monitor->forks != SEM_FAILED)
		sem_close(monitor->forks);
	if (monitor->print != SEM_FAILED)
		sem_close(monitor->print);
	if (monitor->meals != SEM_FAILED)
		sem_close(monitor->meals);
	if (monitor->death != SEM_FAILED)
		sem_close(monitor->death);
	if (monitor->end != SEM_FAILED)
		sem_close(monitor->end);
	if (monitor->threads)
		free(monitor->threads);
}

void	clean_philosophers(t_dinner *dinner)
{
	if (dinner->philosophers)
	{
		kill_all_philosophers(dinner);
		wait_all_philosophers(dinner);
	}
	if (dinner->philosophers)
		free(dinner->philosophers);
}

void	wait_all_philosophers(t_dinner *dinner)
{
	int	i;

	i = 0;
	while (i < dinner->total)
	{
		if (dinner->philosophers[i].pid > 0)
		{
			waitpid(dinner->philosophers[i].pid, NULL, 0);
			dinner->philosophers[i].pid = -1;
		}
		i++;
	}
}

void	unlink_semaphores(void)
{
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_MEALS);
	sem_unlink(SEM_DEATH);
	sem_unlink(SEM_END);
}
