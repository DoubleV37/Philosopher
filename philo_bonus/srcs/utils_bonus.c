/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviovi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 10:55:06 by vviovi            #+#    #+#             */
/*   Updated: 2023/04/10 16:25:10 by vviovi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher_bonus.h"

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

	sem_wait(philo->data->printable);
	timestamp = get_time() - philo->start;
	if (act == 0)
		printf("%li %i is thinking\n", timestamp, philo->num_philo);
	else if (act == 1)
		printf("%li %i is eating\n", timestamp, philo->num_philo);
	else if (act == 2)
		printf("%li %i is sleeping\n", timestamp, philo->num_philo);
	else if (act == 3)
		printf("%li %i has taken a fork\n", timestamp, philo->num_philo);
	sem_post(philo->data->printable);
}

int	is_digit(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

void	clean(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->data->nb_philo)
	{
		kill(philos[i].pid, SIGKILL);
		i++;
	}
	kill(philos->data->eat_supervisor, SIGKILL);
	sem_close(data->forks);
	sem_close(data->printable);
	sem_close(data->is_the_end);
	sem_close(data->eat);
	sem_close(data->waitfork);
	free(philos);
}
