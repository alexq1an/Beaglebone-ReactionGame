// Main program to build the application
// Has main(); does initialization and cleanup and perhaps some basic logic.

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "appOperations.h"
#include "hal/hardwares.h"

int main()
{   
    // terminal default
    printf("Hello embedded world, from Lihao Qian!\n\n");
    printf("When the LEDs light up, press the joystick in that direction!\n");
    printf("(Press left or right to exit)\n");

    init_all(); // Initialization step

    srand(time(NULL));
    long long start;
    long long end;
    int bestReaction = 5001;

    while(true){
        // sleep for a while in case repeat Get Ready & Too Soon
        // Also it prevents we see Please let go of joystick... everytime!
        sleepForMs(300); 

        printf("Get ready...\n");
        ledDefault(); // set led default

        int upOrDown = rand() % 2; // 0 for UP, 1 for Down
        int randomTime = (rand() % 2501 + 500);
        
        // record joystick status here
        int leftJS = readFromFileToScreen(JS_LEFT);
        int rightJS = readFromFileToScreen(JS_RIGHT);
        int upJS = readFromFileToScreen(JS_UP);
        int downJS = readFromFileToScreen(JS_DOWN);

        if(upJS == 0 || downJS == 0 || leftJS == 0 || rightJS == 0){
            printf("Please let go of joystick...\n");
        }
        while(upJS == 0 || downJS == 0 || leftJS == 0 || rightJS == 0){ // let go of joystick
            // Keep updating here, if user let go the joystick, we start counting time
            // After this, any button being press will treat as Too Soon (next while)
            upJS = readFromFileToScreen(JS_UP);
            downJS = readFromFileToScreen(JS_DOWN);
            leftJS = readFromFileToScreen(JS_LEFT);
            rightJS = readFromFileToScreen(JS_RIGHT);

        }
        
        start = getTimeInMs();// start timer
        bool tooSoon = false;
        while(start + randomTime > getTimeInMs()){ // Waiting time, for implement TOO SOON!
            // keep track of joystick status
            // leftJS = readFromFileToScreen(JS_LEFT);
            // rightJS = readFromFileToScreen(JS_RIGHT);
            upJS = readFromFileToScreen(JS_UP);
            downJS = readFromFileToScreen(JS_DOWN);

            if (upJS == 0 || downJS == 0){ // if user press early, TOO SOON!
                printf("Too Soon!\n");
                tooSoon = true;
                break;
            }
            // ignore, keep going
            // if (leftJS == 0 || rightJS == 0){ // Ensure user can quit anytime
            //     printf("User selected to quit.\n");
            //     ledDefault(); // set led default
            //     return 0;
            // }
        }

        if (upOrDown == 0 && !tooSoon){
            printf("Press UP now!\n");
        }
        else if(upOrDown == 1 && !tooSoon){
            printf("Press DOWN now!\n");
        }



        while(true){ // Game loop
            if (tooSoon){ // if user is too soon press the button, we start over from outer loop
                sleepForMs(300); // sleep for a while in case repeat Get Ready & Too Soon
                break;
            }
            // set led UP or DOWN
            if(upOrDown == 0){
                upLight();
            }
            else if (upOrDown == 1){
                downLight();
            }

            // keep track of joystick status
            leftJS = readFromFileToScreen(JS_LEFT);
            rightJS = readFromFileToScreen(JS_RIGHT);
            upJS = readFromFileToScreen(JS_UP);
            downJS = readFromFileToScreen(JS_DOWN);

            end = getTimeInMs(); 
            if(end - start - randomTime> 5000){ // check if time exceeds that means User wants to quit
                printf("No input within 5000ms; quitting!\n");
                ledDefault(); // set led default
                return 0;
            }

            if ((upJS == 0 && upOrDown == 1) || (downJS == 0 && upOrDown == 0)) // user press wrong direaction
            {
                printf("Incorrect.\n");
                for (int i = 0; i < 10; i++){ // Incorrect sync 4 LED flash 10hz for 1s
                    allLight();
                    sleepForMs(50);
                    allOff();
                    sleepForMs(50);
                }
                break;
            }
            else if ((upJS == 0 && upOrDown == 0) || (downJS == 0 && upOrDown == 1)) // user press the right direction
            {
                end = getTimeInMs();
                int currentReact = end - start - randomTime; // reaction time 
                bestReaction = currentReact < bestReaction ? currentReact : bestReaction; // compare with currentReaction
                if (currentReact == bestReaction){
                    printf("New best time!");
                }
                // current reaction and best reaction
                printf("Your reaction time was %dms; best so far in game is %dms\n", currentReact, bestReaction);

                for (int i = 0; i < 2; i++){ // Correct sync 4 LED flash 4hz for 0.5s
                    allLight();
                    sleepForMs(125);
                    allOff();
                    sleepForMs(125);
                }

                break;
            }

            if(leftJS == 0 || rightJS == 0){ // user press left or right, quit
                printf("User selected to quit.\n");
                ledDefault(); // set led default
                return 0;
            }
            
        }
    }


    
    getchar();
    return 0;
}