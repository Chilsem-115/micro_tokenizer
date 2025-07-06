
#include "tokenize.h"

static int	handle_or(t_tokenizer_state *ctx, char *line)
{
	return (emit_token(ctx, line, TOK_OR, 2));
}

static int	handle_and(t_tokenizer_state *ctx, char *line)
{
	return (emit_token(ctx, line, TOK_AND, 2));
}

static int	handle_pipe(t_tokenizer_state *ctx, char *line)
{
	return (emit_token(ctx, line, TOK_PIPE, 1));
}

int	dispatch_control_ops(t_tokenizer_state *ctx, char *line)
{
    char	c;
    char	n;

	c = line[ctx->pos];
	n = line[ctx->pos + 1];
    if (c == '|' && n == '|')
        return (handle_or(ctx, line));
    else if (c == '&' && n == '&')
        return (handle_and(ctx, line));
    else if (c == '|')
        return (handle_pipe(ctx, line));
    return (0);
}
