/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apodader <apodader@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 16:10:20 by apodader          #+#    #+#             */
/*   Updated: 2023/09/28 16:10:20 by apodader         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>
# include <inttypes.h>
# define FULL "all philos are full 👌\n"
# define DEAD "is dead 💀\n"
# define EAT "is eating 🍝\n"
# define THINK "is thinking 🤔\n"
# define SLEEP "is sleeping 😴\n"
# define LEFT "has taken left fork 🍴\n"
# define RIGHT "has taken right fork 🍴\n"

typedef struct s_data
{
	int				n_philos;
	int				t_eat;
	int				t_die;
	int				t_sleep;
	int				n_meals;
	int				end;
	int				full_philos;
	pthread_mutex_t	mutex;
}	t_data;

typedef struct s_philos
{
	int				id;
	int				n_meals;
	int				full;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		t_id;
	int64_t			last_meal;
	int64_t			start_t;
	t_data			*data;
}	t_philos;

int				args_checker(char **argv, t_data *data);
pthread_mutex_t	*init_forks(t_data *data);
t_philos		*init_philos(t_data *data, pthread_mutex_t *forks);
int64_t			get_time(void);
void			*routine(void *philos);
int				threads(t_data *data, t_philos *philos);
void			monitoring(char *str, t_philos *philos);
void			destroy(t_data *data, pthread_mutex_t *forks, t_philos *philos);

#endif
