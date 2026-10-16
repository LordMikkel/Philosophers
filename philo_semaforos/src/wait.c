/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 21:48:55 by migarrid          #+#    #+#             */
/*   Updated: 2025/08/04 19:18:15 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	wait_for_simulation(t_dinner *dinner)
{
	int	i;
	int	status;
	int	satisfied;

	satisfied = 0;
	while (satisfied < dinner->total)
	{
		i = 0;
		while (i < dinner->total)
		{
			if (waitpid(dinner->philosophers[i].pid, &status, WNOHANG) > 0)
			{
				if (WEXITSTATUS(status) == FINISH)
					satisfied++;
				else
					return (RIP);
			}
			i++;
		}
		msleep(1);
	}
	end_simulation(dinner);
	return (SUCCES);
}

void	end_simulation(t_dinner *dinner)
{
	kill_all_philosophers(dinner);
	sem_wait(dinner->monitor.end);
	dinner->stop = TRUE;
	printf("%s%s", DINNER_SUCCES, DINNER_ENDED);
}
