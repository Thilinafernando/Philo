/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:02:38 by tkurukul          #+#    #+#             */
/*   Updated: 2025/06/05 00:47:24 by tkurukul         ###   ########.fr       */
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

typedef struct s_info t_info;

typedef struct s_philo {
	int				index;
	int				num_eaten;
	int				full;
	long long		last_meal_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_info			*info;
}	t_philo;

typedef struct s_info {
	long			num_philo;
	long			time_die;
	long			time_eat;
	long			time_sleep;
	long			limit_eat;
	long long		start_time;
	pthread_t		*tids;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	int				deathflag;
	t_philo			*philo;
}	t_info;

// parsing
void	err_parsing(const char *str, int i);
void	init_parssing(char **av, t_info *info);

// utils
void		init_struct(t_info *info);
int			ft_strlen(const char *str);
void		init_structpt2(t_info *info);
void		init_philo_info(t_info *info);
long long	get_time_in_ms(void);

//free
void	free_all(t_info *info);

void	*routine(void *arg);

#endif
