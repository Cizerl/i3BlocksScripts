//Author: A. Cizerl
//16 June 2022

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

int read_batteryData(const char *path){

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

char read_batteryStatus(const char *path){
    const size_t BUFFER_SIZE = 64;
    char input_buffer[BUFFER_SIZE];

    FILE *in;
    if((in = fopen(path, "r")) == NULL){
        return 'f';
    }
    fgets(input_buffer, BUFFER_SIZE, in);
    fclose(in);

    if(strstr(input_buffer, "Discharging") != NULL)
        return 'D';
    
    if(strstr(input_buffer, "Not charging") != NULL)
        return 'N';
        
    if(strstr(input_buffer, "Charging") != NULL)
        return 'C';

    return 'f';
}

bool data_verification(int capacity, int eNow, int eFull, int eThreshold, char status){
    if(status == 'f'){
        return false;
    }
    if((capacity == -1)||(eNow == -1)||(eFull == -1)||(eThreshold == -1)){
        return false;
    }else{
        return true;
    }
}

int screen_output(int charge, bool both_BatOK, char bat0_status, char bat1_status){
   
   int exit_code = 0;

    const char *color_green = "#00FF00";
    const char *color_yellow= "#FFFF00";
    const char *color_orange= "#FFA500";
    const char *color_red   = "#FF0000";

    const char *icon_plug   = "\uF1E6";

    const char *icon_empty  = "\uF244";
    const char *icon_oneQ   = "\uF243";
    const char *icon_half   = "\uF242";
    const char *icon_threeQ = "\uF241";
    const char *icon_full   = "\uF240";

    //double output because thats how i3blocks prefers it according to the Doc...
    if(both_BatOK){
        if((bat0_status=='C')||(bat1_status=='C')){
            printf("<span color=\"%s\">%s² %d%%</span>\n", color_green, icon_plug, charge);
            printf("<span color=\"%s\">%s² %d%%</span>\n", color_green, icon_plug, charge);
        }else{
            if(charge > 85){
                printf("<span>%s² %d%%</span>\n", icon_full, charge);
                printf("<span>%s² %d%%</span>\n", icon_full, charge);
            }else if(charge > 65){
                printf("<span>%s² %d%%</span>\n", icon_threeQ, charge);
                printf("<span>%s² %d%%</span>\n", icon_threeQ, charge);
            }else if(charge > 40){
                printf("<span>%s² %d%%</span>\n", icon_half, charge);
                printf("<span>%s² %d%%</span>\n", icon_half, charge);
            }else if(charge > 30){
                printf("<span color=\"%s\">%s² %d%%</span>\n", color_yellow, icon_oneQ, charge);
                printf("<span color=\"%s\">%s² %d%%</span>\n", color_yellow, icon_oneQ, charge);
            }else if(charge > 20){
                printf("<span color=\"%s\">%s² %d%%</span>\n", color_orange, icon_oneQ, charge);
                printf("<span color=\"%s\">%s² %d%%</span>\n", color_orange, icon_oneQ, charge);
            }else if(charge > 10){
                printf("<span color=\"%s\">%s² %d%%</span>\n", color_red, icon_empty, charge);
                printf("<span color=\"%s\">%s² %d%%</span>\n", color_red, icon_empty, charge);
            }else{
                printf("<span>%s² %d%%</span>\n", icon_empty, charge);
                printf("<span>%s² %d%%</span>\n", icon_empty, charge);
                exit_code = 33;
            }
        }
    }else{
        if((bat0_status=='C')||(bat1_status=='C')){
            printf("<span color=\"%s\">%s¹ %d%%</span>\n", color_green, icon_plug, charge);
            printf("<span color=\"%s\">%s¹ %d%%</span>\n", color_green, icon_plug, charge);
        }else{
            if(charge > 85){
                printf("<span>%s¹ %d%%</span>\n", icon_full, charge);
                printf("<span>%s¹ %d%%</span>\n", icon_full, charge);
            }else if(charge > 65){
                printf("<span>%s¹ %d%%</span>\n", icon_threeQ, charge);
                printf("<span>%s¹ %d%%</span>\n", icon_threeQ, charge);
            }else if(charge > 40){
                printf("<span>%s¹ %d%%</span>\n", icon_half, charge);
                printf("<span>%s¹ %d%%</span>\n", icon_half, charge);
            }else if(charge > 30){
                printf("<span color=\"%s\">%s¹ %d%%</span>\n", color_yellow, icon_oneQ, charge);
                printf("<span color=\"%s\">%s¹ %d%%</span>\n", color_yellow, icon_oneQ, charge);
            }else if(charge > 20){
                printf("<span color=\"%s\">%s¹ %d%%</span>\n", color_orange, icon_oneQ, charge);
                printf("<span color=\"%s\">%s¹ %d%%</span>\n", color_orange, icon_oneQ, charge);
            }else if(charge > 10){
                printf("<span color=\"%s\">%s¹ %d%%</span>\n", color_red, icon_empty, charge);
                printf("<span color=\"%s\">%s¹ %d%%</span>\n", color_red, icon_empty, charge);
            }else{
                printf("<span>%s¹ %d%%</span>\n", icon_empty, charge);
                printf("<span>%s¹ %d%%</span>\n", icon_empty, charge);
                exit_code = 33;
            }
        }
    }

    return exit_code;
}

int main(void){

    double charge = -1;
    bool both_BatOK = false;

    int bat0_capacity       = read_batteryData("/sys/class/power_supply/BAT0/capacity");
    int bat0_energyNow      = read_batteryData("/sys/class/power_supply/BAT0/energy_now");
    int bat0_energyFull     = read_batteryData("/sys/class/power_supply/BAT0/energy_full");
    int bat0_endThreshold   = read_batteryData("/sys/class/power_supply/BAT0/charge_stop_threshold");   //check if this is the right threshold path
    char bat0_status        = read_batteryStatus("/sys/class/power_supply/BAT0/status");

    int bat1_capacity       = read_batteryData("/sys/class/power_supply/BAT1/capacity");
    int bat1_energyNow      = read_batteryData("/sys/class/power_supply/BAT1/energy_now");
    int bat1_energyFull     = read_batteryData("/sys/class/power_supply/BAT1/energy_full");
    int bat1_endThreshold   = read_batteryData("/sys/class/power_supply/BAT1/charge_stop_threshold");     //check if this is the right threshold path
    char bat1_status        = read_batteryStatus("/sys/class/power_supply/BAT1/status");
    
    bool bat0_dataOK = data_verification(bat0_capacity, bat0_energyNow, bat0_energyFull, bat0_endThreshold, bat0_status);
    bool bat1_dataOK = data_verification(bat1_capacity, bat1_energyNow, bat1_energyFull, bat1_endThreshold, bat1_status);

    if(bat0_dataOK && bat1_dataOK){
        double total_energyNow = bat0_energyNow + bat1_energyNow;
        //change if threshold isn't working how envisioned, if thresholds dont get changed, just leave it like this since its just --> /100*100 <--
        double total_energyFullScaled = (bat0_energyFull / 100 * bat0_endThreshold) + (bat1_energyFull / 100 * bat1_endThreshold);
        charge = (total_energyNow / total_energyFullScaled *100);
        both_BatOK = true;
    }else if(bat0_dataOK){
        //if capacity isn't auto-scaled use following equation
        charge = (((double)bat0_capacity) / bat0_endThreshold) * 100;
        //if capacity is auto-scaled with threshold uncomment following equation 
        //charge = bat0_capacity;
    }else if(bat1_dataOK){
        //if capacity isn't auto-scaled use following equation
        charge = (((double)bat1_capacity) / bat1_endThreshold) * 100;
        //if capacity is auto-scaled with threshold uncomment following equation 
        //charge = bat1_capacity;
    }else{
        //double output because thats how i3blocks prefers it according to the Doc...
        printf("Battery Data not available!\n");
        printf("Battery Data not available!\n");
        return 33;
    }

    // +1 to round up, since it wont ever be 100% otherwise or only for one second
    int charge_i = (int)(charge + 1);

    return screen_output(charge_i, both_BatOK, bat0_status, bat1_status);
}
