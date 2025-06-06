/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:06:56 by tkurukul          #+#    #+#             */
/*   Updated: 2025/06/06 22:47:32 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	one_process(t_info *info)
{
	info->start_time = get_time_in_ms();
	info->philo[0].last_meal_time = info->start_time;
	pthread_create(&info->tids[0], NULL, &one_philo,
		&info->philo[0]);
	info->real_count_thread = 1;
}

int	create_philos(t_info *info)
{
	int	i;

	i = -1;
	info->start_time = get_time_in_ms();
	while (++i < info->num_philo)
		info->philo[i].last_meal_time = info->start_time;
	i = -1;
	if (info->num_philo == 1)
	{
		one_process(info);
		return (0);
	}
	while (++i < info->num_philo)
	{
		if (pthread_create(&info->tids[i], NULL, &routine
				, &info->philo[i]) != 0)
		{
			err_parsing("Thread creation failed", -42);
			info->real_count_thread = i;
			return (-1);
		}
	}
	info->real_count_thread = info->num_philo;
	return (0);
}

void	last_block(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->real_count_thread)
	{
		if (info->tids[i])
			pthread_join(info->tids[i], NULL);
	}
	pthread_join(info->reaper, NULL);
	free_all(info);
}

int	main(int ac, char **av)
{
	t_info	info;
	int		i;
	int		flag;

	i = -1;
	flag = 0;
	init_struct(&info);
	init_parssing(ac, av, &info);
	if (init_structpt2(&info) == -1)
		flag = 1;
	if (create_philos(&info) == -1)
		flag = 1;
	if (flag != 1
		&& pthread_create(&info.reaper, NULL, &death_routine, &info) != 0)
	{
		err_parsing("Thread creation failed", -42);
		while (++i < info.real_count_thread)
		{
			if (info.tids[i])
				pthread_join(info.tids[i], NULL);
		}
		return (free_all(&info), 1);
	}
	return (last_block(&info), 0);
}
