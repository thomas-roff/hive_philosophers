/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_things.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 12:15:38 by thblack-          #+#    #+#             */
/*   Updated: 2025/12/14 12:22:20 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	what_you_doing(char *s, t_philo *p, t_data *v);
static int	take_cutlery(t_philo *p, t_data *v);
static int	return_cutlery(t_philo *p, t_data *v);

int	go_eat(t_philo *p, t_data *v)
{
	int				flag;

	flag = take_cutlery(p, v);
	if (flag != SUCCESS)
		return (flag);
	if (!what_you_doing("eating", p, v))
		return (ERROR);
	usleep(v->eat);
	if (return_cutlery(p, v) != SUCCESS)
		return (ERROR);
	if (v->end == true)
		return (FAIL);
	if (!what_you_doing("sleeping", p, v))
		return (ERROR);
	usleep(v->sleep);
	if (v->end == true)
		return (FAIL);
	if (!what_you_doing("thinking", p, v))
		return (ERROR);
	return (SUCCESS);
}

static int	what_you_doing(char *s, t_philo *p, t_data *v)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (FAIL);
	if (s[1] == SLEEPING)
	{
		p->ate_s = time.tv_sec;
		p->ate_u = time.tv_usec;
		p->meals++;
	}
	if (v->end == false)
	{
		if (pthread_mutex_lock(&v->m))
			return (FAIL);
		printf("%ld%06u %u is %s\n", time.tv_sec, time.tv_usec, p->x, s);
		if (pthread_mutex_unlock(&v->m))
			return (FAIL);
	}
	return (SUCCESS);
}

static int	take_cutlery(t_philo *p, t_data *v)
{
	struct timeval	t;
	int				flag;

	if (gettimeofday(&t, NULL) == -1)
		return (ERROR);
	if (*p->fork_l == false && *p->fork_r == false && v->end == false)
	{
		if (pthread_mutex_lock(&p->lock_l))
			return (ERROR);
		*p->fork_l = true;
		printf("%ld%06u %u has taken a fork\n", t.tv_sec, t.tv_usec, p->x);
		if (pthread_mutex_unlock(&p->lock_l))
			return (ERROR);
		if (pthread_mutex_lock(&p->lock_r))
			return (ERROR);
		*p->fork_r = true;
		printf("%ld%06u %u has taken a fork\n", t.tv_sec, t.tv_usec, p->x);
		if (pthread_mutex_unlock(&p->lock_r))
			return (ERROR);
		flag = SUCCESS;
	}
	else
		flag = FAIL;
	return (flag);
}

static int	return_cutlery(t_philo *p, t_data *v)
{
	int	flag;

	(void)v;
	if (*p->fork_l == true && *p->fork_r == true)
	{
		*p->fork_l = false;
		*p->fork_r = false;
		flag = SUCCESS;
	}
	else
		flag = ERROR;
	return (flag);
}
