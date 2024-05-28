#include "philo.h"

void printf_message(t_philo *philo, char *text)
{
	if (!ft_strncmp(text, "Eat", 3))
	{
		pthread_mutex_lock(&philo->data->printf);
		printf("%ld %d is eating\n", get_time() - philo->start_time,
		philo->id);
		pthread_mutex_unlock(&philo->data->printf);
	}
	else if (!ft_strncmp(text, "Sleep", 5))
	{
		pthread_mutex_lock(&philo->data->printf);
		printf("%ld %d is sleeping\n", get_time() - philo->start_time,
		philo->id);
		pthread_mutex_unlock(&philo->data->printf);
	}
	else if (!ft_strncmp(text, "Think", 5))
	{
		pthread_mutex_lock(&philo->data->printf);
		printf("%ld %d is thinking\n", get_time() - philo->start_time,
			philo->id);
		pthread_mutex_unlock(&philo->data->printf);
	}
	else if (!ft_strncmp(text, "Fork", 4))
	{
		pthread_mutex_lock(&philo->data->printf);
		printf("%ld %d has taken a fork\n", get_time() - philo->start_time,
		philo->id);
		pthread_mutex_unlock(&philo->data->printf);
	}
}

// void checker_t_last_eaten(t_philo *philo)
// {
// 	if (philo->t_last_eaten >= philo->data->t_die)
// 	{
// 		pthread_mutex_lock(&philo->data->protect);
// 		philo->data->id_dead = philo->id;
// 		philo->data->is_dead = true;
// 		philo->data->boss->start_time = philo->start_time;
// 		pthread_mutex_unlock(&philo->data->protect);
// 		return ;
// 	}
// }

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
	//checker_t_last_eaten(philo);
	//philo->t_last_eaten = 0;
	taking_the_forks(philo);
	printf_message(philo, "Eat");
	ft_usleep(philo->data->t_eat+1);
	pthread_mutex_unlock(&philo->protect);
	dropping_the_forks(philo);
	//philo->t_last_eaten += philo->data->t_eat;
	return ;
}

void	is_sleeping(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	//checker_t_last_eaten(philo);
	printf_message(philo, "Sleep");
	ft_usleep(philo->data->t_sleep+1);
	//philo->t_last_eaten += philo->data->t_sleep;
	return ;
}

void	is_thinking(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	//checker_t_last_eaten(philo);
	return ;
}
