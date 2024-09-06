/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apodader <apodader@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 15:51:14 by apodader          #+#    #+#             */
/*   Updated: 2023/09/28 15:51:14 by apodader         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	destroy(t_data *data, pthread_mutex_t *forks, t_philos *philos)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->mutex);
	if (forks)
	{
		while (i < data->n_philos)
		{
			pthread_mutex_destroy(&forks[i]);
			i++;
		}
		free(forks);
	}
	if (philos)
		free(philos);
}

void	monitoring(char *str, t_philos *philos)
{
	int64_t	time;

	pthread_mutex_lock(&philos->data->mutex);
	time = get_time() - philos->start_t;
	if (str[0] == 'a')
		printf("%lld %s", (long long)time, str);
	else if (philos->data->end != 1)
		printf("%lld %d %s", (long long)time, philos->id, str);
	pthread_mutex_unlock(&philos->data->mutex);
}

int	main(int argc, char **argv)
{
	t_data			data;
	pthread_mutex_t	*forks;
	t_philos		*philos;

	if (argc < 5 || argc > 6 || args_checker(argv, &data))
	{
		printf("Invalid arguments\n");
		return (1);
	}
	forks = init_forks(&data);
	if (!forks)
		return (1);
	philos = init_philos(&data, forks);
	if (!philos)
		return (1);
	threads(&data, philos);
	destroy(&data, forks, philos);
	return (0);
}
