#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

char	*ft_pwd(void)
{
	char	buff[4096];
	char	*pwd;

	pwd = getcwd(buff, 4096);
	if (pwd == NULL)
	{
		printf("%s", strerror(errno), 2);
		return NULL;
	}
	return (pwd);
}

int main(void)
{
    chdir("../.././//./././///./sources/../../");
    printf("%s\n", ft_pwd());
    printf("%s\n", getenv("PWD"));
    printf("%s\n", ft_pwd());
    // export
}