#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>


void benchmarkReaddir(char * dirName, int nFiles,timer* t, recorder* r)
{
    int i,err;
    
	//Creation des fichiers dans le dossier
    for(i = 0; i< nFiles; i++){
        
        char str[15];
        sprintf(str, "%d", i);
        strcat(str,"test.txt");
        
        char str2[20] = "temp/";
        strcat(str2,str);
        
        int fd = creat(str2,S_IWUSR|S_IRUSR);
        if(fd==-1){
            perror("open");
            exit(EXIT_FAILURE);
        }
    }
    
    //Ouverture du dossier
    DIR *dirp;
    struct dirent *dp;
    
    dirp = opendir(dirName);
    if(dirp==NULL) {
        perror("opendir");
        exit(EXIT_FAILURE);
    }
    
	
	//lance le timer
	start_timer(t);
    while ((dp = readdir(dirp)) != NULL) {
        //ne fait rien
    }
	//on ecrit le temps moyen pour nfile fichiers, par fichier
    write_record_n(r,nFiles,stop_timer(t),nFiles);
	
	//fermeture du dossier
    err = closedir(dirp);
    if(err<0) {
        perror("closedir");
        exit(EXIT_FAILURE);
    }
    
    //suppression des fichiers crees
    for(i = 0; i<nFiles; i++){
        
        char str[15];
        sprintf(str, "%d", i);
        strcat(str,"test.txt");
        
        char str2[20] = "temp/";
        strcat(str2,str);
        
        err = unlink(str2);
        if(err==-1){
            perror("unlink");
            exit(EXIT_FAILURE);
        }
    }	
	
}

int main(int argc, const char * argv[])
{
    timer *t = timer_alloc();
	recorder *readdir_rec = recorder_alloc("readdir.csv");
	
    char dirName[]="temp";
    
    int err = mkdir(dirName, S_IRUSR|S_IWUSR|S_IXUSR);
    if(err==-1){
        perror("mkdir");
        exit(EXIT_FAILURE);
    }
    
	
	benchmarkReaddir(dirName,1,t,readdir_rec);
	benchmarkReaddir(dirName,10,t,readdir_rec);
	benchmarkReaddir(dirName,50,t,readdir_rec);
	benchmarkReaddir(dirName,100,t,readdir_rec);
	
    
    err = rmdir(dirName);
    if(err==-1){
        perror("rmdir");
        exit(EXIT_FAILURE);
    }
    
	recorder_free(readdir_rec);
	timer_free(t);
	
    return 0;
}
