/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviovi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 10:55:06 by vviovi            #+#    #+#             */
/*   Updated: 2023/04/03 12:37:58 by vviovi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

int	ft_atoi(const char *nptr)
{
	long	i;
	int		neg;
	long	res;

	i = 0;
	neg = 1;
	res = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			neg = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res *= 10;
		res += (nptr[i] - '0');
		if ((res > 2147483647 && neg == 1) || (res > 2147483648 && neg == -1))
			return ((-1 - neg) / 2);
		i++;
	}
	return (res * neg);
}

long	get_time(void)
{
	long			time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time);
}

void	print_act(t_philo *philo, int act)
{
	long	timestamp;

	pthread_mutex_lock(&philo->data->var_end);
	if (philo->data->is_the_end)
	{
		pthread_mutex_unlock(&philo->data->var_end);
		return ;
	}
	pthread_mutex_unlock(&philo->data->var_end);
	pthread_mutex_lock(&philo->data->printable);
	timestamp = get_time() - philo->start;
	if (act == 0)
		printf("%li %i is thinking\n", timestamp, philo->num_philo);
	else if (act == 1)
		printf("%li %i is eating\n", timestamp, philo->num_philo);
	else if (act == 2)
		printf("%li %i is sleeping\n", timestamp, philo->num_philo);
	else if (act == 3)
		printf("%li %i has taken a fork\n", timestamp, philo->num_philo);
	pthread_mutex_unlock(&philo->data->printable);
}

int	is_the_end(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->var_end);
	if (philo->data->is_the_end)
	{
		pthread_mutex_unlock(&philo->data->var_end);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->var_end);
	return (0);
}

int	wait_usleep(t_philo *philo, int time)
{
	while (time > 0)
	{
		if (is_the_end(philo))
			return (1);
		if (time >= 9000)
		{
			usleep(9000);
			time = time - 9000;
		}
		else
		{
			usleep(time);
			time = 0;
		}
		if (is_the_end(philo))
			return (1);
	}
	if (is_the_end(philo))
		return (1);
	return (0);
}
