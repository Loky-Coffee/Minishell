/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalatzas <aalatzas@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:46:39 by nmihaile          #+#    #+#             */
/*   Updated: 2024/03/20 17:59:11 by aalatzas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include <sys/errno.h>
/* ************************************************************************** */
# define FALSE 0
# define TRUE 1
# define NINJASHELL "ninjaSHELL"
/* ************************************************************************** */
# define RED			"\033[0;31m"
# define GREEN			"\033[0;32m"
# define YELLOW			"\033[0;33m"
# define BLUE			"\033[0;34m"
# define MAGENTA		"\033[0;35m"
# define CYAN			"\033[0;36m"
# define LIGHTRED		"\033[0;91m"
# define LIGHTGREEN		"\033[0;92m"
# define LIGHTYELLOW	"\033[0;93m"
# define LIGHTBLUE		"\033[0;94m"
# define LIGHTMAGENTA	"\033[0;95m"
# define LIGHTCYAN		"\033[0;96m"
# define RESET			"\033[0m"

/* ************************************************************************** */
// Definition of token types for a shell interpreter.
// This enumeration represents the different kinds of tokens
// that can be identified during the lexical analysis of shell commands.
// Tokens include various symbols for command parsing, redirection,
// logical operators, and environment variable handling.
typedef enum e_tokentype
{
	NO_TOKEN,
	TOKEN_WORD,
	TOKEN_SQUOTE,
	TOKEN_DQUOTE,
	TOKEN_PIPE,
	TOKEN_LESS,
	TOKEN_GREATER,
	TOKEN_AND,
	TOKEN_DOT,
	TOKEN_TILDE,
	TOKEN_MINUS,
	TOKEN_NEWLINE,
	TOKEN_DLESS,
	TOKEN_DGREATER,
	TOKEN_DAND,
	TOKEN_OR,
	TOKEN_TLESS,
	TOKEN_VARIABLE,
	TOKEN_DOLLAR,
} t_tokentype;
/* ************************************************************************** */

// Defines the types of nodes in the Abstract Syntax Tree (AST) for shell
// command parsing.Each node type corresponds to a specific structure in the
// shell command syntax, including commands, pipes, redirections, and logical
// operators. These nodes represent the parsed structure of a command line
// input, allowing for structured interpretation and execution of shell cmd.
typedef enum e_node_type {
	NODE_COMMAND,
	NODE_PIPE,
	NODE_REDIRECT,
	NODE_AND,
	NODE_OR
} t_node_type;

/* ************************************************************************** */

// Defines the structure of a token in the shell
// command parsing process.
// A token represents a syntactically meaningful unit of text,
// such as a word, operator, or symbol,
// identified during the lexical analysis phase. Tokens are
// linked together to form a list, which is then used to construct
// an abstract syntax tree (AST) for parsing the shell command.
typedef struct s_token
{
	t_tokentype		type;
	char			*str;
	struct s_token	*next;
}   t_token;

/* ************************************************************************** */

// Defines a node in the AST, used for parsing shell commands.
//	Each node can represent a command, operator, or other syntactic element,
// holding tokens for the command or operation, arguments if applicable,
// and pointers t child nodes for constructing a hierarchical cmd structure.
// t_node structures an AST node:
// - tokens: linked list of tokenized command parts.
// - left, right: child nodes for command hierarchy.
// - args: command arguments.
// - type: nature of the node (command, operator).
typedef struct s_node
{
	t_token			**tokens;
	struct s_node	*left;
	struct s_node	*right;
	// t_tokentype		operator_type;
}					t_node;
/* ************************************************************************** */

typedef struct s_ms
{
	int			run;
	int			error;
	t_token		*tokens;
	t_node		*nodes;
	char		*line;
	int			ac;
	char		**av;
	char		**envp;
}			t_ms;
/* ************************************************************************** */

typedef struct s_cmd
{
	char	*cmdpth;
	char	**args;
	char	*path;
}			t_cmd;

/* ************************************************************************** */

// Lexer
void			ft_lexer(t_ms *ms);

// Parser
t_node			*ft_parser(t_ms *ms);
int				count_nodes(t_ms *ms);
void			ft_parse2(t_token *current_token, t_node **current_node);

// Renderer
void			render_tokens(t_ms *ms);
void			render_nodes(int depth, t_node *n, char p);

// Terminate
void			del_token_content(void *param);
void			free_node(t_node **node);
void			free_ms(t_ms *ms);
void			free_av(char **av);
void			ft_close_fd(int fdr, int fdw);
void			terminate(t_ms *ms, int exit_code);

// uToken
t_tokentype		is_single_token(char c);
t_tokentype		is_double_token(char *s);
t_tokentype		is_tripple_token(char *s);
t_tokentype 	is_operator(char *s);
t_tokentype 	is_word(char *str);

// token_list_utils
t_token			*ft_token_new(void);
t_token			*ft_token_last(t_token *token);
void			ft_add_token_end(t_token **token, t_token *new_token);
int				tokens_size(t_token *tokens);
void			ft_token_clear(t_token **token, void (*del)(void*));

// executer
int	execute(int fdr, int fdw, t_node *node, t_ms *ms, int is_rgt);
int	execute_cmd(int fdr, int fdw, t_node *node, t_ms *ms, int exit_code);
int	exec_manager(t_ms *ms);

// path.c

int	ft_prepend_path(char **cmd, char *envpaths);

// error.c

void	ft_perror(char *str);
void	ft_cmd_error(char *msg, char *cmd, int error_code);

/* ************************************************************************** */

#endif