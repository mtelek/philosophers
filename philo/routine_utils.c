/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:20:29 by mtelek            #+#    #+#             */
/*   Updated: 2024/07/04 18:18:27 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	delaying_even(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->check);
	if (philo->id % 2 == 0
		&& philo->data->checking_round <= philo->data->n_philo)
	{
		pthread_mutex_unlock(&philo->data->check);
		ft_usleep(philo->data->t_eat);
		pthread_mutex_lock(&philo->protect);
		philo->t_last_eaten += philo->data->t_eat;
		pthread_mutex_unlock(&philo->protect);
		return ;
	}
	pthread_mutex_unlock(&philo->data->check);
}

void	delaying_uneven(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->check);
	if (philo->data->checking_round <= philo->data->n_philo)
	{
		pthread_mutex_unlock(&philo->data->check);
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
		return ;
	}
	pthread_mutex_unlock(&philo->data->check);
}

void	refreshing_data(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->check);
	philo->data->counter += 1;
	philo->data->checking_round += 1;
	pthread_mutex_unlock(&philo->data->check);
	pthread_mutex_lock(&philo->protect);
	philo->t_last_eaten = 0;
	pthread_mutex_unlock(&philo->protect);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		refreshing_data(philo);
		if (philo->data->n_philo % 2 == 0)
			delaying_even(philo);
		else if (philo->data->n_philo % 2 == 1)
			delaying_uneven(philo);
		is_eating(arg);
		if (checking_dead(philo) == true)
			break ;
		is_sleeping(arg);
		if (checking_dead(philo) == true)
			break ;
		is_thinking(arg);
		if (checking_dead(philo) == true)
			break ;
		if (checking_all_done(philo) == true)
			break ;
	}
	return (NULL);
}
