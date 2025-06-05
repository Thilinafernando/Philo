/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 19:23:39 by tkurukul          #+#    #+#             */
/*   Updated: 2025/06/05 21:45:20 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	time_to_die(t_info *info, int i)
{
	pthread_mutex_unlock(&info->philo[i].meal_mutex);
	pthread_mutex_lock(&info->death_mutex);
	info->deathflag = 1;
	pthread_mutex_unlock(&info->death_mutex);
	print_block(&info->philo[i], "has decieded to die.");
}

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
	return (done_count == info->num_philo);
}

void	*death_routine(void *arg)
{
	t_info		*info;
	long long	current;
	int			i;

	info = (t_info *)arg;
	usleep(1000);
	while (1)
	{
		i = -1;
		if (all_philosophers_done(info))
		{
			pthread_mutex_lock(&info->death_mutex);
			info->deathflag = 1;
			pthread_mutex_unlock(&info->death_mutex);
			pthread_mutex_lock(&info->print_mutex);
			printf("All philosophers have finished eating!\n");
			pthread_mutex_unlock(&info->print_mutex);
			break;
		}
		while (++i < info->num_philo)
		{
			pthread_mutex_lock(&info->philo[i].meal_mutex);
			current = get_time_in_ms() - info->philo[i].last_meal_time;
			if (current > info->time_die)
				return (time_to_die(info, i), NULL);
			pthread_mutex_unlock(&info->philo[i].meal_mutex);
		}
		usleep(1000);
	}
	return (NULL);
}
