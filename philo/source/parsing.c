/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:06:50 by tkurukul          #+#    #+#             */
/*   Updated: 2025/06/04 19:25:06 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long	ft_atol(const char *str)
{
	int		i;
	long long	result;

	i = 0;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == 43 || str[i] == 45)
	{
		if (str[i] == 45)
			return (err_parsing(str, 0), exit(1), -1);
		i++;
	}
	while (str[i])
	{
		if (str[i] >= 48 && str[i] <= 57)
			result = (result * 10) + (str[i] - 48);
		else
			return (err_parsing(str, 1), exit(1), -1);
		i++;
	}
	if (result < 0 || result > LONG_MAX)
		return(err_parsing(str, 0), exit(1), -1);
	return ((long)result);
}

void	init_parssing(char **av, t_info *info)
{
	int	i;

	i = 0;
	if (!av[1] || !av[2] || !av[3] || !av[4] || av[6])
		return ( write(2, "Philo: Incorrect number of args\n", 32), exit(1));
	info->num_philo = ft_atol(av[1]);
	info->time_die = ft_atol(av[2]) * 1000;
	info->time_eat = ft_atol(av[3]) * 1000;
	info->time_sleep = ft_atol(av[4]) * 1000;
	if (info->time_die < (MIN_TIME *1000) || info->time_eat < (MIN_TIME *1000)
			|| info->time_sleep < (MIN_TIME *1000))
		return (err_parsing(NULL, 2), exit(1));
	if (av[5])
		info->limit_eat = ft_atol(av[5]);
	if (info->limit_eat == 0 || info->num_philo == 0 || info->time_die == 0
			|| info->time_eat == 0 || info->time_sleep == 0)
		return (err_parsing(NULL, 1), exit(1));
	info->tids = malloc(info->num_philo * sizeof(pthread_t));
	if (!info->tids)
		return (err_parsing(NULL, 3), exit(1));
	memset(info->tids, 0, info->num_philo * sizeof(pthread_t));
}
