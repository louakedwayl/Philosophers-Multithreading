/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:23:34 by wayl              #+#    #+#             */
/*   Updated: 2025/01/11 20:25:57 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hdr/philosopher.h"

bool	is_philosopher_dead(t_philosopher *philo)
{
	bool	retval;

	pthread_mutex_lock(&(philo->table->death_m));
	retval = philo->table->death;
	pthread_mutex_unlock(&(philo->table->death_m));
	return (retval);
}

int	ft_death(t_philosopher *philo, t_table *table)
{
	pthread_mutex_lock(&(philo->meal_time_mutex));
	table->end = time_elapsed_for_start(table->start);
	if (table->end - philo->last_meal_time >= table->time_to_die - 110)
	{
		pthread_mutex_unlock(&(philo->meal_time_mutex));
		pthread_mutex_lock(&(table->death_m));
		table->death = true;
		pthread_mutex_unlock(&(table->death_m));
		pthread_mutex_lock(&(philo->id_mutex));
		pthread_mutex_lock(&(table->megaphone));
		printf ("%ld ", time_elapsed_for_start(philo->table->start) + 110);
		printf ("%d died\n", philo->id);
		pthread_mutex_unlock(&(philo->id_mutex));
		pthread_mutex_unlock(&(table->megaphone));
		return (EXIT_FAILURE);
	}
	pthread_mutex_unlock(&(philo->meal_time_mutex));
	return (EXIT_SUCCESS);
}

int	ft_death_meal(t_philosopher *philo, t_table *table)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i <= table->nbr_philosophers)
	{
		pthread_mutex_lock((&philo[i].satisfy_m));
		if (philo[i].satisfy)
			count++;
		pthread_mutex_unlock((&philo[i].satisfy_m));
		i++;
	}
	if (count == table->nbr_philosophers)
	{
		pthread_mutex_lock(&(table->death_m));
		table->death = true;
		pthread_mutex_unlock(&(table->death_m));
		return (EXIT_FAILURE);
	}
	else
		return (EXIT_SUCCESS);
}

int	check_death(t_philosopher *philo, t_table *table)
{
	int	i;

	i = 0;
	while (1)
	{
		if (i >= table->nbr_philosophers)
			i = 0;
		if (ft_death(&philo[i], table))
			break ;
		if (table->nbr_of_bites != -2)
		{
			if (ft_death_meal(philo, table))
				break ;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
