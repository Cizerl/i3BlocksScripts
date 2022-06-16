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

    const char *color_yellow = "#FFFF00";
    const char *color_orange = "#FFA500";
    const char *color_red    = "#FF0000";

    const char *icon = "\uF0A0";

    if(avail > (all*0.15)){
        printf("<span>%s %.1fGB</span>\n", icon, avail);
        printf("<span>%s %.1fGB</span>\n", icon, avail);
        return 0;
    }else if(avail > (all*0.10)){
        printf("<span color=\"%s\">%s %.1fGB</span>\n", color_yellow, icon, avail);
        printf("<span color=\"%s\">%s %.1fGB</span>\n", color_yellow, icon, avail);
        return 0;
    }else if(avail > (all*0.05)){
        printf("<span color=\"%s\">%s %.1fGB</span>\n", color_orange, icon, avail);
        printf("<span color=\"%s\">%s %.1fGB</span>\n", color_orange, icon, avail);
        return 0;
    }else if(avail > (all*0.025)){
        printf("<span color=\"%s\">%s %.1fGB</span>\n", color_red, icon, avail);
        printf("<span color=\"%s\">%s %.1fGB</span>\n", color_red, icon, avail);
        return 0;
    }else{
        printf("<span>%s %.1fGB</span>\n", icon, avail);
        printf("<span>%s %.1fGB</span>\n", icon, avail);
        return 33;
    }

}
