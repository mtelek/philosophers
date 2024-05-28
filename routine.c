/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 21:45:48 by mtelek            #+#    #+#             */
/*   Updated: 2024/05/28 14:06:38 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	dropping_the_forks(t_philo *philo)
{
	if (philo->data->is_dead == false)
	{
		pthread_mutex_unlock(&philo->l_fork);
		pthread_mutex_unlock(&philo->r_fork);
	}
	//here the if statement might not even neccesary
}

void checker_t_last_eaten(t_philo *philo)
{
	if (philo->t_last_eaten >= philo->data->t_die)
	{
		pthread_mutex_lock(&philo->data->protect);
		philo->data->id_dead = philo->id;
		philo->data->is_dead = true;
		philo->data->boss->start_time = philo->start_time;
		pthread_mutex_unlock(&philo->data->protect);
		return ;
	}
}

void taking_the_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->l_fork);
	pthread_mutex_lock(&philo->r_fork);
	pthread_mutex_lock(&philo->data->printf);
	printf("%ld %d has taken a fork\n", get_time() - philo->start_time,
		philo->id);
	printf("%ld %d has taken a fork\n", get_time() - philo->start_time,
		philo->id);
	printf("%ld %d is eating\n", get_time() - philo->start_time,
		philo->id);

}

void	is_eating(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	checker_t_last_eaten(philo);
	philo->t_last_eaten = 0;
	taking_the_forks(philo);
	dropping_the_forks(philo);
	ft_usleep(philo->data->t_eat+1);
	philo->t_last_eaten += philo->data->t_eat;
	pthread_mutex_unlock(&philo->data->printf);
	return ;
}

void	is_sleeping(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	checker_t_last_eaten(philo);
	pthread_mutex_lock(&philo->data->printf);
	printf("%ld %d is sleeping\n", get_time() - philo->start_time,
		philo->id);
	pthread_mutex_unlock(&philo->data->printf);
	ft_usleep(philo->data->t_sleep+1);
	philo->t_last_eaten += philo->data->t_sleep;
	return ;
}

void	is_thinking(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	checker_t_last_eaten(philo);
	pthread_mutex_lock(&philo->data->printf);
	printf("%ld %d is thinking\n", get_time() - philo->start_time,
			philo->id);
	pthread_mutex_unlock(&philo->data->printf);
	return ;
}
