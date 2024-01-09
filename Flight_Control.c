#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_FLIGHTS 100

void Menu();

struct Flight {
    int number;
    int type;
    char from[50];
    char to[50];
    char date[20];
    char time[10];
};

void Menu();
	int first_process(struct Flight *flight);
	void add_flight(struct Flight *flight,int num_flights, int* ptr);
	void update_flight(struct Flight *flight,const int num_flights);
	void search_departure_city(struct Flight *flight, const int num_flights);
	void search_arrival_city(struct Flight *flight,const int num_flights);
	void list_of_flight(struct Flight *flight,const int num_flights);

int main() {
    Menu();
    return 0;
}

void Menu(){
	bool run = true ;
	do{
		struct Flight flights[MAX_FLIGHTS];
    		int num_flights = first_process(flights);
    		int *num_flights_ptr = &num_flights;
    		int temp;
    
			printf("\nMENU:\n1. Add a new flight\n2. Update a flight\n3. Search for a flight with departure city\n4. Search for a flights with arrival city\n5. List all flights\n6. Exit\nEnter your choice(1-6): ");
    		scanf("%d",&temp);
    		switch (temp)
		    		{
		    	case 1:
		        	add_flight(flights,num_flights,num_flights_ptr);
		        	break;
		    	case 2:
		    		update_flight(flights,num_flights);
		        	break;
		    	case 3:
		    		search_departure_city(flights, num_flights);
		        	break;
		    	case 4:
		    		search_arrival_city(flights, num_flights);
		        	break;
		    	case 5:
		    		list_of_flight(flights, num_flights);
		        	break;
		    	case 6:
		    		printf("\nYou are exiting a program.\n");
		    		run = false;
		        	break;
		    	default:
		       		break;
		    	}
			}while (run);
    
}

int first_process(struct Flight *flights){ 
    FILE *fp; 
    int num_flights = 0;
    char filename[] = "flights.txt"; 
    char line[200]; 
    char *token;
    int i;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("\nError: Could not open file. %s\n", filename);
        exit(0);
    }

    while (fgets(line, 100, fp) != NULL) {
        token = strtok(line, ",");
        flights[num_flights].number=atoi(token);
        token = strtok(NULL, ",");
        flights[num_flights].type=atoi(token);
        token = strtok(NULL, ",");
        strcpy(flights[num_flights].from, token);
        token = strtok(NULL, ",");
        strcpy(flights[num_flights].to, token);
        token = strtok(NULL, ",");
        strcpy(flights[num_flights].date, token);
        token = strtok(NULL, ",");
        strcpy(flights[num_flights].time, token);
        num_flights++;
    }
    fclose(fp);
    return num_flights;
}

void add_flight(struct Flight *flight,int num_flights, int* ptr){
    int number,type;
    char from[50],to[50],date[20],time[10];
    	printf("\nEnter flight number:\n");
    	scanf("%d",&number);
    	
	    printf("\nEnter flight type 1 for domestic 0 for international flights :\n");
	    scanf("%d",&type);
	    
	    printf("\nEnter the departure city of the flight:\n");
	    scanf("%s",from);
	    
	    printf("\nEnter the arrival city of the flight:\n");
	    scanf("%s",to);
	    
	    printf("\nEnter the flight date:\n");
	    scanf("%s",date);
	    
	    printf("\nEnter the flight time:\n");
	    scanf("%s",time);
	    
    num_flights++;
    
    flight[num_flights].number=number;
    flight[num_flights].type=type;
    strcpy(flight[num_flights].from,from);
    strcpy(flight[num_flights].to, to);
    strcpy(flight[num_flights].date, date);
    strcpy(flight[num_flights].time, time);
    
    FILE *fp; 
    
    char filename[] = "flights.txt";
    
    fp = fopen(filename, "a+");
    fprintf(fp,"\n%d,%d,%s,%s,%s,%s",number,type,from,to,date,time);
    fclose(fp);
    
    printf("\nFlight inserted successfully.\n");
    *ptr = num_flights;
}

