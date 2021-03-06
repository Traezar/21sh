/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_op1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeguing <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 09:48:12 by pdeguing          #+#    #+#             */
/*   Updated: 2018/11/15 12:45:54 by pdeguing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Ok so Here Doc is working, we just need to precise the way we get the input 
** with readline. Maybe we should use get_next_line instead. We need to 
** keep the newlines in the final string and should not append the limiter
** to it
*/

void	exe_op_dless(t_tree **root, char flag, t_io *io_stack)
{
	char	*heredoc;
	t_tree	*head;
	int		offset;
	int		p[2];

	head = *root;
	offset = 0;
	heredoc = NULL;
	if (pipe(p) == -1)
	{
		perror("21sh");
		exit(EXIT_FAILURE);
	}
	while (!heredoc || ft_strcmp(head->right->token->literal, heredoc + offset))
	{
		if (heredoc)
			offset = ft_strlen(heredoc);
		if (!heredoc)
			heredoc = rl_readline();
		else
			heredoc = ft_strffjoin(heredoc, rl_readline());
	}
	ft_putstr_fd(heredoc, p[WRITE]);
	close(p[WRITE]);
	execute_tree(&head->left, flag, io_push(0, p[READ], io_stack, PIPELINE));
	close(p[READ]);
}

void	exe_op_dgreat(t_tree **root, char flag, t_io *io_stack)
{
	int		fd;
	t_tree	*head;

	head = *root;
	fd = open(head->right->token->literal, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd == -1)
	{
		perror(head->right->token->literal);
		exit(EXIT_FAILURE);
	}
	execute_tree(&head->left, flag, io_push(1, fd, io_stack, DGREAT));
	close(fd);
}

void	exe_op_greatand(t_tree **root, char flag, t_io *io_stack)
{
	int		fd;
	t_tree	*head;

	head = *root;
	fd = '-';
	if (ft_strcmp(head->right->token->literal, "-"))
		fd = ft_atoi(head->right->token->literal);
	/* Check if open for output */
	execute_tree(&head->left, flag, io_push(1, fd, io_stack, GREATAND));
}

void	exe_op_lessand(t_tree **root, char flag, t_io *io_stack)
{
	int		fd;
	t_tree	*head;

	head = *root;
	fd = ft_atoi(head->right->token->literal);
	/* Check if open for input */
	execute_tree(&head->left, flag, io_push(0, fd, io_stack, LESSAND));
}
