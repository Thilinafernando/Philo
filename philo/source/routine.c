/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 00:17:49 by tkurukul          #+#    #+#             */
/*   Updated: 2025/06/05 00:55:11 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	print_block(t_philo *philo, char *str)
{
	long long	time;

	pthread_mutex_lock(&philo->info->print_mutex);
	if (!philo->info->deathflag)
	{
		time = get_time_in_ms() - philo->info->start_time;
		printf("%lld %d %s\n", time, philo->index, str);
	}
	pthread_mutex_unlock(&philo->info->print_mutex);
}

void	*routine(void *arg)
{
	t_philo *philo;
	long long	current;

	philo = (t_philo *)arg;
	while (!philo->info->deathflag)
	{
		print_block(philo, "is thinking...");
		if (philo->info->limit_eat != -1 && philo->num_eaten < philo->info->limit_eat)
		{
			pthread_mutex_lock(philo->left_fork);
			print_block(philo, "has taken the left fork...");
			pthread_mutex_lock(philo->right_fork);
			print_block(philo, "has taken the right fork...");
			print_block(philo, "has started eating...");
			philo->last_meal_time = get_time_in_ms();
			philo->num_eaten += 1;
			usleep(philo->info->time_eat * 1000);
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
		}
		current = get_time_in_ms() - philo->last_meal_time;
		if (current > philo->info->time_die)
		{
			print_block(philo, "has died...");
			philo->info->deathflag++;
		}
		print_status(philo, "is sleeping");
		usleep(philo->info->time_sleep * 1000);
	}
	return (NULL);
}
