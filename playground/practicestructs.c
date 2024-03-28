#include <stdio.h>
#include <stdlib.h>

typedef struct	s_vals
{
	int	valsnum;
	int	*valsnump;
	char	valschr;
	char	*valsstr;
	char	**valsstrarr;
}	t_vals;

typedef struct	s_valsp
{
	int	valspnum;
	int	*valspnump;
	char	valspchr;
	char	*valspstr;
	char	**valspstrarr;
}	t_valsp;

typedef struct s_data
{
	int	num;
	int	*nump;
	char	chr;
	char	*str;
	char	**strarr;
	int	intarrst[3];
	int	*intarrhp;
	t_vals	vals;
	t_valsp	*valsp;
}	t_data;

// already here 'data' must be ptr to struct, else changes not reflected outside;
// also meaning 'data.num' syntax useless: must use data->num, because 'data' == ptr to struct
void	init_data(t_data *data)
{
	data->num = 1;
	data->nump = malloc(sizeof(int));
	*data->nump = 11;
	data->chr = 'a';
	data->str = malloc(sizeof(char) * 3);
	*data->str = 'H';
	data->str[1] = 'i';
	data->str[2] = 0;
	data->strarr = malloc(sizeof(char *) * 3);
	data->strarr[0] = malloc(sizeof(char) * 2);
	data->strarr[1] = malloc(sizeof(char) * 2);
	data->strarr[0][0] = 'H';
	data->strarr[0][1] = 0;
	data->strarr[1][0] = 'M';
	data->strarr[1][1] = 0;
	data->strarr[2] = NULL;
	data->intarrst[0] = 1;
	data->intarrst[1] = 2;
	data->intarrst[2] = 3;
	data->intarrhp = malloc(sizeof(int) * 3);
	data->intarrhp[0] = 11;
	data->intarrhp[1] = 12;
	data->intarrhp[2] = 13;

	data->vals.valsnum = 1;
	data->vals.valsnump = malloc(sizeof(int));
	*data->vals.valsnump = 11;
	data->vals.valschr = 'a';
	data->vals.valsstr = malloc(sizeof(char) * 3);
	data->vals.valsstr[0] = 'H';
	data->vals.valsstr[1] = 'i';
	data->vals.valsstr[2] = 0;
	data->vals.valsstrarr = malloc(sizeof(char *) * 3);
	data->vals.valsstrarr[0] = malloc(sizeof(char) * 2);
	data->vals.valsstrarr[1] = malloc(sizeof(char) * 2);
	data->vals.valsstrarr[0][0] = 'H';
	data->vals.valsstrarr[0][1] = 0;
	data->vals.valsstrarr[1][0] = 'M';
	data->vals.valsstrarr[1][1] = 0;
	data->vals.valsstrarr[2] = NULL;
}

int	main(void)
{
	t_data	data;

	init_data(&data);
	printf("Init data complete\n");
	printf("data.num is %d\n", data.num);
	printf("*data.nump has %d\n", *data.nump); // just...same behavior as int *ptr. Must deref.
	printf("data.chr is %c\n", data.chr);
	printf("*data.str is %c\n", *data.str);	// cmp this...
	printf("data.str has %s\n", data.str);	// ...to this. Bc %s won't work if *data.str. Wth.
	printf("data.strarr[0] has %s\n", data.strarr[0]);
	printf("data.strarr[1] has %s\n", data.strarr[1]);
	printf("data.intarrst[0] has %d\n", data.intarrst[0]);
	printf("data.intarrst[1] has %d\n", data.intarrst[1]);
	printf("data.intarrst[2] has %d\n", data.intarrst[2]);
	printf("data.intarrhp[0] has %d\n", data.intarrhp[0]);
	printf("data.intarrhp[1] has %d\n", data.intarrhp[1]);
	printf("data.intarrhp[2] has %d\n\n", data.intarrhp[2]);
	printf("data.vals.valsnum is %d\n", data.vals.valsnum);
	printf("*data.vals.valsnump has %d\n", *data.vals.valsnump);
	printf("data.vals.valschr is %c\n", data.vals.valschr);
	printf("data.vals.valsstr has %s\n", data.vals.valsstr); // ...caught off guard again. Not *
	printf("data.vals.valsstrarr[0] has string %s\n", data.vals.valsstrarr[0]);
	printf("data.vals.valsstrarr[1] has string %s\n", data.vals.valsstrarr[1]);
	

	free(data.nump);
	free(data.str);
	free(data.strarr[0]);
	free(data.strarr[1]);
	free(data.strarr);
	free(data.intarrhp);
	free(data.vals.valsnump);
	free(data.vals.valsstr);
	free(data.vals.valsstrarr[0]);
	free(data.vals.valsstrarr[1]);
	free(data.vals.valsstrarr);
}
