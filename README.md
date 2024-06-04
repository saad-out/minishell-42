# Minishell

Minishell is a cursus project in the 42 network programming school. The goal of this project is to implement a simple version of a Bash-like shell in C, supporting features such as pipes, redirections, expansions, and command execution.

The project aims to provide a hands-on experience in developing a command-line interpreter, exploring concepts like process management, signal handling, and parsing user input. By building a mini shell, students gain a deeper understanding of how shell programs work under the hood and learn about the intricacies of handling user interactions and executing commands.

## How Minishell Works

Minishell follows a simple yet effective workflow to process user input and execute commands:

1. **Read Line**: The shell prompts the user for input and reads the entered command line.

2. **Parse Input**: The input line is then parsed to identify individual tokens, such as the command name, arguments, and other special characters like pipes, redirections, or expansions.

3. **Execute Command**: After parsing the input, the shell creates the necessary processes and executes the specified command. This may involve setting up pipes, handling redirections, or performing expansions as required.

4. **Repeat**: Once the command execution is complete, the shell returns to the initial state and prompts the user for a new command, repeating the cycle.

This continuous loop of reading input, parsing, executing commands, and repeating allows the shell to provide an interactive command-line interface for users to execute various commands and perform complex operations.

### Parsing

The parsing process in Minishell involves two main stages: lexing and parsing.

#### 1. Lexer

The lexer, or tokenizer, is responsible for breaking down the input command line into a sequence of meaningful tokens. These tokens can represent commands, arguments, operators (such as pipes or redirections), or other special characters.

The lexer scans the input string character by character, applying a set of rules to identify and categorize the different token types. It generates a stream of tokens that serves as input for the parser.

#### 2. Parser

The parser takes the token stream generated by the lexer and constructs an abstract syntax tree (AST) that represents the structure of the command line. The AST is a hierarchical tree-like data structure that captures the relationships between commands, arguments, and operators.

The parser follows a set of grammar rules to analyze the token stream and build the AST. These rules define the valid syntax and semantics of the command line, ensuring that the input is correctly interpreted.

Once the AST is constructed, it can be traversed and processed by the shell to execute the specified commands, handle redirections, set up pipes, and perform any necessary expansions or substitutions.

### Execution

After the parsing stage, the shell enters the execution phase, where it processes the abstract syntax tree (AST) generated by the parser and carries out the specified commands and operations.

#### AST Traversal and Command Execution

The shell traverses the AST, following the structure defined by the parser. During this traversal, it identifies the commands to be executed and their associated arguments, as well as any operators or special characters that require specific handling.

When a command is encountered, the shell checks if it is a built-in command or an external program. Built-in commands are executed directly within the shell process, while external programs are executed by creating a new child process using the `fork()` system call and invoking the appropriate program via an `exec()` system call.

#### Variable Expansion

Minishell supports variable expansion, allowing users to define and reference environment variables within their commands. During the execution phase, the shell scans the command line for variable references (e.g., `$VAR`) and substitutes them with their corresponding values.

#### Wildcard Expansion

Wildcard expansion is another feature supported by Minishell. When a command line contains wildcard characters (e.g., `*`, `?`), the shell expands them to match the corresponding files or directories in the current working directory.

#### Built-in Commands

Minishell includes a set of built-in commands that are implemented directly within the shell. These commands provide functionality such as changing directories (`cd`) or setting environment variables (`export`). Built-in commands are executed without creating a new process, improving efficiency and reducing overhead.

#### Signal Handling

The shell also handles various signals, such as `SIGINT` (Ctrl+C) and `SIGQUIT` (Ctrl+\). Appropriate actions are taken in response to these signals, such as terminating the currently running process or printing diagnostic messages.

## Enough theory, let's code :)

Now that we've covered the theoretical aspects of how Minishell works, it's time to dive into the implementation details. In this section, we'll explore the core components of the shell, including the lexer, parser, and executor.

It's important to note that the code snippets provided here represent my approach to implementing Minishell. While they serve as a reference and a starting point, feel free to adjust the data structures, algorithms, and overall design as per your understanding and coding style.

Remember, there are multiple ways to achieve the same functionality, and the true learning experience lies in understanding the underlying concepts and crafting your own solution. The goal is not to merely copy and paste the code but to use it as a guide and adapt it to your specific needs and preferences.

### Lexer
Let's take this prompt line as an example: `ls -la | grep "dr" | wc -l > file1 && cd $HOME`.

