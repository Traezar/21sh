/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_get_word.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeguing <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 11:25:11 by pdeguing          #+#    #+#             */
/*   Updated: 2018/11/13 17:10:42 by pdeguing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*append_char(char *str, char c)
{
	int		size;
	char	*new;

	size = 1;
	if (str)
		size += ft_strlen(str);
	new = ft_strnew(size + 1);
	if (!new)
		return (NULL);
	new[size] = '\0';
	if (str)
		ft_strcpy(new, str);
	ft_strdel(&str);
	new[size - 1] = c;
	return (new);

}

/*
** Added append_char(), just need to manage quotes now, they will always be
** correct based on readline, so we just need to remove the quotes character
** and keep track of the state to know if we append newline or just skip
** it
*/

/* Bash ignores nested quotes */

int		token_get_word(char **pstr, char *pchar, t_token *token)
{
	int		quote;
	char	*first_char;

	quote = 0;
	first_char = pchar;
	token->type = TOKEN;
	while (*pchar != '\0')
	{
		if (!quote && ft_strchr(";|<>", *pchar))
			break ;
		else if (!quote && ft_strchr(" 	", *pchar))
			break ;
		else if (*pchar == '\\')
			quote ^= Q_BSLASH;
		else if (*pchar == '\'')
			quote ^= Q_SQUOTE;
		else if (*pchar == '\"')
			quote ^= Q_DQUOTE;
		else if (!(quote & Q_BSLASH) || *pchar != '\n')
		{
			token->literal = append_char(token->literal, *pchar);
		}
		pchar++;
	}
	*pstr = pchar;
	return (1);
}
