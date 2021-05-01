// Created by Joshua Gonzales
// Version 1.0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// linked list
struct memory{
    char* name;
    unsigned long int startByte;
    unsigned long int size;
    struct memory *next;
    struct memory *prev;
    unsigned long int lastBool;
    unsigned long int headBool;
};


int main(int argc, char* argv[], char **envp){

    int fitSel = -1;
    
    // ints for later implementation
    if(strcmp(argv[1], "BESTFIT") == 0){
        fitSel = 0;
    } else if (strcmp(argv[1], "FIRSTFIT") == 0){
        fitSel = 1;
    } else if (strcmp(argv[1], "NEXTFIT") == 0){
        fitSel = 2;
    } else if (strcmp(argv[1], "WORSTFIT") == 0){
        fitSel = 3;
    }

    // Memory allocation number N, for 2^N bytes
    unsigned long int memAmount = atoi(argv[2]);

    // // total memory allocation of 2^N
    // int totMem = 1;
    // for(int i = 0; i < memAmount; i++){
    //     totMem = totMem * 2;
    // }

    //DEBUG
    // printf("%s\n", argv[1]);
    // printf("Selected algorithm: %d\n", fitSel);
    // printf("memAmount: %d\n\n", memAmount);


    // File for script input
    FILE *fin;
    fin=fopen(argv[3], "r");

    //for storing the commands from the script
    char command[100];
    char* allCommand;
    char* cmd1;
    char* cmd2;
    char* cmd3;

    unsigned long int byteSize;
    unsigned long int existsHeadBool = 1;
    unsigned long int nextfitHeadsetBool = 0;
    unsigned long int succPlaceBool = 0;
    unsigned long int nextFitExitCond = 0;
    unsigned long int availableBool = 0;
    unsigned long int allocatedBool = 0;
    unsigned long int foundBool = 0;
    unsigned long int foundReleaseBool = 0;
    unsigned long int nextFitPrevFail = 0;


    struct memory *head = (struct memory*)malloc(sizeof(struct memory));
    struct memory *current = (struct memory*)malloc(sizeof(struct memory));
    struct memory *prevToPlacement = (struct memory*)malloc(sizeof(struct memory));
    struct memory *nextFitStruct = (struct memory*)malloc(sizeof(struct memory));
    struct memory *temp = (struct memory*)malloc(sizeof(struct memory));
    struct memory *newMem0 = (struct memory*)malloc(sizeof(struct memory));


    newMem0->headBool = 1;
    newMem0->lastBool = 1;
    newMem0->next = NULL;
    newMem0->prev = NULL;
    newMem0->startByte = 0;
    newMem0->size = 0;
    head = newMem0;



    // helps understand what is going on with commands
    unsigned long int spaceSize = 0;
    unsigned long int nextFreeByteAddr = 0;
    unsigned long int bestFitSpaceAddr;
    unsigned long int bestFitSpaceSize;
    unsigned long int firstFitSpaceAddr;
    unsigned long int nextFitSpaceAddr;
    unsigned long int worstFitSpaceAddr;
    unsigned long int worstFitSpaceSize;




    while(fgets(command, 100, fin) != NULL){

        //DEBUG
        //printf("Command: %s\n", command);

        cmd1 = strtok(command, " ");
        cmd2 = strtok(NULL, " \n");
        cmd3 = strtok(NULL, " \n");
        availableBool = 0;

        // DEBUG
        //printf("Command 1: %s\nCommand 2: %s\nCommand 3: %s\n", cmd1, cmd2, cmd3);
        


        if((strcmp(cmd1, "LIST") == 0) || (strcmp(cmd1, "list") == 0)){
            
            
            // code for LIST AVAILABLE
            if((strcmp(cmd2, "AVAILABLE") == 0) || (strcmp(cmd2, "available") == 0)){
                current = head;
                
                //print head of memory space if available
                if(head->startByte != 0){
                    printf("(%ld, 0) ", head->startByte);
                    availableBool = 1;
                }
                
                //iterate through list
                while (current->next != NULL){
                    if ((current->next->startByte - (current->startByte + current->size)) != 0){
                        printf("(%ld, %ld) ", (current->next->startByte - (current->startByte + current->size)),
                        (current->startByte + current->size));
                        availableBool = 1;
                    }

                    current = current->next;
                }

                //print end of memory
                if(current->next == NULL){
                    if ((memAmount - (current->startByte + current->size) != 0)){
                        printf("(%ld, %ld) ", (memAmount - (current->startByte + current->size)), 
                        (current->startByte + current->size));

                    }
                }

                //if there's nothing available
                if(availableBool = 0){
                    printf("FULL");
                }

                printf("\n");


            // Code for LIST ASSIGNED
            } else if((strcmp(cmd2, "ASSIGNED") == 0) || (strcmp(cmd2, "assigned") == 0)){
                current = head;
                current = current->next;

                //printf("NAME: %s\n", current->name);
                

                while(current != NULL){
                    printf("(%s, %ld, %ld) ", current->name, current->size, current->startByte);
                    allocatedBool = 1;

                    current = current->next;

                }



                if(allocatedBool == 0){
                    printf("NONE");
                }


                printf("\n");
            }
            // Code for REQUEST A n
        } else if((strcmp(cmd1, "REQUEST") == 0) || (strcmp(cmd1, "request") == 0)){

            succPlaceBool = 0;
            existsHeadBool = 1;
            byteSize = atoi(cmd3);
            struct memory  *newMem = (struct memory*)malloc(sizeof(struct memory));
            newMem->size = byteSize;
            //newMem->name = cmd2;
            char * stringy = (char *) malloc(100);
            strcpy(stringy, cmd2);
            newMem->name = stringy;

            //DEBUG
            //printf("Str: %s Name:%s\n", stringy, newMem->name);


            


            if(existsHeadBool == 0){

                // if(byteSize < memAmount){
                    // newMem->headBool = 1;
                    // newMem->lastBool = 1;
                    // newMem->next = NULL;
                    // newMem->prev = NULL;
                    // newMem->startByte = 0;
                    // head = newMem;
                //     printf("ALLOCATED %s %ld\n", cmd2, newMem->startByte);
                //     existsHeadBool = 1;

                // } else {
                //     printf("FAIL REQUEST %s %d\n", cmd2, atoi(cmd3));

                // }


            } else {

                switch (fitSel){

                    // BESTFIT ***********************************************
                    case 0:

                    current = head;

                    bestFitSpaceAddr = 0;
                    bestFitSpaceSize = 9999999999999;
                    

                    while(current->next != NULL){
                        current = current->next;


                        nextFreeByteAddr = (current->startByte + current->size);

                        //DEBUG
                        // printf("NAME: %s\n", current->name);
                        // printf("STARTBYTE %ld\n", current->startByte);
                        // printf("SIZE %ld\n", current->size);
                        // printf("NEXTFREEBYTEADDR %ld\n", nextFreeByteAddr);

                        if(current->next == NULL){
                            spaceSize = (memAmount - nextFreeByteAddr);
                        } else {
                            spaceSize = (current->next->startByte - (current->startByte + current->size));
                        }


                        
                        // if the space is big enough and smaller than another space that works
                        if((spaceSize >= byteSize) && (spaceSize < bestFitSpaceSize)){
                            bestFitSpaceAddr = nextFreeByteAddr;
                            bestFitSpaceSize = spaceSize;
                            prevToPlacement = current;
                            succPlaceBool = 1;
                            newMem->headBool = 0;

                        }

                    }

                    
                    // check end of memory
                    if ((current->next == NULL)){
                        spaceSize = (memAmount - nextFreeByteAddr);
                        // if the space is big enough and smaller than another space that works
                        if((spaceSize >= byteSize) && (spaceSize < bestFitSpaceSize)){
                            bestFitSpaceAddr = nextFreeByteAddr;
                            bestFitSpaceSize = spaceSize;
                            prevToPlacement = current;
                            succPlaceBool = 1;
                            newMem->headBool = 0;


                        }

                    }


                    //If the head exists but doesn't start at addr 0
                    if(head->startByte != 0){

                        spaceSize = head->startByte;
                        nextFreeByteAddr = 0;
                        if((spaceSize >= byteSize) && (spaceSize < bestFitSpaceSize)){
                            bestFitSpaceAddr = nextFreeByteAddr;
                            prevToPlacement = current;
                            succPlaceBool = 1;
                            newMem->headBool = 1;
                        }
                    }

                    // if successful place
                    if ((succPlaceBool == 1) && (newMem->headBool == 0)){
                        

                        //insert into doubly linked list
                        if(prevToPlacement->next != NULL){

                        prevToPlacement->next->prev = newMem;
                        newMem->next = prevToPlacement->next;

                        newMem->lastBool = 0;


                        } else {
                            newMem->next = NULL;
                            newMem->lastBool = 1;


                        }
                        prevToPlacement->next = newMem;
                        newMem->prev = prevToPlacement;

                        // is not the head, starts at a specific bit addr
                        newMem->startByte = bestFitSpaceAddr;

                        // print the success
                        printf("ALLOCATED %s %ld\n", cmd2, newMem->startByte);

                        
                    // Else If the placement is a new head
                    } else if ((succPlaceBool == 1) && (newMem->headBool == 1)) {
                        
                        newMem->next = head;
                        head->prev = newMem;
                        head->headBool = 0;
                        newMem->startByte = 0;
                        head = newMem;

                        printf("ALLOCATED %s %ld\n", cmd2, newMem->startByte);


                    // If unsuccessful place
                    } else {
                        // print the fail
                        printf("FAIL REQUEST %s %d\n", cmd2, atoi(cmd3));
                    }


                    
                    break;


                    // FIRSTFIT **********************************
                    case 1:
                    

                   succPlaceBool = 0;

                    current = head;
                    firstFitSpaceAddr = 0;

                    //If the head exists but doesn't start at addr 0
                    if(head->startByte != 0){
                        spaceSize = head->startByte;
                        nextFreeByteAddr = 0;
                        if((spaceSize >= byteSize)){
                            firstFitSpaceAddr = nextFreeByteAddr;
                            prevToPlacement = current;
                            succPlaceBool = 1;
                            newMem->headBool = 1;
                        }
                    }



                    //while there are still places to check and there hasn't been a successful placement
                    while((current->next != NULL) && (succPlaceBool == 0)){

                    current = current->next;

                        nextFreeByteAddr = (current->startByte + current->size);


                        if(current->next == NULL){
                            spaceSize = (memAmount - nextFreeByteAddr);
                        } else {
                            spaceSize = (current->next->startByte - (current->startByte + current->size));
                        }

                        
                        // if the space is big enough
                        if((spaceSize >= byteSize)){
                            firstFitSpaceAddr = nextFreeByteAddr;
                            prevToPlacement = current;
                            succPlaceBool = 1;
                            newMem->headBool = 0;

                        }
                    }

                


                    // check end of memory
                    if ((current->next == NULL) && (succPlaceBool == 0)){
                        spaceSize = (memAmount - nextFreeByteAddr);
                        // if the space is big enough
                        if((spaceSize >= byteSize)){
                            firstFitSpaceAddr = nextFreeByteAddr;
                            prevToPlacement = current;
                            succPlaceBool = 1;
                            newMem->headBool = 0;

                        }

                    }


                    // if successful place
                    if ((succPlaceBool == 1) && (newMem->headBool == 0)){
                        

                        //insert into doubly linked list
                        if(prevToPlacement->next != NULL){

                        prevToPlacement->next->prev = newMem;
                        newMem->next = prevToPlacement->next;

                        newMem->lastBool = 0;

                        } else {
                            newMem->next = NULL;
                            newMem->lastBool = 1;

                        }
                        prevToPlacement->next = newMem;
                        newMem->prev = prevToPlacement;

                        // is not the head, starts at a specific bit addr
                        newMem->startByte = firstFitSpaceAddr;

                        // print the success
                        printf("ALLOCATED %s %ld\n", cmd2, newMem->startByte);
                        
                    // Else If the placement is a new head
                    } else if ((succPlaceBool == 1) && (newMem->headBool == 1)) {
                        
                        newMem->next = head;
                        head->prev = newMem;
                        head->headBool = 0;
                        newMem->startByte = 0;
                        head = newMem;

                        printf("ALLOCATED %s %ld\n", cmd2, newMem->startByte);

                    // If unsuccessful place
                    } else {
                        // print the fail
                        printf("FAIL REQUEST %s %d\n", cmd2, atoi(cmd3));
                    }


                    break;



                    // NEXTFIT ********************************************************
                    case 2:

                    if(nextfitHeadsetBool == 0){
                        current = head;
                        nextfitHeadsetBool = 1;
                        nextFitStruct = current;


                    } else {
                        current = nextFitStruct;
                    }
                    
                    nextFitExitCond = 0;
                    nextFitSpaceAddr = 0;

                    while((current->next != nextFitStruct) && (succPlaceBool == 0)
                     && (nextFitExitCond == 0)){

                        //current = current->next;

                        nextFreeByteAddr = (current->startByte + current->size);


                        //If it failed previously, start at beginning
                        if(nextFitPrevFail == 1){
                        printf("MADEITHERE\n");

                            nextFitStruct = head;
                            nextfitHeadsetBool = 1;

                            spaceSize = head->startByte;
                            nextFreeByteAddr = 0;
                            if((spaceSize >= byteSize)){
                                nextFitSpaceAddr = nextFreeByteAddr;
                                prevToPlacement = current;
                                succPlaceBool = 1;
                                newMem->headBool = 1;
                            }
                            current = current->next;
                            printf("MADEITHERE\n");


                        }
                        
                        // if the space is big enough
                        if((spaceSize >= byteSize)){
                            nextFitSpaceAddr = nextFreeByteAddr;
                            prevToPlacement = current;
                            succPlaceBool = 1;
                            newMem->headBool = 0;

                        }

                        // if the next list item is null and there hasn't been a successful place
                        if ((current->next == NULL) && (succPlaceBool == 0)){

                            spaceSize = (memAmount - nextFreeByteAddr);

                            //check if space until end is big enough
                            if((spaceSize >= byteSize)){
                                nextFitSpaceAddr = nextFreeByteAddr;
                                prevToPlacement = current;
                                succPlaceBool = 1;
                                newMem->headBool = 0;

                        }

                            // If the head exists but doesn't start at addr 0, 
                            // and there hasn't been a successful place

                            if((head->startByte != 0) && (succPlaceBool == 0)){
                                spaceSize = head->startByte;
                                nextFreeByteAddr = 0;
                                if((spaceSize >= byteSize)){
                                    nextFitSpaceAddr = nextFreeByteAddr;
                                    prevToPlacement = current;
                                    succPlaceBool = 1;
                                    newMem->headBool = 1;
                                }
                            }

                            if(nextfitHeadsetBool == 1){
                                nextFitExitCond = 1;
                            } else {
                                current = head;
                            }
                        }

                    }


                    // if successful place
                    if ((succPlaceBool == 1) && (newMem->headBool == 0)){
                        

                        //insert into doubly linked list
                        if(prevToPlacement->next != NULL){

                        prevToPlacement->next->prev = newMem;
                        newMem->next = prevToPlacement->next;

                        newMem->lastBool = 0;

                        } else {
                            newMem->next = NULL;
                            newMem->lastBool = 1;

                        }
                        prevToPlacement->next = newMem;
                        newMem->prev = prevToPlacement;

                        // is not the head, starts at a specific bit addr
                        newMem->startByte = nextFitSpaceAddr;
                        nextFitStruct = newMem;

                        nextFitPrevFail = 0;

                        // print the success
                        printf("ALLOCATED %s %ld\n", cmd2, newMem->startByte);
                        
                    // Else If the placement is a new head
                    } else if ((succPlaceBool == 1) && (newMem->headBool == 1)) {
                        
                        newMem->next = head;
                        head->prev = newMem;
                        head->headBool = 0;
                        newMem->startByte = 0;
                        head = newMem;

                        nextFitPrevFail = 0;
                        printf("ALLOCATED %s %ld\n", cmd2, newMem->startByte);

                    // If unsuccessful place
                    } else {
                        nextFitStruct = head;
                        nextFitPrevFail = 1;
                        // print the fail
                        printf("FAIL REQUEST %s %d\n", cmd2, atoi(cmd3));
                    }
                    

                    break;

                    // WORSTFIT ******************************************************
                    case 3:

                    current = head;

                    worstFitSpaceAddr = 0;
                    worstFitSpaceSize = 0;
                    

                    while(current->next != NULL){


                        current = current->next;


                        nextFreeByteAddr = (current->startByte + current->size);

                        //DEBUG
                        // printf("NAME: %s\n", current->name);
                        // printf("STARTBYTE %ld\n", current->startByte);
                        // printf("SIZE %ld\n", current->size);
                        // printf("NEXTFREEBYTEADDR %ld\n", nextFreeByteAddr);

                        if(current->next == NULL){
                            spaceSize = (memAmount - nextFreeByteAddr);
                        } else {
                            spaceSize = (current->next->startByte - (current->startByte + current->size));
                        }


                        
                        // if the space is big enough and smaller than another space that works
                        if((spaceSize >= byteSize) && (spaceSize > worstFitSpaceSize)){
                            worstFitSpaceAddr = nextFreeByteAddr;
                            worstFitSpaceSize = spaceSize;
                            prevToPlacement = current;
                            succPlaceBool = 1;
                            newMem->headBool = 0;

                        }

                    }

                    
                    // check end of memory
                    if ((current->next == NULL)){
                        spaceSize = (memAmount - nextFreeByteAddr);
                        // if the space is big enough and smaller than another space that works
                        if((spaceSize >= byteSize) && (spaceSize > worstFitSpaceSize)){
                            worstFitSpaceAddr = nextFreeByteAddr;
                            worstFitSpaceSize = spaceSize;
                            prevToPlacement = current;
                            succPlaceBool = 1;
                            newMem->headBool = 0;


                        }

                    }


                    //If the head exists but doesn't start at addr 0
                    if(head->startByte != 0){

                        spaceSize = head->startByte;
                        nextFreeByteAddr = 0;
                        if((spaceSize >= byteSize) && (spaceSize > worstFitSpaceSize)){
                            worstFitSpaceAddr = nextFreeByteAddr;
                            prevToPlacement = current;
                            succPlaceBool = 1;
                            newMem->headBool = 1;
                        }
                    }

                    // if successful place
                    if ((succPlaceBool == 1) && (newMem->headBool == 0)){
                        

                        //insert into doubly linked list
                        if(prevToPlacement->next != NULL){

                        prevToPlacement->next->prev = newMem;
                        newMem->next = prevToPlacement->next;

                        newMem->lastBool = 0;


                        } else {
                            newMem->next = NULL;
                            newMem->lastBool = 1;


                        }
                        prevToPlacement->next = newMem;
                        newMem->prev = prevToPlacement;

                        // is not the head, starts at a specific bit addr
                        newMem->startByte = worstFitSpaceAddr;

                        // print the success
                        printf("ALLOCATED %s %ld\n", cmd2, newMem->startByte);

                        
                    // Else If the placement is a new head
                    } else if ((succPlaceBool == 1) && (newMem->headBool == 1)) {
                        
                        newMem->next = head;
                        head->prev = newMem;
                        head->headBool = 0;
                        newMem->startByte = 0;
                        head = newMem;

                        printf("ALLOCATED %s %ld\n", cmd2, newMem->startByte);


                    // If unsuccessful place
                    } else {
                        // print the fail
                        printf("FAIL REQUEST %s %d\n", cmd2, atoi(cmd3));
                    }


                    break;
                }


            }



            // Code for RELEASE A
        } else if((strcmp(cmd1, "RELEASE") == 0) || (strcmp(cmd1, "release") == 0)){
            //NOTE make sure to account for nextfit pointer stuff when releasing
            current = head;
            foundReleaseBool = 0;

            while((current->next != NULL) && (foundReleaseBool == 0)){
                current = current->next;

                //printf("%s, %ld", current->name, current->startByte);

                if (strcmp(cmd2, current->name) == 0){

                    if(nextFitStruct == current){

                        struct memory *tempNextFit = (struct memory*)malloc(sizeof(struct memory));
                        tempNextFit = current;
                        tempNextFit->name = NULL;
                        tempNextFit->startByte = (tempNextFit->size + tempNextFit->startByte);
                        tempNextFit->size = 0;
                        nextFitStruct = tempNextFit;
                    }

                    if(current == head){
                        current->next->headBool == 1;
                        current->next->prev = NULL;
                        current->next = NULL;


                    } else if (current->next == NULL){
                        current->prev->next = NULL;
                        current->prev->lastBool = 1;
                        current->prev = NULL;


                    } else if (current->next != NULL){
                        

                        current->prev->next = current->next;
                        current->next->prev = current->prev;
                    }
                    foundReleaseBool = 1;
                }
                



            }

                if(foundReleaseBool == 1){
                    printf("FREE %s %ld %ld", current->name, current->size, current->startByte);
                    current->startByte = -1;
                    current->size = -1;
                } else {
                    printf("FAIL RELEASE %s", cmd2);
                }
                printf("\n");


            //code for FIND A
        } else if((strcmp(cmd1, "FIND") == 0) || (strcmp(cmd1, "find") == 0)){
            current = head->next;
            foundBool = 0;

            while(current != NULL){
                                    //printf("search: %s, current: %s", cmd2, current->name);

                if(strcmp(cmd2, current->name) == 0){
                    printf("(%s, %ld, %ld)", current->name, current->size, current->startByte);
                    foundBool = 1;
                }

                current = current->next;

            }

            if(foundBool == 0){
                printf("FAULT");
            }

        printf("\n");

            
        }




    }


    fclose(fin);
    return 0;
}