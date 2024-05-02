#include <sys/wait.h>

typedef struct s_tokens
{
	char	*cmd;
	char	*opt;
	char	*pth;
	char	*arg;
}		t_tokens;

// are pth and arg the same thing to Shell?

typedef struct s_berta
{
	int	argc;
	char	**argv;
	char	**envp;
	t_tokens *tokens;
}		t_berta;
