/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvasanc <alvasanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 10:19:44 by alvasanc          #+#    #+#             */
/*   Updated: 2024/09/04 10:28:08 by alvasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pars_args(int argc, char **argv)
{
	int	i;

	i = 0;
	while (i < argc)
	{
		if (argv[1][0] == '\0' || argv[i][0] == ' ' || argv[i] == NULL)
			print_error("Command not found\n");
		i++;
	}
	if (argc == 5)
		return ;
	else
		print_error("Invalid arguments\n");
}
