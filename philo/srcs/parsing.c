/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviovi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 11:26:46 by vviovi            #+#    #+#             */
/*   Updated: 2023/04/06 15:32:49 by vviovi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

static int	is_digit(char *str)
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

static int	get_arg(int argc, char **argv, t_data *data)
{
	if (is_digit(argv[1]) == 0 || is_digit(argv[2]) == 0
		|| is_digit(argv[3]) == 0 || is_digit(argv[4]) == 0
		|| (argc == 6 && is_digit(argv[5]) == 0))
	{
		printf("Error : argument incorrect\n");
		return (0);
	}
	data->nb_philo = ft_atoi(argv[1]);
	if (data->nb_philo < 1)
	{
		printf("Error number of philosopher incorrect\n");
		return (0);
	}
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	return (1);
}

int	parsing(int argc, char **argv, t_data *data)
{
	if (!get_arg(argc, argv, data))
		return (0);
	if (data->time_to_die <= 0)
		return (0);
	if (data->time_to_eat <= 0)
		return (0);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (data->time_to_sleep <= 0)
		return (0);
	if (argc == 6)
		data->nb_eat = ft_atoi(argv[5]);
	else
		data->nb_eat = -5;
	data->is_the_end = 0;
	data->is_the_end_eat = 0;
	pthread_mutex_init(&data->var_end, NULL);
	pthread_mutex_init(&data->var_end_eat, NULL);
	pthread_mutex_init(&data->printable, NULL);
	return (1);
}

static void	assign_second_fork(t_philo *philos)
{
	int	i;

	if (philos->data->nb_philo == 1)
	{
		philos->fork2 = NULL;
		return ;
	}
	philos[0].fork2 = &philos[philos->data->nb_philo - 1].fork1;
	i = 1;
	while (i < philos->data->nb_philo)
	{
		philos[i].fork2 = &philos[i - 1].fork1;
		i++;
	}
}

t_philo	*build_philo(t_data *data)
{
	int		i;
	t_philo	*philos;

	i = 0;
	philos = malloc(sizeof(t_philo) * data->nb_philo);
	while (i != data->nb_philo)
	{
		philos[i].data = data;
		pthread_mutex_init(&philos[i].fork1, NULL);
		pthread_mutex_init(&philos[i].var_eat, NULL);
		philos[i].num_philo = i + 1;
		philos[i].nb_eat = data->nb_eat;
		philos[i].nb_philo = data->nb_philo;
		i++;
	}
	assign_second_fork(philos);
	return (philos);
}
