/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:07:14 by migarrid          #+#    #+#             */
/*   Updated: 2025/07/17 21:39:07 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	main(int ac, char **av)
{
	t_dinner	table;

	if (ac > 5 || ac < 4)
		return (error(ERR_ARGS, NULL), EXIT_FAILURE);
	return (EXIT_FAILURE);
}
