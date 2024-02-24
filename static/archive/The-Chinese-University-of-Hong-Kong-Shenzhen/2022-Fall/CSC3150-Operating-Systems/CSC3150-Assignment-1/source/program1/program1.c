#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
        /* fork a child process */
        printf("Process start to fork\n");

        pid_t process_id = fork();

        /* execute test program */
        if (process_id == -1) {
                perror("error");

        } else if (process_id == 0) {
                int idx = 1;
                char *arg[argc];

                printf("I'm the Child Process, my pid = %d\n", getpid());

                while (idx <= argc - 1) {
                        arg[idx - 1] = argv[idx];
                        ++idx;
                }
                arg[idx - 1] = NULL;

                printf("Child process start to execute test program:\n");

                execve(arg[0], arg, NULL);

                perror("execve");

                exit(EXIT_FAILURE);

        } else {
                int stat;

                printf("I'm the Parent Process, my pid = %d\n", getpid());

                /* wait for child process terminates */
                (void)waitpid(process_id, &stat, WUNTRACED);

                printf("Parent process receives SIGCHLD signal\n");

                /*      check child process
            termination status */
                if (WIFEXITED(stat)) {
                        printf("Normal termination with EXIT STATUS = %d\n",
                               WEXITSTATUS(stat));

                } else if (WIFSIGNALED(stat)) {
                        int event = WTERMSIG(stat);
                        char signals[16][8] = { "",     "SIGHUP",  "SIGINT",
                                                "SIGQUIT", "SIGILL",  "SIGTRAP",
                                                "SIGABRT", "SIGBUS",  "SIGFPE",
                                                "SIGKILL", "",  "SIGSEGV",
                                                "",     "SIGPIPE", "SIGALRM",
                                                "SIGTERM" };
                        char reasons[16][20] = { "",
                                                 "hang up signal",
                                                 "interrupt signal",
                                                 "quit signal",
                                                 "illegal instruction",
                                                 "trap signal",
                                                 "abort signal",
                                                 "bus signal",
                                                 "floating",
                                                 "kill signal",
                                                 "",
                                                 "segmentation fault",
                                                 "",
                                                 "pipe signal",
                                                 "alarm signal",
                                                 "termination signal" };

                        if (event > 15) {
                                exit(1);
                        } else {
                                printf("Child process receives %s signal\n",
                                       signals[event]);
                                printf("Child process is terminated due to "
                                       "%s\n",
                                       reasons[event]);
                        }

                        printf("CHILD PROCESS FAILED\n");

                } else if (WIFSTOPPED(stat)) {
                        printf("Child process receives SIGSTOP signal\n");
                        
                        printf("CHILD PROCESS STOPPED\n");

                } else {
                        printf("CHILD PROCESS CONTINUED\n");
                }

                exit(0);
        }

        return 0;
}