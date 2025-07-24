/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:07:14 by migarrid          #+#    #+#             */
/*   Updated: 2025/07/24 21:47:56 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	main(int ac, char **av)
{
	t_dinner	dinner;

	if (!is_valid_args(ac, av))
		return (error(ERR_ARGS, NULL), EXIT_FAILURE);
	dinner = (t_dinner){0};
	if (!init_dinner(&dinner, ac, av))
		return (error(ERR_MEM, &dinner), EXIT_FAILURE);
	wait_for_threads(&dinner);
	return (EXIT_SUCCESS);
}
