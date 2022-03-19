#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>

int makeDIR(char *new_directory_name) {
    struct stat sb;

    if(stat(new_directory_name, &sb) == -1) {
        pid_t pid = fork();
        int result = 0;

        if(pid == 0) {
            result = execl("/bin/mkdir", "mkdir", new_directory_name, NULL);
           
            if(result == -1) {
                printf("mkdir %s failed\n", new_directory_name);
            }

            exit(result);
        } else {
            if(wait(&result) == -1) perror("Wait failed\n");
            else if(result == 0) {
                printf("New directory %s created\n", new_directory_name);

                return 0;
            }
        }
    } else {
        printf("Directory %s already exist\n", new_directory_name);

        return 1;
    }

    return -1;
}

int main() {
    makeDIR("darat");
    makeDIR("air");

    return 0;
}
