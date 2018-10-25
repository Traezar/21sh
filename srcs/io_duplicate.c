/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_duplicate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeguing <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 08:54:02 by pdeguing          #+#    #+#             */
/*   Updated: 2018/10/24 09:57:16 by pdeguing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	io_duplicate(int fd_src, int fd_dst)
{
	if (dup2(fd_src, fd_dst) == -1)
	{
		perror("21sh");
		exit(EXIT_FAILURE);
	}
}