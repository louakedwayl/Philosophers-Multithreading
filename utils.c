/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:27:11 by wayl              #+#    #+#             */
/*   Updated: 2025/01/09 17:22:56 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hdr/philosopher.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
	{
		return (EXIT_FAILURE);
	}
	else
	{
		return (EXIT_SUCCESS);
	}
}

void	ft_init_atoi(int *i, int *val, int *is_neg)
{
	*i = 0;
	*is_neg = 1;
	*val = 0;
}

int	ft_atoi(const char *str)
{
	int	i;
	int	val;
	int	is_neg;

	ft_init_atoi(&i, &val, &is_neg);
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-')
	{
		is_neg = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (-1);
		if (val > (2147483647 - (str[i] - '0')) / 10)
			return (-1);
		val = val * 10 + (str[i] - '0');
		i++;
	}
	return (val * is_neg);
}

void	release_ressource(t_table *table, t_philosopher **philo)
{
	pthread_mutex_destroy(&(table->megaphone));
	destroy_and_free_forks(table);
	free (*philo);
}
