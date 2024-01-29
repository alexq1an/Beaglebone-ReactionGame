#include "hal/hardwares.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

void runCommand(char* command) { // from Brian

    // Execute the shell command (output into pipe)
    FILE *pipe = popen(command, "r");

    // Ignore output of the command; but consume it // so we don't get an error when closing the pipe. 
    char buffer[1024];
    while (!feof(pipe) && !ferror(pipe)) {
        if (fgets(buffer, sizeof(buffer), pipe) == NULL) break;
            // printf("--> %s", buffer);  // Uncomment for debugging
    }

    // Get the exit code from the pipe; non-zero is an error: 
    int exitCode = WEXITSTATUS(pclose(pipe));
    if (exitCode != 0) {
            perror("Unable to execute command:");
            printf("  command:   %s\n", command);
            printf("  exit code: %d\n", exitCode);
    } 
}

void init_all(){
    // LED0
    runCommand("echo none > /sys/class/leds/beaglebone:green:usr0/trigger");
    runCommand("echo 0 > /sys/class/leds/beaglebone:green:usr0/brightness");
    // LED1
    runCommand("echo none > /sys/class/leds/beaglebone:green:usr1/trigger");
    runCommand("echo 1 > /sys/class/leds/beaglebone:green:usr1/brightness");
    // LED2
    runCommand("echo none > /sys/class/leds/beaglebone:green:usr2/trigger");
    runCommand("echo 1 > /sys/class/leds/beaglebone:green:usr2/brightness");
    // LED3
    runCommand("echo none > /sys/class/leds/beaglebone:green:usr3/trigger");
    runCommand("echo 0 > /sys/class/leds/beaglebone:green:usr3/brightness");
    // UP JS
    runCommand("config-pin p8.14 gpio");
    runCommand("cd /sys/class/gpio");
    runCommand("echo 26 > export");
    runCommand("cd /sys/class/gpio/gpio26");
    runCommand("echo in > direction");
    // RIGHT JS
    runCommand("config-pin p8.15 gpio");
    runCommand("cd /sys/class/gpio");
    runCommand("echo 47 > export");
    runCommand("cd /sys/class/gpio/gpio47");
    runCommand("echo in > direction");
    // DOWN JS
    runCommand("config-pin p8.16 gpio");
    runCommand("cd /sys/class/gpio");
    runCommand("echo 46 > export");
    runCommand("cd /sys/class/gpio/gpio46");
    runCommand("echo in > direction");
    // LEFT JS
    runCommand("config-pin p8.18 gpio");
    runCommand("cd /sys/class/gpio");
    runCommand("echo 65 > export");
    runCommand("cd /sys/class/gpio/gpio65");
    runCommand("echo in > direction");
    runCommand("rm direction");
    runCommand("rm export");
    
}

void ledDefault(){
    // LED0
    runCommand("echo none > /sys/class/leds/beaglebone:green:usr0/trigger");
    runCommand("echo 0 > /sys/class/leds/beaglebone:green:usr0/brightness");
    // LED1
    runCommand("echo none > /sys/class/leds/beaglebone:green:usr1/trigger");
    runCommand("echo 1 > /sys/class/leds/beaglebone:green:usr1/brightness");
    // LED2
    runCommand("echo none > /sys/class/leds/beaglebone:green:usr2/trigger");
    runCommand("echo 1 > /sys/class/leds/beaglebone:green:usr2/brightness");
    // LED3
    runCommand("echo none > /sys/class/leds/beaglebone:green:usr3/trigger");
    runCommand("echo 0 > /sys/class/leds/beaglebone:green:usr3/brightness");
}

void upLight(){
    // set for LED0 UP
    runCommand("echo none > /sys/class/leds/beaglebone:green:usr0/trigger");
    runCommand("echo 1 > /sys/class/leds/beaglebone:green:usr0/brightness");
    // LED1 off
    runCommand("echo none > /sys/class/leds/beaglebone:green:usr1/trigger");
    runCommand("echo 0 > /sys/class/leds/beaglebone:green:usr1/brightness");
    // LED2 off
    runCommand("echo none > /sys/class/leds/beaglebone:green:usr2/trigger");
    runCommand("echo 0 > /sys/class/leds/beaglebone:green:usr2/brightness");
}

void downLight(){
    // set for LED3 UP
    runCommand("echo none > /sys/class/leds/beaglebone:green:usr3/trigger");
    runCommand("echo 1 > /sys/class/leds/beaglebone:green:usr3/brightness");
    // LED1 off
    runCommand("echo none > /sys/class/leds/beaglebone:green:usr1/trigger");
    runCommand("echo 0 > /sys/class/leds/beaglebone:green:usr1/brightness");
    // LED2 off
    runCommand("echo none > /sys/class/leds/beaglebone:green:usr2/trigger");
    runCommand("echo 0 > /sys/class/leds/beaglebone:green:usr2/brightness");
}

void allLight(){
    // LED0
    // runCommand("echo none > /sys/class/leds/beaglebone:green:usr0/trigger");
    runCommand("echo 1 > /sys/class/leds/beaglebone:green:usr0/brightness");
    // LED1
    // runCommand("echo none > /sys/class/leds/beaglebone:green:usr1/trigger");
    runCommand("echo 1 > /sys/class/leds/beaglebone:green:usr1/brightness");
    // LED2
    // runCommand("echo none > /sys/class/leds/beaglebone:green:usr2/trigger");
    runCommand("echo 1 > /sys/class/leds/beaglebone:green:usr2/brightness");
    // LED3
    // runCommand("echo none > /sys/class/leds/beaglebone:green:usr3/trigger");
    runCommand("echo 1 > /sys/class/leds/beaglebone:green:usr3/brightness");
}

void allOff(){
    // LED0
    // runCommand("echo none > /sys/class/leds/beaglebone:green:usr0/trigger");
    runCommand("echo 0 > /sys/class/leds/beaglebone:green:usr0/brightness");
    // LED1
    // runCommand("echo none > /sys/class/leds/beaglebone:green:usr1/trigger");
    runCommand("echo 0 > /sys/class/leds/beaglebone:green:usr1/brightness");
    // LED2
    // runCommand("echo none > /sys/class/leds/beaglebone:green:usr2/trigger");
    runCommand("echo 0 > /sys/class/leds/beaglebone:green:usr2/brightness");
    // LED3
    // runCommand("echo none > /sys/class/leds/beaglebone:green:usr3/trigger");
    runCommand("echo 0 > /sys/class/leds/beaglebone:green:usr3/brightness");
}




int readFromFileToScreen(char *fileName) { // From Brian
    FILE *pFile = fopen(fileName, "r"); 
    if (pFile == NULL) {
        printf("ERROR: Unable to open file (%s) for read\n", fileName);
        exit(-1); 
    }
    // Read string (line)
    const int MAX_LENGTH = 1024; 
    char buff[MAX_LENGTH]; 
    fgets(buff, MAX_LENGTH, pFile);
    // Close
    fclose(pFile);
    int ret = atoi(buff);
    return ret;
}