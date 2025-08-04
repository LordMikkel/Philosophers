/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:07:14 by migarrid          #+#    #+#             */
/*   Updated: 2025/08/04 19:18:43 by migarrid         ###   ########.fr       */
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
		return (error(ERR_INIT, &dinner), EXIT_FAILURE);
	if (!start_simulation(&dinner))
		return (error(ERR_SIM, &dinner), EXIT_FAILURE);
	if (!wait_for_simulation(&dinner))
		return (error(ERR_WAIT, &dinner), EXIT_FAILURE);
	clean_all(&dinner);
	return (EXIT_SUCCESS);
}
