//Author: A. Cizerl
//16 June 2022

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

int read_tempSensor(const char *path){

    const size_t BUFFER_SIZE = 64;
    char input_buffer[BUFFER_SIZE];
    int result = 0;

    FILE *in;
    if((in = fopen(path, "r")) == NULL){
        return -1;
    }
    fgets(input_buffer, BUFFER_SIZE, in);
    fclose(in);
    
    result = atoi(input_buffer);
    
    return result;
}

int screen_output(int temp){

    int exit_code = 0;    

    const char *color_yellow = "#FFFF00";
    const char *color_orange = "#FFA500";
    const char *color_red    = "#FF0000";

    const char *icon_empty  = "\uF2CB";
    const char *icon_oneQ   = "\uF2CA";
    const char *icon_half   = "\uF2C9";
    const char *icon_threeQ = "\uF2C8";
    const char *icon_full   = "\uF2C7";


    if(temp != -1){
        temp = temp / 1000;

        //double printf-output because thats how i3blocks prefers it according to the Doc...

        if(temp >= 90){
            printf("<span>%s %d°C</span>\n", icon_full, temp);
            printf("<span>%s %d°C</span>\n", icon_full, temp);
            exit_code = 33;
        }else if(temp >= 80){
            printf("<span color=\"%s\">%s %d°C</span>\n", color_red, icon_full, temp);
            printf("<span color=\"%s\">%s %d°C</span>\n", color_red, icon_full, temp);
        }else if(temp >= 70){
            printf("<span color=\"%s\">%s %d°C</span>\n", color_orange, icon_threeQ, temp);
            printf("<span color=\"%s\">%s %d°C</span>\n", color_orange, icon_threeQ, temp);
        }else if(temp >= 60){
            printf("<span color=\"%s\">%s %d°C</span>\n", color_yellow, icon_half, temp);
            printf("<span color=\"%s\">%s %d°C</span>\n", color_yellow, icon_half, temp);
        }else if(temp >= 50){
            printf("<span>%s %d°C</span>\n", icon_oneQ, temp);
            printf("<span>%s %d°C</span>\n", icon_oneQ, temp);
        }else{
            printf("<span>%s %d°C</span>\n", icon_empty, temp);
            printf("<span>%s %d°C</span>\n", icon_empty, temp);
        }

        return exit_code;
    }else{
        printf("Temperature not available!\n");
        printf("Temperature not available!\n");

        return 33;
    } 
}


int main(){
    
    //you have to find out through 'acpi -V' and other tools which thermal_zone is the right one for you. In my case its zone '0'.
    int temp = read_tempSensor("/sys/class/thermal/thermal_zone0/temp");

    return screen_output(temp);
}
