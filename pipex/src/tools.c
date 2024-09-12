/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvasanc <alvasanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 10:43:25 by alvasanc          #+#    #+#             */
/*   Updated: 2024/09/05 10:37:36 by alvasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_error(char *str)
{
	ft_putstr_fd(str, 2);
	exit(EXIT_FAILURE);
}

void	free_matrix(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

int	count_char(char *str, int c)
{
	int	i;
	int	count_char;

	i = 0;
	count_char = 0;
	while (str[i])
	{
		if (str[i] == c)
			count_char++;
		i++;
	}
	return (count_char);
}