void update_flight(struct Flight *flight, const int num_flights) {
    int temp, newType, i, check = 0;
    char newFrom[50], newTo[50], newDate[20], newTime[10];
    
    FILE *fp, *tempFile;
    
    char filename[] = "flights.txt";
    char tempFilename[] = "temp.txt";

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("\nError opening file.\n");
        return;
    }

    tempFile = fopen(tempFilename, "w");
    if (tempFile == NULL) {
        printf("\nError creating temporary file.\n");
        fclose(fp);
        return;
    }

    printf("\nEnter flight number to update:\n");
    scanf("%d", &temp);

    for (i = 0; i < num_flights; i++) {
        if (temp == flight[i].number) {
            check = 1;
            break;
        }
    }

    if (!check) {
        printf("\nFlight not found. Please enter a number already declared.\n");
        fclose(fp);
        fclose(tempFile);
        return;
    } else {
        printf("\nFlight found. Which field would you like to update?\n1. Type\n2. Departure City\n3. Arrival City\n4. Date\n5. Time\nEnter your choice (1-5):\n");
        scanf("%d", &temp);
        switch (temp) {
            case 1:
                printf("Enter new type:\n");
                scanf("%d", &newType);
                flight[i].type = newType;
                break;
            case 2:
                printf("Enter new departure city:\n");
                scanf("%s", newFrom);
                strcpy(flight[i].from, newFrom);
                break;
            case 3:
                printf("Enter new arrival city:\n");
                scanf("%s", newTo);
                strcpy(flight[i].to, newTo);
                break;
            case 4:
                printf("Enter new date:\n");
                scanf("%s", newDate);
                strcpy(flight[i].date, newDate);
                break;
            case 5:
                printf("Enter new time:\n");
                scanf("%s", newTime);
                strcpy(flight[i].time, newTime);
                break;
            default:
                printf("\nInvalid choice !\n");
                fclose(fp);
                fclose(tempFile);
                return;
        }

        char line[100];
        while (fgets(line, sizeof(line), fp)) {
            int number;
            sscanf(line, "%d,", &number);
            
            if (number == flight[i].number) {
            	
            	printf(tempFile, "%d,%d,%s,%s,%s,%s", flight[i].number, flight[i].type, flight[i].from, flight[i].to, flight[i].date, flight[i].time);
            	
        		} else {
           			 fprintf(tempFile, "%s", line);
        			}
   		}

    fclose(fp);
    fclose(tempFile);
    
    remove(filename);
    rename(tempFilename, filename);

    printf("\nFlight updated successfully.\n");
		}
}


void search_departure_city(struct Flight *flights, const int num_flights) {
    char searchCity[50];
    int i, found = 0;

    printf("\nEnter the departure city to search: ");
    scanf("%s", searchCity);

    printf("\nFlights with departure city '%s':\n\n", searchCity);
    printf("--------------------------------------------------\n");
    for (i = 0; i < num_flights; i++) {
        if (strcmp(flights[i].from, searchCity) == 0) {
            printf("Flight Number: %d\n", flights[i].number);
            printf("Type: %d\n", flights[i].type);
            printf("Arrival: %s\n", flights[i].to);
            printf("Date: %s\n", flights[i].date);
            printf("Time: %s", flights[i].time);
            printf("--------------------------------------------------\n");
            found = 1;
        }
    }

    if (!found) {
        printf("\nNo flights found with entered departure city!'%s'\n", searchCity);
    }
}
void search_arrival_city(struct Flight *flights, const int num_flights) {
    char searchCity[50];
    int i, found = 0;

    printf("\nEnter the arrival city to search: ");
    scanf("%s", searchCity);

    printf("\nFlights with arrival city '%s':\n\n", searchCity);
    printf("--------------------------------------------------\n");
    for (i = 0; i < num_flights; i++) {
        if (strcmp(flights[i].to, searchCity) == 0) {
            printf("Flight Number: %d\n", flights[i].number);
            printf("Type: %d\n", flights[i].type);
            printf("Departure: %s\n", flights[i].from);
            printf("Date: %s\n", flights[i].date);
            printf("Time: %s", flights[i].time);
            printf("--------------------------------------------------\n");
            found = 1;
        }
    }

    if (!found) {
        printf("\nNo flights found with entered arrival city!'%s'\n", searchCity);
    }
}
void list_of_flight(struct Flight *flights, const int num_flights) {
    int i;
    
    printf("\n%-15s%-10s%-20s%-20s%-15s%s\n", "Number", "D/I", "Departure", "Arrival", "Date", "Time");
    printf("-------------------------------------------------------------------------------------\n");
    
    for (i = 0; i < num_flights; i++) {
        printf("%-15d%-10d%-20s%-20s%-15s%s\n", flights[i].number, flights[i].type, flights[i].from, flights[i].to, flights[i].date, flights[i].time);
    }
    
	printf("-------------------------------------------------------------------------------------\n");
	
    if (num_flights == 0) {
        printf("\nNo flights found.\n");
    }
}
