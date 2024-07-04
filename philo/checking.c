/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:17:20 by mtelek            #+#    #+#             */
/*   Updated: 2024/07/04 18:30:14 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	checking_done(t_philo *monitor)
{
	pthread_mutex_lock(&monitor->data->alldone);
	if (monitor->data->all_done == true)
	{
		pthread_mutex_unlock(&monitor->data->alldone);
		pthread_mutex_unlock(&monitor->data->printf);
		return (true);
	}
	pthread_mutex_unlock(&monitor->data->alldone);
	return (false);
}

bool	checking_all_done(t_philo *philo)
{
	if (philo->data->n_eat != -1 && philo->data->counter == philo->data->n_eat
		* philo->data->n_philo)
	{
		pthread_mutex_lock(&philo->data->alldone);
		philo->data->all_done = true;
		pthread_mutex_unlock(&philo->data->alldone);
		return (true);
	}
	return (false);
}

bool	checking_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->printf);
	if (philo->data->is_dead == true)
	{
		pthread_mutex_unlock(&philo->data->printf);
		return (true);
	}
	pthread_mutex_unlock(&philo->data->printf);
	return (false);
}
