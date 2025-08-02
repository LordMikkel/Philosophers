/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 16:23:41 by migarrid          #+#    #+#             */
/*   Updated: 2025/08/02 20:19:16 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	clean_all(t_dinner *dinner)
{
	clean_philosophers(dinner);
	clean_monitor(&dinner->monitor);
}

void	clean_monitor(t_monitor *monitor)
{
	if (monitor->forks)
		sem_close(monitor->forks);
	if (monitor->service)
		sem_close(monitor->service);
	if (monitor->print)
		sem_close(monitor->print);
	if (monitor->end)
		sem_close(monitor->end);
	if (monitor->death)
		sem_close(monitor->death);
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_SERVICE);
	sem_unlink(SEM_DEATH);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_END);
}

void	clean_philosophers(t_dinner *dinner)
{
	if (dinner->philosophers)
		free(dinner->philosophers);
}
