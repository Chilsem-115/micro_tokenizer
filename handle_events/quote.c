
#include "tokenize.h"

void	handle_quote(t_tokenizer_state *ctx, char *line, char quote)
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
