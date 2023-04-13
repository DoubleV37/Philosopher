/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviovi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 11:26:46 by vviovi            #+#    #+#             */
/*   Updated: 2023/04/10 10:11:36 by vviovi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher_bonus.h"

static int	get_arg(int argc, char **argv, t_data *data)
{
	data->nb_philo = ft_atoi(argv[1]);
	if (is_digit(argv[1]) == 0 || is_digit(argv[2]) == 0
		|| is_digit(argv[3]) == 0 || is_digit(argv[4]) == 0
		|| (argc == 6 && is_digit(argv[5]) == 0))
	{
		printf("Error: arguments must be integers\n");
		return (0);
	}
	if (data->nb_philo < 1)
	{
		printf("Error number of philosopher incorrect\n");
		return (0);
	}
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->nb_eat = ft_atoi(argv[5]);
	else
		data->nb_eat = -5;
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
	if (data->time_to_sleep <= 0)
		return (0);
	data->forks = sem_open("fork", O_CREAT | O_EXCL, 0664, data->nb_philo);
	sem_unlink("fork");
	data->eat = sem_open("eat", O_CREAT | O_EXCL, 0664, 0);
	sem_unlink("eat");
	data->waitfork = sem_open("waitfork", O_CREAT | O_EXCL, 0664, 1);
	sem_unlink("waitfork");
	data->printable = sem_open("printable", O_CREAT | O_EXCL, 0664, 1);
	sem_unlink("printable");
	data->is_the_end = sem_open("end", O_CREAT | O_EXCL, 0664, 0);
	sem_unlink("end");
	return (1);
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
		philos[i].num_philo = i + 1;
		philos[i].nb_eat = data->nb_eat;
		philos[i].nb_philo = data->nb_philo;
		i++;
	}
	return (philos);
}
