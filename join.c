/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 21:37:37 by wlouaked          #+#    #+#             */
/*   Updated: 2025/01/09 17:55:00 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hdr/philosopher.h"

int	handler_thread_join(t_philosopher *philo)
{
	int	i;

	i = 0;
	while (i < philo->nbr_philosophers)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	return (EXIT_SUCCESS);
}
