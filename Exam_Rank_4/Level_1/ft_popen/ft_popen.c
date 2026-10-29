# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>

int ft_popen(const char *file, char const **av, char type)
{
    // Partsing - Valid paramaters
    if (!file || !av || (type != 'w' && type != 'r'))
        return (-1);

    // Create pipe
    
    int pipefd[2]; // Declare one pipe for father process and other for child proocess

    if (pipe(pipefd) == -1)
        return (-1);

    // Fork

    pid_t pid = fork()
    if (pid == -1)
        return(close(pipefd[0], close(pipefd[1]), -1));

    // Child 

    if (pid == 0)
    {
        if (type == 'r')
        {
            close(pipefd[0]);
            dup2(pipefd[1], 1);
            close(pipefd[1]);
        }
        else
        {
            close(pipefd[1]);
            dup2(pipefd[0], 0);
            close(pipefd[0]);
        }
        execvp(file, av);
        exit(1);
    }

    // Father process

    if (type == 'r')
    {
        close(pipefd[1]);
        return (pipefd[0]);
    }
    else
    {
        close(pipefd[0]);
        return (pipefd[1]);
    }
}
