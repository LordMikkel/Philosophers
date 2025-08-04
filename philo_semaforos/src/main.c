/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:07:14 by migarrid          #+#    #+#             */
/*   Updated: 2025/08/04 17:02:34 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	main(int ac, char **av)
{
	t_dinner	dinner;

	if (!is_valid_args(ac, av))
		return (error(ERR_ARGS, NULL), EXIT_FAILURE);
	// printf("1 - Valid Args");
	dinner = (t_dinner){0};
	if (!init_dinner(&dinner, ac, av))
		return (error(ERR_INIT, &dinner), EXIT_FAILURE);
	// printf("2 - Initi Data");
	if (!start_simulation(&dinner))
		return (error(ERR_SIM, &dinner), EXIT_FAILURE);
	// printf("3 - Simulation Started");
	if (!wait_for_simulation(&dinner))
		return (error(ERR_WAIT, &dinner), EXIT_FAILURE);
	// printf("4 - Simulation Ended");
	clean_all(&dinner);
	// printf("5 - Data Cleanend");
	return (EXIT_SUCCESS);
}
