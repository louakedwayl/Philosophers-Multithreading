/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:58:49 by wlouaked          #+#    #+#             */
/*   Updated: 2025/01/11 18:56:37 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hdr/philosopher.h"

int	alloc_philo(t_philosopher **philo, t_table table)
{
	*philo = malloc (sizeof(t_philosopher) * table.nbr_philosophers);
	if (!(*philo))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	destroy_id_mutex(t_philosopher *philo, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		pthread_mutex_destroy(&philo[j].id_mutex);
		j++;
	}
}

int	handler_init_philo(t_philosopher **philo, t_table *table)
{
	if (alloc_philo(philo, *table))
	{
		pthread_mutex_destroy(&(table->megaphone));
		destroy_and_free_forks(table);
		return (EXIT_FAILURE);
	}
	if (create_philo(*philo, table))
	{
		pthread_mutex_destroy(&(table->megaphone));
		destroy_and_free_forks(table);
		free (philo);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	init_philo_one(t_philosopher *philo, t_table *table, int i)
{
	if (pthread_mutex_init(&(philo->id_mutex), NULL) != 0)
		return (EXIT_FAILURE);
	philo->id = i;
	philo->left_forks = &table->forks[i];
	philo->meals_eaten = 0;
	philo->last_meal_time = 0;
	philo->nbr_philosophers = table->nbr_philosophers;
	philo->time_to_die = table->time_to_die;
	philo->time_to_eat = table->time_to_eat;
	philo->time_to_sleep = table->time_to_sleep;
	philo->nbr_of_bites = table->nbr_of_bites;
	philo->table = table;
	philo->satisfy = 0;
	return (EXIT_SUCCESS);
}
