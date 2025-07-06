
#include "tokenize.h"

static void	handle_quote(t_tokenizer_state *ctx, char *line, char quote)
{
	ctx->pos++;
	ctx->current.start = ctx->pos;
	while (line[ctx->pos] && line[ctx->pos] != quote)
		ctx->pos++;
	if (line[ctx->pos] == quote)
	{
		ctx->current.length = ctx->pos - ctx->current.start;
		create_token(ctx, line);
		ctx->pos++;
	}
	else
		tokenizer_error(ERR_UNCLOSED_QUOTE);
}

int	quote_handler(t_tokenizer_state *ctx, char *line)
{
	char	c;

	c = line[ctx->pos];
	if (c == '\'')
	{
		ctx->current.type = TOK_SQUOTE;
		handle_quote(ctx, line, c);
		return (1);
	}
	else if (c == '"')
	{
		ctx->current.type = TOK_DQUOTE;
		handle_quote(ctx, line, c);
		return (1);
	}
	return (0);
}
