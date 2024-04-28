/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaoussi <mfaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:22:53 by mfaoussi          #+#    #+#             */
/*   Updated: 2024/04/28 12:29:53 by mfaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	check_syntax(char **argv);

/**
* check_input - will check that the input is valid.
* Return : 0 if all good 
*		   1 in case of  error
**/

int	check_input(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
		return (1);
	if (check_syntax(argv) == 1)
		return (1);
	i = 1;
	while (i < 5)
	{
		if (ft_atoi(argv[i]) <= 0)
			return (1);
		i++;
	}
	if (argc == 6)
	{
		if (ft_atoi(argv[5]) < 0)
			return (1);
	}
	if (ft_atoi(argv[1]) > 200)
		return (1);
	return (0);
}

/**
* check_syntax - will check for syntax error in the input .
* Return : 0 if all good 
*		   1 in case of  error
**/

int	check_syntax(char **argv)
{
	int	i;
	int	index;

	i = 1;
	while (argv[i])
	{
		index = 0;
		while (argv[i][index])
		{
			if (argv[i][index] < '0' || argv[i][index] > '9')
				return (1);
			index++;
		}
		i++;
	}
	return (0);
}
