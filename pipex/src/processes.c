/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvasanc <alvasanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 10:31:09 by alvasanc          #+#    #+#             */
/*   Updated: 2024/09/11 11:10:54 by alvasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exe_commands(char *path, char *str, char **envp)
{
	char	**command;

	command = fixed_commands(str);
	if (!command)
	{
		free_matrix(command);
		free(path);
		print_error("Error finding command\n");
	}
	if (execve(path, command, envp) == -1)
	{
		free_matrix(command);
		free(path);
		print_error("Execution failed\n");
	}
}

void	parent_process(char **argv, int *fd, char **envp)
{
	pid_t	pid_c1;
	pid_t	pid_c2;

	pid_c1 = fork();
	if (pid_c1 == -1)
		print_error("Error: Child process one failed\n");
	else if (pid_c1 == 0)
		child_process(argv, fd, envp);
	else
	{
		close(fd[1]);
		pid_c2 = fork();
		if (pid_c2 == -1)
			print_error("Error: Child process two failed\n");
		else if (pid_c2 == 0)
			child_process(argv, fd, envp);
		else
		{
			close(fd[0]);
			waitpid(pid_c1, 0, 0);
			waitpid(pid_c2, 0, 0);
		}
	}
}