After this line is taken from the user (probably using `readline()`), we want to turn this string into a linked list of tokens, each with a type and the characters themselves, like the following:
```
word -> word -> pipe -> word -> literal -> pipe -> word -> word -> redir_in -> word -> AND -> word -> ENV
ls     -la     |       grep   "dr"          |       wc     -l         >         file1   &&     cd     $HOME
```
Building a tree using the stream of tokens is easier and more straightforward than using the raw string entered by the user. This means that this step is an intermediate step before parsing, not mandatory, but preferred.

We are going to represent our token types as an enum in C:
```
enum						e_token_type
{
	WORD = 1 << 0,
	PIPE = 1 << 1,
	REDIR_IN = 1 << 2,
	REDIR_OUT = 1 << 3,
	APPEND = 1 << 4,
	HEREDOC = 1 << 5,
	WHITESPACE = 1 << 6,
	ENV = 1 << 7,
	AND = 1 << 8,
	OR = 1 << 9,
	LPAR = 1 << 10,
	RPAR = 1 << 11,
	SINGLE_Q = 1 << 12,
	DOUBLE_Q = 1 << 13,
	WILDCARD = 1 << 14,
	LITERAL = 1 << 15,
	BLOCK = 1 << 16,
	EXEC = 1 << 17,
	UNKNOWN = 1 << 18,
	VOID = 1 << 19,
	PARAN = LPAR | RPAR,
	QUOTES = SINGLE_Q | DOUBLE_Q,
	REDIR = REDIR_IN | REDIR_OUT | APPEND | HEREDOC,
	CTRL = AND | OR,
	STRING = WORD | ENV | WILDCARD | LITERAL,
	CONNECTORS = PIPE | AND | OR | LPAR,
};
typedef enum e_token_type	t_etype;
```
We don't have to allocate for each token string at this stage, instead we'll just put a `char *` at the first char and provide the length of the token:
```
struct	s_slice
{
	char	*start;
	size_t	len;
};
typedef struct s_slice		t_slice;
```
We are going to use a doubly linked list, because we will perform operations such as deletion of nodes etc... which is a bit easier if you have pointer to `*prev` and `*next`.
So our final struct to represent a token would be like this:
```
struct	s_token
{
	t_etype	type;        // enum type
	t_slice	location;    // token string
	t_token	*prev;       // points to previous node in list
	t_token	*next;       // points to next node in list
};
typedef struct s_token		t_token;
```
We declare a `t_token *head` initialized to `NULL`, the lexer function takes a reference to this variable and the string entered by the user, iterate through the string character by character, building the linked list of tokens. The `head` variable should point to the beginning of the list.
Note that we create tokens for whitespace as well, and also separate tokens for double and single quotes (unlike the above illustration), this is because we tend to not loose any information at the beginning to help us check the syntax and some other things. Once we are done with that, we will call a `post_lexer()` function which will delete whitespace tokens and double/single quote tokens, providing the final list in the above illustration.
```
bool	is_special(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == '$' || c == '(' || c == ')'
		|| c == '*' || c == '&')
		return (true);
	return (false);
}

void	lexer(t_token **head, const char *line)
{
	t_charitr	itr;

	itr = (t_charitr)line;
	while (itr_has_next(itr))
	{
		if (is_whitespace(itr_peek(itr)))
			whitespace_token(head, &itr);
		else if (is_special(itr_peek(itr)))
			special_tokens(head, &itr);
		else if (itr_peek(itr) == '\"' || itr_peek(itr) == '\'')
			literal_token(head, &itr);
		else
			word_token(head, &itr);
	}
}
```
This is the main function for the lexer part, `t_charitr` is just a `char *` type (`typedef char	*t_charitr;`), a token is either a special token like `PIPE`, `REDIR_IN`, `REDIR_OUT`, `AND`... , a literal (content inside quotes), a whitespace or a regular word (which could be command, its arguments, filenames etc...).
You can explore the full lexer code in the `src/lexer` folder.

