/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 21:45:48 by mtelek            #+#    #+#             */
/*   Updated: 2024/05/28 22:36:23 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void printf_message(t_philo *philo, char *text)
{
	pthread_mutex_lock(&philo->data->printf);
	if (!ft_strncmp(text, "Eat", 3))
	{
		printf("%ld %d is eating\n", get_time() - philo->start_time,
		philo->id);
	}
	else if (!ft_strncmp(text, "Sleep", 5))
	{
		printf("%ld %d is sleeping\n", get_time() - philo->start_time,
		philo->id);
	}
	else if (!ft_strncmp(text, "Think", 5))
	{
		printf("%ld %d is thinking\n", get_time() - philo->start_time,
			philo->id);
	}
	else if (!ft_strncmp(text, "Fork", 4))
	{
		printf("%ld %d has taken a fork\n", get_time() - philo->start_time,
		philo->id);
	}
	pthread_mutex_unlock(&philo->data->printf);
}

void taking_the_forks(t_philo *philo)
{
    pthread_mutex_lock(&philo->l_fork);
    printf_message(philo, "Fork");
    pthread_mutex_lock(&philo->r_fork);
    printf_message(philo, "Fork");
}


void	dropping_the_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->l_fork);
	pthread_mutex_unlock(&philo->r_fork);
}

void	is_eating(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->protect);
	taking_the_forks(philo);
	printf_message(philo, "Eat");
	ft_usleep(philo->data->t_eat+1);
	pthread_mutex_unlock(&philo->protect);
	dropping_the_forks(philo);
	return ;
}

void	is_sleeping(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	printf_message(philo, "Sleep");
	ft_usleep(philo->data->t_sleep+1);
	return ;
}

void	is_thinking(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	printf_message(philo, "Think");
	return ;
}
