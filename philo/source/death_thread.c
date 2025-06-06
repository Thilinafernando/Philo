/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 19:23:39 by tkurukul          #+#    #+#             */
/*   Updated: 2025/06/06 22:58:45 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	all_philosophers_done(t_info *info)
{
	int	i;
	int	done_count;

	if (info->limit_eat == -1)
		return (0);
	done_count = 0;
	i = -1;
	while (++i < info->num_philo)
	{
		pthread_mutex_lock(&info->philo[i].meal_mutex);
		if (info->philo[i].num_eaten >= info->limit_eat)
			done_count++;
		pthread_mutex_unlock(&info->philo[i].meal_mutex);
	}
	if (done_count == info->num_philo)
		return (1);
	return (0);
}

void	process_done(t_info *info)
{
	pthread_mutex_lock(&info->print_mutex);
	printf("All philosophers have finished Philosophizing!\n");
	pthread_mutex_unlock(&info->print_mutex);
	pthread_mutex_lock(&info->death_mutex);
	info->deathflag = 1;
	pthread_mutex_unlock(&info->death_mutex);
}

int	process_death(t_info *info, long current, int i)
{
	if (current > info->time_die)
	{
		print_block(&info->philo[i], "has decided to die...");
		pthread_mutex_unlock(&info->philo[i].meal_mutex);
		pthread_mutex_lock(&info->death_mutex);
		info->deathflag = 1;
		pthread_mutex_unlock(&info->death_mutex);
		return (1);
	}
	return (0);
}

void	*death_routine(void *arg)
{
	t_info		*info;
	long		current;
	int			i;

	info = (t_info *)arg;
	usleep(1000);
	while (1)
	{
		i = -1;
		if (all_philosophers_done(info))
		{
			process_done(info);
			break ;
		}
		while (++i < info->num_philo)
		{
			pthread_mutex_lock(&info->philo[i].meal_mutex);
			current = get_time_in_ms() - info->philo[i].last_meal_time;
			if (process_death(info, current, i))
				return (NULL);
			pthread_mutex_unlock(&info->philo[i].meal_mutex);
		}
		usleep(1000);
	}
	return (NULL);
}
