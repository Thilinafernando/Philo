/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:06:56 by tkurukul          #+#    #+#             */
/*   Updated: 2025/06/05 21:34:58 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	create_philos(t_info *info)
{
	int	i;

	i = -1;
	info->start_time = get_time_in_ms();
	while (++i < info->num_philo)
		info->philo[i].last_meal_time = info->start_time;
	i = -1;
	if (info->num_philo == 1)
	{
		info->start_time = get_time_in_ms();
		info->philo[0].last_meal_time = info->start_time;
		pthread_create(&info->tids[0], NULL, &single_philo_routine, &info->philo[0]);
		info->real_count_thread = 1;
		return;
	}
	while (++i < info->num_philo)
	{
		if (pthread_create(&info->tids[i], NULL, &routine, &info->philo[i]) != 0)
		{
			err_parsing("Thread creation failed", -42);
			info->real_count_thread = i;
			return (free_all(info), exit(1));
		}
	}
	info->real_count_thread = info->num_philo;
}

int	main(int ac, char **av)
{
	t_info info;
	int		i;

	(void)ac;
	i = -1;
	init_struct(&info);
	init_parssing(av, &info);
	init_structpt2(&info);
	create_philos(&info);
	if (pthread_create(&info.reaper, NULL, &death_routine, &info) != 0)
	{
		err_parsing("Thread creation failed", -42);
		while (++i < info.real_count_thread)
		{
			if (info.tids[i])
				pthread_join(info.tids[i], NULL);
		}
		return (free_all(&info), 1);
	}
	while (++i < info.real_count_thread)
	{
		if (info.tids[i])
			pthread_join(info.tids[i], NULL);
	}
	pthread_join(info.reaper, NULL);
	free_all(&info);
	return (0);
}
