/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeguing <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 08:42:57 by pdeguing          #+#    #+#             */
/*   Updated: 2018/10/24 09:57:15 by pdeguing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			get_nbr_args(t_tree **root)
{
	t_tree	*head;
	int		i;

	i = 0;
	head = *root;
	while (head)
	{
		i++;
		head = head->right;
	}
	return (i);
}

char		**get_args(t_tree **root)
{
	char	**args;
	t_tree	*head;
	int		size;
	int		i;

	size = get_nbr_args(root);
	args = malloc(sizeof(char *) * (size + 1));
	args[size] = NULL;
	head = *root;
	i = 0;
	while (i < size)
	{
		args[i] = head->token->literal;
		head = head->right;
		i++;
	}
	return (args);
}

/*
** I wanted to implement a stack here, keeping track of the fds used for each
** command. It would have been interesting, but sadly it seems smarter to go
** with a standard recursive method. We are parsing shell language, so the size
** of the input and thus the resulting tree should always be manageable
** within the stack. And using a manual stack would create an exceptional
** case where we should always let stdin (or the fd replacing it after a
** redirection) on top. This would lead to the necessicity to
** implement two parallel stacks or to do some value swapping within
** a stack storing an array of 2 fd, read end write end.
*/

void		execute_tree(t_tree **root, char flag, int fd_read, int fd_write)
{
	t_tree	*head;
	int		p[2];
	int		fd;

	head = *root;
	if (!head)
		return ;
	// Execute cmd
	if (!head->left)
		execute_cmd(get_args(&head), flag, fd_read, fd_write);
	else if (head->token->type == SEMICOLON)
	{
		execute_tree(&head->left, flag, fd_read, fd_write);
		execute_tree(&head->right, flag, fd_read, fd_write);
	}
	else if (head->token->type == PIPELINE)
	{
		if (pipe(p) == -1)
		{
			perror("21sh");
			exit(EXIT_FAILURE);
		}
		execute_tree(&head->left, flag ^ WAIT, fd_read, p[WRITE]);
		close(p[WRITE]);
		execute_tree(&head->right, flag, p[READ], fd_write);
		close(p[READ]);
	}
	else if (head->token->type == GREAT)
	{
		fd = open(head->right->token->literal, O_WRONLY | O_CREAT, 0644);
		if (fd == -1)
		{
			perror(head->right->token->literal);
			exit(EXIT_FAILURE);
		}
		execute_tree(&head->left, flag, fd_read, fd);
		close(fd);
	}
	else if (head->token->type == LESS)
	{
		fd = open(head->right->token->literal, O_RDONLY);
		if (fd == -1)
		{
			perror(head->right->token->literal);
			exit(EXIT_FAILURE);
		}
		execute_tree(&head->left, flag, fd, fd_write);
		close(fd);
	}
	else if (head->token->type == DGREAT)
	{
		fd = open(head->right->token->literal, O_APPEND | O_CREAT, 0644);
		if (fd == -1)
		{
			perror(head->right->token->literal);
			exit(EXIT_FAILURE);
		}
		execute_tree(&head->left, flag, fd_read, fd);
		close(fd);
	}
	else if (head->token->type == LESSAND)
	{
		p[0] = 
		execute_tree(&head->left, flag | DUPLICATE, fd_read, fd_write);
	}
}
