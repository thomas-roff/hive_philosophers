/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 13:10:20 by thblack-          #+#    #+#             */
/*   Updated: 2025/12/14 12:34:50 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "messages.h"

static void	vars_init(t_data *v);

bool	parse_args(t_data *v, char **argv)
{
	vars_init(v);
	if (!ft_atoui(&v->n, argv[1])
		|| !ft_atoui(&v->die, argv[2])
		|| !ft_atoui(&v->eat, argv[3])
		|| !ft_atoui(&v->sleep, argv[4]))
	{
		printf("%s\n", MSG_VALID);
		printf("%s", MSG_PROMPT);
		return (false);
	}
	if (argv[5])
	{
		if (!ft_atoui(&v->fed, argv[5]))
		{
			printf("%s\n", MSG_VALID);
			printf("%s", MSG_PROMPT);
			return (false);
		}
	}
	if (pthread_mutex_init(&v->m, NULL))
		ft_error("pthread_mutex_init() fail", NULL);
	return (true);
}

static void	vars_init(t_data *v)
{
	v->n = 0;
	v->die = 0;
	v->eat = 0;
	v->sleep = 0;
	v->fed = 0;
	v->i = 1;
	v->f = NULL;
	v->end = false;
	v->t = NULL;
}
