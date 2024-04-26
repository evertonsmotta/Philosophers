/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evdos-sa <evdos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 18:20:34 by evdos-sa          #+#    #+#             */
/*   Updated: 2023/09/18 18:51:49 by evdos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	init_forks(t_data *data)
{
	int		i;
	t_philo	*philos;

	philos = data->philos;
	i = -1;
	while (++i < data->nb_philos)
		pthread_mutex_init(&data->forks[i], NULL);
	i = 0;
	philos[0].left_f = &data->forks[0];
	philos[0].right_f = &data->forks[data->nb_philos - 1];
	while (++i < data->nb_philos)
	{
		philos[i].left_f = &data->forks[i];
		philos[i].right_f = &data->forks[i - 1];
	}
	return (0);
}

int	init_philos(t_data *data)
{
	t_philo	*philos;
	int		i;

	i = -1;
	philos = data->philos;
	while (++i < data->nb_philos)
	{
		philos[i].data = data;
		philos[i].id = i + 1;
		philos[i].nb_meals_had = 0;
		philos[i].state = IDLE;
		pthread_mutex_init(&philos[i].mut_state, NULL);
		pthread_mutex_init(&philos[i].mut_nb_meals_had, NULL);
		pthread_mutex_init(&philos[i].mut_last_eat_time, NULL);
		update_last_meal_time(&philos[i]);
	}
	return (0);
}

int	malloc_data_pointers(t_data *data)
{
	data->philo_ths = malloc(sizeof(pthread_t) * data->nb_philos);
	if (!data->philo_ths)
		return (EXIT_FAILURE);
	data->forks = malloc(sizeof(t_philo) * data->nb_philos);
	if (!data->forks)
	{
		free(data->philo_ths);
		return (EXIT_FAILURE);
	}
	data->philos = malloc(sizeof(t_philo) * data->nb_philos);
	if (!data->philos)
	{
		free(data->philo_ths);
		free(data->forks);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	init_data(t_data *data, int ac, char **av)
{
	data->nb_philos = ft_atoi(av[1]);
	data->nb_meals = -1;
	if (ac == 6)
		data->nb_meals = ft_atoi(av[5]);
	data->nb_full_p = 0;
	data->keep_iterating = true;
	data->die_time = ft_atoi(av[2]);
	data->eat_time = ft_atoi(av[3]);
	data->sleep_time = ft_atoi(av[4]);
	pthread_mutex_init(&data->mut_nb_philos, NULL);
	pthread_mutex_init(&data->mut_die_t, NULL);
	pthread_mutex_init(&data->mut_eat_t, NULL);
	pthread_mutex_init(&data->mut_sleep_t, NULL);
	pthread_mutex_init(&data->mut_print, NULL);
	pthread_mutex_init(&data->mut_keep_iter, NULL);
	pthread_mutex_init(&data->mut_start_time, NULL);
	malloc_data_pointers(data);
	return (EXIT_SUCCESS);
}

int	philosophers(int argc, char **argv)
{
	t_data	data;

	if (init_data(&data, argc, argv) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	init_philos(&data);
	init_forks(&data);
	run_threads(&data);
	join_threads(&data);
	free_data(&data);
	return (0);
}
