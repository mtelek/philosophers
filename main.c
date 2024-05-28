/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 15:12:59 by mtelek            #+#    #+#             */
/*   Updated: 2024/05/28 22:20:13 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*s1_routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo * )arg;
	return (NULL);
}

int sen_one(t_data *data)
{
    data->philo->start_time = get_time();
    if (pthread_create(&data->thread[0], NULL, &s1_routine, &data->philo[0]))
        return (m_destroy_free(data), 1);
    while (get_time() - data->philo->start_time <= data->t_die)
        ft_usleep(0);
    pthread_join(data->thread[0], NULL);
    printf("%lu %d has died\n", get_time() - data->philo->start_time, 1);
    return (m_destroy_free(data), 0);
}


int	mem_alloc(t_data **data)
{
	(*data)->forks = (pthread_mutex_t *)malloc((*data)->n_philo
			* sizeof(pthread_mutex_t));
	if (!(*data)->forks)
		return(printf("Error, failed to allocate memory for forks\n"), 1);
	(*data)->philo = malloc((*data)->n_philo * sizeof(t_philo));
	if (!(*data)->philo)
		return(printf("Error, failed to allocate memory for philos\n"), 1);
	(*data)->thread = (pthread_t *)malloc(((*data)->n_philo + 1)
			* sizeof(pthread_t));
	if (!(*data)->thread)
		return(printf("Error, failed to allocate memory for philos\n"), 1);
	(*data)->boss = malloc(sizeof(t_boss));
		if (!(*data)->boss)
		return(printf("Error, failed to allocate memory for boss\n"), 1);
	return (0);
}

int	create_data(t_data **data, char **argv)
{
	*data = (t_data *)malloc(sizeof(t_data));
	if (!*data)
		return(printf("Error, failed to allocate memory for data\n"), 1);
	(*data)->n_philo = ft_atoi(argv[1]);
	(*data)->t_die = (u_int64_t)ft_atoi(argv[2]);
	(*data)->t_eat = (u_int64_t)ft_atoi(argv[3]);
	(*data)->t_sleep = (u_int64_t)ft_atoi(argv[4]);
	if (argv[5])
		(*data)->n_eat = ft_atoi(argv[5]);
	(*data)->is_dead = false;
	(*data)->id_dead = 0;
	pthread_mutex_init(&(*data)->printf, NULL);
	return (0);
}

void	m_destroy_free(t_data *data)
{
	int	i;

	i = 0;
	while (i <= data->n_philo && data->n_philo != 1)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philo[i].protect);
		i++;
	}
	pthread_mutex_destroy(&data->printf);
	if (data->thread)
		free(data->thread);
	if (data->boss)
		free(data->boss);
	if (data->forks)
		free(data->forks);
	if (data->philo)
		free(data->philo);
	if (data)
		free(data);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (checker(argc, argv))
		return (1);
	if (create_data(&data, argv))
		return (1);
	if (mem_alloc(&data))
		return (m_destroy_free(data), 1);
	if (data->n_philo == 1)
		return (sen_one(data));
	philo_init(data);
	if (thread_init(data))
		return (m_destroy_free(data), 1);
	if (forks_init(data))
		return (m_destroy_free(data), 1);
	if (join_init(data))
		return (m_destroy_free(data), 1);
	return (m_destroy_free(data), 0);
}
