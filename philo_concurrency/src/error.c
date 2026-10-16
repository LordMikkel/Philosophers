/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 18:28:46 by migarrid          #+#    #+#             */
/*   Updated: 2025/07/31 19:28:42 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	error(char *error, t_dinner *dinner)
{
	if (error)
		put_str_fd(STDERR, error);
	if (!dinner)
		return ;
	if (dinner->philosophers)
		clean_philosophers(dinner);
	if (dinner->mtx[0] || dinner->mtx[1])
		clean_dinner(dinner);
}
