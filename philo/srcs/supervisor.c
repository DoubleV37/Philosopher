/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviovi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 16:12:46 by vviovi            #+#    #+#             */
/*   Updated: 2023/04/10 11:31:02 by vviovi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

static int	put_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->var_eat);
	if (get_time() - philo->last_eat > philo->data->time_to_die)
	{
		pthread_mutex_unlock(&philo->var_eat);
		pthread_mutex_lock(&philo->data->var_end);
		philo->data->is_the_end = 1;
		pthread_mutex_unlock(&philo->data->var_end);
		pthread_mutex_lock(&philo->data->printable);
		printf("%li %i died\n", get_time() - philo->start, philo->num_philo);
		pthread_mutex_unlock(&philo->data->printable);
		return (1);
	}
	pthread_mutex_unlock(&philo->var_eat);
	return (0);
}

static void	check_nb_eat(t_philo *philos)
{
	pthread_mutex_lock(&philos->data->var_end);
	pthread_mutex_lock(&philos->data->var_end_eat);
	if (philos->data->is_the_end != 1
		&& philos->data->is_the_end_eat == philos->data->nb_philo)
		philos->data->is_the_end = 1;
	pthread_mutex_unlock(&philos->data->var_end_eat);
	pthread_mutex_unlock(&philos->data->var_end);
}

void	*check_death(void *h)
{
	int		i;
	t_philo	*philos;

	philos = (t_philo *) h;
	pthread_mutex_lock(&philos->data->var_end);
	while (philos->data->is_the_end != 1)
	{
		pthread_mutex_unlock(&philos->data->var_end);
		i = 0;
		while (i < philos->data->nb_philo)
		{
			if (put_death(&philos[i]))
				return (NULL);
			check_nb_eat(philos);
			usleep(1000);
			i++;
		}
		pthread_mutex_lock(&philos->data->var_end);
	}
	pthread_mutex_unlock(&philos->data->var_end);
	return (NULL);
}
