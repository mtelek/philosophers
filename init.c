/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 21:00:21 by mtelek            #+#    #+#             */
/*   Updated: 2024/05/28 22:37:57 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *routine(void *arg)
{
    t_philo *philo;
    
    philo = (t_philo *)arg;
    while (1)
    {
        if (philo->data->is_dead == true)
            break;
        is_eating(arg);
        if (philo->data->is_dead == true)
            break;
        is_sleeping(arg);
        if (philo->data->is_dead == true)
            break;
        is_thinking(arg);
        if (philo->data->is_dead == true)
            break;
    }
    return (NULL);
}

void	*monitor(void *arg)
{
	t_boss		*boss;
	uint64_t	time;

	boss = (t_boss *)arg;
	while (1)
	{
		if (boss->data->is_dead == true)
		{
			time = get_time() - boss->start_time;
			pthread_mutex_lock(&boss->data->printf);
			printf("%lu %d died\n", time, boss->data->id_dead);
			pthread_mutex_unlock(&boss->data->printf);
			break ;
		}
		//somehow not entering this if statement above when a philo dies
		//should protect the is_dead value when overwriting it somewhere
		//for the mentioned above check chatgpts last response
	}
	return (NULL);
}

int	thread_init(t_data *data)
{
	int			i;
	pthread_t	boss_thread;

	i = -1;
	if (pthread_create(&boss_thread, 0, &monitor, &data->boss) != 0)
		return (printf("Error, failed to create thread for monitoring"), 1);
	while (data->n_philo > ++i)
	{
		if (pthread_create(&data->thread[i], 0, &routine, &data->philo[i]) != 0)
			return (printf("Error, failed to create thread\n"), 1);
		data->philo[i].start_time = get_time();
		ft_usleep(1);
	}
	return (0);
}

int	join_init(t_data *data)
{
	int	i;

	i = 0;
	while (data->n_philo > i)
	{
		if (pthread_join(data->thread[i], NULL) != 0)
			return(printf("Error, failed to join thread\n"), 1);
		i++;
	}
	return (0);
}

int	forks_init(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philo)
		pthread_mutex_init(&data->forks[i], NULL);
	data->philo[0].l_fork = data->forks[data->n_philo];
	data->philo[0].r_fork = data->forks[0];
	i = 1;
	while (i < data->n_philo)
	{
		data->philo[i].l_fork = data->forks[i - 1];
		data->philo[i].r_fork = data->forks[i];
		i++;
	}
	return (0);
}

void	philo_init(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		data->philo[i].data = data;
		data->philo[i].id = i + 1;
		data->philo[i].eat_count = 0;
		data->philo[i].t_last_eaten = 0;
		data->philo[i].start_time = 0;
		pthread_mutex_init(&data->philo[i].protect, NULL);
		i++;
	}
	data->boss->start_time = 0;
}
