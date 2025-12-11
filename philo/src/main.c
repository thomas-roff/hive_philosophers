/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 17:58:39 by thblack-          #+#    #+#             */
/*   Updated: 2025/12/11 14:18:51 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "messages.h"
#include <signal.h>

void	clean_up(t_vars *v)
{
	if (v->t)
		free(v->t);
	if (v->f)
		free(v->f);
}

bool	threads_init(t_vars *v)
{
	v->t = malloc(sizeof(pthread_t) * v->n);
	v->f = malloc(sizeof(sig_atomic_t) * v->n);
	if (!v->t || !v->f)
	{
		clean_up(v);
		return (false);
	}
	return (true);
}

int	num_fetch(t_philo *p, t_vars *v)
{
	if (pthread_mutex_lock(&v->m))
		return (FAIL);
	p->x = v->i++;
	if (pthread_mutex_unlock(&v->m))
		return (FAIL);
	return (SUCCESS);
}

void	*philosophise(void *data)
{
	t_vars			*v;
	t_philo			p;
	struct timeval	time;

	v = data;
	if (!num_fetch(&p, v))
		return (0);
	if (gettimeofday(&time, NULL) == -1)
		return (0);
	printf("%ld.%u %u is here\n", time.tv_sec, time.tv_usec, p.x);
	return (0);
}

bool	threads_run(t_vars *v)
{
	uint32_t	i;

	i = 0;
	while (i < v->n)
	{
		if (pthread_create(&v->t[i], NULL, philosophise, v))
		{
			printf("Error: thread failed\n");
			clean_up(v);
			return (false);
		}
		i++;
	}
	return (true);
}

bool	threads_join(t_vars *v)
{
	uint32_t	i;

	i = 0;
	while (i < v->n)
	{
		if (pthread_join(v->t[i], NULL))
		{
			printf("Error: thread join failed\n");
			clean_up(v);
			return (false);
		}
		i++;
	}
	return (true);
}

static bool	philo(char **argv)
{
	t_vars		p;

	if (!parse_args(&p, argv) || p.n == 0 || (argv[5] && p.fed == 0))
		return (true);
	if (!threads_init(&p) || !threads_run(&p) || !threads_join(&p))
		return (false);
	clean_up(&p);
	return (true);
}

int	main(int argc, char **argv)
{
	if (argc < 5 || !valid_input(argv))
	{
		if (argc < 5)
			printf("%s\n", MSG_ARGS);
		printf("%s", MSG_PROMPT);
		return (EXIT_SUCCESS);
	}
	if (!philo(argv))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
