---

# Simple Shell

This project is a simple UNIX command-line interpreter developed as part of the Holberton School curriculum. It demonstrates basic shell functionalities including process management, command execution, and environment handling.

## Table of Contents

1. [Features](#features)
2. [Installation](#installation)
3. [Usage](#usage)
4. [Concepts](#concepts)
   - [Processes](#processes)
   - [Forking and Execution](#forking-and-execution)
   - [Environment](#environment)
5. [Built-in Commands](#built-in-commands)
6. [Contributing](#contributing)
7. [Authors](#authors)
8. [License](#license)

## Features

- Process Management: Retrieve and display the current process ID (PID) and parent process ID (PPID).
- Command Execution: Execute commands using execve and manage multiple child processes.
- Argument Handling: Process and display command-line arguments.
- Environment Handling: Access and display environment variables.
- File Operations: Use stat to check file existence and find files in the PATH.

## Installation

Clone the repository:

```bash
git clone https://github.com/yourusername/holbertonschool-simple_shell.git
cd holbertonschool-simple_shell
```

Compile the shell:

```bash
gcc -Wall -Wextra -Werror -pedantic *.c -o hsh
```

## Usage

To start the shell, execute:

```bash
./hsh
```

You will see a prompt `#cisfun$ ` waiting for your commands. Type commands as you would in a standard shell and press enter to execute.

```bash
#cisfun$ ls -l
#cisfun$ pwd
#cisfun$ cd /path/to/directory
#cisfun$ echo "Hello, World!"
#cisfun$ exit
```

## Concepts

### Processes

A process is an instance of an executing program. Each process has a unique process ID (PID), which is used for various system interactions. The `getpid` system call retrieves the current process ID, and `getppid` retrieves the parent process ID.

```c
#include <stdio.h>
#include <unistd.h>

int main(void)
{
    pid_t my_pid;
    pid_t my_ppid;

    my_pid = getpid();
    my_ppid = getppid();
    printf("PID: %u, PPID: %u\n", my_pid, my_ppid);
    return (0);
}
```

### Forking and Execution

The `fork` system call creates a new process by duplicating the existing process. The new process is known as the child process. The `execve` system call replaces the current process image with a new program image, effectively running a new program within the same process.

```c
#include <stdio.h>
#include <unistd.h>

int main(void)
{
    pid_t pid = fork();

    if (pid == -1)
    {
        perror("Error:");
        return (1);
    }
    else if (pid == 0)
    {
        char *argv[] = {"/bin/ls", "-l", NULL};
        execve(argv[0], argv, NULL);
        perror("execve");
    }
    else
    {
        wait(NULL);  // Wait for the child process to finish
    }
    return (0);
}
```

### Environment

Each process has an environment, a set of strings that define the current state. The shell can access the environment variables and modify them. When a new process is created, it inherits a copy of its parent’s environment.

```c
#include <stdio.h>

int main(int ac, char **av, char **env)
{
    unsigned int i = 0;

    while (env[i] != NULL)
    {
        printf("%s\n", env[i]);
        i++;
    }
    return (0);
}
```
## Exercises and Implementations
## 1. PID and PPID
- Program to print the PID of the current process: Use getpid() to retrieve and display the process ID.
- Program to print the PID of the parent process: Use getppid() to retrieve and display the parent process ID.
## 2. Command Line Arguments
- Print all command-line arguments: Implement a function that prints all arguments passed to the program without using ac.
## 3. Read Line
- Prompt for user input: Write a program that displays a prompt ($ ), waits for the user to enter a command, and prints the entered command.
## 4. Command Execution
- Execute a command: Use execve to run a command (/bin/ls -l /tmp) in a child process. Handle multiple child processes and wait for each to exit before creating a new one.
## 5. Find a File in PATH
- Locate files in PATH: Write a program that searches for files in the directories listed in the PATH environment variable.

## Advanced Features
- Custom getline: Implement your own version of the getline function to read user input.
- String Splitting Without strtok: Write a function to split a string into words without using strtok.


## Files
- shell.c: Main source file for the shell implementation.
- pid.c: Example of using getpid() to retrieve the process ID.
- ppid.c: Example of using getppid() to retrieve the parent process ID.
- exec.c: Demonstrates the usage of execve.
- fork.c: Shows how to create child processes using fork.
- wait.c: Example of using wait to wait for child processes.
- stat.c: Demonstrates file status checking using stat.
- env-main.c: Prints the environment variables.
- prompt.c: Example of reading user input using getline.

## Man Page
Refer to man_1_simple_shell for detailed documentation on the simple_shell command.

## Built-in Commands

- **cd**: Change the current directory.
- **exit**: Exit the shell.
- **env**: Display the environment variables.

## Contributing

Contributions to this project are welcome. To contribute:

1. Fork the repository.
2. Create a new branch for your feature or bug fix.
3. Commit your changes with descriptive commit messages.
4. Push your changes to your fork.
5. Create a pull request to the main repository.

## Authors

- Sabillva <https://github.com/Sabillva>
- Sadatnazarli <https://github.com/sadatnazarli>

## License

This project is open-source and available under the MIT License. See the LICENSE file for more information.

