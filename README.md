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

## Authorized functions

1 - user commands
2 - system calls
3 - library functions
8 - sysadmin commands
rl_lib - rl_lib

* readline(3) - gnl, but official
* rl_clear_history(rl lib) - void rl_clear_history (void); Clear the history list by deleting all of the entries, in the same manner as the History library’s clear_history() function. This differs from clear_history because it frees private data Readline saves in the history list.
* rl_on_new_line(rl lib) - int rl_on_new_line (void); Tell the update functions that we have moved onto a new (empty) line, usually after outputting a newline.
* rl_replace_line(rl lib) - void rl_replace_line (const char \*text, int clear_undo); Replace the contents of rl_line_buffer with text. The point and mark are preserved, if possible. If clear_undo is non-zero, the undo list associated with the current line is cleared.
* rl_redisplay(rl lib) - void rl_redisplay(void); Change what’s displayed on the screen to reflect the current contents of rl_line_buffer. 
* add_history(rl lib) - void add_history(line); add_history (line); If you want the user to be able to get at the line later, (with C-p for example), you must call add_history() to save the line away in a history list of such lines.
* printf(3)
* getent(1) - get entries from Name Service Switch libraries
