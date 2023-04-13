/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviovi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 13:53:41 by vviovi            #+#    #+#             */
/*   Updated: 2023/04/10 16:21:38 by vviovi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher_bonus.h"

void	do_eat(t_philo *philo)
{
	sem_wait(philo->data->waitfork);
	sem_wait(philo->data->forks);
	print_act(philo, 3);
	sem_wait(philo->data->forks);
	print_act(philo, 3);
	sem_post(philo->data->waitfork);
	print_act(philo, 1);
	usleep(philo->data->time_to_eat * 1000);
	philo->last_eat = get_time();
	if (philo->nb_eat > 0)
		philo->nb_eat -= 1;
	if (philo->nb_eat == 0)
	{
		sem_post(philo->data->eat);
	}
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}

void	do_sleep(t_philo *philo)
{
	print_act(philo, 2);
	usleep(philo->data->time_to_sleep * 1000);
}

void	*check_death(void *h)
{
	t_philo	*philo;

	philo = (t_philo *)h;
	while (1)
	{
		if (get_time() - philo->last_eat > philo->data->time_to_die)
		{
			sem_wait(philo->data->printable);
			printf("%li %i died\n", get_time() - philo->start, philo->num_philo);
			sem_post(philo->data->is_the_end);
			exit(0);
		}
	}
}

void	routine(t_philo *philo)
{
	pthread_t	death;

	pthread_create(&death, NULL, check_death, philo);
	pthread_detach(death);
	while (1)
	{
		print_act(philo, 0);
		do_eat(philo);
		do_sleep(philo);
	}
}

void	*check_eat(void *d)
{
	t_data	*data;
	int		i;

	data = (t_data *)d;
	i = 0;
	while (i < data->nb_philo)
	{
		sem_wait(data->eat);
		i++;
	}
	sem_post(data->is_the_end);
	return (NULL);
}
