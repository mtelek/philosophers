/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 21:45:48 by mtelek            #+#    #+#             */
/*   Updated: 2024/07/04 12:55:28 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	dropping_the_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->l_fork);
	pthread_mutex_unlock(&philo->r_fork);
}

void	taking_the_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->r_fork);
	pthread_mutex_lock(&philo->l_fork);
	printf_message(philo, "Fork");
}

void	is_eating(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	checker_t_last_eaten(philo);
	taking_the_forks(philo);
	printf_message(philo, "Eat");
	pthread_mutex_lock(&philo->protect);
	ft_usleep(philo->data->t_eat);
	philo->t_last_eaten = 0;
	philo->t_last_eaten += philo->data->t_eat;
	pthread_mutex_unlock(&philo->protect);
	dropping_the_forks(philo);
	checker_t_last_eaten(philo);
	return ;
}

void	is_sleeping(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	checker_t_last_eaten(philo);
	printf_message(philo, "Sleep");
	pthread_mutex_lock(&philo->protect);
	ft_usleep(philo->data->t_sleep);
	philo->t_last_eaten += philo->data->t_sleep;
	pthread_mutex_unlock(&philo->protect);
	checker_t_last_eaten(philo);
	return ;
}

void	is_thinking(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	checker_t_last_eaten(philo);
	printf_message(philo, "Think");
	pthread_mutex_lock(&philo->protect);
	if (philo->data->n_philo % 2 == 0)
		philo->thinking_time = philo->data->t_eat - philo->data->t_sleep;
	if (philo->data->n_philo % 2 == 1)
		philo->thinking_time = 3 * philo->data->t_eat - 2
			* philo->data->t_sleep;
	ft_usleep(philo->thinking_time);
	philo->t_last_eaten += philo->thinking_time;
	pthread_mutex_unlock(&philo->protect);
	checker_t_last_eaten(philo);
	return ;
}
