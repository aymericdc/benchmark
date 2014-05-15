#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

#include "benchmark.h"

/* \brief cree nFiles fichiers dans le dossier dirName et puis les parcourt avec readdir
 *
 * \param dirName est le nom du dossier
 *
 * \param nFiles est le nombre de fichiers a creer et a parcourir dans le dossier 
 *
 * \param t Le temps dans lequel on stocke le temps de debut
 *
 * \param r Sauvegarde le temps dans un fichier .csv
 *
 * Cree les fichiers puis le parcourt et fini par les supprimer.
 *
 */
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
            perror("creat in benchmarkReaddir");
            exit(EXIT_FAILURE);
        }
    }
    
    
    //Ouverture du dossier
    DIR *dirp;
    struct dirent *dp;
    
    dirp = opendir(dirName);
    if(dirp==NULL) {
        perror("opendir in benchmarkReaddir");
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
        perror("closedir in benchmarkReaddir");
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
            perror("unlink in benchmarkReaddir");
            exit(EXIT_FAILURE);
        }
    }	
}


/* \brief Enregistre les temps de calcul pour parcourir un dossiers avec readdir
 *
 *	Le dossier qui est cree est supprime avec le Makefile, car il en salle intel,
 *   il y a des fichiers .nfs qui se crees et qui empechent la suppression du dossier.
 */
int main(int argc, const char * argv[])
{
    timer *t = timer_alloc();
	recorder *readdir_rec = recorder_alloc("readdir.csv");
	
	//creation du dossier pour les fichiers
    char dirName[]="temp";
    
    int err = mkdir(dirName, S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IWGRP|S_IXGRP);
    if(err==-1){
        perror("mkdir in main");
        exit(EXIT_FAILURE);
    }
    
	//lancement des tests
	benchmarkReaddir(dirName,1,t,readdir_rec);
	benchmarkReaddir(dirName,10,t,readdir_rec);
	benchmarkReaddir(dirName,50,t,readdir_rec);
	benchmarkReaddir(dirName,100,t,readdir_rec);
	benchmarkReaddir(dirName,200,t,readdir_rec);
	benchmarkReaddir(dirName,500,t,readdir_rec);
	benchmarkReaddir(dirName,1000,t,readdir_rec);
	
    
    /* Ne pas fonctionne pas a cause de fichiers .nfs
    err = rmdir(dirName);
    if(err==-1){
        perror("rmdir in main");
        exit(EXIT_FAILURE);
    }
    */
	
    
	recorder_free(readdir_rec);
	timer_free(t);
	
    return 0;
}
