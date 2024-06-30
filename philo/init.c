/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 21:00:21 by mtelek            #+#    #+#             */
/*   Updated: 2024/06/30 19:39:19 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *routine(void *arg)
{
    t_philo *philo;
    
    philo = (t_philo *)arg;
    while (1)
    {
		pthread_mutex_lock(&philo->protect);
		philo->data->counter += 1;
		philo->data->checking_round += 1;
		pthread_mutex_unlock(&philo->protect);
		philo->t_last_eaten = 0;
		if (philo->id == 1)
			philo->data->n_philos_eaten = 0;
		if (philo->data->checking_round <= philo->data->n_philo)
		{
			if (philo->id % 2 == 0 && philo->data->n_philo % 2 == 0)
			{
				ft_usleep(philo->data->t_eat);
				philo->t_last_eaten += philo->data->t_eat;
			}
			else if (philo->data->n_philo % 2 == 1)
			{
				if (philo->id % 2 == 0 && philo->id != philo->data->n_philo)
				{
					ft_usleep(philo->data->t_eat);
					philo->t_last_eaten += philo->data->t_eat;
				}
				else if (philo->id % 2 == 1 && philo->id == philo->data->n_philo)
				{
					ft_usleep(2 * philo->data->t_eat);
					philo->t_last_eaten += 2 * philo->data->t_eat;
				}
			}
		}
        is_eating(arg);
        if (philo->data->is_dead == true)
            break;
        is_sleeping(arg);
        if (philo->data->is_dead == true)
            break;
        is_thinking(arg);
        if (philo->data->is_dead == true)
            break;
		if (philo->data->n_eat && philo->data->counter == philo->data->n_eat * philo->data->n_philo)
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
		pthread_mutex_lock(&boss->data->death_mutex);
		if (boss->data->is_dead == true)
		{
			boss->start_time = boss->data->philo[boss->data->id_dead - 1].start_time;
			time = get_time() - boss->data->boss->start_time;
			pthread_mutex_lock(&boss->data->printf);
			printf("%lu %d died\n", time, boss->data->id_dead);
			pthread_mutex_unlock(&boss->data->printf);
			pthread_mutex_unlock(&boss->data->death_mutex);
			break ;
		}
		pthread_mutex_unlock(&boss->data->death_mutex);
		ft_usleep(1);
	}
	return (NULL);
}

int	thread_init(t_data *data)
{
	int			i;
	pthread_t	boss_thread;

	i = -1;
	if (pthread_create(&boss_thread, 0, &monitor, &data) != 0)
		return (printf("Error, failed to create thread for monitoring"), 1);
	while (data->n_philo > ++i)
	{
		if (pthread_create(&data->thread[i], 0, &routine, &data->philo[i]) != 0)
			return (printf("Error, failed to create thread\n"), 1);
		data->philo[i].start_time = get_time();
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
	data->philo[0].l_fork = data->forks[data->n_philo - 1];
	data->philo[0].r_fork = data->forks[0];
	i = 1;
	while (i < data->n_philo )
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
		data->philo[i].thinking_time = 0;
		pthread_mutex_init(&data->philo[i].protect, NULL);
		i++;
	}
	pthread_mutex_init(&data->death_mutex, NULL);
}
