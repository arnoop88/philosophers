/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apodader <apodader@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 17:03:51 by apodader          #+#    #+#             */
/*   Updated: 2023/11/05 12:40:51 by apodader         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_usleep(long long time)
{
	time += get_time();
	while (get_time() <= time)
		usleep(200);
}

void	pick_forks(t_philos *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		monitoring(RIGHT, philo);
		pthread_mutex_lock(philo->left_fork);
		monitoring(LEFT, philo);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		monitoring(LEFT, philo);
		pthread_mutex_lock(philo->right_fork);
		monitoring(RIGHT, philo);
	}
}

void	drop_forks(t_philos *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
}

void	eat(t_philos *philo)
{
	pick_forks(philo);
	pthread_mutex_lock(&philo->data->mutex);
	philo->last_meal = get_time();
	philo->n_meals++;
	pthread_mutex_unlock(&philo->data->mutex);
	monitoring(EAT, philo);
	ft_usleep(philo->data->t_eat);
	drop_forks(philo);
}

void	*routine(void *philos)
{
	t_philos	*philo;

	philo = (t_philos *)philos;
	if (philo->data->n_philos == 1)
	{
		monitoring(LEFT, philo);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->t_eat * 0.1);
	while (1)
	{
		pthread_mutex_lock(&philo->data->mutex);
		if (philo->data->end == 1)
		{
			pthread_mutex_unlock(&philo->data->mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->data->mutex);
		eat(philo);
		monitoring(SLEEP, philo);
		ft_usleep(philo->data->t_sleep);
		monitoring(THINK, philo);
		ft_usleep(philo->data->t_eat * 0.01);
	}
}
