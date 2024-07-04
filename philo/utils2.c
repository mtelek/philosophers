/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:12:54 by mtelek            #+#    #+#             */
/*   Updated: 2024/07/04 16:16:40 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	checker_t_last_eaten(t_philo *philo)
{
	if (philo->t_last_eaten > philo->data->t_die)
	{
		pthread_mutex_lock(&philo->data->printf);
		if (philo->data->id_dead == 0)
		{
			philo->data->id_dead = philo->id;
			philo->data->is_dead = true;
			philo->data->boss->start_time = philo->start_time;
			ft_usleep(1);
		}
		pthread_mutex_unlock(&philo->data->printf);
	}
}

void	printf_message(t_philo *philo, char *text)
{
	pthread_mutex_lock(&philo->data->printf);
	if (!ft_strncmp(text, "Eat", 3) && philo->data->is_dead != true)
	{
		printf("%ld %d is eating\n", get_time() - philo->start_time, philo->id);
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

int	ft_usleep(useconds_t time)
{
	u_int64_t	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(time / 10);
	return (0);
}

u_int64_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (1);
	return ((time.tv_sec * (u_int64_t)1000) + (time.tv_usec / 1000));
}
