/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 14:14:34 by klakbuic          #+#    #+#             */
/*   Updated: 2024/03/23 15:50:13 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lexer.h"

void print_type(int type) {
    printf("token type: ");
    switch(type) {
        case WORD:
            printf("WORD\n");
            break;
        case PIPE:
            printf("PIPE\n");
            break;
        case WHITESPACE:
            printf("WHITESPACE\n");
            break;
        case REDIR_IN:
            printf("REDIR_IN\n");
            break;
        case REDIR_OUT:
            printf("REDIR_OUT\n");
            break;
        case LITERAL:
            printf("LITERAL\n");
            break;
        case APPEND:
            printf("APPEND\n");
            break;
        case HEREDOC:
            printf("HEREDOC\n");
            break;
        case ENV:
            printf("ENV\n");
            break;
        case AND:
            printf("AND\n");
            break;
        case OR:
            printf("OR\n");
            break;
        case LPAR:
            printf("LPAR\n");
            break;
        case RPAR:
            printf("RPAR\n");
            break;
        case SINGLE_Q:
            printf("SINGLE_Q\n");
            break;
        case DOUBLE_Q:
            printf("DOUBLE_Q\n");
            break;
        case WILDCARD:
            printf("WILDCARD\n");
            break;
        case UNKNOWN:
            printf("UNKNOWN\n");
            break;
        default:
            printf("Invalid type\n");
            break;
    }
}

void	print_token(void *data)
{
	t_token		*token;
	const char	*lexem;

	lexem = "token lexem: ";
    
	token = (t_token *)data;
	print_type(token->type);
	write(STDOUT_FILENO, lexem, ft_strlen(lexem));
	write(STDOUT_FILENO, token->location.start, token->location.len);
	puts("\n-------------------------------------------------------------------------------------");
}