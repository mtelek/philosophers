/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 20:39:17 by mtelek            #+#    #+#             */
/*   Updated: 2024/07/04 18:20:49 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <errno.h>
# include <pthread.h>
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
	pthread_mutex_t	check;
	pthread_mutex_t	alldone;
	pthread_t		*thread;
	pthread_mutex_t	*forks;
	struct s_philo	*philo;
	struct s_boss	*boss;
	int				n_philos_eaten;
	int				counter;
	int				checking_round;
	bool			all_done;
}					t_data;

typedef struct s_philo
{
	int				id;
	int				eat_count;
	u_int64_t		t_last_eaten;
	u_int64_t		start_time;
	u_int64_t		thinking_time;
	pthread_mutex_t	l_fork;
	pthread_mutex_t	r_fork;
	pthread_mutex_t	protect;
	pthread_mutex_t	lock;

	t_data			*data;

}					t_philo;

typedef struct s_boss
{
	t_data			*data;
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
void				refreshing_data(t_philo *philo);
void				delaying_even(t_philo *philo);
void				delaying_uneven(t_philo *philo);
void				printf_message(t_philo *philo, char *text);
void				checker_t_last_eaten(t_philo *philo);
void				*s1_routine(void *arg);
int					sen_one(t_data *data);

// checking
bool				checking_all_done(t_philo *philo);
bool				checking_done(t_philo *monitor);
bool				checking_dead(t_philo *philo);

// time setting
int					ft_usleep(useconds_t time);
u_int64_t			get_time(void);

// helperhelper

int					ft_strncmp(const char *str1, const char *str2, size_t n);

#endif
