/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviovi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 11:12:37 by vviovi            #+#    #+#             */
/*   Updated: 2023/04/06 16:14:20 by vviovi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_data
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_eat;
	int				is_the_end;
	int				is_the_end_eat;
	pthread_mutex_t	var_end;
	pthread_mutex_t	var_end_eat;
	pthread_mutex_t	printable;
}					t_data;

typedef struct s_philo
{
	int				num_philo;
	pthread_t		tid;
	pthread_mutex_t	fork1;
	pthread_mutex_t	*fork2;
	pthread_mutex_t	var_eat;
	long			start;
	long			last_eat;
	int				nb_eat;
	int				nb_philo;
	t_data			*data;
}					t_philo;

//================utils.c==================
int		ft_atoi(const char *nptr);
long	get_time(void);
void	print_act(t_philo *philo, int act);
int		wait_usleep(t_philo *philo, int time);
int		is_the_end(t_philo *philo);

//================routine.c================
void	do_eat(t_philo *philo);
void	do_sleep(t_philo *philo);
void	*check_death(void *h);

//================supervisor.c=============
void	*check_death(void *h);

//================parsing.c================
int		parsing(int argc, char **argv, t_data *data);
t_philo	*build_philo(t_data *data);

#endif
