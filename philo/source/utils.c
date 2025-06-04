/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:46:18 by tkurukul          #+#    #+#             */
/*   Updated: 2025/06/04 19:24:47 by tkurukul         ###   ########.fr       */
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
}


void	err_parsing(const char *str, int i)
{
	write(2, "Philo: ", 7);
	if (str)
	{
		write(2, str, ft_strlen(str));
		write(2, ": ", 2);
	}
	if (i == 0)
		write(2, "Argument out of range\n", 22);
	else if (i == 1)
		write(2, "Invalid argument\n", 17);
	else if (i == 2)
		write(2, "Time values must be at least 60ms\n", 34);
	else if (i == 3)
		write(2, "Malloc failed\n", 14);
}

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}
