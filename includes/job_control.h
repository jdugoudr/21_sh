/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_control.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 00:51:48 by mdaoud            #+#    #+#             */
/*   Updated: 2019/08/26 02:06:10 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOB_CONTROL_H
# define JOB_CONTROL_H
# include <stdio.h>

#include "shell21.h"
#include "libft.h"
#include "editor.h"

# define MAX_JOBS	50
# define MAX_JPID	50
# define CREATED	0
# define RUNNING	1
# define STOPPED	2
# define SUSPENDED	4
# define DONE		8	//	 same as terminated (by a signal)?

/*
** Structure describing one job.
** the status variable describes the status of the job.
** fg: 1 if the job is in the foreground, 0 otherwise.
** current: 1 if the job is the current (or last) active job, 0 otherwise.
** pid[]: saves all the pids of the process contained in one job.
*/

/*
typedef	struct	s_job
{
	int		status;
	int		fg;
	// int		current_job;	//	necessairy?
	pid_t	pid[MAX_JPID];
}				t_job;
*/

/*
** The global variable that keeps track of all the current job.
** The array index indicates the job number.
** The "current" variable holds the index of the current job (active job).
*/

/*
typedef struct s_jobs
{
	t_job		jobs[MAX_JOBS];
	int			current_job;
}				t_jobs;
*/

typedef struct	s_process
{
	struct s_process	*next;			/* next process in pipeline */
	char				**argv;			/* for exec */
	pid_t				pid;			/* process ID */
	char				completed;		/* true if process has completed */
	char				stopped;		/* true if process has stopped */
	int					status;			/* reported status value */
}				t_process;


typedef struct job
{
	struct job		*next;				/* next active job */
	char				*command;		/* command line, used for messages */
	t_process			*first_process;	/* list of processes in this job */
	pid_t				pgid;			/* process group ID */
	char				notified;		/* true if user told about stopped job */
	struct termios	tmodes;				/* saved terminal modes */
//   int stdin, stdout, stderr;			/* standard i/o channels */
} job;

void			job_control(char	*cmd);

#endif