### Parser
Now that we have turned our prompt string into a list of meaningful tokens, we need to generate an [AST (Abstract Syntax Tree)](https://dev.to/balapriya/abstract-syntax-tree-ast-explained-in-plain-english-1h38) that represents the flow of execution. The `&&` token should be translated into a tree node that has some command on its left as well as its right. The tokens `ls` -> `-la` should be translated into a command node that has `ls` as the command and `-la` as its argument. This representation is constructed in a tree-like structure.
The algorithm we are going to use to build this tree is called [Recursive Descent Parser](https://en.wikipedia.org/wiki/Recursive_descent_parser#:~:text=In%20computer%20science%2C%20a%20recursive,the%20nonterminals%20of%20the%20grammar.). You can conclude from its name that it is based on recursion.

First, we have to define a grammar. It's like a definition of bash syntax and is usually written in [BNF](https://en.wikipedia.org/wiki/Backus%E2%80%93Naur_form).
The following is not strict BNF, just a BNF-like grammar (for the sake of simplicity):
```
SEQ = PIPE
	| PIPE '&&' SEQ
	| PIPE '||' SEQ
# A sequence is either a single PIPE, or PIPE followed by ('&&' or '||') followed by another sequence.
You can spot the recursivity in this pattern that we have on the right where you can have an '&&' or '||' and then another SEQ which folds back into another single or multiple pipes.

PIPE = CMD
	| BLOCK
	| CMD '|' PIPE
	| BLOCK '|' PIPE
# Same goes for the rest patterns: A pipe is either a single CMD, or CMD followed by pipe '|' character followed by another PIPE.

BLOCK = '(' SEQ ')'
	| BLOCK REDIR
# Block is anything inside parenthesis, and it could be followed by redirections.

CMD = WORD
	| WORD CMD
	| WORD CMD REDIR
	| WORD REDIR CMD
	| REDIR WORD CMD
# Redirections can be placed anywhere in a command: `ls -la >file1 >file2` is the same as `>file1 ls >file2 -la`

REDIR = '>' WORD
	| '>>' WORD
	| '<' WORD
	| '<<' WORD
# Minishell does not require to handle number redirections (like 2> to redirect stderr).

WORD = [a-zA-Z0-9_]+
# WORD is represented as a wildcard pattern, alphanum characters and underscore '_'
```

For `&&` and `||` operators, we are going to have a tree node that has left and right:
```
struct	s_and_or
{
	t_etype	type;
	t_tree	*left;
	t_tree	*right;
};
```
A block represents what's inside parenthesis, so it'll have only one child:
```
struct	s_block
{
	t_etype	type;
	t_tree	*child;
};
```
For a pipe, we are going to store the chain of pipelines in an array and keep track of its size:
```
struct	s_pipe
{
	t_etype	type;
	size_t	nb_pipes;
	t_tree	**nodes;
};
```
Redirections will be in a seperate node, pointing to the child:
```
struct	s_redir
{
	t_etype	type;
	int		fd; // for input redir: fd = 0, for output redir: fd = 1
	char	*file;		// the filename itself, or delimiter string in case of heredoc
	int		flags;  // flags to open the file with: differs between append and normal out-redir
	bool	expand;		// ONLY IN CASE OF HEREDOC: flag to check if we should expand heredoc content or not
	t_tree	*child;
};
```
Finally, exec node contains the argv to be passed to `execve()`, argc to keep track of number of elements and pointer to the environment:
```
struct	s_exec
{
	t_etype	type;
	char	**argv;
	int		argc;
	t_env	**env;
};
```


We declare a `t_tree *head` initialized to `NULL`, the parser function takes reference to this variable and the linked list of tokens generated by the lexer:
```
void	parser(t_tree **tree, t_token *tokens)
{
	if (!tokens)
		return ;
	*tree = parse_sequence(&tokens);
	if (!*tree)
		error("Syntax error", "parser");
}
```
We need to respect the hierarchy of patterns: sequence -> pipe/block -> cmd. This means that simple command like `ls` is a sequence that contains a single pipe, which contains a single command, that does not have any redirections.

If we have something like: `cmd1 && cmd2 || cmd3`, we want the last `||` to be the root of our tree, with `cmd3` to its right, and `&&` to its left that also has `cmd1` and `cmd2` to its left and right respectively. In other words, we need left recursivity for `&&` and `||` tree nodes:
```
t_tree	*parse_sequence_tail(t_token **tokens, t_tree *left)
{
	t_tree	*right;
	t_etype	type;

	if (!(*tokens))
		return (left);
	else if (!((*tokens)->type & CTRL))
		return (NULL);
	type = (*tokens)->type;
	(*tokens) = (*tokens)->next;
	right = parse_pipe(tokens);
	if (!right)
		return (NULL);
	if (!(*tokens) || !((*tokens)->type & CTRL))
		return (and_or_node(type, left, right));
	left = and_or_node(type, left, right);
	return (parse_sequence_tail(tokens, left));
}

t_tree	*parse_sequence(t_token **tokens)
{
	t_tree	*left;

	left = parse_pipe(tokens);
	if (!left)
		return (NULL);
	return (parse_sequence_tail(tokens, left));
}
```

To parse a pipe, we create a pipe node, parse command or block (based on token type) and add it to our pipe array, while we have PIPE tokens left:
```
t_tree	*parse_pipe(t_token **tokens)
{
	t_pipe	*pipe;
	t_tree	*exec;

	pipe = (t_pipe *)pipe_node();
	if (!pipe)
		return (NULL);
	exec = NULL;
	while ((*tokens))
	{
		if ((*tokens)->type == LPAR)
			exec = parse_block(tokens);
		else
			exec = parse_exec(tokens);
		if (!exec)
			return (NULL);
		pipe = (t_pipe *)pipe_add_node((t_tree *)pipe, exec);
		if ((*tokens) && (*tokens)->type == PIPE)
			(*tokens) = (*tokens)->next;
		else
			break ;
	}
	if (pipe->nb_pipes <= 1)
		return (ft_free((void *)pipe, PARSER), (t_tree *)exec);
	return ((t_tree *)pipe);
}
```

Suppose we have this subcommand: `ls > f1 > f2`, we want our subtree to look like this: `f1 -> f2 -> ls`. It means that command redirections are represented as a linked list with the last child being the command node itself. Whenever a redirection is encountered during parsing, it is added at the end of the linked list, just before the last command node: `ls` ==> `f1 -> ls` ==> `f1 -> f2 -> ls`.
```
t_tree	*parse_cmd_and_redirs(t_token **tokens, t_exec *node)
{
	t_token	*tmp;
	t_tree	*exec;

	exec = (t_tree *)node;
	tmp = *tokens;
	while (tmp)
	{
		if (tmp->type & STRING)
		{
			parse_str(tmp, node);
			tmp = tmp->next;
		}
		else if (tmp->type & REDIR)
		{
			exec = parse_redir(&tmp, exec);
			if (!exec)
				return (NULL);
		}
		else
			break ;
	}
	*tokens = tmp;
	return (exec);
}

t_tree	*parse_exec(t_token **tokens)
{
	t_tree	*exec;
	t_exec	*node;

	node = init_exec();
	exec = parse_cmd_and_redirs(tokens, node);
	node->argv = ft_realloc(node->argv, sizeof(char *) * (node->argc), \
							sizeof(char *) * (node->argc + 1));
	if (!node->argv)
		return (NULL);
	node->argv[node->argc] = NULL;
	return (exec);
}
```

When a redircton token is encountered, the following STRING token is the filename (or delimiter in case of heredoc):
```
t_tree	*parse_redir(t_token **tokens, t_tree *child)
{
	t_tree	*redir;
	t_redir	*last_redir;
	t_etype	type;
	char	*s;

	if (!(*tokens) || !((*tokens)->type & REDIR))
		return (NULL);
	type = (*tokens)->type;
	(*tokens) = (*tokens)->next;
	if (!(*tokens) || !((*tokens)->type & STRING))
		return (NULL);
	s = ft_strndup((*tokens)->location.start, (*tokens)->location.len);
	(*tokens) = (*tokens)->next;
	last_redir = get_last_redir(child);
	if (last_redir)
	{
		redir = redir_node(type, last_redir->child, s);
		last_redir->child = redir;
		redir = child;
	}
	else
		redir = redir_node(type, child, s);
	return (redir);
}
```

Finally, a block is left paran token, followed by a sequence inside, then a right paran token:
```
t_tree	*parse_block(t_token **tokens)
{
	t_tree	*block;
	t_tree	*child;

	if (!(*tokens) || (*tokens)->type != LPAR)
		return (NULL);
	(*tokens) = (*tokens)->next;
	child = parse_pipe(tokens);
	if (!child)
		return (NULL);
	if ((*tokens) && ((*tokens)->type & CTRL))
	{
		child = parse_sequence_tail(tokens, child);
		if (!child)
			return (NULL);
	}
	if (!(*tokens) || (*tokens)->type != RPAR)
		return (NULL);
	(*tokens) = (*tokens)->next;
	block = block_node(child);
	while ((*tokens) && (*tokens)->type & REDIR)
		block = parse_redir(tokens, block);
	return (block);
}
```

One last thing to note is that we don't know the type of childs for each tree node. Let's take this command for example: `ls && echo` => the left pointer of the `&&` node should have a command node type `t_exec *`, but for this command `ls | cd && echo` => the left would point to a pipe `|` node `t_pipe *`, so how did we solve this ?
The solution used here is to declare an additional struct `t_tree *`:
```
struct	s_tree
{
	t_etype	type;
};
```
This struct is never allocated, but all childs in every other struct of our tree has type `t_tree *`. Whatever type was allocated for a child, it is typecasted into `t_tree *` before assigning it a child to another struct. That's why all our parsing functions return `t_tree *` which is a more generic type that represents all our types. The `type` variable is used to "trick" the compiler not to complain when we do this `node->type` where `node` is still of type `t_tree *` to check the type and typecast into the actual struct type used. You'll see how this is done in execution later on.

You can explore the full parser code in the `src/parser` folder.

### Execution


# ...
