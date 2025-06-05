/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 19:22:24 by tkurukul          #+#    #+#             */
/*   Updated: 2025/06/05 21:34:16 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*single_philo_routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	print_block(philo, "is thinking...");
	print_block(philo, "has taken the left fork...");
	usleep(philo->info->time_die * 1000);
	print_block(philo, "died");
	return (NULL);
}

void	print_block(t_philo *philo, char *str)
{
	long long	time;

	pthread_mutex_lock(&philo->info->print_mutex);
	if (!philo->info->deathflag)
	{
		time = get_time_in_ms() - philo->info->start_time;
		printf("%lld %d %s\n", time, philo->index + 1, str);
	}
	pthread_mutex_unlock(&philo->info->print_mutex);
}

void	lock_fork(t_philo *philo)
{
	if (philo->index % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_block(philo, "has taken the right fork...");
		pthread_mutex_lock(philo->left_fork);
		print_block(philo, "has taken the left fork...");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_block(philo, "has taken the left fork...");
		pthread_mutex_lock(philo->right_fork);
		print_block(philo, "has taken the right fork...");
	}
}

void	unlock_fork(t_philo *philo)
{
	if (philo->index % 2 == 0)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
}

int	meal_lock_unlock(t_philo *philo)
{
	int flag;

	flag = 0;
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = get_time_in_ms();
	philo->num_eaten += 1;
	if (philo->info->limit_eat != -1 && philo->num_eaten >= philo->info->limit_eat)
		flag = -1;
	pthread_mutex_unlock(&philo->meal_mutex);
	return (flag);
}
