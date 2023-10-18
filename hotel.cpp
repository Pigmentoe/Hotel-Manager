/*
Hotel Simulator Project
5/7/2023
Thomas Landzaat
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#define FLOOR_SIZE 10

typedef struct{
    int roomNumber;
    int occupancy;
    char name[20];
    int rate;
} Room;

/*
upper and lower are inclusive
*/
bool filterInput(char *input, int lower, int upper){
    while(fgets(input, 2, stdin) != 0){
        if(atoi(input) >= lower && atoi(input) <= upper){
            return true;
        }
    }
    return false;
}

void initialize(Room floor[], int size){
    for(int index = 0; index < 10; index++) {
        floor[index].roomNumber = (index + 1); // Indicies start counting at 0 while rooms logically start at 1
        floor[index].occupancy = 0; //Initialize room occupancy to 0
        strcpy(floor[index].name, ""/*Indicate that there is no one in the room*/);
    }
}

/*
Floor must not be full
*/
int checkin(Room floor[], int size, int floorNum, char occChoice[], char name[], int rate){
    char rateChoice[2];
    int index;
    
    for(index = 0; index < FLOOR_SIZE; index++){
        if(floor[index].occupancy == 0){
            floor[index].occupancy = atoi(occChoice);
            floor[index].rate = rate;
            strcpy(floor[index].name, name);
            break;
        }
    }
    if(index == FLOOR_SIZE){
        return -1;
    }
    printf("Room Number: %d\n", floorNum*100 + floor[index].roomNumber);
    return index;
}

int availableRooms(Room floor[], int size){//count the number of rooms with occ 0 and add to the tally each time (per floor)
    int sum = 0;
    for(int i = 0; i < size; i++){
        if(floor[i].occupancy == 0)
            sum++;
    }
    return sum;
}

int numOccupants(Room floor[], int size){// walk through each floor's occupancy array and tally the number of people
    int total = 0;
    for(int i = 0; i < size; i++){
        total += floor[i].occupancy;
    }
    return total;
}

int nightRev(Room floor[], int size){//multiply rate by occupancy per room 
    int total = 0;
    for(int i = 0; i < size; i++){
        total += floor[i].occupancy * floor[i].rate;
    }
    return total;
}

