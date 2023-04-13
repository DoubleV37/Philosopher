/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviovi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 11:25:02 by vviovi            #+#    #+#             */
/*   Updated: 2023/04/07 14:11:39 by vviovi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

static void	take_a_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork1);
	print_act(philo, 3);
	pthread_mutex_lock(philo->fork2);
	print_act(philo, 3);
}

void	do_eat(t_philo *philo)
{
	take_a_fork(philo);
	print_act(philo, 1);
	if (wait_usleep(philo, philo->data->time_to_eat * 1000))
	{
		pthread_mutex_unlock(&philo->fork1);
		pthread_mutex_unlock(philo->fork2);
		return ;
	}
	pthread_mutex_unlock(&philo->fork1);
	pthread_mutex_unlock(philo->fork2);
	pthread_mutex_lock(&philo->var_eat);
	philo->last_eat = get_time();
	pthread_mutex_unlock(&philo->var_eat);
	if (philo->nb_eat > -1)
		philo->nb_eat -= 1;
	if (philo->nb_eat == 0)
	{
		pthread_mutex_lock(&philo->data->var_end_eat);
		philo->data->is_the_end_eat += 1;
		pthread_mutex_unlock(&philo->data->var_end_eat);
	}
}

void	do_sleep(t_philo *philo)
{
	print_act(philo, 2);
	wait_usleep(philo, philo->data->time_to_sleep * 1000);
}
