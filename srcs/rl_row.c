/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_row.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeguing <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 12:01:21 by pdeguing          #+#    #+#             */
/*   Updated: 2018/11/06 07:51:41 by pdeguing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static t_row	rl_row_new(char *buf)
{
	t_row	new;

	if (buf)
		new.bsize = ft_strlen(buf);
	else
		new.bsize = 0;
	new.buf = buf;
	return (new);
}

void	rl_row_insert(t_rl *rl, char *buf)
{
	t_row	*tmp;
	int		i;

	tmp = rl->row;
	rl->row = (t_row *)malloc(sizeof(t_row) * (rl->row_max + 1));
	if (!rl->row)
		exit(EXIT_FAILURE);
	i = 0;
	while (i < rl->row_max)
	{
		rl->row[i] = tmp[i];
		i++;
	}
	rl->row[i] = rl_row_new(buf);
	rl->row_max++;
	free(tmp);
}