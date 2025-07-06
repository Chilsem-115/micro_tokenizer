
#include "tokenize.h"

void	create_token(t_tokenizer_state *ctx, char *line)
{
	ctx->tokens[ctx->count] = strndup(&line[ctx->current.start],
			ctx->current.length);
	if (!ctx->tokens[ctx->count])
		tokenizer_error(ERR_MEMORY);
	ctx->count++;
}

void	ctx_init(t_tokenizer_state *ctx)
{
	ctx->pos = 0;
	ctx->count = 0;
	ctx->tokens = malloc(sizeof(char *) * (MAX_TOKENS + 1));
	if (!ctx->tokens)
		tokenizer_error(ERR_MEMORY);
}

/* NOTE: this fuction is unsafe, its not recommended to send NULL or an empty string */
char	**tokenize(char *line)
{
	t_tokenizer_state	ctx;

	ctx_init(&ctx);
	while (line[ctx.pos])
	{
		while (isspace(line[ctx.pos]))
			ctx.pos++;
		if (!line[ctx.pos])
			break ;
		if (quote_handler(&ctx, line) || operator_handler(&ctx, line) ||
				env_handler(&ctx, line))
			continue ;
		word_handler(&ctx, line);
	}
	ctx.tokens[ctx.count] = NULL;
	return (ctx.tokens);
}
