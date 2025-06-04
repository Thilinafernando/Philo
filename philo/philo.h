/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:02:38 by tkurukul          #+#    #+#             */
/*   Updated: 2025/06/04 19:14:51 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define MIN_TIME 60

# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <errno.h>
# include <unistd.h>
# include <dirent.h>
# include <stdio.h>
# include <string.h>
# include <signal.h>
# include <fcntl.h>
# include <limits.h>

typedef struct s_info {
	long		num_philo;
	long		time_die;
	long		time_eat;
	long		time_sleep;
	long		limit_eat;
	pthread_t	*tids;
}	t_info;

// parsing
void	err_parsing(const char *str, int i);
void	init_parssing(char **av, t_info *info);

// utils
void	init_struct(t_info *info);
int		ft_strlen(const char *str);

#endif
