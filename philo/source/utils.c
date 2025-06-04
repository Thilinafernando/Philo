/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:46:18 by tkurukul          #+#    #+#             */
/*   Updated: 2025/06/05 00:13:24 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	err_parsing(const char *str, int i)
{
	write(2, "Philo: ", 7);
	if (str)
	{
		write(2, str, ft_strlen(str));
		if (i != -42)
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
	else if (i == -42)
		write(2, "\n", 1);
}

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

long long	get_time_in_ms(void)
{
	struct timeval	tv;
	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000LL) + (tv.tv_usec / 1000));
}
