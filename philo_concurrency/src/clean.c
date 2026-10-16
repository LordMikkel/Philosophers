/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 16:23:41 by migarrid          #+#    #+#             */
/*   Updated: 2025/07/31 19:22:13 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	clean_all(t_dinner *dinner)
{
	if (dinner->philosophers)
		clean_philosophers(dinner);
	if (dinner->mtx[0] || dinner->mtx[1])
		clean_dinner(dinner);
}

void	clean_philosophers(t_dinner *dinner)
{
	int	i;

	i = 0;
	while (i < dinner->total)
	{
		if (dinner->philosophers[i].mtx[0] == TRUE)
		{
			if (pthread_mutex_destroy(&dinner->philosophers[i].fork_mutex))
				put_str_fd(STDERR, ERR_MUTEX_DESTROY);
		}
		if (dinner->philosophers[i].mtx[1] == TRUE)
		{
			if (pthread_mutex_destroy(&dinner->philosophers[i].meal_mutex))
				put_str_fd(STDERR, ERR_MUTEX_DESTROY);
		}
		i++;
	}
	free(dinner->philosophers);
}

void	clean_dinner(t_dinner *dinner)
{
	if (dinner->mtx[0] == TRUE)
	{
		if (pthread_mutex_destroy(&dinner->print_mutex))
			put_str_fd(STDERR, ERR_MUTEX_DESTROY);
	}
	if (dinner->mtx[1] == TRUE)
	{
		if (pthread_mutex_destroy(&dinner->end_mutex))
			put_str_fd(STDERR, ERR_MUTEX_DESTROY);
	}
}
