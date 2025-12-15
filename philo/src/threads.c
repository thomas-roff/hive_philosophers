/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 12:10:04 by thblack-          #+#    #+#             */
/*   Updated: 2025/12/14 12:30:24 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	threads_and_forks_init(t_data *v)
{
	uint32_t	i;

	v->t = malloc(sizeof(pthread_t) * v->n);
	v->f = malloc(sizeof(atomic_bool) * v->n);
	if (!v->t || !v->f)
	{
		ft_error("malloc() fail", v);
		philo_main_exit(v);
		return (false);
	}
	i = 0;
	while (i < v->n)
		v->f[i++] = false;
	return (true);
}

bool	threads_run(t_data *v)
{
	uint32_t	i;

	i = 0;
	while (i < v->n)
	{
		if (pthread_create(&v->t[i], NULL, philosophise, v))
		{
			ft_error("pthread_create() fail", v);
			return (false);
		}
		i++;
	}
	return (true);
}

bool	threads_join(t_data *v)
{
	uint32_t	i;

	i = 0;
	while (i < v->n)
	{
		if (pthread_join(v->t[i], NULL))
		{
			ft_error("pthread_join() fail", v);
			return (false);
		}
		i++;
	}
	return (true);
}
