/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:06:56 by tkurukul          #+#    #+#             */
/*   Updated: 2025/06/04 19:17:36 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	main(int ac, char **av)
{
	t_info info;

	(void)ac;
	init_struct(&info);
	init_parssing(av, &info);
	
}
