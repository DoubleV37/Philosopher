/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviovi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:11:41 by vviovi            #+#    #+#             */
/*   Updated: 2023/04/10 16:26:44 by vviovi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher_bonus.h"

static void	eat_supervisor(t_data *data)
{
	pthread_t	supervisor;

	data->eat_supervisor = fork();
	if (data->eat_supervisor == 0)
	{
		pthread_create(&supervisor, NULL, check_eat, data);
		pthread_detach(supervisor);
	}
}

static int	launch_philo(t_data *data, t_philo *philos)
{
	int			i;
	long		time;

	time = get_time();
	i = 0;
	while (i < philos->data->nb_philo)
	{
		philos[i].start = time;
		philos[i].last_eat = time;
		philos[i].pid = fork();
		if (philos[i].pid == 0)
		{
			routine(&philos[i]);
			return (1);
		}
		else if (philos[i].pid < 0)
			return (0);
		i++;
	}
	if (data->nb_eat > 0)
		eat_supervisor(data);
	sem_wait(data->is_the_end);
	clean(data, philos);
	return (1);
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
		return (1);
	philos = build_philo(&data);
	if (!launch_philo(&data, philos))
		return (1);
	return (0);
}
