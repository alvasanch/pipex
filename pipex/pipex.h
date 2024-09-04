/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvasanc <alvasanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 10:43:08 by alvasanc          #+#    #+#             */
/*   Updated: 2024/09/04 11:55:44 by alvasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft+gnl+printf/libft.h"

void	pars_args(int argc, char **argv);
void	print_error(char *str);
void	free_matrix(char **str);
int		count_char(char *str, int c);
char	**get_path(char **envp);
char	*get_command(char **envp, char *argv);
char	**fixed_commands(char *str);

#endif
