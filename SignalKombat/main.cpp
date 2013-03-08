//
//  main.cpp
//  SignalKombat
//
//  Created by THIERY Adrien et (ALAY-EDDINE Maxime) on 08/03/13.
//

#include <stdio.h> /* printf et perror */
#include <sys/types.h> /* fork et getpid */
#include <sys/uio.h>
#include <unistd.h>
#include <pthread.h>

int pidResults[60];

/*void check_pid() {
    int pid;
    int fdsCommandeBash[2]; // Récupèrera les flux de sortie des forks
    int fdsLecturePid[2]; // File Descriptor principal
    FILE * fdsToRead;
    if(pipe(fdsCommandeBash) < 0) {
        perror("pipe");
    }
    if (pipe(fdsLecturePid) < 0) {
        perror("pipe2");
    }
    if ((pid = fork()) < 0){
		perror("fork");
    }
    if (pid != 0) { // Processus principal
        close(fdsLecturePid[1]);
        close(fdsCommandeBash[0]);
        close(fdsCommandeBash[1]);
        fdsToRead = fdopen(fdsLecturePid[0], "r"); // On lit la sortie du pipe fds2
        if (fdsToRead == NULL) {
            perror("fdopen");
        }
        else { // Si quelque chose y est écrit, on le lit et on le met dans un tableau
            int i = 0;
            while(!feof(fdsToRead)) {
                fscanf(fdsToRead, "%d", &pidResults[i]);
                i++;
            }
            fclose(fdsToRead);
            for(int j = 0; j<i; j++) { // Vérification des données du tableau
                printf("%d\n", pidResults[j]);
            }
        }
    }
    else {
        int pid2;
        if ((pid2 = fork()) < 0) {
            perror("fork2");
        }
        if (pid2 == 0){ // Processus fils 1
            close(fdsCommandeBash[0]);
            close(fdsLecturePid[0]);
            close(fdsLecturePid[1]);
            dup2(fdsCommandeBash[1], 1); // On redirige la sortie standard sur l'entrée du pipe Bash
            execl("/bin/ps", "ps", "ux", NULL);
        }
        else { // Processus fils 2
            close(fdsCommandeBash[1]);
            close(fdsLecturePid[0]);
            dup2(fdsCommandeBash[0], 0); // On redirige l'entrée standard sur la sortie du pipe Bash
            dup2(fdsLecturePid[1], 1); // On redirige la sortie standard sur l'entrée du pipe LecturePid
            execl("/usr/bin/awk", "awk", "/bash/ && !/awk/ {print $2}", NULL);
        }
    }
}*/

int main(int argc, const char * argv[])
{
    /*pthread_t threadCheckPid;
    pthread_create(&threadCheckPid, NULL, (void *)&check_pid, NULL);
    pthread_join(threadCheckPid,NULL);*/
    int pid;
    int fdsCommandeBash[2]; // Récupèrera les flux de sortie des forks
    int fdsLecturePid[2]; // File Descriptor principal
    FILE * fdsToRead;
    if(pipe(fdsCommandeBash) < 0) {
        perror("pipe");
    }
    if (pipe(fdsLecturePid) < 0) {
        perror("pipe2");
    }
    if ((pid = fork()) < 0){
		perror("fork");
    }
    if (pid != 0) { // Processus principal
        close(fdsLecturePid[1]);
        close(fdsCommandeBash[0]);
        close(fdsCommandeBash[1]);
        fdsToRead = fdopen(fdsLecturePid[0], "r"); // On lit la sortie du pipe fds2
        if (fdsToRead == NULL) {
            perror("fdopen");
        }
        else { // Si quelque chose y est écrit, on le lit et on le met dans un tableau
            int i = 0;
            while(!feof(fdsToRead)) {
                fscanf(fdsToRead, "%d", &pidResults[i]);
                i++;
            }
            fclose(fdsToRead);
            for(int j = 0; j<i; j++) { // Vérification des données du tableau
                printf("%d\n", pidResults[j]);
            }
        }
    }
    else {
        int pid2;
        if ((pid2 = fork()) < 0) {
            perror("fork2");
        }
        if (pid2 == 0){ // Processus fils 1
            close(fdsCommandeBash[0]);
            close(fdsLecturePid[0]);
            close(fdsLecturePid[1]);
            dup2(fdsCommandeBash[1], 1); // On redirige la sortie standard sur l'entrée du pipe Bash
            execl("/bin/ps", "ps", "ux", NULL);
        }
        else { // Processus fils 2
            close(fdsCommandeBash[1]);
            close(fdsLecturePid[0]);
            dup2(fdsCommandeBash[0], 0); // On redirige l'entrée standard sur la sortie du pipe Bash
            dup2(fdsLecturePid[1], 1); // On redirige la sortie standard sur l'entrée du pipe LecturePid
            execl("/usr/bin/awk", "awk", "/bash/ && !/awk/ {print $2}", NULL);
        }
    }
    return 0;
}

