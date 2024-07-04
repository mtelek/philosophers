/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sen_one.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:55:52 by mtelek            #+#    #+#             */
/*   Updated: 2024/07/03 18:57:23 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*s1_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	return (NULL);
}

int	sen_one(t_data *data)
{
	data->philo->start_time = get_time();
	if (pthread_create(&data->thread[0], NULL, &s1_routine, &data->philo[0]))
		return (m_destroy_free(data), 1);
	while (get_time() - data->philo->start_time <= data->t_die)
		ft_usleep(1);
	if (pthread_detach(data->thread[0]) != 0)
		return (printf("Error, failed to join thread at sen_one\n"), 1);
	printf("%lu %d has died\n", get_time() - data->philo->start_time, 1);
	return (m_destroy_free(data), 0);
}
