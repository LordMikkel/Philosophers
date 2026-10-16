/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 04:07:17 by migarrid          #+#    #+#             */
/*   Updated: 2025/08/01 14:58:15 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	*monitor_routine(void *arg)
{
	t_monitor	*monitor;
	int			i;

	monitor = (t_monitor *)arg;
	msleep(50);
	while (!safe_read_end(monitor->dinner))
	{
		i = 0;
		while (i < monitor->dinner->total)
		{
			if (is_philosopher_dead(&monitor->dinner->philosophers[i]))
			{
				death(&monitor->dinner->philosophers[i]);
				return (DEATH);
			}
			i++;
		}
		if (all_philosophers_are_satisfied(monitor->dinner))
		{
			end_simulation(monitor->dinner);
			return (SIMULATION_ENDED);
		}
		msleep(10);
	}
	return (SIMULATION_ENDED);
}

int	all_philosophers_are_satisfied(t_dinner *dinner)
{
	int	i;

	if (dinner->meals < 1)
		return (HUNGRY);
	i = 0;
	while (i < dinner->total)
	{
		if (!has_eaten_enough(&dinner->philosophers[i]))
			return (HUNGRY);
		i++;
	}
	return (SATISFYED);
}

int	is_philosopher_dead(t_philo *philosopher)
{
	int	current_time;
	int	time_since_meal;

	if (has_eaten_enough(philosopher))
		return (FALSE);
	current_time = get_timestamp(philosopher->dinner->start);
	pthread_mutex_lock(&philosopher->meal_mutex);
	time_since_meal = current_time - philosopher->starvation;
	pthread_mutex_unlock(&philosopher->meal_mutex);
	if (time_since_meal >= philosopher->dinner->dead)
		return (TRUE);
	return (FALSE);
}

void	end_simulation(t_dinner *dinner)
{
	pthread_mutex_lock(&dinner->print_mutex);
	pthread_mutex_lock(&dinner->end_mutex);
	dinner->stop = TRUE;
	pthread_mutex_unlock(&dinner->end_mutex);
	printf("%s%s", DINNER_SUCCES, DINNER_ENDED);
	pthread_mutex_unlock(&dinner->print_mutex);
}

int	request_for_forks(t_monitor *monitor, t_philo *philosopher)
{
	int	left_fork;
	int	right_fork;

	left_fork = calculate_fork_id(philosopher->id, monitor->dinner->total, 0);
	right_fork = calculate_fork_id(philosopher->id, monitor->dinner->total, 1);
	while (!safe_read_end(philosopher->dinner))
	{
		pthread_mutex_lock(&monitor->service_mutex);
		if (monitor->forks_available[left_fork] == FREE
			&& monitor->forks_available[right_fork] == FREE)
		{
			monitor->forks_available[left_fork] = TAKEN;
			monitor->forks_available[right_fork] = TAKEN;
			pthread_mutex_unlock(&monitor->service_mutex);
			return (YOU_CAN_EAT);
		}
		pthread_mutex_unlock(&monitor->service_mutex);
		msleep(calculate_wait_time(philosopher));
	}
	return (SIMULATION_ENDED);
}
