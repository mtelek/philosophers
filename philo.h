/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 20:39:17 by mtelek            #+#    #+#             */
/*   Updated: 2024/05/28 22:20:39 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <errno.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/types.h>
# include <unistd.h>

struct	s_philo;
struct	s_boss;

typedef struct s_data
{
	int				n_philo;
	u_int64_t		t_die;
	u_int64_t		t_eat;
	u_int64_t		t_sleep;
	int				n_eat;
	bool			is_dead;
	int				id_dead;
	pthread_mutex_t	printf;
	pthread_t		*thread;
	pthread_mutex_t	*forks;
	struct s_philo	*philo;
	struct s_boss	*boss;
}					t_data;

typedef struct s_philo
{
	int				id;
	int				eat_count;
	u_int64_t		t_last_eaten;
	u_int64_t		start_time;
	pthread_mutex_t	l_fork;
	pthread_mutex_t	r_fork;
	pthread_mutex_t	protect;
	t_data			*data;

}					t_philo;

typedef struct s_boss
{
	t_data 			*data;
	u_int64_t		start_time;
}					t_boss;

// creating_and_initializing
int					thread_init(t_data *data);
int					join_init(t_data *data);
int					forks_init(t_data *data);
void				philo_init(t_data *data);
int					checker(int argc, char **argv);
int					ft_atoi(const char *str);
void				m_destroy_free(t_data *data);

// routine
void				is_eating(void *arg);
void				is_sleeping(void *arg);
void				is_thinking(void *arg);
void				*routine(void *arg);

// time setting
int					ft_usleep(useconds_t time);
u_int64_t			get_time(void);


//helperhelper

int	ft_strncmp(const char *str1, const char *str2, size_t n);

#endif
