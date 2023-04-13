/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_bonus.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviovi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 11:12:37 by vviovi            #+#    #+#             */
/*   Updated: 2023/04/10 16:26:35 by vviovi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_BONUS_H
# define PHILOSOPHER_BONUS_H

# include <pthread.h>
# include <fcntl.h>
# include <semaphore.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <signal.h>

typedef struct s_data
{
	int		nb_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		nb_eat;
	pid_t	eat_supervisor;
	sem_t	*is_the_end;
	sem_t	*forks;
	sem_t	*eat;
	sem_t	*waitfork;
	sem_t	*printable;
}			t_data;

typedef struct s_philo
{
	int		num_philo;
	pid_t	pid;
	long	start;
	long	last_eat;
	int		nb_eat;
	int		nb_philo;
	t_data	*data;
}			t_philo;

//================utils.c==================
int		ft_atoi(const char *nptr);
long	get_time(void);
void	print_act(t_philo *philo, int act);
void	clean(t_data *data, t_philo *philos);
int		is_digit(char *str);

//================routine.c================
void	do_eat(t_philo *philo);
void	do_sleep(t_philo *philo);
void	*check_death(void *h);
void	routine(t_philo *philo);
void	*check_eat(void *d);

//================parsing.c================
int		parsing(int argc, char **argv, t_data *data);
t_philo	*build_philo(t_data *data);

#endif
