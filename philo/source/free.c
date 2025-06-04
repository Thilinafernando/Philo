/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 00:05:18 by tkurukul          #+#    #+#             */
/*   Updated: 2025/06/05 00:05:51 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	free_forks(t_info *info)
{
	int	i;

	i = -1;
	if (info->forks)
	{
		while (i < info->num_philo)
		{
			if (pthread_mutex_destroy(&info->forks[i]) != 0)
				return (err_parsing("Mutex destroy failed", -42));
		}
		free(info->forks);
		info->forks = NULL;
	}
}

void	free_all(t_info *info)
{
	free_forks(info);
	if (pthread_mutex_destroy(&info->print_mutex) != 0)
		err_parsing("Mutex destroy failed", -42);
	if (info->tids)
	{
		free(info->tids);
		info->tids = NULL;
	}
	if (info->philo)
	{
		free(info->philo);
		info->philo = NULL;
	}
}

