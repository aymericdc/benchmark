//
//  main.c
//  P3
//
//  Created by Aymeric De Cocq on 14/05/14.
//  Copyright (c) 2014 Aymeric De Cocq. All rights reserved.
//
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/uio.h>

/*
 Fonction
 */
void writetest (int length, char* buf0) {
    ssize_t bytes_written;
    int fd = open("writeV.txt",  O_RDWR | O_CREAT, S_IRUSR | S_IRGRP | S_IROTH);
    
    
    int iovcnt;
    struct iovec iov[length];
    int i;
    for (i=0; i<length; i++) {
        iov[i].iov_base=buf0;
        iov[i].iov_len=strlen(buf0);
    }
    iovcnt = length;
    
    int j;
    //start timer
    for (j=0; j<length; j++) {};
    bytes_written = writev(fd, iov, iovcnt);
    fsync(fd);
    //stop timer
    close(fd);
}

void writelseek (int length, char* buf0) {
    int fd = open("writeLseek.txt",  O_RDWR | O_CREAT, S_IRUSR | S_IRGRP | S_IROTH);
    
    
    int i;
    //start timer
    for (i=0; i<length; i++) {
        write(fd, buf0, strlen(buf0));
        //lseek(fd, (off_t) strlen(buf0), SEEK_CUR);
    }
    fsync(fd);
    //stop timer
    close(fd);
    
    
}

int main()
{
    char *buf0 = "gqtLsUKFyp1GZdwpZN9CFQncmWAvsC1TGbJ68Hz3RbFrvHIZjkfXRvKObFKyvfzQ0YHCWTDteVsvjJtCxa6Zlsrb8Du3LJYlqtJygwuyPddL557q91YiPmN9svHgrx0kjiiSqrKoVvKgZlAIEDBrvg0TlIaSwU0jjRQnRK1mzqQxS92y93Rv06Oj0j1Uw8GP9TuLwj9KroxnGRFGSZRwtlHkz3avykLTvnpg1suxRdQb0x6rJNsUb5GgvkMxvqDpvdjlfoCc8YjPT5q9YXtzN98WfYIVAqZc29pqFDo7ZKgvuudzPPKJK2tv2kAo4uEmNotlTqRLBuewju8LIX4tMJmSi4a8RpSkZWB8GGQmGP7ItWWpzUSiU4hpYxqO4KPdBDhcnti8FAK1Ri0nTegYnT6dHcNQi7LDyRTPlpldyx0umntZsR2hZAVrcdK9taeg8yrtFgDO51DUuOFAD9k1RejpqTV4vGseswj2kmGPfGk8wu29Ivos61ASwecHjD8M6bDovQqpkFtbfnts1r8bCNtb4csZV5UmlqM3COONk98wX1iUPN09RbsSQjXiiN6srxgyOWKhj2F2CIloGAkbrOFnQ9BDpfmSZJkJg6NQrToWcfrOO7sWgIYzoFwvHwaqZug9Ya3ntRl1SOD31faqCR7eqKjQiTjX8g8xdB1gXq6a8iHzgaf6J7uMXR6gjbXRYa93NrE78flMjbofkQJvMjCbC4h02eyMEmvJfPIjiIFXq0wLR801ORo7HGB0G5bIloYCVej3uds3y5oOjR9C5O4YxfxVx6YyPJCqpmAY2imNYexyhyAdKadXcjlod69K5rWiDGcW6UZiBTrqJZQcckN0SHZxjWDzPYzI6mb5ir4JXcqcRzctowZ6xTMOtJmwI8RfrA2APgdhqqSwBxteqM8f94wsrJwHLuxHxr0jZHKNOLaAGlpReRaL06kRchI10O1ITxRRDLj5zy7wWUBczXpUlNgkEGFLDsUgg4ma9bT5sXZL4SslECrgNYDpMqn\n";
    writetest(1000, buf0);
    writelseek(1000, buf0);
}