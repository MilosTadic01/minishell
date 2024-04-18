# minishell
write a shell in C

let's break it

## Navigating the massive knowledge of Shell

### Formal docs

* [The Open Group Base Secifications Issue 6. IEEE Std 1003.1, 2004 Edition. The definition of the Shell Command Language](https://pubs.opengroup.org/onlinepubs/009604499/utilities/xcu_chap02.html) (Note that 1003.2 is actually the issue that might be more relevant to Bash, though I forgot why)
* [The GNU Bash manual](https://www.gnu.org/software/bash/manual/)

### Referencing specific commands (nav)

* `type <cmd>` - what would get executed by Shell if `<cmd>` were part of the command
  * `type -a <cmd>` - show all possibilities for execution, whereas the top one will get executed if not otherwise specified
* `help <cmd>` - the "man pages" for Shell builtins specifically
* `man <cmd>` vs `info <cmd>` - ultimately, just try both, often they'll end up being the same
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

man section | meaning
:---: | :---
1 | user commands (Shell commands)
2 | system calls
3 | library functions
7 | miscellaneous (file formats)
8 | System Administration topics, incl. sysadmin commands
9 | Kernel developer's manual
rl_lib | rl_lib

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
