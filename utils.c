/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 15:45:59 by mtelek            #+#    #+#             */
/*   Updated: 2024/05/28 21:28:09 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n && (str1[i] != '\0' || str2[i] != '\0'))
	{
		if (str1[i] != str2[i])
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		i++;
	}
	return (0);
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

int	number_check(char **argv)
{
	int	n;
	int	i;

	n = 1;
	while (argv[n])
	{
		i = 0;
		while (argv[n] && argv[n][i])
		{
			if (argv[n][i] == '+' && argv[n][i + 1] == '+')
				return (1);
			if ((argv[n][i] < '0' || argv[n][i] > '9') && argv[n][i] != '+')
				return (1);
			i++;
		}
		n++;
	}
	return (0);
}

int	null_check(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if ((ft_atoi(argv[i])) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	checker(int argc, char **argv)
{
	int	argv5;

	(void)argv5;
	if (argv[5])
		argv5 = ft_atoi(argv[5]);
	if (argc != 5 && argc != 6)
	{
		printf("Error, invalid amount of arguments\n");
		return (1);
	}
	if (number_check(argv))
	{
		printf("Error, not numerical cahracter found\n");
		return (1);
	}
	if (null_check(argv))
	{
		printf("Error, argument cannot be zero\n");
		return (1);
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	int	parity;
	int	num;
	int	i;

	parity = 0;
	num = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			parity++;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		num *= 10;
		num += str[i] - 48;
		i++;
	}
	if (!(parity % 2))
		return (num);
	return (-num);
}
