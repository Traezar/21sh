/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_history.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeguing <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 16:17:20 by pdeguing          #+#    #+#             */
/*   Updated: 2018/11/06 07:09:34 by pdeguing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	key_history_up(t_rl *rl)
{
	if (!rl->history_head)
		return ;
	ft_strdel(&rl->row[rl->cy].buf);
	if (rl->history_head->next && rl->history_state == KEY_HISTORY_DOWN)
		rl->history_head = rl->history_head->next;
	rl->row[rl->cy].buf = ft_strdup(rl->history_head->line);
	rl->row[rl->cy].bsize = ft_strlen(rl->row[rl->cy].buf);
	rl->history_state = KEY_HISTORY_UP;
	if (rl->history_head->next)
		rl->history_head = rl->history_head->next;
	else
		rl->history_state = 0;
	rl->cx = rl->row[rl->cy].bsize;
}

void	key_history_down(t_rl *rl)
{
	if (!rl->history_head)
		return ;
	ft_strdel(&rl->row[rl->cy].buf);
	if (rl->history_head->prev && rl->history_state == KEY_HISTORY_UP)
		rl->history_head = rl->history_head->prev;
	if (!rl->history_head->prev)
	{
		rl->row[rl->cy].buf = NULL;
		rl->row[rl->cy].bsize = 0;
		rl->history_state = 0;
	}
	else
	{
		rl->history_head = rl->history_head->prev;
		rl->row[rl->cy].buf = ft_strdup(rl->history_head->line);
		rl->row[rl->cy].bsize = ft_strlen(rl->row[rl->cy].buf);
		rl->history_state = KEY_HISTORY_DOWN;
	}
	rl->cx = rl->row[rl->cy].bsize;
}

/*
void	key_history_search(t_shell *sh)
{
	clear_line();
	read_char();
	add_char_to_buf();
	search_history(buf);
}
*/
