/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeguing <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 10:16:32 by pdeguing          #+#    #+#             */
/*   Updated: 2018/10/25 10:32:27 by pdeguing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** So we could actually use a stack of duplications to do for a specific
** stage in recursion, or rather an array of fd to duplicate with their
** destination at each level so that at the end we execute with:
** 			-> replace 0, per 3
**			-> replace 1, per 4
**			-> replace 2, per 1
**			-> replace 3, per 6
** or whatever.
*/

void	io_redirect(t_io **io_stack)
{
	t_io	*head;

	head = *io_stack;
	while (head)
	{
		/*
		ft_printf(RED"||| dst: %d, src: %d\n"RESET, head->dst, head->src);
		*/
		if (dup2(head->src, head->dst) == -1)
		{
			perror("21sh");
			exit(EXIT_FAILURE);
		}
		head = head->next;
	}
}
