#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/uio.h>
#include "benchmark.h"
#include <stdlib.h>


/**
 * \brief writeVBenchmark et writeLseekBenchmark testent l ecriture avec deux appels systemes differents
 *
 * \param length represente le nombre de fois le string buf est ecrit
 *
 * \param buf represente le string qui est ecrit. Il a une taille de 1024
 *
 * \param t Le temps dans lequel on stoque le temps de début
 *
 * \param r Sauvegarde le temps dans un fichier .csv
 *
 */


/*
 Fonction pour le test de write v. Elle prend en argument le nombre de fois que on ecrit le string passe en deuxiemme argument
 */
void writeVBenchmark (int length, char* buf, timer* t, recorder* r) {
    ssize_t bytes_written;
    
    //Initialisation du file descriptor
    int fd = open("writeV.txt",  O_RDWR | O_CREAT, S_IRUSR | S_IRGRP | S_IROTH);
    if(fd==-1){
        perror("open in writeVBenchmark");
        exit(EXIT_FAILURE);
    }
    
    int iovcnt;
    
    //Initialisation de la taille de la structure par la taille passee en argument
    struct iovec iov[length];
    int i;
    
    //Ajout dans la structure du string
    for (i=0; i<length; i++) {
        iov[i].iov_base=buf;
        iov[i].iov_len=strlen(buf);
    }
    iovcnt = length;
    
    int j;
    
    //Debut du timer
    start_timer(t);
    
    //Boucle vide mais qui est utilisee pour etre sur un meme peid degalite avec la fonction writeLseekBenchmark
    // puisqu elle contient une boucle for et pas writeVBenchmark
    for (j=0; j<length; j++) {};
    
    bytes_written = writev(fd, iov, iovcnt);
    fsync(fd);
    
    //Fin du timer
    write_record(r,length,stop_timer(t));
    
    close(fd);
    
    //Supprime le fichier .txt 
    int err = unlink("writeV.txt");
    if(err==-1){
        perror("unlink in writeVBenchmark");
        exit(EXIT_FAILURE);
    }
}


/*
 Fonction pour le test de write. Elle prend en argument le nombre de fois que on ecrit le string passe en deuxiemme argument
 */
void writeLseekBenchmark (int length, char* buf, timer* t, recorder* r) {
	
    int fd = open("writeLseek.txt",  O_RDWR | O_CREAT, S_IRUSR | S_IRGRP | S_IROTH);
    if(fd==-1){
        perror("open in writeLseekBenchmark");
        exit(EXIT_FAILURE);
    }

    
    int i;
    //Debut du timer
    start_timer(t);
    
    //Ecriture dans le fichier test
    for (i=0; i<length; i++) {
        write(fd, buf, strlen(buf));
        //lseek(fd, (off_t) strlen(buf), SEEK_CUR);
    }
    fsync(fd);
    
    //Fin du timer
    write_record(r,length,stop_timer(t));
    
    close(fd);
    
    
    //Supprime le fichier.txt
    int err = unlink("writeLseek.txt");
    if(err==-1){
        perror("unlink in writeLseekBenchmark");
        exit(EXIT_FAILURE);
    }
}


int main()
{
    //Initialisation du timer et des fichiers .csv
    timer *t = timer_alloc();
    recorder *writev_rec = recorder_alloc("writev.csv");
    recorder *writelseek_rec = recorder_alloc("writelseek.csv");
    
    //String de taille 1024 Bytes
    char *buf = "gqtLsUKFyp1GZdwpZN9CFQncmWAvsC1TGbJ68Hz3RbFrvHIZjkfXRvKObFKyvfzQ0YHCWTDteVsvjJtCxa6Zlsrb8Du3LJYlqtJygwuyPddL557q91YiPmN9svHgrx0kjiiSqrKoVvKgZlAIEDBrvg0TlIaSwU0jjRQnRK1mzqQxS92y93Rv06Oj0j1Uw8GP9TuLwj9KroxnGRFGSZRwtlHkz3avykLTvnpg1suxRdQb0x6rJNsUb5GgvkMxvqDpvdjlfoCc8YjPT5q9YXtzN98WfYIVAqZc29pqFDo7ZKgvuudzPPKJK2tv2kAo4uEmNotlTqRLBuewju8LIX4tMJmSi4a8RpSkZWB8GGQmGP7ItWWpzUSiU4hpYxqO4KPdBDhcnti8FAK1Ri0nTegYnT6dHcNQi7LDyRTPlpldyx0umntZsR2hZAVrcdK9taeg8yrtFgDO51DUuOFAD9k1RejpqTV4vGseswj2kmGPfGk8wu29Ivos61ASwecHjD8M6bDovQqpkFtbfnts1r8bCNtb4csZV5UmlqM3COONk98wX1iUPN09RbsSQjXiiN6srxgyOWKhj2F2CIloGAkbrOFnQ9BDpfmSZJkJg6NQrToWcfrOO7sWgIYzoFwvHwaqZug9Ya3ntRl1SOD31faqCR7eqKjQiTjX8g8xdB1gXq6a8iHzgaf6J7uMXR6gjbXRYa93NrE78flMjbofkQJvMjCbC4h02eyMEmvJfPIjiIFXq0wLR801ORo7HGB0G5bIloYCVej3uds3y5oOjR9C5O4YxfxVx6YyPJCqpmAY2imNYexyhyAdKadXcjlod69K5rWiDGcW6UZiBTrqJZQcckN0SHZxjWDzPYzI6mb5ir4JXcqcRzctowZ6xTMOtJmwI8RfrA2APgdhqqSwBxteqM8f94wsrJwHLuxHxr0jZHKNOLaAGlpReRaL06kRchI10O1ITxRRDLj5zy7wWUBczXpUlNgkEGFLDsUgg4ma9bT5sXZL4SslECrgNYDpMqn\n";
	
    
    //Tests effectues
    writeVBenchmark(1, buf,t,writev_rec);
    writeVBenchmark(10, buf,t,writev_rec);
    writeVBenchmark(50, buf,t,writev_rec);
    writeVBenchmark(100, buf,t,writev_rec);
    writeVBenchmark(200, buf,t,writev_rec);
    writeVBenchmark(500, buf,t,writev_rec);
    writeVBenchmark(1000, buf,t,writev_rec);
    
    writeLseekBenchmark(1, buf,t,writelseek_rec);
    writeLseekBenchmark(10, buf,t,writelseek_rec);
    writeLseekBenchmark(50, buf,t,writelseek_rec);
    writeLseekBenchmark(100, buf,t,writelseek_rec);
    writeLseekBenchmark(200, buf,t,writelseek_rec);
    writeLseekBenchmark(500, buf,t,writelseek_rec);
    writeLseekBenchmark(1000, buf,t,writelseek_rec);
    
    recorder_free(writev_rec);
    recorder_free(writelseek_rec);
    timer_free(t);
    
    return EXIT_SUCCESS;
}
