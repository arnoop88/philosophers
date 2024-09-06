/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apodader <apodader@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 23:40:44 by apodader          #+#    #+#             */
/*   Updated: 2023/10/03 23:40:44 by apodader         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	is_dead(t_data *data, t_philos *philo)
{
	if (data->n_meals > 0 && philo->full == 0
		&& philo->n_meals == data->n_meals)
	{
		data->full_philos++;
		philo->full = 1;
	}
	if (get_time() - philo->last_meal >= data->t_die)
	{
		pthread_mutex_unlock(&data->mutex);
		monitoring(DEAD, philo);
		pthread_mutex_lock(&data->mutex);
		data->end = 1;
		pthread_mutex_unlock(&data->mutex);
		return (1);
	}
	return (0);
}

void	supervisor(t_data *data, t_philos *philos)
{
	int	i;

	while (1)
	{
		i = 0;
		pthread_mutex_lock(&data->mutex);
		while (i < data->n_philos)
		{
			if (is_dead(data, &philos[i]))
				return ;
			i++;
		}
		if (data->full_philos >= data->n_philos)
		{
			data->end = 1;
			pthread_mutex_unlock(&data->mutex);
			monitoring(FULL, &philos[0]);
			return ;
		}
		pthread_mutex_unlock(&data->mutex);
		usleep(50);
	}
}

int	threads(t_data *data, t_philos *philos)
{
	int	i;

	i = -1;
	while (++i < data->n_philos)
	{
		philos[i].start_t = get_time();
		pthread_create(&philos[i].t_id, NULL,
			routine, (void *)&philos[i]);
	}
	supervisor(data, philos);
	while (i-- > 0)
		pthread_join(philos[i].t_id, NULL);
	return (0);
}
