/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvasanc <alvasanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 11:33:01 by alvasanc          #+#    #+#             */
/*   Updated: 2024/09/06 10:51:39 by alvasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_path(char **envp)
{
	char	*complete_path;
	char	**splitted_path;

	complete_path = NULL;
	while (*envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
		{
			complete_path = (*envp + 5);
			break ;
		}
		envp++;
	}
	if (!complete_path)
		print_error("Error finding the variable in envp");
	splitted_path = ft_split(complete_path, ':');
	return (splitted_path);
}

char	*get_command(char **envp, char *argv)
{
	char	**path;
	char	**command;
	char	*actual_path;
	char	*command_path;
	int		i;

	i = 0;
	command_path = NULL;
	path = get_path(envp);
	command = ft_split(argv, ' ');
	while (path[i])
	{
		actual_path = ft_strjoin(path[i], "/");
		command_path = ft_strjoin(actual_path, command[0]);
		free (actual_path);
		if (access(command_path, F_OK | X_OK) == 0)
			break ;
		free(command_path);
		command_path = NULL;
		i++;
	}
	free_matrix(command);
	free_matrix(path);
	return (command_path);
}

char	**fixed_commands(char *str)
{
	int		quote_num;
	char	**commands;

	quote_num = count_char(str, '\'');
	if (quote_num == 2)
	{
		commands = ft_split(str, '\'');
		commands[0] = ft_strtrim(commands[0], " ");
		return (commands);
	}
	else
	{
		commands = ft_split(str, ' ');
		return (commands);
	}
}
