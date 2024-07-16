/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 21:00:21 by mtelek            #+#    #+#             */
/*   Updated: 2024/07/05 17:29:27 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *arg)
{
	t_philo		*monitor;
	uint64_t	time;

	monitor = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&monitor->data->printf);
		if (monitor->data->is_dead == true)
		{
			monitor->data->boss->start_time
				= monitor->data->philo[monitor->data->id_dead - 1].start_time;
			time = get_time() - monitor->data->boss->start_time;
			printf("%lu %d died\n", time, monitor->data->id_dead);
			pthread_mutex_unlock(&monitor->data->printf);
			break ;
		}
		if (checking_done(monitor) == true)
			break ;
		pthread_mutex_unlock(&monitor->data->printf);
		ft_usleep(1);
	}
	return (NULL);
}

int	thread_init(t_data *data)
{
	int			i;
	pthread_t	boss_thread;

	i = -1;
	if (pthread_create(&boss_thread, 0, &monitor, &data->philo[0]) != 0)
		return (printf("Error, failed to create thread for monitoring"), 1);
	if (pthread_detach(boss_thread) != 0)
		return (printf("Error, failed to detach boss_thread"), 1);
	while (data->n_philo > ++i)
	{
		if (pthread_create(&data->thread[i], 0, &routine, &data->philo[i]) != 0)
			return (printf("Error, failed to create thread\n"), 1);
		pthread_mutex_lock(&data->printf);
		data->philo[i].start_time = get_time();
		pthread_mutex_unlock(&data->printf);
	}
	return (0);
}

int	join_init(t_data *data)
{
	int	i;

	i = -1;
	while (data->n_philo > ++i)
	{
		if (pthread_join(data->thread[i], NULL) != 0)
			return (printf("Error, failed to join thread\n"), 1);
	}
	return (0);
}

int	forks_init(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philo)
		pthread_mutex_init(&data->forks[i], NULL);
	data->philo[0].l_fork = data->forks[data->n_philo - 1];
	data->philo[0].r_fork = data->forks[0];
	i = 0;
	while (++i < data->n_philo)
	{
		data->philo[i].l_fork = data->forks[i - 1];
		data->philo[i].r_fork = data->forks[i];
	}
	return (0);
}

void	philo_init(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philo)
	{
		data->philo[i].data = data;
		data->philo[i].id = i + 1;
		data->philo[i].eat_count = 0;
		data->philo[i].t_last_eaten = 0;
		data->philo[i].start_time = 0;
		data->philo[i].thinking_time = 0;
		pthread_mutex_init(&data->philo[i].protect, NULL);
		pthread_mutex_init(&data->philo[i].lock, NULL);
	}
	data->boss->data = data;
	data->boss->start_time = get_time();
}
