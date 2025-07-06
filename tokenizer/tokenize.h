
#ifndef TOKENIZE_H
# define TOKENIZE_H

/* System headers */
# include <stdlib.h>
# include <string.h>
# include <ctype.h>
# include <stdio.h>

/* Constants */
# define MAX_TOKENS 4096

/* Token types */
typedef enum e_tokentype
{
    /* Basic tokens */
    TOK_WORD,

    /* Quoting */
    TOK_SQUOTE,
    TOK_DQUOTE,

    /* Control operators */
    TOK_PIPE,       // |
    TOK_OR,         // ||
    TOK_AND,        // &&

    /* Redirections */
    TOK_REDIR_IN,   // <
    TOK_HEREDOC,    // <<
    TOK_REDIR_OUT,  // >
    TOK_REDIR_APPEND, // >>

    /* Expansions */
    TOK_ENV_VAR,    // $VAR
    TOK_EXIT_STATUS // $?
} t_tokentype;

/* Error codes */
typedef enum e_tok_err
{
    ERR_NONE,           // No error
    ERR_UNCLOSED_QUOTE, // Unterminated quote
    ERR_UNCLOSED_GROUP, // Unterminated group
    ERR_EMPTY_INPUT,    // Input is empty
    ERR_OVERFLOW,       // Too many tokens
    ERR_MEMORY,         // Allocation failure
    ERR_ESCAPE_SEQ,     // Invalid escape sequence
    ERR_SYNTAX          // General syntax error
} t_tok_err;

/* Token structure */
typedef struct s_token
{
    size_t      start;
    size_t      length;
    t_tokentype type;
} t_token;

/* Tokenizer state */
typedef struct s_tokenizer_state
{
    t_token     current;
    size_t      pos;
    int         count;
    char        **tokens;
    t_tok_err   error;
} t_tokenizer_state;

/* ======================= */
/*      CORE FUNCTIONS     */
/* ======================= */

char                **tokenize(char *line);
void                tokenizer_error(t_tok_err err);

/* ======================= */
/*    STATE MANAGEMENT     */
/* ======================= */

void                ctx_init(t_tokenizer_state *ctx);
void                create_token(t_tokenizer_state *ctx, char *line);

/* ======================= */
/*      TOKEN HANDLERS     */
/* ======================= */

/* Quote handling */
int                 quote_handler(t_tokenizer_state *ctx, char *line);

/* Operator handling */
int		operator_handler(t_tokenizer_state *ctx, char *line);
int		dispatch_control_ops(t_tokenizer_state *ctx, char *line);
int		dispatch_redirections(t_tokenizer_state *ctx, char *line);

/* Word handling */
int                 word_handler(t_tokenizer_state *ctx, char *line);

/* Environment vars handling */
int		env_handler(t_tokenizer_state *ctx, char *line);

/* Token emission*/
int		emit_token(t_tokenizer_state *ctx, char *line, t_tokentype type, int length);

#endif
