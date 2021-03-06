/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeguing <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 15:02:27 by pdeguing          #+#    #+#             */
/*   Updated: 2018/10/23 07:53:39 by pdeguing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	add_env(char *arg)
{
	int		i;
	int		len;
	char	**tmp;

	len = get_envlen(g_env) + 1;
	tmp = g_env;
	g_env = (char **)malloc(sizeof(char *) * (len + 1));
	g_env[len] = NULL;
	i = 0;
	while (tmp[i] != NULL)
	{
		g_env[i] = ft_strdup(tmp[i]);
		i++;
	}
	g_env[i] = ft_strdup(arg);
	ft_pstrdel(tmp);
}

int		ft_setenv(char **args)
{
	int		i;

	i = -1;
	while (args[++i] != NULL)
	{
		if (!ft_strchr(args[i], '='))
		{
			ft_printf("usage: setenv NAME=value\n");
			return (0);
		}
		else if (!replace_env(ft_strdup(args[i])))
			add_env(args[i]);
	}
	return (0);
}
