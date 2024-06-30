/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 21:45:48 by mtelek            #+#    #+#             */
/*   Updated: 2024/06/30 19:27:14 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	dropping_the_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->l_fork);
	pthread_mutex_unlock(&philo->r_fork);
}

void checker_t_last_eaten(t_philo *philo)
{
	if (philo->t_last_eaten > philo->data->t_die)
	{
		pthread_mutex_lock(&philo->data->death_mutex);
		philo->data->id_dead = philo->id;
		philo->data->is_dead = true;
		philo->data->boss->start_time = philo->start_time;
		pthread_mutex_unlock(&philo->data->death_mutex);
		return ;
	}
}

void printf_message(t_philo *philo, char *text)
{
	pthread_mutex_lock(&philo->data->printf);
	if (!ft_strncmp(text, "Eat", 3) && philo->data->is_dead != true)
	{
		printf("%ld %d is eating\n", get_time() - philo->start_time,
		philo->id);
	}
	else if (!ft_strncmp(text, "Sleep", 5) && philo->data->is_dead != true)
	{
		printf("%ld %d is sleeping\n", get_time() - philo->start_time,
		philo->id);
	}
	else if (!ft_strncmp(text, "Think", 5) && philo->data->is_dead != true)
	{
		printf("%ld %d is thinking\n", get_time() - philo->start_time,
			philo->id);
	}
	else if (!ft_strncmp(text, "Fork", 4) && philo->data->is_dead != true)
	{
		printf("%ld %d has taken a fork\n", get_time() - philo->start_time,
		philo->id);
	}
	pthread_mutex_unlock(&philo->data->printf);
}

void taking_the_forks(t_philo *philo)
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
	philo->t_last_eaten = 0;
	ft_usleep(philo->data->t_eat);
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
	ft_usleep(philo->data->t_sleep);
	philo->t_last_eaten += philo->data->t_sleep;
	checker_t_last_eaten(philo);
	return ;
}

void	is_thinking(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	checker_t_last_eaten(philo);
	printf_message(philo, "Think");
	pthread_mutex_lock(&philo->protect);
    philo->data->n_philos_eaten += 1;
	pthread_mutex_unlock(&philo->protect);
	philo->thinking_time = 0;
	if ((philo->data->n_philo % 2 == 0 && philo->data->t_die >= philo->data->t_eat + philo->data->t_sleep)
		|| (philo->data->n_philo % 2 == 1 && philo->data->t_die >= 3 * philo->data->t_eat))
		philo->t_last_eaten += philo->thinking_time;
	else
	{
		while (1)
		{
			pthread_mutex_lock(&philo->protect);
			if (philo->data->n_philos_eaten > philo->data->n_philo 
				|| philo->data->t_die < philo->t_last_eaten + philo->thinking_time)
			{
				pthread_mutex_unlock(&philo->protect);
				break;
			}
			ft_usleep(1);
			philo->thinking_time += 1;
			pthread_mutex_unlock(&philo->protect);
		}
		philo->t_last_eaten += philo->thinking_time;
	}
	pthread_mutex_unlock(&philo->protect);
	checker_t_last_eaten(philo);
	return ;
}

//mistakes in the output, especially with the dining philosophers
//valgrind errors
//funcheck errors
//norminette

