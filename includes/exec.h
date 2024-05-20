/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:32:26 by dzubkova          #+#    #+#             */
/*   Updated: 2024/05/20 17:32:27 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# define MAX_GOS 10000

# include "minishell.h"

typedef struct s_exe
{
	int		exit_st;
	int		heredocs_need_execution;
	t_ast	*s;
	t_list	**env;
	int		i;
	int		hd_count;
	int		hd_idx;
	int		*hd_fds;
	int		fd_redir_in;
	int		fd_redir_out;
	char	**hd_delimiters;
	int		is_pipeline;
	int		subshell_lvl;
	int		subshell_do[MAX_GOS];
	int		ppl_cmd_count;
	int		pp_fds[2][2];
	pid_t	smpl_cmd_pid;
	pid_t	*ppl_pids;
	int		smpl_wstatus;
	int		*ppl_wstatuses;
	char	**my_paths;
	char	*execve_path;
	char	**execve_argv;
	char	**execve_envp;
	int		log_op;
}			t_exe;

enum	e_bltn
{
	ECHO = 1,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT
}	;

// exec_main.c
int		exec(t_ast *s, char *subcmd, t_exe *b);
// init_exe_bus.c
void	big_init_exe_bus_with_ast(t_ast *s, t_exe *exe_bus);
void	pre_ast_init_exe_bus(t_exe *exe_bus, t_list **my_env);
// traversal.c
void	traverse_ast_to_exec(t_ast *s, t_exe *b);
// traversal_utils.c
int		which_builtin(char *str);
void	close_pipes_and_wait_and_reset_pipeline(t_exe *b);
void	increment_hd_idx(t_ast *s, t_exe *b);
// heredoc_boss.c
int		exec_heredocs(t_exe *exe_bus);
void	free_heredocs(t_exe *exe_bus);
// heredoc_count_n_fetch.c
int		count_heredocs(t_ast *s, t_exe *b);
void	fetch_hd_delimiters(t_ast *s, t_exe *b);
// heredoc_prompting.c
void	prompt_for_all_heredocs(t_exe *exe_bus);
// exec_builtin.c
void	exec_builtin(int builtin, t_ast *s, t_exe *b);
// exec_bin.c
void	exec_bin(t_ast *s, t_exe *b);
// bin_prep_execve_args.c
void	prep_execve_args(t_ast *s, t_exe *b);
// bin_path_setup.c
void	seek_path(t_exe *b);
// pipeline_setup.c
void	set_up_pipeline(t_ast *s, t_exe *b);
// pipe_fu_parent.c
int		reuse_pipe_in_parent(t_exe *b);
void	pipe_closer(t_exe *b);
// pipe_fu_children.c
void	lay_child_pipes(t_exe *b);
// wait_pipeline.c
void	go_wait(t_exe *b);
// redir_setup.c
void	set_up_redirs(t_ast *s, t_exe *b);
// redir_ins_setup.c
void	infile_legitimacy_control(t_ast *s, t_exe *b, int hd_count);
int		count_hds_in_this_cmd(t_ast *s);
int		open_and_close_infiles_while_legit(t_ast *s, t_exe *b, int hd_count);
// redir_outs_setup.c
int		try_opening_all_outfiles(t_ast *s, t_exe *b);
// redir_duping_child.c
int		slap_on_redirs_in_child(t_ast *s, t_exe *b);
// redir_utils.c
void	clean_up_after_redirs_in_parent(t_exe *b);
// exec_utils.c
void	fork_one_for_simple_cmd(t_exe *b);
void	fork_one_in_ppl(t_exe *b);
void	free_strarr(char **strarr);
void	free_n_error_n_exit(char *errprefix, t_exe *b);

#endif