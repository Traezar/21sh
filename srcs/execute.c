/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeguing <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 06:40:28 by pdeguing          #+#    #+#             */
/*   Updated: 2018/10/24 12:56:45 by pdeguing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

	// We need to go down left counting operators
	// Then execute from bottom left
	// Get args from right of cmd
	// And change the execution environment depending on
	// counted operators.

/*
** We can implement a stack of int identified via our type enum,
** but isn't it too much?
*/


void			execute(t_tree **root)
{
	t_io	*io_stack;

	execute_tree(root, WAIT, &io_stack);
}
