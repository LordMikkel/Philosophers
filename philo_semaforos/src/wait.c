/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 21:48:55 by migarrid          #+#    #+#             */
/*   Updated: 2025/08/02 19:57:32 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	wait_for_threads(t_dinner *dinner)
{
	int	i;
	int status;

	i = 0;
	while (i < dinner->total)
	{
		waitpid(dinner->philosophers[i].pid, &status, 0);
		i++;
	}
	return (SUCCES);
}
