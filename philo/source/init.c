/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 00:03:42 by tkurukul          #+#    #+#             */
/*   Updated: 2025/06/05 21:33:25 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	init_struct(t_info *info)
{
	info->limit_eat = -1;
	info->time_die = -1;
	info->time_eat = -1;
	info->time_sleep = -1;
	info->num_philo = -1;
	info->real_count_thread = 0;
	info->deathflag = 0;
	info->start_time = 0;
}

void	init_philo_info(t_info *info)
{
	int	i;

	i = -1;
	while(++i < info->num_philo)
	{
		info->philo[i].index = i;
		info->philo[i].num_eaten = 0;
		info->philo[i].last_meal_time = 0;
		if (pthread_mutex_init(&info->philo[i].meal_mutex, NULL) != 0)
			return (err_parsing("Mutex init failed", -42), free_all(info), exit(1));
		info->philo[i].left_fork = &info->forks[i];
		info->philo[i].right_fork = &info->forks[(i +1) % info->num_philo];
		info->philo[i].info = info;
	}
}

void	init_structpt2(t_info *info)
{
	int	i;

	i = -1;
	info->forks = malloc(info->num_philo * sizeof(pthread_mutex_t));
	if (!info->forks)
		return (err_parsing(NULL, 3), exit(1));
	while (++i < info->num_philo)
	{
		if(pthread_mutex_init(&info->forks[i], NULL) != 0)
			return (err_parsing("Mutex init failed", -42), free_all(info), exit(1));
	}
	if (pthread_mutex_init(&info->print_mutex, NULL) != 0)
		return (err_parsing("Mutex init failed", -42), free_all(info), exit(1));
	info->tids = malloc(info->num_philo * sizeof(pthread_t));
	if (!info->tids)
		return (err_parsing(NULL, 3), free_all(info), exit(1));
	memset(info->tids, 0, info->num_philo * sizeof(pthread_t));
	info->philo = malloc(info->num_philo * sizeof(t_philo));
	if (!info->philo)
		return (err_parsing(NULL, 3), free_all(info), exit(1));
	init_philo_info(info);
	if (pthread_mutex_init(&info->death_mutex, NULL)!= 0)
		err_parsing("Mutex init failed", -42);
	return ;
}
