/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sen_one.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:55:52 by mtelek            #+#    #+#             */
/*   Updated: 2025/07/19 14:35:08 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sen_one_free(t_data *data)
{
	if (data->thread)
		free(data->thread);
	if (data->boss)
		free(data->boss);
	if (data->forks)
		free(data->forks);
	if (data->philo)
		free(data->philo);
	pthread_mutex_destroy(&data->check);
	pthread_mutex_destroy(&data->alldone);
	pthread_mutex_destroy(&data->printf);
	if (data)
		free(data);
}

void	*s1_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	(void)philo;
	return (NULL);
}

int	sen_one(t_data *data)
{
	data->philo->start_time = get_time();
	if (pthread_create(&data->thread[0], NULL, &s1_routine, &data->philo[0]))
		return (sen_one_free(data), 1);
	while (get_time() - data->philo->start_time <= data->t_die)
		ft_usleep(1);
	if (pthread_detach(data->thread[0]) != 0)
		return (printf("Error, failed to join thread at sen_one\n"), 1);
	printf("%lu %d has died\n", get_time() - data->philo->start_time, 1);
	return (sen_one_free(data), 0);
}
