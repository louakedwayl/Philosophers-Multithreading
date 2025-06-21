/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 21:06:50 by wlouaked          #+#    #+#             */
/*   Updated: 2025/01/11 19:50:49 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hdr/philosopher.h"

static int	ft_handler_create(t_philosopher *philo, int i)
{
	if (i % 2 == 00)
	{
		if (pthread_create(&philo[i].thread, NULL,
				philosopher_routine_odd, &philo[i]) != 0)
		{
			destroy_id_mutex(philo, i);
			return (EXIT_FAILURE);
		}
	}
	if (i % 2 == 1)
	{
		if (pthread_create(&philo[i].thread, NULL,
				philosopher_routine_even, &philo[i]) != 0)
		{
			destroy_id_mutex(philo, i);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

int	create_philo(t_philosopher *philo, t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nbr_philosophers)
	{
		if (init_philo(&philo[i], table, i))
		{
			destroy_id_mutex(philo, i);
			return (EXIT_FAILURE);
		}
		if (ft_handler_create(philo, i))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	init_philo(t_philosopher *philo, t_table *table, int i)
{
	if (pthread_mutex_init(&(philo->id_mutex), NULL) != 0)
		return (EXIT_FAILURE);
	if (pthread_mutex_init(&(philo->meal_mutex), NULL) != 0)
		return (EXIT_FAILURE);
	if (pthread_mutex_init(&(philo->meal_time_mutex), NULL) != 0)
		return (EXIT_FAILURE);
	if (pthread_mutex_init(&(philo->satisfy_m), NULL) != 0)
		return (EXIT_FAILURE);
	philo->id = i + 1;
	philo->left_forks = &table->forks[i];
	philo->last_meal_time = 0;
	philo->right_forks = &table->forks[(i + 1) % table->nbr_philosophers];
	philo->meals_eaten = 0;
	philo->nbr_philosophers = table->nbr_philosophers;
	philo->time_to_die = table->time_to_die;
	philo->time_to_eat = table->time_to_eat;
	philo->time_to_sleep = table->time_to_sleep;
	philo->nbr_of_bites = table->nbr_of_bites;
	philo->table = table;
	philo->satisfy = 0;
	return (EXIT_SUCCESS);
}
