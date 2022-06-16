//Author: A. Cizerl
//16 June 2022

#include<stdio.h>
#include<stdlib.h>
#include<sys/statvfs.h>

double get_diskSize(unsigned long allBlocks, unsigned long blockSize){
    double all =  allBlocks * blockSize;
    all /= 1000000000;      // 1000*1000*1000 for GB, 1024*1024*1024 for GiB
    all += 0.05;            // Round UP
    return all;
}

double get_availableDiskSpace(unsigned long availableBlocks, unsigned long blockSize){
    double avail = availableBlocks * blockSize;
    avail /= 1000000000;    // 1000*1000*1000 for GB, 1024*1024*1024 for GiB
    avail += 0.05;          // Round UP
    return avail;
}

int main(){

    struct statvfs vfs;
    int fd = statvfs("/", &vfs);
    if(fd == -1){
        printf("Disk FAIL!\n");
        printf("Disk FAIL!\n");
        return 33;
    }

    double all = get_diskSize(vfs.f_blocks, vfs.f_bsize);
    double avail = get_availableDiskSpace(vfs.f_bavail, vfs.f_bsize);

    if(avail > (all*0.15)){
        printf("<span>%.1f GB</span>\n", avail);
        printf("<span>%.1f GB</span>\n", avail);
        return 0;
    }else if(avail > (all*0.10)){
        printf("<span color=\"#FFFF00\">%.1f GB</span>\n", avail);
        printf("<span color=\"#FFFF00\">%.1f GB</span>\n", avail);
        return 0;
    }else if(avail > (all*0.05)){
        printf("<span color=\"#FFA500\">%.1f GB</span>\n", avail);
        printf("<span color=\"#FFA500\">%.1f GB</span>\n", avail);
        return 0;
    }else if(avail > (all*0.025)){
        printf("<span color=\"#FF0000\">%.1f GB</span>\n", avail);
        printf("<span color=\"#FF0000\">%.1f GB</span>\n", avail);
        return 0;
    }else{
        printf("<span>%.1f GB</span>\n", avail);
        printf("<span>%.1f GB</span>\n", avail);
        return 33;
    }

}
