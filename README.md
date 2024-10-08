CS 425 Project 1: A Simple Unix Shell(100 pts)
part 1: due at 11:59pm on 09/24/24
part 2: due at 11:59pm on 10/08/24
This project consists of modifying a C program which serves a shell interface that accepts user com-
mands and then executes each command in a separate process. A shell interface provides the user a
prompt after which the next command is entered. The example below illustrates the prompt sh> and the
user’s next command: cat prog.c. This command displays the file prog.c on the terminal using the Unix
cat command.
sh> cat prog.c
One technique for implementing a shell interface is to have the parent process first read what the user
enters on the command line (i.e. cat prog.c), and then create a separate child process that performs the
command. Unless otherwise specified, the parent process waits for the child to exit before continuing.
However, Unix shells typically also allow the child process to run in the background– or concurrently–as
well by specifying the ampersand (&) at the end of the command. By rewriting the above command as
sh> cat prog.c &
the parent and child processes now run concurrently.
The project is organized into two parts: (1) Design the behavior of an Unix Shell; (2) Implement a
simple Unix Shell.
1 (10 pts) Design the Behavior of an Unix Shell
An Unix Shell basically is a loop that repeatedly do the following actions:
• presents a prompt, say sh> and waits for the user to enter a command line;
• parses the command line into an array, say args. For example, if the user enters ls -l at the sh->
prompt, args[0] becomes equals to the string ls, and args[1] is set to the string to -l;
• create a new process space by the system call fork();
• load the user command (an executable code) by the system call exec();
One trick in the execution of a user command in a Unix Shell is the distinction of foreground and
background of the command by checking whether there is an “&” system at the end of the command
line. If yes, it is supposed to be a background execution, otherwise, a foreground execution. For a
foreground command, the shell should wait the completion of the user command before it presents a
new prompt; for a background commnad, the shell does not wait. Draw a flowchart to design a unix
shell. The design should be clear enough to begin coding, i.e., the implementation of the shell.
The following is a checklist for a good design:
• correct use of graphical symbols, such as diamond, rectangle
• loop structure and no deadend link
1
• major actions included
• correct positions of fork() and exec()
• distinction of parent and child
• distinction of parent-wait and parent-don’t-wait
2 (90 pts) Implement a Simple Unix Shell
Based on the above design, you now need to implement a simple Unix Shell that can execute command
lines input by a user. A significant portion of time will be spent on command line parsing.
As mentioned in the lecture, Unix uses the system call exec() to load a user code (executable) to the
space of the calling process. excevp() is a version of exec() that has the following interface:
execvp(char *command, char *params[]);
where command represents the command to be performed and params stores the parameters to this
command. A typical example of calling excevp() is execvp(args[0], args); be sure to check the value of
background to determine if the parent process is to wait for the child to exit or not.
The following is a checklist for your implementation:
• parse user command lines (20 pts)
• loop in shell process (20 pts)
• position and call of fork() (10 pts)
• position and call of exec() (10 pts)
• branch on return value of fork(), i.e., the pid variable (10 pts)
• handling & (20 pts)
