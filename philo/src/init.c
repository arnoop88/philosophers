/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apodader <apodader@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 14:19:55 by apodader          #+#    #+#             */
/*   Updated: 2023/10/02 14:19:55 by apodader         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int64_t	get_time(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec * 1000) + (now.tv_usec / 1000));
}

pthread_mutex_t	*init_forks(t_data *data)
{
	pthread_mutex_t	*forks;
	int				i;

	i = 0;
	forks = malloc(data->n_philos * sizeof(pthread_mutex_t));
	if (!forks)
	{
		destroy(data, NULL, NULL);
		return (NULL);
	}
	while (i < data->n_philos)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	return (forks);
}

t_philos	*init_philos(t_data *data, pthread_mutex_t *forks)
{
	t_philos	*philo;
	int			i;

	i = 0;
	philo = malloc(data->n_philos * sizeof(t_philos));
	if (!philo)
	{
		destroy(data, forks, NULL);
		return (NULL);
	}
	while (i < data->n_philos)
	{
		philo[i].id = i + 1;
		philo[i].n_meals = 0;
		philo[i].full = 0;
		philo[i].left_fork = &forks[i];
		philo[i].right_fork = &forks[(i + 1) % data->n_philos];
		philo[i].last_meal = get_time();
		philo[i].data = data;
		i++;
	}
	return (philo);
}
