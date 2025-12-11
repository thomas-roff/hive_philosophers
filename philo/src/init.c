/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 13:10:20 by thblack-          #+#    #+#             */
/*   Updated: 2025/12/11 13:11:59 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "messages.h"

bool	valid_input(char **argv)
{
	int	i;

	while (*++argv)
	{
		i = 0;
		while (argv[0][i])
		{
			if (!ft_isdigit(argv[0][i++]))
			{
				printf("%s\n", MSG_VALID);
				printf("%s", MSG_PROMPT);
				return (false);
			}
		}
	}
	return (true);
}

static void	philo_init(t_vars *p)
{
	p->n = 0;
	p->die = 0;
	p->eat = 0;
	p->sleep = 0;
	p->fed = 0;
	p->i = 1;
	p->t = NULL;
	p->f = NULL;
	pthread_mutex_init(&p->m, NULL);
}

bool	parse_args(t_vars *p, char **argv)
{
	philo_init(p);
	if (!ft_atoui(&p->n, argv[1])
			|| !ft_atoui(&p->die, argv[2])
			|| !ft_atoui(&p->eat, argv[3])
			|| !ft_atoui(&p->sleep, argv[4]))
	{
		printf("%s\n", MSG_VALID);
		printf("%s", MSG_PROMPT);
		return (false);
	}
	if (argv[5])
	{
		if (!ft_atoui(&p->fed, argv[5]))
		{
			printf("%s\n", MSG_VALID);
			printf("%s", MSG_PROMPT);
			return (false);
		}
	}
	return (true);
}
