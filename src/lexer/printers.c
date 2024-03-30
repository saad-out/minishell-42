/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 01:46:16 by klakbuic          #+#    #+#             */
/*   Updated: 2024/03/30 01:44:56 by soutchak         ###   ########.fr       */
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

void	print_token(t_token *token)
{
	const char	*lexem;
    
    lexem = "lexem: ";
	print_type(token->type);
	write(STDOUT_FILENO, lexem, strlen(lexem));
	write(STDOUT_FILENO, token->location.start, token->location.len);
	// puts("\n-------------------------------------------------------------------------------------");
    puts("\n");
}