int main(){
    Room f1[FLOOR_SIZE];
    Room f2[FLOOR_SIZE];
    Room f3[FLOOR_SIZE];
    int index, result, result2, totalOccupancy = 0, totalRevenue = 0;
    char menuChoice[2];
    char rateChoice[2];
    char occChoice[2];
    char floorOut[4];
    int floorOuti, floorRoom;
    char roomNum[3];
    char roomNum2[2];
    char name[20];
    rateChoice[0] = 1;
    char psuedoRate[3];
    psuedoRate[0] = 1;
    char buff[2];
    int tries = 0;
    bool isFull = false; // is the hotel full
    
    initialize(f1, FLOOR_SIZE);
    initialize(f2, FLOOR_SIZE);
    initialize(f3, FLOOR_SIZE);

    while(1){
        printf("\n\nPlease enter an option 1-5 or 6 to quit\n\n");
        printf("1. Check in a customer\n");
        printf("2. Check the Capacity of the Hotel\n");
        printf("3. Retrieve the Evacuation Count\n");
        printf("4. Check Nightly Income\n");
        printf("5. Check out a customer\n");
        printf("6. Registry of Guests by Floor\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        
        filterInput(menuChoice, 1, 7);

        switch (atoi(menuChoice)) {
            case 1: // Check in a customer
                while(1){
                    printf("\n\nPlease enter desired rate\n");
                    printf("1. Economy ($80 a night)\n");
                    printf("2. Business ($90 a night)\n");
                    printf("3. Executive ($100 a night)\n");
                    
                    if(filterInput(rateChoice, 1, 3)) break;
                } 
                if(availableRooms(f1, FLOOR_SIZE) == 0 && availableRooms(f2, FLOOR_SIZE) == 0 && availableRooms(f3, FLOOR_SIZE) == 0){
                    isFull = true;
                    printf("\nSorry the Hotel is Full\n");//If the hotel is completely full tell them so and return to main menu
                    rateChoice[0] = 0;
                    break;
                }
                    
                while(1){
                    getchar();
                    printf("\nPlease enter name: ");
                    fgets(name, 20, stdin);
                    break;
                }
    
                    while(1){ 
                        printf("\nPlease enter number of guests(1-4): ");
                        if(filterInput(occChoice, 1, 4)) break;
                    }
                
                strcpy(psuedoRate, rateChoice);// copying the rate value to another variable for modification because rate does not change if desired floor is full
                switch(atoi(psuedoRate)){
                    case 1:
                        strcpy(psuedoRate, "80");
                        break;
                    case 2:
                        strcpy(psuedoRate, "90");
                        break;
                    case 3:
                        strcpy(psuedoRate, "100");
                        break;
                }


                BAD_FLOOR: 
                switch(atoi(rateChoice)){
                    case 1:
                        if(checkin(f1, FLOOR_SIZE, 1, occChoice, name, atoi(psuedoRate)) == -1){//If the floor is full function returns -1, try next floor in list from %3 +1
                            sprintf (buff, "%d", (atoi(rateChoice) % 3 + 1));
                            strcpy(rateChoice, buff);
                            goto BAD_FLOOR;
                        }
                            
                    break;
                    case 2:
                        if(checkin(f2, FLOOR_SIZE, 2, occChoice, name, atoi(psuedoRate)) == -1){
                            sprintf (buff, "%d", (atoi(rateChoice) % 3 + 1));
                            strcpy(rateChoice, buff);
                            goto BAD_FLOOR;
                        }
                            
                    break;
                    case 3:
                        if(checkin(f3, FLOOR_SIZE, 3, occChoice, name, atoi(psuedoRate)) == -1){
                            sprintf (buff, "%d", (atoi(rateChoice) % 3 + 1));
                            strcpy(rateChoice, buff);
                            goto BAD_FLOOR;
                        }
                            
                    break;
                    default: 
                    break;
                }
                break;
            case 2: // Check Capacity
                printf("\n\nEconomy Floor has %d Rooms Available.\n", availableRooms(f1, FLOOR_SIZE));
                printf("Business Floor has %d Rooms Available.\n", availableRooms(f2, FLOOR_SIZE));
                printf("Executive Floor has %d Rooms Available.\n", availableRooms(f3, FLOOR_SIZE));
                break;
            case 3: // Evac Count
                totalOccupancy = 0;
                totalOccupancy += numOccupants(f1, FLOOR_SIZE);
                totalOccupancy += numOccupants(f2, FLOOR_SIZE);
                totalOccupancy += numOccupants(f3, FLOOR_SIZE);
                printf("\n\nTotal number of guests: %d\n", totalOccupancy);
                break;
            case 4: // Nightly Cost
                totalRevenue = 0;
                totalRevenue += nightRev(f1, FLOOR_SIZE);
                totalRevenue += nightRev(f2, FLOOR_SIZE);
                totalRevenue += nightRev(f3, FLOOR_SIZE);
                printf("\n\nTotal Nightly Revenue: $%d\n", totalRevenue);
                break;
            case 5: // Checkout
                while(1){ 
                    printf("\nPlease enter Room Number: ");
                    getchar();
                    fgets(floorOut, 4, stdin);
                    if(atoi(floorOut) >= 101 && atoi(floorOut) <= 310)
                        break;
                }
                floorOuti = ((atoi(floorOut)/100)); // essentially takes first element of array as int from int math rounding
                floorRoom = ((atoi(floorOut) % 100) -1); // essentially grabs last 2 elements of array as int (%) and subtracts one because rooms # is one ahead of index
                getchar();

                ENTERNAME:
                printf("\nPlease enter name under booking: ");
                fgets(name, 20, stdin);

                    switch(floorOuti){
                        case 1:
                                if(strcmp(name, f1[floorRoom].name) == 0){//If the given name matches the name under given room. set occ to 0 and empty booking name
                                    f1[floorRoom].occupancy = 0;
                                    strcpy(f1[floorRoom].name, ""); 
                                }
                                else{
                                printf("Name does not match\n");
                                tries++;
                                if(tries == 3){
                                    printf("\nToo many incorrect attempts\n");
                                    break;
                                }
                                goto ENTERNAME;
                            }
                            printf("\n\nSuccessfully checked out!\n");
                            break;

                        case 2:
                            if(strcmp(name, f2[floorRoom].name) == 0){
                                    f2[floorRoom].occupancy = 0;
                                    strcpy(f2[floorRoom].name, ""); 
                                }
                                else{
                                printf("Name does not match\n");
                                tries++;
                                if(tries == 3){
                                    printf("\nToo many incorrect attempts\n");
                                    break;
                                }
                                goto ENTERNAME;
                            }
                            break;
                        case 3:
                            if(strcmp(name, f3[floorRoom].name) == 0){
                                    f3[floorRoom].occupancy = 0;
                                    strcpy(f3[floorRoom].name, ""); 
                                }
                                else{
                                printf("Name does not match\n");
                                tries++;
                                if(tries == 3){
                                    printf("\nToo many incorrect attempts\n");
                                    break;
                                }
                                goto ENTERNAME;
                            }
                            break;
                        }
                break;
            case 6://Registry
                for(index = 0; index < FLOOR_SIZE; index++){
                    if((f1[index].occupancy) != 0){
                        printf("\nRoom: %d", (100 +f1[index].roomNumber));
                        printf("\t %s", f1[index].name);
                    }
                }
                for(index = 0; index < FLOOR_SIZE; index++){
                    if((f2[index].occupancy) != 0){
                        printf("Room: %d", (200 +f2[index].roomNumber));
                        printf("\t %s", f2[index].name);
                    }
                }
                for(index = 0; index < FLOOR_SIZE; index++){
                    if((f3[index].occupancy) != 0){
                        printf("Room: %d", (300 +f3[index].roomNumber));
                        printf("\t %s", f3[index].name);
                    }
                }                                
                break;
            case 7://Quit
                exit(1);//quit operation terminates program
                break;

        }
    }
}
