/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:06:56 by tkurukul          #+#    #+#             */
/*   Updated: 2025/06/05 00:36:17 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	create_philos(t_info *info)
{
	int	i;

	i = -1;
	info->start_time = get_time_in_ms();
	while (++i < info->num_philo)
	{
		if (pthread_create(&info->tids[i], NULL, &routine, &info->philo[i]) != 0)
			err_parsing("Thread creation failed", -42);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_info info;

	(void)ac;
	init_struct(&info);
	init_parssing(av, &info);
	init_structpt2(&info);
}
