/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 12:16:11 by thblack-          #+#    #+#             */
/*   Updated: 2025/12/14 12:39:36 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	time_fetch(uint64_t *time)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (ft_error("gettimeofday() fail", NULL));
	*time = (tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / (uint64_t)1000);
	return (SUCCESS);
}
