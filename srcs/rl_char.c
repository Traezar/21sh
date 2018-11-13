/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_char.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeguing <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 17:06:46 by pdeguing          #+#    #+#             */
/*   Updated: 2018/11/13 14:33:24 by pdeguing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	rl_char_insert(t_rl *rl)
{
	char *tmp;

	tmp = rl->row[rl->cy].buf;
	rl->row[rl->cy].bsize++;
	rl->row[rl->cy].buf = ft_strnew(rl->row[rl->cy].bsize + 1);
	if (tmp)
	{
		ft_strcpy(rl->row[rl->cy].buf, tmp);
		ft_memmove(rl->row[rl->cy].buf + rl->cx + 1, rl->row[rl->cy].buf + rl->cx, rl->row[rl->cy].bsize - rl->cx);
	}
	rl->row[rl->cy].buf[rl->cx] = rl->key;
	ft_strdel(&tmp);
	key_cursor_right(rl);
}

void	rl_char_quote(t_rl *rl)
{
	if (rl->key == '\\')
		rl->quote ^= Q_BSLASH;
	else if (!(rl->quote & Q_BSLASH) && rl->key == '\'')
		rl->quote ^= Q_SQUOTE;
	else if (!(rl->quote & Q_BSLASH) && rl->key == '\"')
		rl->quote ^= Q_DQUOTE;
	else
		rl->quote &= ~(Q_BSLASH);
}
