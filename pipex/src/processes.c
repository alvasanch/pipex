/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvasanc <alvasanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 10:31:09 by alvasanc          #+#    #+#             */
/*   Updated: 2024/09/12 10:59:12 by alvasanc         ###   ########.fr       */
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

void	child_process(char **argv, int *fd, char **envp)
{
	int		infile_fd;
	char	*path;

	close(fd[0]);
	infile_fd = open(argv[1], O_RDONLY);
	if (infile_fd == -1)
		print_error("Error: Infile can't be read\n");
	dup2(infile_fd, 0);
	dup2(fd[1], 1);
	close(fd[1]);
	path = get_command(envp, argv[2]);
	if (!path)
	{
		print_error("Error: Command not found\n");
		free(path);
	}
	exe_commands(path, argv[2], envp);
}

void	child_process2(char **argv, int *fd, char **envp)
{
	int		outfile_fd;
	char	*path;

	close(fd[1]);
	outfile_fd = open(argv[4], O_WRONLY, O_CREAT, O_TRUNC, 0644);
	if (outfile_fd == -1)
		print_error("Error: Outfile can't be opened\n");
	dup2(outfile_fd, 1);
	close(outfile_fd);
	dup2(fd[0], 0);
	close(fd[0]);
	path = get_command(envp, argv[3]);
	if (!path)
	{
		print_error("Error: Command not found\n");
		free(path);
	}
	exe_commands(path, argv[3], envp);
}
