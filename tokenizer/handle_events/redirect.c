
/* tokenizer_redirections.c */
#include "tokenize.h"

static int	handle_heredoc(t_tokenizer_state *ctx, char *line)
{
	return (emit_token(ctx, line, TOK_HEREDOC, 2));
}

static int	handle_redir_append(t_tokenizer_state *ctx, char *line)
{
	return (emit_token(ctx, line, TOK_REDIR_APPEND, 2));
}

static int	handle_redir_in(t_tokenizer_state *ctx, char *line)
{
	return (emit_token(ctx, line, TOK_REDIR_IN, 1));
}

static int	handle_redir_out(t_tokenizer_state *ctx, char *line)
{
	return (emit_token(ctx, line, TOK_REDIR_OUT, 1));
}

int	dispatch_redirections(t_tokenizer_state *ctx, char *line)
{
	char	c;
	char	n;

	c = line[ctx->pos];
	n = line[ctx->pos + 1];
	if (c == '<' && n == '<')
		return (handle_heredoc(ctx, line));
	else if (c == '>' && n == '>')
		return (handle_redir_append(ctx, line));
	else if (c == '<')
		return (handle_redir_in(ctx, line));
	else if (c == '>')
		return (handle_redir_out(ctx, line));
	return (0);
}
