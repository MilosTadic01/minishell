# minishell

![output2](https://github.com/user-attachments/assets/5ac8626e-2686-438b-8222-3687f0cf42f0)

## Intro

### Aim
The goal of the project was to build a shell which abides by a long list of (rather rudimentary) expectations on one hand, but which at the same time should look up to the decades worth of features Bash shell as a role model. This has forced us as the developers to explore Bash extensively, but has at the same liberated us to selectively mimic those features of Bash which we deemed fun or important.

### Shell definition
A shell is a program which presents the computer user with a command line interface and which does three things in order to be useful:

<details>
	<summary>3 things</summary>

1. **Parsing**: It parses i.e. interprets the user input
2. **Execution**: It utilizes the resources of the OS...
	1. ...by performing system calls aka `syscalls` to the kernel for rudimentary operations like `read`, `write` or `open`
	2. ...by executing other utilities and programs such as `ls` or `wc`
3. **Redirection**: It performs input/output redirection

</details>

The result is a single-layer interface for a program, a shell, which can execute other programs and can manipulate the `i/o` of their respective executions.

### Example

`echo hello world | cat | wc -w`

<details>
	<summary>3 things that happen with this command</summary>

1. **Parsing**: A functional parser should, among other things, establish the following:
	1. `echo`, `cat` and `wc -w` are commands
	2. `hello world` is the argument vector of `echo`
	3. each `|` is a valid pipe, i.e. there is `i/o` taking place for each `|`
	4. `-w` is a flag/option of `wc` rather than its arg, i.e. `wc -w` is in its entirety a command
2. **Execution**: A functional shell should be able to establish that `echo` is a builtin, to locate the binaries of `cat` and `wc`, and to execute the three functions or otherwise inform the user if either is not possible (but still execute the rest). The shell user needn't know where either of the programs `echo` or `cat` or `wc` are located on the system.
3. **Redirection**: A functional shell should redirect the output of `echo hello world` to become the input of `cat` and the output thereof to become the input of `wc -w`.

</details>

## Features Overview

| Feature                    | Description and Example                                                                                                                                | Status |
| -------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------ | :----: |
| **Basic Commands**         | Execution of binaries like `ls`, `cat`.                                                                                                                |   ✅    |
| **Absolute Path Exec**     | `/bin/ls`                                                                                                                                              |   ✅    |
| **Built-in Commands**      | `cd`, `echo`, `pwd`, `exit`, `export`, `unset`, `env` without options.                                                                                 |   ✅    |
| **Parsing Errors**         | `<(`, `(`, `&&\|`, `'`, `"`, etc. Minishell does not prompt for closure of open pairs.                                                                 |   ✅    |
| **Redirections**           | input (`<`), output (`>`), heredoc (`<<`) and append (`>>`) redirections.                                                                              |   ✅    |
| **Environment Variables**  | Interfaced via `export` and `unset`.<br>`export TEST=55 TEST=99`                                                                                       |   ✅    |
| **Variable Expansion**     | `echo $TEST` prints `99`                                                                                                                               |   ✅    |
| **Expansions Execution**   | ➕ incl. pipelines and logical switches `export CMD="echo aa && echo bb"`. `$CMD` prints `aa` `bb`                                                      |   ✅    |
| **Logical Switching**      | Execution of the command to the right of the logical operator depends on the exit status of the command to its left (`&&`, <code>&#124;&#124;</code>). |   ✅    |
| **Logical Layering**       | When parenthesized expression `()`, its execution depends on any anteceding logical switch.                                                            |   ✅    |
| **Pipes**                  | `cat \| sort`; support for indefinite length pipeline                                                                                                  |   ✅    |
| **Signal Handling**        | Handles `SIGINT`, `SIGQUIT` in non-interactive mode, as well as for STDIN_FILENO prompting and heredoc prompting.                                      |   ✅    |
| **History**                | Command history and navigation.                                                                                                                        |   ✅    |
| **Error Handling**         | incl. exit statuses. `echo $?`                                                                                                                         |   ✅    |
| **Err and fd redirection** | `2>`, `&>`, `4096>`                                                                                                                                    |   ❌    |
| **Shell variables**        | `echo $SECONDS` (sec since the Shell was started)                                                                                                      |   ❌    |
| **Built-in variables**     | `echo $HISTSIZE`                                                                                                                                       |   ❌    |
| **Subshells**              | Execution in a child process when parentheses `()`.                                                                                                    |   ❌    |
| **Escaped Characters**     | Escaping is not interpreted as such `\n`, `\t`                                                                                                         |   ❌    |
| **Ansi C Expansion**       | `echo $'apple\nbanana'` prints `apple` `newline` `banana`                                                                                              |   ❌    |
| **Wildcards \* **          | `rm \*.c`                                                                                                                                              |   ❌    |
| **Backgrounding**          | Background a process with `&`.                                                                                                                         |   ❌    |
| **Pipes through ()**       | Yes: `ls \| (cat) \| cat`. No: `(echo aa && echo bb) \| cat`.                                                                                          |   🚧   |

### Legend
- ✅ Implemented and tested.
- 🚧 In Progress: implemented for learning purposes but not entirely Bash-like.
- ❌ Not Implemented.

## Navigating the massive lore of Bash shell

### Formal docs
* [The GNU Bash manual](https://www.gnu.org/software/bash/manual/)
* [The Open Group Base Secifications Issue 7, 2018 Edition. IEEE Std 1003.1-2017. The definition of the Shell Command Language](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html) 

### Understanding Bash / referencing specific commands

* `type <cmd>` - what would get executed by Shell if `<cmd>` were part of the command
  * `type -a <cmd>` - show all possibilities for execution, whereas the top one will get executed if not otherwise specified
* `help <cmd>` - the "man pages" for Shell builtins specifically
* `man <cmd>` vs `info <cmd>` - ultimately, just try both, often they'll even end up pointing to the same file, but other times one or the other may have useful additional info
* compgen - a milion options, a milion useful printouts
  * `compgen -b` - list the builtin cmds of this shell
  * `compgen -v` - list the builtin vars of this shell
  * `compgen -a` - list the aliases of this shell

## Control flow
parsing, execution

### Parsing
extract_tokens(char ***input_string**)
 * `in` is a struct meant to blow up to hold **input_string** as well as other info:
 * ```C
   in->current_position = 0;
   in->input = input_string;
   in->current_char = in->input[in->current_position]; // i.e. 0?
   in->quotations = DEFAULT; // i.e. 0
   ```
 * `token` is gonna get created one at a time:
   * if | or ||
   * else if & or &&
   * else if < or <<
   * else if > or >>
   * else it's a literal

## Authorized functions

| man section | meaning                                               |
| :---------: | :---------------------------------------------------- |
|      1      | user commands (Shell commands)                        |
|      2      | system calls                                          |
|      3      | library functions                                     |
|      4      | special files (usually found in /dev), drivers        |
|      5      | file formats and conventions                          |
|      6      | games and screensavers                                |
|      7      | miscellaneous (incl. macro packages and conventions)  |
|      8      | System Administration topics, incl. sysadmin commands |
|      9      | Kernel developer's manual (non-standard)              |
|   rl_lib    | rl_lib                                                |
`apropos -s X .` - replace `X` with a digit to query for entries in that man section on your system

* readline(3) - gnl, but official. [Programming with GNU readline](https://web.mit.edu/gnu/doc/html/rlman_2.html)
  * #include 
    * <stdio.h>
    * <readline/readline.h>
    * <readline/history.h>
  * rl_clear_history(rl lib) - void rl_clear_history (void); Clear the history list by deleting all of the entries, in the same manner as the History library’s clear_history() function. This differs from clear_history because it frees private data Readline saves in the history list.
  * rl_on_new_line(rl lib) - int rl_on_new_line (void); Tell the update functions that we have moved onto a new (empty) line, usually after outputting a newline.
  * rl_replace_line(rl lib) - void rl_replace_line (const char \*text, int clear_undo); Replace the contents of rl_line_buffer with text. The point and mark are preserved, if possible. If clear_undo is non-zero, the undo list associated with the current line is cleared.
  * rl_redisplay(rl lib) - void rl_redisplay(void); Change what’s displayed on the screen to reflect the current contents of rl_line_buffer.
  * add_history(rl lib) - void add_history(line); add_history (line); If you want the user to be able to get at the line later, (with C-p for example), you must call add_history() to save the line away in a history list of such lines.
* printf(3)
* malloc(3)
* free == malloc(3) man page
* write(2)
* access(2)
  * int access(const char *pathname, int mode);
  * #include
    * <unistd.h>
    * <fcntl.h>           /* Definition of AT_* constants */
    * <unistd.h>
* open(2)
* read(2)
* close(2)
* fork(2)
* wait(2)
* waitpid == wait(2)
* wait4(2)
* wait3 == wait4(2)
* man signal(2) - ANSI C signal handling
* man sigaction(2) - examine and change a signal action
  * int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
* sigsetops(3)
  * sigemptyset - initializes the signal set given by set to empty, with all signals excluded from the set.
  * sigaddset - sigaddset() and sigdelset() add and delete respectively signal signum from set.
* kill(2)
* exit(3) - or could they be meaning exit(2)? Seems unlikely
* getcwd(3)
* chdir(2)
* stat(2) - get file status
  * stat - int stat(const char *pathname, struct stat *statbuf);
  * fstat - int fstat(int fd, struct stat *statbuf);
  * lstat - int lstat(const char *pathname, struct stat *statbuf);
* unlink(2) - delete a name and possibly the file it refers to
* execve(2) - execute a function
* dup(2)
  * dup - int dup(int oldfd);
  * dup2 - int dup2(int oldfd, int newfd);
* pipe(2)
* opendir(3)
* readdir(3)
* closedir(3)
* strerror(3)
* perror(3)
* isatty(3) - test whether a file descriptor refers to a terminal
* ttyname(3)
* ttyslot(3)
* ioctl(2) - manipulates/controls the underlying device parameters of special files.
* getenv(3) - get an env variable
* termios(3) - The  termios  functions  describe a general terminal interface that is provided to control asynchronous communication ports.
  * tcsetattr -
  * tcgetattr - 
* tgetent(3) - access&parse the system's terminfo database. Query the capabilities of your terminal.
  * #include <term.h> (potentially also #include <curses.h>)
  * tgetent - loads the entry for *name*.
    * int tgetent(char *bp, const char *name);
  * tgetflag - gets the boolean entry for *id*, or zero if it is not available.
    * int tgetflag(char *id);
  * tgetnum - gets the numeric entry for *id*, or -1 if it is not available.
    * int tgetnum(char *id);
  * tgetstr - returns the string entry for id, or zero if it is not available. Use tputs to output the returned string.
    * char *tgetstr(char *id, char **area);
  * tgoto - instantiates the parameters into the given capability. The output from this routine is to be passed to tputs.
    * char *tgoto(const char *cap, int col, int row);
  * tputs - described on the curs_terminfo(3X) manual page. It can retrieve capabilities by either termcap or terminfo name. 
    * int tputs(const char *str, int affcnt, int (*putc)(int));
