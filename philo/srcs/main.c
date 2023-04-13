/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviovi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 11:12:21 by vviovi            #+#    #+#             */
/*   Updated: 2023/04/07 15:59:48 by vviovi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

static void	solo_thread(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork1);
	print_act(philo, 3);
	usleep(philo->data->time_to_die * 1000);
	pthread_mutex_unlock(&philo->fork1);
}

void	*launch_routine(void *h)
{
	t_philo	*philo;

	philo = (t_philo *) h;
	print_act(philo, 0);
	if (philo->nb_philo > 1 && philo->num_philo % 2 != 0)
		usleep(9000);
	if (philo->nb_philo == 1)
		solo_thread(philo);
	pthread_mutex_lock(&philo->data->var_end);
	while (!philo->data->is_the_end && philo->data->nb_philo != 1)
	{
		pthread_mutex_unlock(&philo->data->var_end);
		do_eat(philo);
		do_sleep(philo);
		print_act(philo, 0);
		pthread_mutex_lock(&philo->data->var_end);
	}
	pthread_mutex_unlock(&philo->data->var_end);
	return (NULL);
}

void	launch_threads(t_philo *philos, t_data data)
{
	int			i;
	long		time;
	pthread_t	tid;

	i = 0;
	time = get_time();
	while (i < data.nb_philo)
	{
		philos[i].start = time;
		philos[i].last_eat = time;
		pthread_create(&philos[i].tid, NULL, launch_routine, &philos[i]);
		i++;
	}
	pthread_create(&tid, NULL, check_death, philos);
	i = 0;
	while (i < data.nb_philo)
	{
		pthread_join(philos[i].tid, NULL);
		i++;
	}
	pthread_join(tid, NULL);
}

static void	clean_philo(t_philo *philos, t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->var_end);
	pthread_mutex_destroy(&data->var_end_eat);
	pthread_mutex_destroy(&data->printable);
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&philos[i].fork1);
		i++;
	}
	free(philos);
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philos;

	if (argc < 5 || argc > 6)
	{
		printf("Error : number of argument incorrect\n");
		return (1);
	}
	if (!parsing(argc, argv, &data))
	{
		printf("Error : argument incorrect\n");
		return (1);
	}
	philos = build_philo(&data);
	launch_threads(philos, data);
	clean_philo(philos, &data);
	return (0);
}
