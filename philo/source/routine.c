/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 00:17:49 by tkurukul          #+#    #+#             */
/*   Updated: 2025/06/06 23:10:37 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	dining_block(t_philo *philo)
{
	int	flag;

	flag = 0;
	if (philo->info->limit_eat == -1 || (philo->info->limit_eat != -1
			&& philo->num_eaten < philo->info->limit_eat))
	{
		lock_fork(philo);
		print_block(philo, "has started eating...");
		flag = meal_lock_unlock(philo);
		usleep(philo->info->time_eat * 1000);
		unlock_fork(philo);
		if (flag == 1)
			return (-1);
	}
	else
		return (-1);
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->index % 2 == 0)
		usleep(1000);
	while (1)
	{
		if (check_death_flag(philo) || check_if_done(philo))
			break ;
		print_block(philo, "is thinking...");
		if (check_death_flag(philo) || check_if_done(philo))
			break ;
		usleep(1000);
		if (dining_block(philo) == -1)
			break ;
		if (check_death_flag(philo) || check_if_done(philo))
			break ;
		print_block(philo, "is sleeping...");
		usleep(philo->info->time_sleep * 1000);
	}
	return (NULL);
}
