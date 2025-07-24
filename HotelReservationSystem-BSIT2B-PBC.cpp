#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>

#define MAX_RESERVATIONS 100
#define NUM_ROOMS 106
#define NAME_LEN 50
#define PHONE_LEN 15

typedef enum {
    SOLO1, SOLO2, SOLO3,
    DUO1, DUO2, DUO3,
    SQUAD1, SQUAD2, SQUAD3,
    FAMILY1, FAMILY2, FAMILY3,
    INVALID
} RoomType;

typedef struct {
    int month;
    int day;
    int year;
} Date;

typedef struct {
    Date check_in;
    Date check_out;
    char name[NAME_LEN];
    char phone[PHONE_LEN];
    int num_guests;
} Reservation;

typedef struct {
    Reservation reservations[MAX_RESERVATIONS];
    int count;
    RoomType type;
} Room;

Room rooms[NUM_ROOMS];

void clear() {
    system("@cls||clear");
}

bool date_is_less(Date a, Date b) {
    if (a.year < b.year) return true;
    if (a.year > b.year) return false;
    if (a.month < b.month) return true;
    if (a.month > b.month) return false;
    return a.day < b.day;
}

bool date_is_equal(Date a, Date b) {
    return a.year == b.year && a.month == b.month && a.day == b.day;
}

bool check_availability(int room_number, Date check_in, Date check_out) {
    for (int i = 1; i < rooms[room_number].count; i++) {
        Reservation res = rooms[room_number].reservations[i];
        if (!(date_is_less(check_out, res.check_in) || date_is_less(res.check_out, check_in) || date_is_equal(check_out, res.check_in) || date_is_equal(res.check_out, check_in))) {
            return false; 
        }
    }
    return true;
}

bool make_reservation(int room_number, Date check_in, Date check_out, const char* name, const char* phone, int num_guests) {
    if (check_availability(room_number, check_in, check_out)) {
        Reservation* new_res = &rooms[room_number].reservations[rooms[room_number].count];
        new_res->check_in = check_in;
        new_res->check_out = check_out;
        strncpy(new_res->name, name, NAME_LEN);
        strncpy(new_res->phone, phone, PHONE_LEN);
        new_res->num_guests = num_guests;
        rooms[room_number].count++;
        return true;
    }
    return false;
}

void initialize_rooms() {
    for (int i = 1; i < NUM_ROOMS; i++) {
        rooms[i].count = 1;
        if (i < 6) {
            rooms[i].type = SOLO1;
        } else if (i < 11) {
            rooms[i].type = SOLO2;
        } else if (i < 16) {
            rooms[i].type = SOLO3;
        } else if (i < 26) {
            rooms[i].type = DUO1;
        } else if (i < 36) {
            rooms[i].type = DUO2;
        } else if (i < 46) {
            rooms[i].type = DUO3;
        } else if (i < 61) {
            rooms[i].type = SQUAD1;
        } else if (i < 76) {
            rooms[i].type = SQUAD2;
        } else if (i < 91) {
            rooms[i].type = SQUAD3;
        } else if (i < 96) {
            rooms[i].type = FAMILY1;
        } else if (i < 101) {
            rooms[i].type = FAMILY2;
        } else {
            rooms[i].type = FAMILY3;
        }
    }
}

void print_date(Date date) {
    printf("%02d-%02d-%04d", date.month, date.day, date.year);
}

void guest_list_menu(){
	int choice = 0;
	
	while(1){
		printf ("Choose a room type\n");
		printf ("1. Solo\n");
		printf ("2. Duo\n");
		printf ("3. Squad\n");
		printf ("4. Family\n");
		printf ("5. Exit\n");
		printf ("Enter Choice: ");
		int result = scanf ("%d", &choice);	
		clear();
		
		if (choice < 1 || choice > 5) {
            while (getchar() != '\n');
            printf("Invalid input. Please enter a number between 1 and 5.\n");
            printf("Press any key to continue...");
            getch();
            continue;
        }
		
		if (choice == 1){
		printf (">> Type 1 <<\n");
    		for (int i = 1; i < 16; i++){
    			if (i == 6){
    				printf ("\n\n>> Type 2 <<\n");
				} if (i == 11){
					printf ("\n\n>> Type 3 <<\n");
				}
    			if (rooms[i].type == SOLO1){
    				printf ("Room %d\n", i);
    			} else if (rooms[i].type == SOLO2){
   					printf ("Room %d\n", i);
				} else if (rooms[i].type == SOLO3){
    				printf ("Room %d\n", i);
				}
           	 	for (int j = 1; j < rooms[i].count; j++) {
           	    	printf("  Reservation %d: ", j);
           	    	print_date(rooms[i].reservations[j].check_in);
           	    	printf(" to ");
           	    	print_date(rooms[i].reservations[j].check_out);
          		   	printf(" - Name: %s, Phone: %s, Guests: %d\n", rooms[i].reservations[j].name, rooms[i].reservations[j].phone, rooms[i].reservations[j].num_guests);
            	}
			}
			printf("Press any key to continue...");
            getch();
            clear();
            continue;
		} else if (choice == 2){
			printf (">> Type 1 <<\n");
    		for (int i = 16 ; i < 46; i++){
    			if (i == 26){
    				printf ("\n\n>> Type 2 <<\n");
				} if (i == 36){
				printf ("\n\n>> Type 3 <<\n");
			}
    		if (rooms[i].type == DUO1){
    			printf ("Room %d\n", i);
    		} else if (rooms[i].type == DUO2){
   				printf ("Room %d\n", i);
			} else if (rooms[i].type == DUO3){
    			printf ("Room %d\n", i);
			}
            	for (int j = 1; j < rooms[i].count; j++) {
               		printf("  Reservation %d: ", j);
               		print_date(rooms[i].reservations[j].check_in);
           	    	printf(" to ");
           	    	print_date(rooms[i].reservations[j].check_out);
           	    	printf(" - Name: %s, Phone: %s, Guests: %d\n", rooms[i].reservations[j].name, rooms[i].reservations[j].phone, rooms[i].reservations[j].num_guests);
            	}	
	 		}
	 		printf("Press any key to continue...");
            getch();
            clear();
            continue;
		} else if (choice == 3){
			printf ("Type 1\n\n");
    		for (int i = 46 ; i < 91; i++){
    			if (i == 61){
    				printf ("\n\n>> Type 2 <<\n");
				} if (i == 76 ){
					printf ("\n\n>> Type 3 <<\n");
				}
    			if (rooms[i].type == SQUAD1){
    				printf ("Room %d\n", i);
    			} else if (rooms[i].type == SQUAD2){
   					printf ("Room %d\n", i);
				} else if (rooms[i].type == SQUAD3){
    				printf ("Room %d\n", i);
				}
            	for (int j = 1; j < rooms[i].count; j++) {
               		printf("  Reservation %d: ", j);
               		print_date(rooms[i].reservations[j].check_in);
           	    	printf(" to ");
           	    	print_date(rooms[i].reservations[j].check_out);
           	    	printf(" - Name: %s, Phone: %s, Guests: %d\n", rooms[i].reservations[j].name, rooms[i].reservations[j].phone, rooms[i].reservations[j].num_guests);
            	}	
			}
			printf("Press any key to continue...");
            getch();
            clear();
            continue;
		} else if (choice == 4){
			printf (">> Type 1 <<\n");
    		for (int i = 91 ; i < 106; i++){
    			if (i == 96){
    				printf ("\n\n>> Type 2 <<\n");
				} if (i == 101){
					printf ("\n\n>> Type 3 <<\n");
				}
    			if (rooms[i].type == FAMILY1){
    				printf ("Room %d\n", i);
    			} else if (rooms[i].type == FAMILY2){
   					printf ("Room %d\n", i);
				} else if (rooms[i].type == FAMILY3){
    				printf ("Room %d\n", i);
				}
            	for (int j = 1; j < rooms[i].count; j++) {
               		printf("  Reservation %d: ", j);
               		print_date(rooms[i].reservations[j].check_in);
           	    	printf(" to ");
           	    	print_date(rooms[i].reservations[j].check_out);
           	    	printf(" - Name: %s, Phone: %s, Guests: %d\n", rooms[i].reservations[j].name, rooms[i].reservations[j].phone, rooms[i].reservations[j].num_guests);
            	}
			}
			printf("Press any key to continue...");
            getch();
            clear();
            continue;	
		}
		
		if(choice == 5){
            clear();
            printf("Exiting....\n");
            break;
        }
	}
}

Date get_current_date() {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    Date current_date;
    current_date.month = tm.tm_mon + 1; // tm_mon is months since January (0-11)
    current_date.day = tm.tm_mday;
    current_date.year = tm.tm_year + 1900; // tm_year is years since 1900
    return current_date;
}

bool is_within_current_year(Date date) {
    Date current_date = get_current_date();
    return date.year == current_date.year;
}

bool is_date_valid(Date check_in, Date check_out) {
    Date current_date = get_current_date();
    
    if (!is_within_current_year(check_in) || !is_within_current_year(check_out)) {
        printf("Reservation dates must be within the current year.\n");
        return false;
    }
    
    if (date_is_less(check_in, current_date) || date_is_less(check_out, current_date)) {
        printf("Reservation dates must not be in the past.\n");
        return false;
    }

    if (!date_is_less(check_in, check_out)) {
        printf("Check-in date must be before check-out date.\n");
        return false;
    }

    return true;
}

RoomType determine_room_type(int num_guests) {
    if (num_guests == 1) return SOLO1; // Choosing the first subtype for simplicity
    if (num_guests == 2) return DUO1;  
    if (num_guests >= 3 && num_guests <= 4) return SQUAD1; 
    if (num_guests >= 5 && num_guests <= 8) return FAMILY1;  
    return INVALID;
}


void func1111(){
	printf("Room Accomodations You've Selected:\n\n25 sqm room \nQueen sized bed \nAir-conditioned room \nNon-smoking \n\n");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n");
    printf("* 40-inch LED flat-screen \n* Cable/Satellite TV \n");
    printf("* Bottled water \n* In-room dining service \n\n");
}
void func1112(){
	printf("Room Accomodations You've Selected:\n\n25 sqm room \nQueen sized bed \nAir-conditioned room \nNon-smoking \n\n");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n");
    printf("* 40-inch LED flat-screen \n* Cable/Satellite TV \n* Wireless internet access\n");
    printf("* Bottled water \n* Mini-refrigerator \n* In-room dining service \n\n");
}
void func1113(){
	printf("Room Accomodations You've Selected:\n\n25 sqm room \nQueen sized bed \nAir-conditioned room \nNon-smoking \n\n");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n");
    printf("* 40-inch LED flat-screen \n* Cable/Satellite TV \n* Wireless internet access \n* Coffee and tea making facilities \n");
    printf("* Bottled water \n* Mini-refrigerator \n* In-room dining service\n\n");
}
void func1121(){
	printf("Room Accomodations You've Selected:\n\n25 sqm room \nQueen sized bed \nAir-conditioned room \nNon-smoking \n\n");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n* Hair dyer \n* Bidet\n");
	printf("* 40-inch LED flat-screen \n* Cable/Satellite TV \n");
    printf("* Bottled water \n* In-room dining service \n\n");
}
void func1122(){
	printf("Room Accomodations You've Selected:\n\n25 sqm room \nQueen sized bed \nAir-conditioned room \nNon-smoking \n\n");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n* Hair dyer \n* Bidet\n");
	printf("* 40-inch LED flat-screen \n* Cable/Satellite TV \n* Wireless internet access\n");
    printf("* Bottled water \n* Mini-refrigerator \n* In-room dining service \n\n");
}
void func1123(){
	printf("Room Accomodations You've Selected:\n\n25 sqm room \nQueen sized bed \nAir-conditioned room \nNon-smoking \n\n");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n* Hair dyer \n* Bidet\n");
	printf("* 40-inch LED flat-screen \n* Cable/Satellite TV \n* Wireless internet access \n* Coffee and tea making facilities \n");
    printf("* Bottled water \n* Mini-refrigerator \n* In-room dining service\n\n");
}
void func1131(){
	printf("Room Accomodations You've Selected:\n\n25 sqm room \nQueen sized bed \nAir-conditioned room \nNon-smoking \n\n");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n* Hair dyer \n* Bidet \n* Bathrobes\n");
	printf("* 40-inch LED flat-screen \n* Cable/Satellite TV \n");
    printf("* Bottled water \n* In-room dining service \n\n");
}
void func1132(){
	printf("Room Accomodations You've Selected:\n\n25 sqm room \nQueen sized bed \nAir-conditioned room \nNon-smoking \n\n");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n* Hair dyer \n* Bidet \n* Bathrobes\n");
	printf("* 40-inch LED flat-screen \n* Cable/Satellite TV \n* Wireless internet access\n");
    printf("* Bottled water \n* Mini-refrigerator \n* In-room dining service \n\n");
}
void func1133(){
	printf("Room Accomodations You've Selected:\n\n25 sqm room \nQueen sized bed \nAir-conditioned room \nNon-smoking \n\n");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n* Hair dyer \n* Bidet \n* Bathrobes\n");
	printf("* 40-inch LED flat-screen \n* Cable/Satellite TV \n* Wireless internet access \n* Coffee and tea making facilities \n");
    printf("* Bottled water \n* Mini-refrigerator \n* In-room dining service\n\n");
}
void func1211(){
	printf("Room Accomodations You've Selected:\n\n25 sqm room \nQueen sized bed or Twin beds\nAir-conditioned room \nNon-smoking \n\n");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n");
	printf("* 40-inch LED flat-screen \n* Cable/Satellite TV \n");
    printf("* Bottled water \n* In-room dining service \n\n");
}
void func1212(){
	printf("Room Accomodations You've Selected:\n\n25 sqm room \nQueen sized bed or Twin beds\nAir-conditioned room \nNon-smoking \n\n");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n");
	printf("* 40-inch LED flat-screen \n* Cable/Satellite TV \n* Wireless internet access\n");
    printf("* Bottled water \n* Mini-refrigerator \n* In-room dining service \n\n");
}
void func1213(){
	printf("Room Accomodations You've Selected:\n\n25 sqm room \nQueen sized bed or Twin beds\nAir-conditioned room \nNon-smoking \n\n");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n");
	printf("* 40-inch LED flat-screen \n* Cable/Satellite TV \n* Wireless internet access \n* Coffee and tea making facilities \n");
    printf("* Bottled water \n* Mini-refrigerator \n* In-room dining service\n\n");
}
void func1221(){
	printf("Room Accomodations You've Selected:\n\n25 sqm room \nQueen sized bed or Twin beds\nAir-conditioned room \nNon-smoking \n\n");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n* Hair dyer \n* Bidet\n");
	printf("* 40-inch LED flat-screen \n* Cable/Satellite TV \n");
    printf("* Bottled water \n* In-room dining service \n\n");
}
void func1222(){
	printf("Room Accomodations You've Selected:\n\n25 sqm room \nQueen sized bed or Twin beds\nAir-conditioned room \nNon-smoking \n\n");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n* Hair dyer \n* Bidet\n");
	printf("* 40-inch LED flat-screen \n* Cable/Satellite TV \n* Wireless internet access\n");
    printf("* Bottled water \n* Mini-refrigerator \n* In-room dining service \n\n");
}
void func1223(){
	printf("Room Accomodations You've Selected:\n\n25 sqm room \nQueen sized bed or Twin beds\nAir-conditioned room \nNon-smoking \n\n");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n* Hair dyer \n* Bidet\n");
	printf("* 40-inch LED flat-screen \n* Cable/Satellite TV \n* Wireless internet access \n* Coffee and tea making facilities \n");
    printf("* Bottled water \n* Mini-refrigerator \n* In-room dining service\n\n");
}
void func1231(){
	printf("Room Accomodations You've Selected:\n\n25 sqm room \nQueen sized bed or Twin beds\nAir-conditioned room \nNon-smoking \n\n");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n* Hair dyer \n* Bidet\n");
	printf("* 40-inch LED flat-screen \n* Cable/Satellite TV \n");
    printf("* Bottled water \n* In-room dining service \n\n");
}
void func1232(){
	printf("Room Accomodations You've Selected:\n\n25 sqm room \nQueen sized bed or Twin beds\nAir-conditioned room \nNon-smoking \n\n");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n* Hair dyer \n* Bidet\n");
	printf("* 40-inch LED flat-screen \n* Cable/Satellite TV \n* Wireless internet access\n");
    printf("* Bottled water \n* Mini-refrigerator \n* In-room dining service \n\n");
}
void func1233(){
	printf("Room Accomodations You've Selected:\n\n25 sqm room \nQueen sized bed or Twin beds\nAir-conditioned room \nNon-smoking \n\n");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n* Hair dyer \n* Bidet\n");
	printf("* 40-inch LED flat-screen \n* Cable/Satellite TV \n* Wireless internet access \n* Coffee and tea making facilities \n");
    printf("* Bottled water \n* Mini-refrigerator \n* In-room dining service\n\n");
}
void func1311(){
	printf("Room Accomodations You've Selected:\n\n25 sqm room \nKing sized bed\nAir-conditioned room \nNon-smoking \n\n");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n");
	printf("* 40-inch LED flat-screen \n* Cable/Satellite TV \n");
    printf("* Bottled water \n* In-room dining service \n\n");
}
void func1312(){
	printf("Room Accomodations You've Selected:\n\n25 sqm room \nKing sized bed\nAir-conditioned room \nNon-smoking \n\n");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n");
	printf("* 40-inch LED flat-screen \n* Cable/Satellite TV \n* Wireless internet access\n");
    printf("* Bottled water \n* Mini-refrigerator \n* In-room dining service \n\n");
}
void func1313(){
	printf("Room Accomodations You've Selected:\n\n25 sqm room \nKing sized bed\nAir-conditioned room \nNon-smoking \n\n");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n");
	printf("* 40-inch LED flat-screen \n* Cable/Satellite TV \n* Wireless internet access \n* Coffee and tea making facilities \n");
    printf("* Bottled water \n* Mini-refrigerator \n* In-room dining service\n\n");
}
void func1321(){
	printf("Room Accomodations You've Selected:\n\n25 sqm room \nKing sized bed\nAir-conditioned room \nNon-smoking \n\n");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n* Hair dyer \n* Bidet\n");
	printf("* 40-inch LED flat-screen \n* Cable/Satellite TV \n");
    printf("* Bottled water \n* In-room dining service \n\n");
}
void func1322(){
	printf("Room Accomodations You've Selected:\n\n25 sqm room \nKing sized bed\nAir-conditioned room \nNon-smoking \n\n");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n* Hair dyer \n* Bidet\n");
	printf("* 40-inch LED flat-screen \n* Cable/Satellite TV \n* Wireless internet access\n");
    printf("* Bottled water \n* Mini-refrigerator \n* In-room dining service \n\n");
}
void func1323(){
	printf("Room Accomodations You've Selected:\n\n25 sqm room \nKing sized bed\nAir-conditioned room \nNon-smoking \n\n");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n* Hair dyer \n* Bidet\n");
	printf("* 40-inch LED flat-screen \n* Cable/Satellite TV \n* Wireless internet access \n* Coffee and tea making facilities \n");
    printf("* Bottled water \n* Mini-refrigerator \n* In-room dining service\n\n");
}
void func1331(){
	printf("Room Accomodations You've Selected:\n\n25 sqm room \nKing sized bed\nAir-conditioned room \nNon-smoking \n\n");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n* Hair dyer \n* Bidet \n* Bathrobes\n");
	printf("* 40-inch LED flat-screen \n* Cable/Satellite TV \n");
    printf("* Bottled water \n* In-room dining service \n\n");
}
void func1332(){
	printf("Room Accomodations You've Selected:\n\n25 sqm room \nKing sized bed\nAir-conditioned room \nNon-smoking \n\n");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n* Hair dyer \n* Bidet \n* Bathrobes\n");
	printf("* 40-inch LED flat-screen \n* Cable/Satellite TV \n* Wireless internet access\n");
    printf("* Bottled water \n* Mini-refrigerator \n* In-room dining service \n\n");
}
void func1333(){
	printf("Room Accomodations You've Selected:\n\n25 sqm room \nKing sized bed\nAir-conditioned room \nNon-smoking \n\n");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n* Hair dyer \n* Bidet \n* Bathrobes\n");
	printf("* 40-inch LED flat-screen \n* Cable/Satellite TV \n* Wireless internet access \n* Coffee and tea making facilities \n");
    printf("* Bottled water \n* Mini-refrigerator \n* In-room dining service\n\n");
}

void func2111(){
	printf("Room Accomodations You've Selected:\n\n30 sqm room \nQueen-sized bed \nSofa \nAir-conditioned room \nNon-smoking \n\n");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n");
    printf("* 40-inch LED flat-screen \n* Cable/Satellite TV \n");
    printf("* Bottled water \n* In-room dining service \n\n");
}
void func2112(){
	printf("Room Accomodations You've Selected:\n\n30 sqm room \nQueen-sized bed \nSofa \nAir-conditioned room \nNon-smoking \n\n");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n");
    printf("* 40-inch LED flat-screen \n* Cable/Satellite TV \n* Wireless internet access\n");
    printf("* Bottled water \n* Mini-refrigerator \n* In-room dining service \n\n");
}
void func2113(){
	printf("Room Accomodations You've Selected:\n\n30 sqm room \nQueen-sized bed \nSofa \nAir-conditioned room \nNon-smoking \n\n");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n");
    printf("* 40-inch LED flat-screen \n* Cable/Satellite TV \n* Wireless internet access \n* Coffee and tea making facilities \n");
    printf("* Bottled water \n* Mini-refrigerator \n* In-room dining service\n\n");
}
void func2121(){
	printf("Room Accomodations You've Selected:\n\n30 sqm room \nQueen-sized bed \nSofa \nAir-conditioned room \nNon-smoking \n\n");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n* Hair dyer \n* Bidet\n");
	printf("* 40-inch LED flat-screen \n* Cable/Satellite TV \n");
    printf("* Bottled water \n* In-room dining service \n\n");
}
void func2122(){
	printf("Room Accomodations You've Selected:\n\n30 sqm room \nQueen-sized bed \nSofa \nAir-conditioned room \nNon-smoking \n\n");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n* Hair dyer \n* Bidet\n");
	printf("* 40-inch LED flat-screen \n* Cable/Satellite TV \n* Wireless internet access\n");
    printf("* Bottled water \n* Mini-refrigerator \n* In-room dining service \n\n");
}
void func2123(){
	printf("Room Accomodations You've Selected:\n\n30 sqm room \nQueen-sized bed \nSofa \nAir-conditioned room \nNon-smoking \n\n");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n* Hair dyer \n* Bidet\n");
	printf("* 40-inch LED flat-screen \n* Cable/Satellite TV \n* Wireless internet access \n* Coffee and tea making facilities \n");
    printf("* Bottled water \n* Mini-refrigerator \n* In-room dining service\n\n");
}
void func2131(){
	printf("Room Accomodations You've Selected:\n\n30 sqm room \nQueen-sized bed \nSofa \nAir-conditioned room \nNon-smoking \n\n");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n* Hair dyer \n* Bidet \n* Bathrobes\n");
	printf("* 40-inch LED flat-screen \n* Cable/Satellite TV \n");
    printf("* Bottled water \n* In-room dining service \n\n");
}
void func2132(){
	printf("Room Accomodations You've Selected:\n\n30 sqm room \nQueen-sized bed \nSofa \nAir-conditioned room \nNon-smoking \n\n");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n* Hair dyer \n* Bidet \n* Bathrobes\n");
	printf("* 40-inch LED flat-screen \n* Cable/Satellite TV \n* Wireless internet access\n");
    printf("* Bottled water \n* Mini-refrigerator \n* In-room dining service \n\n");
}
void func2133(){
	printf("Room Accomodations You've Selected:\n\n30 sqm room \nQueen-sized bed \nSofa \nAir-conditioned room \nNon-smoking \n\n");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n* Hair dyer \n* Bidet \n* Bathrobes\n");
	printf("* 40-inch LED flat-screen \n* Cable/Satellite TV \n* Wireless internet access \n* Coffee and tea making facilities \n");
    printf("* Bottled water \n* Mini-refrigerator \n* In-room dining service\n\n");
}
void func2211(){
	printf("Room Accomodations You've Selected:\n\n35 sqm room \nQueen-sized bed or Twin beds \nSofa \nAir-conditioned room \nNon-smoking \n\n");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n");
	printf("* 40-inch LED flat-screen \n* Cable/Satellite TV \n");
    printf("* Bottled water \n* In-room dining service \n\n");
}
void func2212(){
	printf("Room Accomodations You've Selected:\n\n35 sqm room \nQueen-sized bed or Twin beds \nSofa \nAir-conditioned room \nNon-smoking \n\n");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n");
	printf("* 40-inch LED flat-screen \n* Cable/Satellite TV \n* Wireless internet access\n");
    printf("* Bottled water \n* Mini-refrigerator \n* In-room dining service \n\n");
}
void func2213(){
	printf("Room Accomodations You've Selected:\n\n35 sqm room \nQueen-sized bed or Twin beds \nSofa \nAir-conditioned room \nNon-smoking \n\n");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n");
	printf("* 40-inch LED flat-screen \n* Cable/Satellite TV \n* Wireless internet access \n* Coffee and tea making facilities \n");
    printf("* Bottled water \n* Mini-refrigerator \n* In-room dining service\n\n");
}
void func2221(){
	printf("Room Accomodations You've Selected:\n\n35 sqm room \nQueen-sized bed or Twin beds \nSofa \nAir-conditioned room \nNon-smoking \n\n");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n* Hair dyer \n* Bidet\n");
	printf("* 40-inch LED flat-screen \n* Cable/Satellite TV \n");
    printf("* Bottled water \n* In-room dining service \n\n");
}
void func2222(){
	printf("Room Accomodations You've Selected:\n\n35 sqm room \nQueen-sized bed or Twin beds \nSofa \nAir-conditioned room \nNon-smoking \n\n");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n* Hair dyer \n* Bidet\n");
	printf("* 40-inch LED flat-screen \n* Cable/Satellite TV \n* Wireless internet access\n");
    printf("* Bottled water \n* Mini-refrigerator \n* In-room dining service \n\n");
}
void func2223(){
	printf("Room Accomodations You've Selected:\n\n35 sqm room \nQueen-sized bed or Twin beds \nSofa \nAir-conditioned room \nNon-smoking \n\n");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n* Hair dyer \n* Bidet\n");
	printf("* 40-inch LED flat-screen \n* Cable/Satellite TV \n* Wireless internet access \n* Coffee and tea making facilities \n");
    printf("* Bottled water \n* Mini-refrigerator \n* In-room dining service\n\n");
}
void func2231(){
	printf("Room Accomodations You've Selected:\n\n35 sqm room \nQueen-sized bed or Twin beds \nSofa \nAir-conditioned room \nNon-smoking \n\n");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n* Hair dyer \n* Bidet\n");
	printf("* 40-inch LED flat-screen \n* Cable/Satellite TV \n");
    printf("* Bottled water \n* In-room dining service \n\n");
}
void func2232(){
	printf("Room Accomodations You've Selected:\n\n35 sqm room \nQueen-sized bed or Twin beds \nSofa \nAir-conditioned room \nNon-smoking \n\n");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n* Hair dyer \n* Bidet\n");
	printf("* 40-inch LED flat-screen \n* Cable/Satellite TV \n* Wireless internet access\n");
    printf("* Bottled water \n* Mini-refrigerator \n* In-room dining service \n\n");
}
void func2233(){
	printf("Room Accomodations You've Selected:\n\n35 sqm room \nQueen-sized bed or Twin beds \nSofa \nAir-conditioned room \nNon-smoking \n\n");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n* Hair dyer \n* Bidet\n");
	printf("* 40-inch LED flat-screen \n* Cable/Satellite TV \n* Wireless internet access \n* Coffee and tea making facilities \n");
    printf("* Bottled water \n* Mini-refrigerator \n* In-room dining service\n\n");
}
void func2311(){
	printf("Room Accomodations You've Selected:\n\n40 sqm room \nking-sized bed and Twin beds \nSofa \nAir-conditioned room \nNon-smoking \nCity view \n\n");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n");
	printf("* 40-inch LED flat-screen \n* Cable/Satellite TV \n");
    printf("* Bottled water \n* In-room dining service \n\n");
}
void func2312(){
	printf("Room Accomodations You've Selected:\n\n40 sqm room \nking-sized bed and Twin beds \nSofa \nAir-conditioned room \nNon-smoking \nCity view \n\n");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n");
	printf("* 40-inch LED flat-screen \n* Cable/Satellite TV \n* Wireless internet access\n");
    printf("* Bottled water \n* Mini-refrigerator \n* In-room dining service \n\n");
}
void func2313(){
	printf("Room Accomodations You've Selected:\n\n40 sqm room \nking-sized bed and Twin beds \nSofa \nAir-conditioned room \nNon-smoking \nCity view \n\n");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n");
	printf("* 40-inch LED flat-screen \n* Cable/Satellite TV \n* Wireless internet access \n* Coffee and tea making facilities \n");
    printf("* Bottled water \n* Mini-refrigerator \n* In-room dining service\n\n");
}
void func2321(){
	printf("Room Accomodations You've Selected:\n\n40 sqm room \nking-sized bed and Twin beds \nSofa \nAir-conditioned room \nNon-smoking \nCity view \n\n");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n* Hair dyer \n* Bidet\n");
	printf("* 40-inch LED flat-screen \n* Cable/Satellite TV \n");
    printf("* Bottled water \n* In-room dining service \n\n");
}
void func2322(){
	printf("Room Accomodations You've Selected:\n\n40 sqm room \nking-sized bed and Twin beds \nSofa \nAir-conditioned room \nNon-smoking \nCity view \n\n");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n* Hair dyer \n* Bidet\n");
	printf("* 40-inch LED flat-screen \n* Cable/Satellite TV \n* Wireless internet access\n");
    printf("* Bottled water \n* Mini-refrigerator \n* In-room dining service \n\n");
}
void func2323(){
	printf("Room Accomodations You've Selected:\n\n40 sqm room \nking-sized bed and Twin beds \nSofa \nAir-conditioned room \nNon-smoking \nCity view \n\n");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n* Hair dyer \n* Bidet\n");
	printf("* 40-inch LED flat-screen \n* Cable/Satellite TV \n* Wireless internet access \n* Coffee and tea making facilities \n");
    printf("* Bottled water \n* Mini-refrigerator \n* In-room dining service\n\n");
}
void func2331(){
	printf("Room Accomodations You've Selected:\n\n40 sqm room \nking-sized bed and Twin beds \nSofa \nAir-conditioned room \nNon-smoking \nCity view \n\n");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n* Hair dyer \n* Bidet \n* Bathrobes\n");
	printf("* 40-inch LED flat-screen \n* Cable/Satellite TV \n");
    printf("* Bottled water \n* In-room dining service \n\n");
}
void func2332(){
	printf("Room Accomodations You've Selected:\n\n40 sqm room \nking-sized bed and Twin beds \nSofa \nAir-conditioned room \nNon-smoking \nCity view \n\n");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n* Hair dyer \n* Bidet \n* Bathrobes\n");
	printf("* 40-inch LED flat-screen \n* Cable/Satellite TV \n* Wireless internet access\n");
    printf("* Bottled water \n* Mini-refrigerator \n* In-room dining service \n\n");
}
void func2333(){
	printf("Room Accomodations You've Selected:\n\n40 sqm room \nking-sized bed and Twin beds \nSofa \nAir-conditioned room \nNon-smoking \nCity view \n\n");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n* Hair dyer \n* Bidet \n* Bathrobes\n");
	printf("* 40-inch LED flat-screen \n* Cable/Satellite TV \n* Wireless internet access \n* Coffee and tea making facilities \n");
    printf("* Bottled water \n* Mini-refrigerator \n* In-room dining service\n\n");
}

void func3111(){
	printf("Room Accomodations You've Selected:\n\n35 sqm room \nQueen-sized bed \nSofa \nAir-conditioned room \nNon-smoking \n\n");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n");
    printf("* 40-inch LED flat-screen \n* Cable/Satellite TV \n");
    printf("* Bottled water \n* In-room dining service \n\n");
}
void func3112(){
	printf("Room Accomodations You've Selected:\n\n35 sqm room \nQueen-sized bed \nSofa \nAir-conditioned room \nNon-smoking \n\n");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n");
    printf("* 40-inch LED flat-screen \n* Cable/Satellite TV \n* Wireless internet access\n");
    printf("* Bottled water \n* Mini-refrigerator \n* In-room dining service \n\n");
}
void func3113(){
	printf("Room Accomodations You've Selected:\n\n35 sqm room \nQueen-sized bed \nSofa \nAir-conditioned room \nNon-smoking \n\n");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n");
    printf("* 40-inch LED flat-screen \n* Cable/Satellite TV \n* Wireless internet access \n* Coffee and tea making facilities \n");
    printf("* Bottled water \n* Mini-refrigerator \n* In-room dining service\n\n");
}
void func3121(){
	printf("Room Accomodations You've Selected:\n\n35 sqm room \nQueen-sized bed \nSofa \nAir-conditioned room \nNon-smoking \n\n");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n* Hair dyer \n* Bidet\n");
	printf("* 40-inch LED flat-screen \n* Cable/Satellite TV \n");
    printf("* Bottled water \n* In-room dining service \n\n");
}
void func3122(){
	printf("Room Accomodations You've Selected:\n\n35 sqm room \nQueen-sized bed \nSofa \nAir-conditioned room \nNon-smoking \n\n");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n* Hair dyer \n* Bidet\n");
	printf("* 40-inch LED flat-screen \n* Cable/Satellite TV \n* Wireless internet access\n");
    printf("* Bottled water \n* Mini-refrigerator \n* In-room dining service \n\n");
}
void func3123(){
	printf("Room Accomodations You've Selected:\n\n35 sqm room \nQueen-sized bed \nSofa \nAir-conditioned room \nNon-smoking \n\n");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n* Hair dyer \n* Bidet\n");
	printf("* 40-inch LED flat-screen \n* Cable/Satellite TV \n* Wireless internet access \n* Coffee and tea making facilities \n");
    printf("* Bottled water \n* Mini-refrigerator \n* In-room dining service\n\n");
}
void func3131(){
	printf("Room Accomodations You've Selected:\n\n35 sqm room \nQueen-sized bed \nSofa \nAir-conditioned room \nNon-smoking \n\n");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n* Hair dyer \n* Bidet \n* Bathrobes\n");
	printf("* 40-inch LED flat-screen \n* Cable/Satellite TV \n");
    printf("* Bottled water \n* In-room dining service \n\n");
}
void func3132(){
	printf("Room Accomodations You've Selected:\n\n35 sqm room \nQueen-sized bed \nSofa \nAir-conditioned room \nNon-smoking \n\n");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n* Hair dyer \n* Bidet \n* Bathrobes\n");
	printf("* 40-inch LED flat-screen \n* Cable/Satellite TV \n* Wireless internet access\n");
    printf("* Bottled water \n* Mini-refrigerator \n* In-room dining service \n\n");
}
void func3133(){
	printf("Room Accomodations You've Selected:\n\n35 sqm room \nQueen-sized bed \nSofa \nAir-conditioned room \nNon-smoking \n\n");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n* Hair dyer \n* Bidet \n* Bathrobes\n");
	printf("* 40-inch LED flat-screen \n* Cable/Satellite TV \n* Wireless internet access \n* Coffee and tea making facilities \n");
    printf("* Bottled water \n* Mini-refrigerator \n* In-room dining service\n\n");
}
void func3211(){
	printf("Room Accomodations You've Selected:\n\n40 sqm room \nQueen-sized bed or Twin beds \nSofa \nAir-conditioned room \nNon-smoking \n\n");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n");
	printf("* 40-inch LED flat-screen \n* Cable/Satellite TV \n");
    printf("* Bottled water \n* In-room dining service \n\n");
}
void func3212(){
	printf("Room Accomodations You've Selected:\n\n40 sqm room \nQueen-sized bed or Twin beds \nSofa \nAir-conditioned room \nNon-smoking \n\n");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n");
	printf("* 40-inch LED flat-screen \n* Cable/Satellite TV \n* Wireless internet access\n");
    printf("* Bottled water \n* Mini-refrigerator \n* In-room dining service \n\n");
}
void func3213(){
	printf("Room Accomodations You've Selected:\n\n40 sqm room \nQueen-sized bed or Twin beds \nSofa \nAir-conditioned room \nNon-smoking \n\n");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n");
	printf("* 40-inch LED flat-screen \n* Cable/Satellite TV \n* Wireless internet access \n* Coffee and tea making facilities \n");
    printf("* Bottled water \n* Mini-refrigerator \n* In-room dining service\n\n");
}
void func3221(){
	printf("Room Accomodations You've Selected:\n\n40 sqm room \nQueen-sized bed or Twin beds \nSofa \nAir-conditioned room \nNon-smoking \n\n");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n* Hair dyer \n* Bidet\n");
	printf("* 40-inch LED flat-screen \n* Cable/Satellite TV \n");
    printf("* Bottled water \n* In-room dining service \n\n");
}
void func3222(){
	printf("Room Accomodations You've Selected:\n\n40 sqm room \nQueen-sized bed or Twin beds \nSofa \nAir-conditioned room \nNon-smoking \n\n");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n* Hair dyer \n* Bidet\n");
	printf("* 40-inch LED flat-screen \n* Cable/Satellite TV \n* Wireless internet access\n");
    printf("* Bottled water \n* Mini-refrigerator \n* In-room dining service \n\n");
}
void func3223(){
	printf("Room Accomodations You've Selected:\n\n40 sqm room \nQueen-sized bed or Twin beds \nSofa \nAir-conditioned room \nNon-smoking \n\n");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n* Hair dyer \n* Bidet\n");
	printf("* 40-inch LED flat-screen \n* Cable/Satellite TV \n* Wireless internet access \n* Coffee and tea making facilities \n");
    printf("* Bottled water \n* Mini-refrigerator \n* In-room dining service\n\n");
}
void func3231(){
	printf("Room Accomodations You've Selected:\n\n40 sqm room \nQueen-sized bed or Twin beds \nSofa \nAir-conditioned room \nNon-smoking \n\n");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n* Hair dyer \n* Bidet\n");
	printf("* 40-inch LED flat-screen \n* Cable/Satellite TV \n");
    printf("* Bottled water \n* In-room dining service \n\n");
}
void func3232(){
	printf("Room Accomodations You've Selected:\n\n40 sqm room \nQueen-sized bed or Twin beds \nSofa \nAir-conditioned room \nNon-smoking \n\n");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n* Hair dyer \n* Bidet\n");
	printf("* 40-inch LED flat-screen \n* Cable/Satellite TV \n* Wireless internet access\n");
    printf("* Bottled water \n* Mini-refrigerator \n* In-room dining service \n\n");
}
void func3233(){
	printf("Room Accomodations You've Selected:\n\n40 sqm room \nQueen-sized bed or Twin beds \nSofa \nAir-conditioned room \nNon-smoking \n\n");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n* Hair dyer \n* Bidet\n");
	printf("* 40-inch LED flat-screen \n* Cable/Satellite TV \n* Wireless internet access \n* Coffee and tea making facilities \n");
    printf("* Bottled water \n* Mini-refrigerator \n* In-room dining service\n\n");
}
void func3311(){
	printf("Room Accomodations You've Selected:\n\n45 sqm room \nking-sized bed and Twin beds \nSofa \nAir-conditioned room \nNon-smoking \nCity view \n\n");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n");
	printf("* 40-inch LED flat-screen \n* Cable/Satellite TV \n");
    printf("* Bottled water \n* In-room dining service \n\n");
}
void func3312(){
	printf("Room Accomodations You've Selected:\n\n45 sqm room \nking-sized bed and Twin beds \nSofa \nAir-conditioned room \nNon-smoking \nCity view \n\n");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n");
	printf("* 40-inch LED flat-screen \n* Cable/Satellite TV \n* Wireless internet access\n");
    printf("* Bottled water \n* Mini-refrigerator \n* In-room dining service \n\n");
}
void func3313(){
	printf("Room Accomodations You've Selected:\n\n45 sqm room \nking-sized bed and Twin beds \nSofa \nAir-conditioned room \nNon-smoking \nCity view \n\n");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n");
	printf("* 40-inch LED flat-screen \n* Cable/Satellite TV \n* Wireless internet access \n* Coffee and tea making facilities \n");
    printf("* Bottled water \n* Mini-refrigerator \n* In-room dining service\n\n");
}
void func3321(){
	printf("Room Accomodations You've Selected:\n\n45 sqm room \nking-sized bed and Twin beds \nSofa \nAir-conditioned room \nNon-smoking \nCity view \n\n");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n* Hair dyer \n* Bidet\n");
	printf("* 40-inch LED flat-screen \n* Cable/Satellite TV \n");
    printf("* Bottled water \n* In-room dining service \n\n");
}
void func3322(){
	printf("Room Accomodations You've Selected:\n\n45 sqm room \nking-sized bed and Twin beds \nSofa \nAir-conditioned room \nNon-smoking \nCity view \n\n");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n* Hair dyer \n* Bidet\n");
	printf("* 40-inch LED flat-screen \n* Cable/Satellite TV \n* Wireless internet access\n");
    printf("* Bottled water \n* Mini-refrigerator \n* In-room dining service \n\n");
}
void func3323(){
	printf("Room Accomodations You've Selected:\n\n45 sqm room \nking-sized bed and Twin beds \nSofa \nAir-conditioned room \nNon-smoking \nCity view \n\n");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n* Hair dyer \n* Bidet\n");
	printf("* 40-inch LED flat-screen \n* Cable/Satellite TV \n* Wireless internet access \n* Coffee and tea making facilities \n");
    printf("* Bottled water \n* Mini-refrigerator \n* In-room dining service\n\n");
}
void func3331(){
	printf("Room Accomodations You've Selected:\n\n45 sqm room \nking-sized bed and Twin beds \nSofa \nAir-conditioned room \nNon-smoking \nCity view \n\n");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n* Hair dyer \n* Bidet \n* Bathrobes\n");
	printf("* 40-inch LED flat-screen \n* Cable/Satellite TV \n");
    printf("* Bottled water \n* In-room dining service \n\n");
}
void func3332(){
	printf("Room Accomodations You've Selected:\n\n45 sqm room \nking-sized bed and Twin beds \nSofa \nAir-conditioned room \nNon-smoking \nCity view \n\n");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n* Hair dyer \n* Bidet \n* Bathrobes\n");
	printf("* 40-inch LED flat-screen \n* Cable/Satellite TV \n* Wireless internet access\n");
    printf("* Bottled water \n* Mini-refrigerator \n* In-room dining service \n\n");
}
void func3333(){
	printf("Room Accomodations You've Selected:\n\n45 sqm room \nking-sized bed and Twin beds \nSofa \nAir-conditioned room \nNon-smoking \nCity view \n\n");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n* Hair dyer \n* Bidet \n* Bathrobes\n");
	printf("* 40-inch LED flat-screen \n* Cable/Satellite TV \n* Wireless internet access \n* Coffee and tea making facilities \n");
    printf("* Bottled water \n* Mini-refrigerator \n* In-room dining service\n\n");
}

void func8111(){
	printf("Room Accomodations You've Selected:\n\n50 sqm room \nCity view \nQueen-sized \nAit-conditioned room \nNon-smoking \nBalcony");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n* Hair dyer \n* Bidet \n");
	printf("* 40-inch LED flat-screen \n* Cable/Satellite TV \n* Wireless internet access \n");
    printf("* Bottled water \n* In-room dining service\n\n");
}
void func8112(){
	printf("Room Accomodations You've Selected:\n\n50 sqm room \nCity view \nQueen-sized \nAit-conditioned room \nNon-smoking \nBalcony");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n* Hair dyer \n* Bidet \n");
	printf("* 40-inch LED flat-screen (Bedroom)\n* Cable/Satellite TV \n* Wireless internet access \n* Coffee and tea making facilities \n");
    printf("* Bottled water \n* Mini-refrigerator\n\n");
}
void func8113(){
	printf("Room Accomodations You've Selected:\n\n50 sqm room \nCity view \nQueen-sized \nAit-conditioned room \nNon-smoking \nBalcony");
	printf("* Toilet amenities \n* Bath linen and towels \n* Hot and cold shower \n* Slippers \n* Hair dyer \n* Bidet \n");
	printf("* 40-inch LED flat-screen (Bedroom)\n* Cable/Satellite TV \n* Wireless internet access \n* Coffee and tea making facilities \n");
    printf("* Bottled water \n* Mini-refrigerator \n* 49-inch LED flat-screen (Living room)\n\n");
}

int selection(int type_choice, int numguest){
	int type = 0;
	int comfort = 0;
	int num_guests = 0;
	int indulgence = 0;
	
	num_guests = numguest;
	type = type_choice;
	
	if(num_guests == 1) {
		printf("Solo type 1: \t\t\t\tSolo type 2:  \t\t\t\tSolo type 3:\n\n25 sqm room\t\t\t\t25 sqm room \t\t\t\t30 sqm room \nQueen sized bed\t\t\t\tQueen sized bed or Twin beds \t\tKing sized bed \nAir-conditioned room \t\t\tAir-conditioned room \t\t\tAir-conditioned room \nNon-smoking \t\t\t\tNon-smoking \t\t\t\tNon-Smoking\n\n");
    	
    	while (1) { 
        	printf("Select Type: ");
        	if (scanf("%d", &type) != 1) { 
           		while (getchar() != '\n');
          			printf("Invalid input. Please enter a valid integer.\n");
       		} else if (type >= 1 && type <= 3) {
				break;
			} else {
				printf("Invalid input. Please enter a number between 1 and 3.\n");
       		}
   		}
   		if (type == 1){
    			printf("----------------------------------------------------------------------------------------------------------\n");
				printf("\nOption 1: \t\t\t\tOption 2:  \t\t\t\tOption 3:\n\n");
    			printf("==AMENITIES== \t\t\t\t==AMENITIES== \t\t\t\t==AMENITIES==\n\n");
    			printf("For your Comfort: \t\t\tFor your Comfort: \t\t\tFor your Comfort:\n\n");
    			printf("* Toilet amenities \t\t\t* Toilet amenities \t\t\t* Toilet amenities\n* Bath linen and towels \t\t* Bath linen and towels \t\t* Bath linen and towels \n* Hot and cold shower \t\t\t* Hot and cold shower \t\t\t* Hot and cold shower \n* Slippers \t\t\t\t* Slippers \t\t\t\t* Slippers \n\t\t\t\t\t* Hair Dryer \t\t\t\t* Hair Dryer \n\t\t\t\t\t* Bidet \t\t\t\t* Bidet \n\t\t\t\t\t\t\t\t\t\t* Bathrobes\n\n");
    			while (1) { 
        			printf("Select Comfort: ");
        			if (scanf("%d", &comfort) != 1) { 
            			while (getchar() != '\n');
           			 	printf("Invalid input. Please enter a valid integer.\n");
        			} else if (comfort >= 1 && comfort <= 3) {
						break;
					} else {
						printf("Invalid input. Please enter a number between 1 and 3.\n");
       				}
   				}
    			if (comfort == 1) {
    				printf("\nOption 1: \t\t\t\tOption 2:  \t\t\t\tOption 3:\n\n");
    				printf("For your Indulgence: \t\t\tFor your Indulgence: \t\t\tFor your Indulgence: \n\n");
    				printf("* 40-inch LED flat-screen \t\t* 40-inch LED flat-sceen \t\t* 40-inch LED flat-screen \n* Cable/Satellite TV \t\t\t* Cable/Satellite TV \t\t\t* Cable/Satellite TV\n");
    				printf("* Bottled water \t\t\t* Bottled water \t\t\t* Bottled water\n* In-room dining service \t\t* In-room dining service \t\t* In-room dining service \n");
					printf("\t\t\t\t\t* Mini-refrigerator \t\t\t* Mini-refrigerator\n ");
					printf("\t\t\t\t\t* Wireless internet access\t\t* Wireless internet access\n");
					printf("\t\t\t\t\t\t\t\t\t\t* Coffee and tea making facilities \n\n");
					while (1) { 
        				printf("Choose Indulgence: ");
        				if (scanf("%d", &indulgence) != 1) { 
            				while (getchar() != '\n');
           			 		printf("Invalid input. Please enter a valid integer.\n");
        				} else if (indulgence >= 1 && indulgence <= 3) {
							break;
						} else {
							printf("Invalid input. Please enter a number between 1 and 3.\n");
       					}
   					}
					printf("----------------------------------------------------------------------------------------------------------\n");
					printf("You will be accomodated in a \x1b[31mSOLO TYPE 1\x1b[0m room.\n");
					if (indulgence == 1){
						func1111();
					}
					if (indulgence == 2){
						func1112();
					}
					if (indulgence == 3){
						func1113();
					}
					printf("----------------------------------------------------------------------------------------------------------\n");
				}
				if (comfort == 2) {
					printf("----------------------------------------------------------------------------------------------------------\n");
					printf("\nOption 1: \t\t\t\tOption 2:  \t\t\t\tOption 3:\n\n");
    				printf("For your Indulgence: \t\t\tFor your Indulgence: \t\t\tFor your Indulgence: \n\n");
    				printf("* 40-inch LED flat-screen \t\t* 40-inch LED flat-sceen \t\t* 40-inch LED flat-screen \n* Cable/Satellite TV \t\t\t* Cable/Satellite TV \t\t\t* Cable/Satellite TV\n");
    				printf("* Bottled water \t\t\t* Bottled water \t\t\t* Bottled water\n* In-room dining service \t\t* In-room dining service \t\t* In-room dining service \n");
					printf("\t\t\t\t\t* Mini-refrigerator \t\t\t* Mini-refrigerator\n ");
					printf("\t\t\t\t\t* Wireless internet access\t\t* Wireless internet access\n");
					printf("\t\t\t\t\t\t\t\t\t\t* Coffee and tea making facilities \n\n");
					while (1) { 
        				printf("Choose Indulgence: ");
        				if (scanf("%d", &indulgence) != 1) { 
            				while (getchar() != '\n');
           			 		printf("Invalid input. Please enter a valid integer.\n");
        				} else if (indulgence >= 1 && indulgence <= 3) {
							break;
						} else {
							printf("Invalid input. Please enter a number between 1 and 3.\n");
       					}
   					}
					printf("----------------------------------------------------------------------------------------------------------\n");
					printf("You will be accomodated in a \x1b[31mSOLO TYPE 1\x1b[0m room.\n");
					if (indulgence == 1){
						func1121();
					}
					if (indulgence == 2){
						func1122();
					}
					if (indulgence == 3){
						func1123();
					}
					printf("----------------------------------------------------------------------------------------------------------\n");
				}
				if (comfort == 3) {
					printf("----------------------------------------------------------------------------------------------------------\n");
					printf("\nOption 1: \t\t\t\tOption 2:  \t\t\t\tOption 3:\n\n");
    				printf("For your Indulgence: \t\t\tFor your Indulgence: \t\t\tFor your Indulgence: \n\n");
    				printf("* 40-inch LED flat-screen \t\t* 40-inch LED flat-sceen \t\t* 40-inch LED flat-screen \n* Cable/Satellite TV \t\t\t* Cable/Satellite TV \t\t\t* Cable/Satellite TV\n");
    				printf("* Bottled water \t\t\t* Bottled water \t\t\t* Bottled water\n* In-room dining service \t\t* In-room dining service \t\t* In-room dining service \n");
					printf("\t\t\t\t\t* Mini-refrigerator \t\t\t* Mini-refrigerator\n ");
					printf("\t\t\t\t\t* Wireless internet access\t\t* Wireless internet access\n");
					printf("\t\t\t\t\t\t\t\t\t\t* Coffee and tea making facilities \n\n");
					while (1) { 
        				printf("Choose Indulgence: ");
        				if (scanf("%d", &indulgence) != 1) { 
            				while (getchar() != '\n');
           			 		printf("Invalid input. Please enter a valid integer.\n");
        				} else if (indulgence >= 1 && indulgence <= 3) {
							break;
						} else {
							printf("Invalid input. Please enter a number between 1 and 3.\n");
       					}
   					}
					printf("----------------------------------------------------------------------------------------------------------\n");
					printf("You will be accomodated in a \x1b[31mSOLO TYPE 1\x1b[0m room.\n");
					if (indulgence == 1){
						func1131();
					}
					if (indulgence == 2){
						func1132();
					}
					if (indulgence == 3){
						func1133;
					}
					printf("----------------------------------------------------------------------------------------------------------\n");
				}
			}
			if (type == 2){
				printf("----------------------------------------------------------------------------------------------------------\n");
				printf("\nOption 1: \t\t\t\tOption 2:  \t\t\t\tOption 3:\n\n");
    			printf("==AMENITIES== \t\t\t\t==AMENITIES== \t\t\t\t==AMENITIES==\n\n");
    			printf("For your Comfort: \t\t\tFor your Comfort: \t\t\tFor your Comfort:\n\n");
    			printf("* Toilet amenities \t\t\t* Toilet amenities \t\t\t* Toilet amenities\n* Bath linen and towels \t\t* Bath linen and towels \t\t* Bath linen and towels \n* Hot and cold shower \t\t\t* Hot and cold shower \t\t\t* Hot and cold shower \n* Slippers \t\t\t\t* Slippers \t\t\t\t* Slippers \n\t\t\t\t\t* Hair Dryer \t\t\t\t* Hair Dryer \n\t\t\t\t\t* Bidet \t\t\t\t* Bidet \n\t\t\t\t\t\t\t\t\t\t* Bathrobes\n\n");
    			while (1) { 
        			printf("Select Comfort: ");
        			if (scanf("%d", &comfort) != 1) { 
            			while (getchar() != '\n');
           			 	printf("Invalid input. Please enter a valid integer.\n");
        			} else if (comfort >= 1 && comfort <= 3) {
						break;
					} else {
						printf("Invalid input. Please enter a number between 1 and 3.\n");
       				}
   				}
    			if (comfort == 1) {
    				printf("Option 1: \t\t\t\tOption 2:  \t\t\t\tOption 3:\n\n");
    				printf("For your Indulgence: \t\t\tFor your Indulgence: \t\t\tFor your Indulgence: \n\n");
    				printf("* 40-inch LED flat-screen \t\t* 40-inch LED flat-sceen \t\t* 40-inch LED flat-screen \n* Cable/Satellite TV \t\t\t* Cable/Satellite TV \t\t\t* Cable/Satellite TV\n");
    				printf("* Bottled water \t\t\t* Bottled water \t\t\t* Bottled water\n* In-room dining service \t\t* In-room dining service \t\t* In-room dining service \n");
					printf("\t\t\t\t\t* Mini-refrigerator \t\t\t* Mini-refrigerator\n ");
					printf("\t\t\t\t\t* Wireless internet access\t\t* Wireless internet access\n");
					printf("\t\t\t\t\t\t\t\t\t\t* Coffee and tea making facilities \n\n");
					while (1) { 
        				printf("Choose Indulgence: ");
        				if (scanf("%d", &indulgence) != 1) { 
            				while (getchar() != '\n');
           			 		printf("Invalid input. Please enter a valid integer.\n");
        				} else if (indulgence >= 1 && indulgence <= 3) {
							break;
						} else {
							printf("Invalid input. Please enter a number between 1 and 3.\n");
       					}
   					}
					printf("----------------------------------------------------------------------------------------------------------\n");
					printf("You will be accomodated in a \x1b[31mSOLO TYPE 2\x1b[0m room.\n");
					if (indulgence == 1){
						func1211();
					}
					if (indulgence == 2){
						func1212();
					}
					if (indulgence == 3){
						func1213();
					}
					printf("----------------------------------------------------------------------------------------------------------\n");
				}
				if (comfort == 2) {
					printf("----------------------------------------------------------------------------------------------------------\n");
					printf("\nOption 1: \t\t\t\tOption 2:  \t\t\t\tOption 3:\n\n");
    				printf("For your Indulgence: \t\t\tFor your Indulgence: \t\t\tFor your Indulgence: \n\n");
    				printf("* 40-inch LED flat-screen \t\t* 40-inch LED flat-sceen \t\t* 40-inch LED flat-screen \n* Cable/Satellite TV \t\t\t* Cable/Satellite TV \t\t\t* Cable/Satellite TV\n");
    				printf("* Bottled water \t\t\t* Bottled water \t\t\t* Bottled water\n* In-room dining service \t\t* In-room dining service \t\t* In-room dining service \n");
					printf("\t\t\t\t\t* Mini-refrigerator \t\t\t* Mini-refrigerator\n ");
					printf("\t\t\t\t\t* Wireless internet access\t\t* Wireless internet access\n");
					printf("\t\t\t\t\t\t\t\t\t\t* Coffee and tea making facilities \n\n");
					while (1) { 
        				printf("Choose Indulgence: ");
        				if (scanf("%d", &indulgence) != 1) { 
            				while (getchar() != '\n');
           			 		printf("Invalid input. Please enter a valid integer.\n");
        				} else if (indulgence >= 1 && indulgence <= 3) {
							break;
						} else {
							printf("Invalid input. Please enter a number between 1 and 3.\n");
       					}
   					}
					printf("----------------------------------------------------------------------------------------------------------\n");
					printf("You will be accomodated in a \x1b[31mSOLO TYPE 2\x1b[0m room.\n");
					if (indulgence == 1){
						func1221();
					}
					if (indulgence == 2){
						func1222();
					}
					if (indulgence == 3){
						func1223();
					}
					printf("----------------------------------------------------------------------------------------------------------\n");
				}
				if (comfort == 3) {
					printf("----------------------------------------------------------------------------------------------------------\n");
					printf("\nOption 1: \t\t\t\tOption 2:  \t\t\t\tOption 3:\n\n");
    				printf("For your Indulgence: \t\t\tFor your Indulgence: \t\t\tFor your Indulgence: \n\n");
    				printf("* 40-inch LED flat-screen \t\t* 40-inch LED flat-sceen \t\t* 40-inch LED flat-screen \n* Cable/Satellite TV \t\t\t* Cable/Satellite TV \t\t\t* Cable/Satellite TV\n");
    				printf("* Bottled water \t\t\t* Bottled water \t\t\t* Bottled water\n* In-room dining service \t\t* In-room dining service \t\t* In-room dining service \n");
					printf("\t\t\t\t\t* Mini-refrigerator \t\t\t* Mini-refrigerator\n ");
					printf("\t\t\t\t\t* Wireless internet access\t\t* Wireless internet access\n");
					printf("\t\t\t\t\t\t\t\t\t\t* Coffee and tea making facilities \n\n");
					while (1) { 
        				printf("Choose Indulgence: ");
        				if (scanf("%d", &indulgence) != 1) { 
            				while (getchar() != '\n');
           			 		printf("Invalid input. Please enter a valid integer.\n");
        				} else if (indulgence >= 1 && indulgence <= 3) {
							break;
						} else {
							printf("Invalid input. Please enter a number between 1 and 3.\n");
       					}
   					}
					printf("----------------------------------------------------------------------------------------------------------\n");
					printf("You will be accomodated in a \x1b[31mSOLO TYPE 2\x1b[0m room.\n");
					if (indulgence == 1){
						func1231();
					}
					if (indulgence == 2){
						func1232();
					}
					if (indulgence == 3){
						func1233();
					}
					printf("----------------------------------------------------------------------------------------------------------\n");
				}
			}
    		if (type == 3){
    			printf("----------------------------------------------------------------------------------------------------------\n");
				printf("\nOption 1: \t\t\t\tOption 2:  \t\t\t\tOption 3:\n\n");
    			printf("==AMENITIES== \t\t\t\t==AMENITIES== \t\t\t\t==AMENITIES==\n\n");
    			printf("For your Comfort: \t\t\tFor your Comfort: \t\t\tFor your Comfort:\n\n");
    			printf("* Toilet amenities \t\t\t* Toilet amenities \t\t\t* Toilet amenities\n* Bath linen and towels \t\t* Bath linen and towels \t\t* Bath linen and towels \n* Hot and cold shower \t\t\t* Hot and cold shower \t\t\t* Hot and cold shower \n* Slippers \t\t\t\t* Slippers \t\t\t\t* Slippers \n\t\t\t\t\t* Hair Dryer \t\t\t\t* Hair Dryer \n\t\t\t\t\t* Bidet \t\t\t\t* Bidet \n\t\t\t\t\t\t\t\t\t\t* Bathrobes\n\n");
    			while (1) { 
        			printf("Select Comfort: ");
        			if (scanf("%d", &comfort) != 1) { 
            			while (getchar() != '\n');
           			 	printf("Invalid input. Please enter a valid integer.\n");
        			} else if (comfort >= 1 && comfort <= 3) {
						break;
					} else {
						printf("Invalid input. Please enter a number between 1 and 3.\n");
       				}
   				}
    			if (comfort == 1) {
    				printf("----------------------------------------------------------------------------------------------------------\n");
					printf("\nOption 1: \t\t\t\tOption 2:  \t\t\t\tOption 3:\n\n");
    				printf("For your Indulgence: \t\t\tFor your Indulgence: \t\t\tFor your Indulgence: \n\n");
    				printf("* 40-inch LED flat-screen \t\t* 40-inch LED flat-sceen \t\t* 40-inch LED flat-screen \n* Cable/Satellite TV \t\t\t* Cable/Satellite TV \t\t\t* Cable/Satellite TV\n");
    				printf("* Bottled water \t\t\t* Bottled water \t\t\t* Bottled water\n* In-room dining service \t\t* In-room dining service \t\t* In-room dining service \n");
					printf("\t\t\t\t\t* Mini-refrigerator \t\t\t* Mini-refrigerator\n ");
					printf("\t\t\t\t\t* Wireless internet access\t\t* Wireless internet access\n");
					printf("\t\t\t\t\t\t\t\t\t\t* Coffee and tea making facilities \n\n");
					while (1) { 
        				printf("Choose Indulgence: ");
        				if (scanf("%d", &indulgence) != 1) { 
            				while (getchar() != '\n');
           			 		printf("Invalid input. Please enter a valid integer.\n");
        				} else if (indulgence >= 1 && indulgence <= 3) {
							break;
						} else {
							printf("Invalid input. Please enter a number between 1 and 3.\n");
       					}
   					}
					printf("----------------------------------------------------------------------------------------------------------\n");
					printf("You will be accomodated in a \x1b[31mSOLO TYPE 3\x1b[0m room.\n");
					if (indulgence == 1){
						func1311();
					}
					if (indulgence == 2){
						func1312();
					}
					if (indulgence == 3){
						func1313();
					}
					printf("----------------------------------------------------------------------------------------------------------\n");
				}
				if (comfort == 2) {
					printf("----------------------------------------------------------------------------------------------------------\n");
					printf("\nOption 1: \t\t\t\tOption 2:  \t\t\t\tOption 3:\n\n");
    				printf("For your Indulgence: \t\t\tFor your Indulgence: \t\t\tFor your Indulgence: \n\n");
    				printf("* 40-inch LED flat-screen \t\t* 40-inch LED flat-sceen \t\t* 40-inch LED flat-screen \n* Cable/Satellite TV \t\t\t* Cable/Satellite TV \t\t\t* Cable/Satellite TV\n");
    				printf("* Bottled water \t\t\t* Bottled water \t\t\t* Bottled water\n* In-room dining service \t\t* In-room dining service \t\t* In-room dining service \n");
					printf("\t\t\t\t\t* Mini-refrigerator \t\t\t* Mini-refrigerator\n ");
					printf("\t\t\t\t\t* Wireless internet access\t\t* Wireless internet access\n");
					printf("\t\t\t\t\t\t\t\t\t\t* Coffee and tea making facilities \n\n");
					while (1) { 
        				printf("Choose Indulgence: ");
    				    scanf("%d", &indulgence);
        				if (indulgence >= 1 && indulgence <= 3) { 
            				break; 
        				} else {
            				printf("Invalid input. Please enter a number between 1 and 3.\n");
        				}
   					}
					printf("----------------------------------------------------------------------------------------------------------\n");
					printf("You will be accomodated in a \x1b[31mSOLO TYPE 3\x1b[0m room.\n");
					if (indulgence == 1){
						func1322();
					}
					if (indulgence == 2){
						func1322();
					}
					if (indulgence == 3){
						func1323();
					}
					printf("----------------------------------------------------------------------------------------------------------\n");
				}
				if (comfort == 3) {
					printf("----------------------------------------------------------------------------------------------------------\n");
					printf("\nOption 1: \t\t\t\tOption 2:  \t\t\t\tOption 3:\n\n");
    				printf("For your Indulgence: \t\t\tFor your Indulgence: \t\t\tFor your Indulgence: \n\n");
    				printf("* 40-inch LED flat-screen \t\t* 40-inch LED flat-sceen \t\t* 40-inch LED flat-screen \n* Cable/Satellite TV \t\t\t* Cable/Satellite TV \t\t\t* Cable/Satellite TV\n");
    				printf("* Bottled water \t\t\t* Bottled water \t\t\t* Bottled water\n* In-room dining service \t\t* In-room dining service \t\t* In-room dining service \n");
					printf("\t\t\t\t\t* Mini-refrigerator \t\t\t* Mini-refrigerator\n ");
					printf("\t\t\t\t\t* Wireless internet access\t\t* Wireless internet access\n");
					printf("\t\t\t\t\t\t\t\t\t\t* Coffee and tea making facilities \n\n");
					while (1) { 
        				printf("Choose Indulgence: ");
    				    scanf("%d", &indulgence);
        				if (indulgence >= 1 && indulgence <= 3) { 
            				break; 
        				} else {
            				printf("Invalid input. Please enter a number between 1 and 3.\n");
        				}
   					}
					printf("----------------------------------------------------------------------------------------------------------\n");
					printf("You will be accomodated in a \x1b[31mSOLO TYPE 3\x1b[0m room.\n");
					if (indulgence == 1){
						func1331();
					}
					if (indulgence == 2){
						func1332();
					}
					if (indulgence == 3){
						func1333();
					}
					printf("----------------------------------------------------------------------------------------------------------\n");
				}
			}
	}
	if(num_guests == 2) {
		printf("Duo type 1: \t\t\t\tDuo type 2: \t\t\t\tDuo type 3:\n\n30 sqm room \t\t\t\t35 sqm room \t\t\t\t40 sqm room\nQueen-sized bed \t\t\tQueen-sized bed or Twin beds \t\tKing-sized bed and Twin beds  \nAir-conditioned room \t\t\tAir-conditioned room \t\t\tAir-conditioned room\nNon-smoking \t\t\t\tNon-smoking \t\t\t\tNon-Smoking \nSofa \t\t\t\t\tSofa \t\t\t\t\tSofa\n\n");
		
		while (1) { 
        	printf("Select Type: ");
        	if (scanf("%d", &type) != 1) { 
           		while (getchar() != '\n');
           			printf("Invalid input. Please enter a valid integer.\n");
        	} else if (type >= 1 && type <= 3) {
				break;
			} else {
				printf("Invalid input. Please enter a number between 1 and 3.\n");
       		}
   		}
    		if (type == 1){
    			printf("----------------------------------------------------------------------------------------------------------\n");
				printf("\nOption 1: \t\t\t\tOption 2:  \t\t\t\tOption 3:\n\n");
    			printf("==AMENITIES== \t\t\t\t==AMENITIES== \t\t\t\t==AMENITIES==\n\n");
    			printf("For your Comfort: \t\t\tFor your Comfort: \t\t\tFor your Comfort:\n\n");
    			printf("* Toilet amenities \t\t\t* Toilet amenities \t\t\t* Toilet amenities\n* Bath linen and towels \t\t* Bath linen and towels \t\t* Bath linen and towels \n* Hot and cold shower \t\t\t* Hot and cold shower \t\t\t* Hot and cold shower \n* Slippers \t\t\t\t* Slippers \t\t\t\t* Slippers \n\t\t\t\t\t* Hair Dryer \t\t\t\t* Hair Dryer \n\t\t\t\t\t* Bidet \t\t\t\t* Bidet \n\t\t\t\t\t\t\t\t\t\t* Bathrobes\n\n");
    			while (1) { 
        			printf("Select Comfort: ");
        			if (scanf("%d", &comfort) != 1) { 
            			while (getchar() != '\n');
           			 	printf("Invalid input. Please enter a valid integer.\n");
        			} else if (comfort >= 1 && comfort <= 3) {
						break;
					} else {
						printf("Invalid input. Please enter a number between 1 and 3.\n");
       				}
   				}
    			if (comfort == 1) {
    				printf("----------------------------------------------------------------------------------------------------------\n");
					printf("\nOption 1: \t\t\t\tOption 2:  \t\t\t\tOption 3:\n\n");
    				printf("For your Indulgence: \t\t\tFor your Indulgence: \t\t\tFor your Indulgence: \n\n");
    				printf("* 40-inch LED flat-screen \t\t* 40-inch LED flat-sceen \t\t* 40-inch LED flat-screen \n* Cable/Satellite TV \t\t\t* Cable/Satellite TV \t\t\t* Cable/Satellite TV\n");
    				printf("* Bottled water \t\t\t* Bottled water \t\t\t* Bottled water\n* In-room dining service \t\t* In-room dining service \t\t* In-room dining service \n");
					printf("\t\t\t\t\t* Mini-refrigerator \t\t\t* Mini-refrigerator\n ");
					printf("\t\t\t\t\t* Wireless internet access\t\t* Wireless internet access\n");
					printf("\t\t\t\t\t\t\t\t\t\t* Coffee and tea making facilities \n\n");
					while (1) { 
        				printf("Choose Indulgence: ");
        				if (scanf("%d", &indulgence) != 1) { 
            				while (getchar() != '\n');
           			 		printf("Invalid input. Please enter a valid integer.\n");
        				} else if (indulgence >= 1 && indulgence <= 3) {
							break;
						} else {
							printf("Invalid input. Please enter a number between 1 and 3.\n");
       					}
   					}
					printf("----------------------------------------------------------------------------------------------------------\n");
					printf("You will be accomodated in a \x1b[31mDUO TYPE 1\x1b[0m room.\n");
					if (indulgence == 1){
						func2111();
					}
					if (indulgence == 2){
						func2112();
					}
					if (indulgence == 3){
						func2113();
					}
					printf("----------------------------------------------------------------------------------------------------------\n");
				}
				if (comfort == 2) {
					printf("----------------------------------------------------------------------------------------------------------\n");
					printf("\nOption 1: \t\t\t\tOption 2:  \t\t\t\tOption 3:\n\n");					
    				printf("For your Indulgence: \t\t\tFor your Indulgence: \t\t\tFor your Indulgence: \n\n");
    				printf("* 40-inch LED flat-screen \t\t* 40-inch LED flat-sceen \t\t* 40-inch LED flat-screen \n* Cable/Satellite TV \t\t\t* Cable/Satellite TV \t\t\t* Cable/Satellite TV\n");
    				printf("* Bottled water \t\t\t* Bottled water \t\t\t* Bottled water\n* In-room dining service \t\t* In-room dining service \t\t* In-room dining service \n");
					printf("\t\t\t\t\t* Mini-refrigerator \t\t\t* Mini-refrigerator\n ");
					printf("\t\t\t\t\t* Wireless internet access\t\t* Wireless internet access\n");
					printf("\t\t\t\t\t\t\t\t\t\t* Coffee and tea making facilities \n\n");
					while (1) { 
        				printf("Choose Indulgence: ");
        				if (scanf("%d", &indulgence) != 1) { 
            				while (getchar() != '\n');
           			 		printf("Invalid input. Please enter a valid integer.\n");
        				} else if (indulgence >= 1 && indulgence <= 3) {
							break;
						} else {
							printf("Invalid input. Please enter a number between 1 and 3.\n");
       					}
   					}
					printf("----------------------------------------------------------------------------------------------------------\n");
					printf("You will be accomodated in a \x1b[31mDUO TYPE 1\x1b[0m room.\n");
					if (indulgence == 1){
						func2121();
					}
					if (indulgence == 2){
						func2122();
					}
					if (indulgence == 3){
						func2123();
					}
					printf("----------------------------------------------------------------------------------------------------------\n");
				}
				if (comfort == 3) {
					printf("----------------------------------------------------------------------------------------------------------\n");
					printf("\nOption 1: \t\t\t\tOption 2:  \t\t\t\tOption 3:\n\n");					
    				printf("For your Indulgence: \t\t\tFor your Indulgence: \t\t\tFor your Indulgence: \n\n");
    				printf("* 40-inch LED flat-screen \t\t* 40-inch LED flat-sceen \t\t* 40-inch LED flat-screen \n* Cable/Satellite TV \t\t\t* Cable/Satellite TV \t\t\t* Cable/Satellite TV\n");
    				printf("* Bottled water \t\t\t* Bottled water \t\t\t* Bottled water\n* In-room dining service \t\t* In-room dining service \t\t* In-room dining service \n");
					printf("\t\t\t\t\t* Mini-refrigerator \t\t\t* Mini-refrigerator\n ");
					printf("\t\t\t\t\t* Wireless internet access\t\t* Wireless internet access\n");
					printf("\t\t\t\t\t\t\t\t\t\t* Coffee and tea making facilities \n\n");
					while (1) { 
        				printf("Choose Indulgence: ");
        				if (scanf("%d", &indulgence) != 1) { 
            				while (getchar() != '\n');
           			 		printf("Invalid input. Please enter a valid integer.\n");
        				} else if (indulgence >= 1 && indulgence <= 3) {
							break;
						} else {
							printf("Invalid input. Please enter a number between 1 and 3.\n");
       					}
   					}
					printf("----------------------------------------------------------------------------------------------------------\n");
					printf("You will be accomodated in a \x1b[31mDUO TYPE 1\x1b[0m room.\n");
					if (indulgence == 1){
						func2131();
					}
					if (indulgence == 2){
						func2132();
					}
					if (indulgence == 3){
						func2133();
					}
					printf("----------------------------------------------------------------------------------------------------------\n");
				}
			}
			if (type == 2){
				printf("----------------------------------------------------------------------------------------------------------\n");
				printf("\nOption 1: \t\t\t\tOption 2:  \t\t\t\tOption 3:\n\n");
    			printf("==AMENITIES== \t\t\t\t==AMENITIES== \t\t\t\t==AMENITIES==\n\n");
    			printf("For your Comfort: \t\t\tFor your Comfort: \t\t\tFor your Comfort:\n\n");
    			printf("* Toilet amenities \t\t\t* Toilet amenities \t\t\t* Toilet amenities\n* Bath linen and towels \t\t* Bath linen and towels \t\t* Bath linen and towels \n* Hot and cold shower \t\t\t* Hot and cold shower \t\t\t* Hot and cold shower \n* Slippers \t\t\t\t* Slippers \t\t\t\t* Slippers \n\t\t\t\t\t* Hair Dryer \t\t\t\t* Hair Dryer \n\t\t\t\t\t* Bidet \t\t\t\t* Bidet \n\t\t\t\t\t\t\t\t\t\t* Bathrobes\n\n");
    			while (1) { 
        			printf("Select Comfort: ");
        			if (scanf("%d", &comfort) != 1) { 
            			while (getchar() != '\n');
           			 	printf("Invalid input. Please enter a valid integer.\n");
        			} else if (comfort >= 1 && comfort <= 3) {
						break;
					} else {
						printf("Invalid input. Please enter a number between 1 and 3.\n");
       				}
   				}
    			if (comfort == 1) {
    				printf("----------------------------------------------------------------------------------------------------------\n");
					printf("\nOption 1: \t\t\t\tOption 2:  \t\t\t\tOption 3:\n\n");
    				printf("For your Indulgence: \t\t\tFor your Indulgence: \t\t\tFor your Indulgence: \n\n");
    				printf("* 40-inch LED flat-screen \t\t* 40-inch LED flat-sceen \t\t* 40-inch LED flat-screen \n* Cable/Satellite TV \t\t\t* Cable/Satellite TV \t\t\t* Cable/Satellite TV\n");
    				printf("* Bottled water \t\t\t* Bottled water \t\t\t* Bottled water\n* In-room dining service \t\t* In-room dining service \t\t* In-room dining service \n");
					printf("\t\t\t\t\t* Mini-refrigerator \t\t\t* Mini-refrigerator\n ");
					printf("\t\t\t\t\t* Wireless internet access\t\t* Wireless internet access\n");
					printf("\t\t\t\t\t\t\t\t\t\t* Coffee and tea making facilities \n\n");
					while (1) { 
        				printf("Choose Indulgence: ");
        				if (scanf("%d", &indulgence) != 1) { 
            				while (getchar() != '\n');
           			 		printf("Invalid input. Please enter a valid integer.\n");
        				} else if (indulgence >= 1 && indulgence <= 3) {
							break;
						} else {
							printf("Invalid input. Please enter a number between 1 and 3.\n");
       					}
   					}
					printf("----------------------------------------------------------------------------------------------------------\n");
					printf("You will be accomodated in a \x1b[31mDUO TYPE 2\x1b[0m room.\n");
					if (indulgence == 1){
						func2211();
					}
					if (indulgence == 2){
						func2212();
					}
					if (indulgence == 3){
						func2213();
					}
					printf("----------------------------------------------------------------------------------------------------------\n");
				}
				if (comfort == 2) {
					printf("----------------------------------------------------------------------------------------------------------\n");
					printf("\nOption 1: \t\t\t\tOption 2:  \t\t\t\tOption 3:\n\n");
    				printf("For your Indulgence: \t\t\tFor your Indulgence: \t\t\tFor your Indulgence: \n\n");
    				printf("* 40-inch LED flat-screen \t\t* 40-inch LED flat-sceen \t\t* 40-inch LED flat-screen \n* Cable/Satellite TV \t\t\t* Cable/Satellite TV \t\t\t* Cable/Satellite TV\n");
    				printf("* Bottled water \t\t\t* Bottled water \t\t\t* Bottled water\n* In-room dining service \t\t* In-room dining service \t\t* In-room dining service \n");
					printf("\t\t\t\t\t* Mini-refrigerator \t\t\t* Mini-refrigerator\n ");
					printf("\t\t\t\t\t* Wireless internet access\t\t* Wireless internet access\n");
					printf("\t\t\t\t\t\t\t\t\t\t* Coffee and tea making facilities \n\n");
					while (1) { 
        				printf("Choose Indulgence: ");
        				if (scanf("%d", &indulgence) != 1) { 
            				while (getchar() != '\n');
           			 		printf("Invalid input. Please enter a valid integer.\n");
        				} else if (indulgence >= 1 && indulgence <= 3) {
							break;
						} else {
							printf("Invalid input. Please enter a number between 1 and 3.\n");
       					}
   					}
					printf("----------------------------------------------------------------------------------------------------------\n");
					printf("You will be accomodated in a \x1b[31mDUO TYPE 2\x1b[0m room.\n");
					if (indulgence == 1){
						func2221();
					}
					if (indulgence == 2){
						func2222();
					}
					if (indulgence == 3){
						func2223();
					}
					printf("----------------------------------------------------------------------------------------------------------\n");
				}
				if (comfort == 3) {printf("----------------------------------------------------------------------------------------------------------\n");
					printf("\nOption 1: \t\t\t\tOption 2:  \t\t\t\tOption 3:\n\n");
    				printf("For your Indulgence: \t\t\tFor your Indulgence: \t\t\tFor your Indulgence: \n\n");
    				printf("* 40-inch LED flat-screen \t\t* 40-inch LED flat-sceen \t\t* 40-inch LED flat-screen \n* Cable/Satellite TV \t\t\t* Cable/Satellite TV \t\t\t* Cable/Satellite TV\n");
    				printf("* Bottled water \t\t\t* Bottled water \t\t\t* Bottled water\n* In-room dining service \t\t* In-room dining service \t\t* In-room dining service \n");
					printf("\t\t\t\t\t* Mini-refrigerator \t\t\t* Mini-refrigerator\n ");
					printf("\t\t\t\t\t* Wireless internet access\t\t* Wireless internet access\n");
					printf("\t\t\t\t\t\t\t\t\t\t* Coffee and tea making facilities \n\n");
				while (1) { 
        				printf("Choose Indulgence: ");
        				if (scanf("%d", &indulgence) != 1) { 
            				while (getchar() != '\n');
           			 		printf("Invalid input. Please enter a valid integer.\n");
        				} else if (indulgence >= 1 && indulgence <= 3) {
							break;
						} else {
							printf("Invalid input. Please enter a number between 1 and 3.\n");
       					}
   					}
					printf("----------------------------------------------------------------------------------------------------------\n");
					printf("You will be accomodated in a \x1b[31mDUO TYPE 2\x1b[0m room.\n");
					if (indulgence == 1){
						func2231();
					}
					if (indulgence == 2){
						func2232();
					}
					if (indulgence == 3){
						func2233();
					}
					printf("----------------------------------------------------------------------------------------------------------\n");
				}
			}
    		if (type == 3){
    			printf("----------------------------------------------------------------------------------------------------------\n");
				printf("\nOption 1: \t\t\t\tOption 2:  \t\t\t\tOption 3:\n\n");
    			printf("==AMENITIES== \t\t\t\t==AMENITIES== \t\t\t\t==AMENITIES==\n\n");
    			printf("For your Comfort: \t\t\tFor your Comfort: \t\t\tFor your Comfort:\n\n");
    			printf("* Toilet amenities \t\t\t* Toilet amenities \t\t\t* Toilet amenities\n* Bath linen and towels \t\t* Bath linen and towels \t\t* Bath linen and towels \n* Hot and cold shower \t\t\t* Hot and cold shower \t\t\t* Hot and cold shower \n* Slippers \t\t\t\t* Slippers \t\t\t\t* Slippers \n\t\t\t\t\t* Hair Dryer \t\t\t\t* Hair Dryer \n\t\t\t\t\t* Bidet \t\t\t\t* Bidet \n\t\t\t\t\t\t\t\t\t\t* Bathrobes\n\n");
    			while (1) { 
        			printf("Select Comfort: ");
        			if (scanf("%d", &comfort) != 1) { 
            			while (getchar() != '\n');
           			 	printf("Invalid input. Please enter a valid integer.\n");
        			} else if (comfort >= 1 && comfort <= 3) {
						break;
					} else {
						printf("Invalid input. Please enter a number between 1 and 3.\n");
       				}
   				}
    			if (comfort == 1) {
    				printf("----------------------------------------------------------------------------------------------------------\n");
					printf("\nOption 1: \t\t\t\tOption 2:  \t\t\t\tOption 3:\n\n");
    				printf("For your Indulgence: \t\t\tFor your Indulgence: \t\t\tFor your Indulgence: \n\n");
    				printf("* 40-inch LED flat-screen \t\t* 40-inch LED flat-sceen \t\t* 40-inch LED flat-screen \n* Cable/Satellite TV \t\t\t* Cable/Satellite TV \t\t\t* Cable/Satellite TV\n");
    				printf("* Bottled water \t\t\t* Bottled water \t\t\t* Bottled water\n* In-room dining service \t\t* In-room dining service \t\t* In-room dining service \n");
					printf("\t\t\t\t\t* Mini-refrigerator \t\t\t* Mini-refrigerator\n ");
					printf("\t\t\t\t\t* Wireless internet access\t\t* Wireless internet access\n");
					printf("\t\t\t\t\t\t\t\t\t\t* Coffee and tea making facilities \n\n");
					while (1) { 
        				printf("Choose Indulgence: ");
        				if (scanf("%d", &indulgence) != 1) { 
            				while (getchar() != '\n');
           			 		printf("Invalid input. Please enter a valid integer.\n");
        				} else if (indulgence >= 1 && indulgence <= 3) {
							break;
						} else {
							printf("Invalid input. Please enter a number between 1 and 3.\n");
       					}
   					}
					printf("----------------------------------------------------------------------------------------------------------\n");
					printf("You will be accomodated in a \x1b[31mDUO TYPE 3\x1b[0m room.\n");
					if (indulgence == 1){
						func2311();
					}
					if (indulgence == 2){
						func2312();
					}
					if (indulgence == 3){
						func2313();
					}
					printf("----------------------------------------------------------------------------------------------------------\n");
				}
				if (comfort == 2) {
					printf("----------------------------------------------------------------------------------------------------------\n");
					printf("\nOption 1: \t\t\t\tOption 2:  \t\t\t\tOption 3:\n\n");
    				printf("For your Indulgence: \t\t\tFor your Indulgence: \t\t\tFor your Indulgence: \n\n");
    				printf("* 40-inch LED flat-screen \t\t* 40-inch LED flat-sceen \t\t* 40-inch LED flat-screen \n* Cable/Satellite TV \t\t\t* Cable/Satellite TV \t\t\t* Cable/Satellite TV\n");
    				printf("* Bottled water \t\t\t* Bottled water \t\t\t* Bottled water\n* In-room dining service \t\t* In-room dining service \t\t* In-room dining service \n");
					printf("\t\t\t\t\t* Mini-refrigerator \t\t\t* Mini-refrigerator\n ");
					printf("\t\t\t\t\t* Wireless internet access\t\t* Wireless internet access\n");
					printf("\t\t\t\t\t\t\t\t\t\t* Coffee and tea making facilities \n\n");
					while (1) { 
        				printf("Choose Indulgence: ");
        				if (scanf("%d", &indulgence) != 1) { 
            				while (getchar() != '\n');
           			 		printf("Invalid input. Please enter a valid integer.\n");
        				} else if (indulgence >= 1 && indulgence <= 3) {
							break;
						} else {
							printf("Invalid input. Please enter a number between 1 and 3.\n");
       					}
   					}
					printf("----------------------------------------------------------------------------------------------------------\n");
					printf("You will be accomodated in a \x1b[31mDUO TYPE 3\x1b[0m room.\n");
					if (indulgence == 1){
						func2321();
					}
					if (indulgence == 2){
						func2322();
					}
					if (indulgence == 3){
						func2323();
					}
					printf("----------------------------------------------------------------------------------------------------------\n");
				}
				if (comfort == 3) {
					printf("----------------------------------------------------------------------------------------------------------\n");
					printf("\nOption 1: \t\t\t\tOption 2:  \t\t\t\tOption 3:\n\n");
    				printf("For your Indulgence: \t\t\tFor your Indulgence: \t\t\tFor your Indulgence: \n\n");
    				printf("* 40-inch LED flat-screen \t\t* 40-inch LED flat-sceen \t\t* 40-inch LED flat-screen \n* Cable/Satellite TV \t\t\t* Cable/Satellite TV \t\t\t* Cable/Satellite TV\n");
    				printf("* Bottled water \t\t\t* Bottled water \t\t\t* Bottled water\n* In-room dining service \t\t* In-room dining service \t\t* In-room dining service \n");
					printf("\t\t\t\t\t* Mini-refrigerator \t\t\t* Mini-refrigerator\n ");
					printf("\t\t\t\t\t* Wireless internet access\t\t* Wireless internet access\n");
					printf("\t\t\t\t\t\t\t\t\t\t* Coffee and tea making facilities \n\n");
					while (1) { 
        				printf("Choose Indulgence: ");
        				if (scanf("%d", &indulgence) != 1) { 
            				while (getchar() != '\n');
           			 		printf("Invalid input. Please enter a valid integer.\n");
        				} else if (indulgence >= 1 && indulgence <= 3) {
							break;
						} else {
							printf("Invalid input. Please enter a number between 1 and 3.\n");
       					}
   					}
					printf("----------------------------------------------------------------------------------------------------------\n");
					printf("You will be accomodated in a \x1b[31mDUO TYPE 3\x1b[0m room.\n");
					if (indulgence == 1){
						func2331();
					}
					if (indulgence == 2){
						func2332();
					}
					if (indulgence == 3){
						func2333();
					}
					printf("----------------------------------------------------------------------------------------------------------\n");
				}
			}
	}
	if(num_guests > 2 && num_guests < 5) {
		printf("Squad type 1: \t\t\t\tSquad type 2: \t\t\t\tSquad type 3:\n\n35 sqm room \t\t\t\t40 sqm room \t\t\t\t45 sqm room\nQueen-sized bed \t\t\tQueen-sized bed or Twin beds \t\tKing-sized beds or Twin beds\nSofa \t\t\t\t\tSofa \t\t\t\t\tSofa\nAir-conditioned room \t\t\tAir-conditioned room \t\t\tAir-conditioned room\nNon-smoking \t\t\t\tNon-smoking \t\t\t\tNon-smoking\n\n");
		
		while (1) { 
        		printf("Select Type: ");
        		if (scanf("%d", &type) != 1) { 
            		while (getchar() != '\n');
           			printf("Invalid input. Please enter a valid integer.\n");
        		} else if (type >= 1 && type <= 3) {
					break;
				} else {
					printf("Invalid input. Please enter a number between 1 and 3.\n");
       			}
   			}
		
    		if (type == 1){
    			printf("----------------------------------------------------------------------------------------------------------\n");
				printf("\nOption 1: \t\t\t\tOption 2:  \t\t\t\tOption 3:\n\n");
    			printf("==AMENITIES== \t\t\t\t==AMENITIES== \t\t\t\t==AMENITIES==\n\n");
    			printf("For your Comfort: \t\t\tFor your Comfort: \t\t\tFor your Comfort:\n\n");
    			printf("* Toilet amenities \t\t\t* Toilet amenities \t\t\t* Toilet amenities\n* Bath linen and towels \t\t* Bath linen and towels \t\t* Bath linen and towels \n* Hot and cold shower \t\t\t* Hot and cold shower \t\t\t* Hot and cold shower \n* Slippers \t\t\t\t* Slippers \t\t\t\t* Slippers \n\t\t\t\t\t* Hair Dryer \t\t\t\t* Hair Dryer \n\t\t\t\t\t* Bidet \t\t\t\t* Bidet \n\t\t\t\t\t\t\t\t\t\t* Bathrobes\n\n");
    			while (1) { 
        			printf("Select Comfort: ");
        			if (scanf("%d", &comfort) != 1) { 
            			while (getchar() != '\n');
           			 	printf("Invalid input. Please enter a valid integer.\n");
        			} else if (comfort >= 1 && comfort <= 3) {
						break;
					} else {
						printf("Invalid input. Please enter a number between 1 and 3.\n");
       				}
   				}
    			if (comfort == 1){
    				printf("----------------------------------------------------------------------------------------------------------\n");
					printf("\nOption 1: \t\t\t\tOption 2:  \t\t\t\tOption 3:\n\n");
    				printf("For your Indulgence: \t\t\tFor your Indulgence: \t\t\tFor your Indulgence: \n\n");
    				printf("* 40-inch LED flat-screen \t\t* 40-inch LED flat-sceen \t\t* 40-inch LED flat-screen \n* Cable/Satellite TV \t\t\t* Cable/Satellite TV \t\t\t* Cable/Satellite TV\n");
    				printf("* Bottled water \t\t\t* Bottled water \t\t\t* Bottled water\n* In-room dining service \t\t* In-room dining service \t\t* In-room dining service \n");
					printf("\t\t\t\t\t* Mini-refrigerator \t\t\t* Mini-refrigerator\n ");
					printf("\t\t\t\t\t* Wireless internet access\t\t* Wireless internet access\n");
					printf("\t\t\t\t\t\t\t\t\t\t* Coffee and tea making facilities \n\n");
					while (1) { 
        				printf("Choose Indulgence: ");
        				if (scanf("%d", &indulgence) != 1) { 
            				while (getchar() != '\n');
           			 		printf("Invalid input. Please enter a valid integer.\n");
        				} else if (indulgence >= 1 && indulgence <= 3) {
							break;
						} else {
							printf("Invalid input. Please enter a number between 1 and 3.\n");
       					}
   					}
					printf("----------------------------------------------------------------------------------------------------------\n");
					printf("You will be accomodated in a \x1b[31mSQUAD TYPE 1\x1b[0m room.\n");
					if (indulgence == 1){
						func3111();
					}
					if (indulgence == 2){
						func3112();
					}
					if (indulgence == 3){
						func3113();
					}
					printf("----------------------------------------------------------------------------------------------------------\n");
				}
				if (comfort == 2) {
					printf("----------------------------------------------------------------------------------------------------------\n");
					printf("\nOption 1: \t\t\t\tOption 2:  \t\t\t\tOption 3:\n\n");
    				printf("For your Indulgence: \t\t\tFor your Indulgence: \t\t\tFor your Indulgence: \n\n");
    				printf("* 40-inch LED flat-screen \t\t* 40-inch LED flat-sceen \t\t* 40-inch LED flat-screen \n* Cable/Satellite TV \t\t\t* Cable/Satellite TV \t\t\t* Cable/Satellite TV\n");
    				printf("* Bottled water \t\t\t* Bottled water \t\t\t* Bottled water\n* In-room dining service \t\t* In-room dining service \t\t* In-room dining service \n");
					printf("\t\t\t\t\t* Mini-refrigerator \t\t\t* Mini-refrigerator\n ");
					printf("\t\t\t\t\t* Wireless internet access\t\t* Wireless internet access\n");
					printf("\t\t\t\t\t\t\t\t\t\t* Coffee and tea making facilities \n\n");
					while (1) { 
        				printf("Choose Indulgence: ");
        				if (scanf("%d", &indulgence) != 1) { 
            				while (getchar() != '\n');
           			 		printf("Invalid input. Please enter a valid integer.\n");
        				} else if (indulgence >= 1 && indulgence <= 3) {
							break;
						} else {
							printf("Invalid input. Please enter a number between 1 and 3.\n");
       					}
   					}
					printf("----------------------------------------------------------------------------------------------------------\n");
					printf("You will be accomodated in a \x1b[31mSQUAD TYPE 1\x1b[0m room.\n");
					if (indulgence == 1){
						func3121();
					}
					if (indulgence == 2){
						func3122();
					}
					if (indulgence == 3){
						func3123();
					}
					printf("----------------------------------------------------------------------------------------------------------\n");
				}
				if (comfort == 3) {
					printf("----------------------------------------------------------------------------------------------------------\n");
					printf("\nOption 1: \t\t\t\tOption 2:  \t\t\t\tOption 3:\n\n");
    				printf("For your Indulgence: \t\t\tFor your Indulgence: \t\t\tFor your Indulgence: \n\n");
    				printf("* 40-inch LED flat-screen \t\t* 40-inch LED flat-sceen \t\t* 40-inch LED flat-screen \n* Cable/Satellite TV \t\t\t* Cable/Satellite TV \t\t\t* Cable/Satellite TV\n");
    				printf("* Bottled water \t\t\t* Bottled water \t\t\t* Bottled water\n* In-room dining service \t\t* In-room dining service \t\t* In-room dining service \n");
					printf("\t\t\t\t\t* Mini-refrigerator \t\t\t* Mini-refrigerator\n ");
					printf("\t\t\t\t\t* Wireless internet access\t\t* Wireless internet access\n");
					printf("\t\t\t\t\t\t\t\t\t\t* Coffee and tea making facilities \n\n");
					while (1) { 
        				printf("Choose Indulgence: ");
        				if (scanf("%d", &indulgence) != 1) { 
            				while (getchar() != '\n');
           			 		printf("Invalid input. Please enter a valid integer.\n");
        				} else if (indulgence >= 1 && indulgence <= 3) {
							break;
						} else {
							printf("Invalid input. Please enter a number between 1 and 3.\n");
       					}
   					}
					printf("----------------------------------------------------------------------------------------------------------\n");
					printf("You will be accomodated in a \x1b[31mSQUAD TYPE 1\x1b[0m room.\n");
					if (indulgence == 1){
						func3131();
					}
					if (indulgence == 2){
						func3132();
					}
					if (indulgence == 3){
						func3133();
					}
					printf("----------------------------------------------------------------------------------------------------------\n");
				}
			}
			if (type == 2){
				printf("----------------------------------------------------------------------------------------------------------\n");
				printf("\nOption 1: \t\t\t\tOption 2:  \t\t\t\tOption 3:\n\n");
    			printf("==AMENITIES== \t\t\t\t==AMENITIES== \t\t\t\t==AMENITIES==\n\n");
    			printf("For your Comfort: \t\t\tFor your Comfort: \t\t\tFor your Comfort:\n\n");
    			printf("* Toilet amenities \t\t\t* Toilet amenities \t\t\t* Toilet amenities\n* Bath linen and towels \t\t* Bath linen and towels \t\t* Bath linen and towels \n* Hot and cold shower \t\t\t* Hot and cold shower \t\t\t* Hot and cold shower \n* Slippers \t\t\t\t* Slippers \t\t\t\t* Slippers \n\t\t\t\t\t* Hair Dryer \t\t\t\t* Hair Dryer \n\t\t\t\t\t* Bidet \t\t\t\t* Bidet \n\t\t\t\t\t\t\t\t\t\t* Bathrobes\n\n");
    			while (1) { 
        			printf("Select Comfort: ");
        			if (scanf("%d", &comfort) != 1) { 
            			while (getchar() != '\n');
           			 	printf("Invalid input. Please enter a valid integer.\n");
        			} else if (comfort >= 1 && comfort <= 3) {
						break;
					} else {
						printf("Invalid input. Please enter a number between 1 and 3.\n");
       				}
   				}
    			if (comfort == 1) {
    				printf("----------------------------------------------------------------------------------------------------------\n");
					printf("\nOption 1: \t\t\t\tOption 2:  \t\t\t\tOption 3:\n\n");
    				printf("For your Indulgence: \t\t\tFor your Indulgence: \t\t\tFor your Indulgence: \n\n");
    				printf("* 40-inch LED flat-screen \t\t* 40-inch LED flat-sceen \t\t* 40-inch LED flat-screen \n* Cable/Satellite TV \t\t\t* Cable/Satellite TV \t\t\t* Cable/Satellite TV\n");
    				printf("* Bottled water \t\t\t* Bottled water \t\t\t* Bottled water\n* In-room dining service \t\t* In-room dining service \t\t* In-room dining service \n");
					printf("\t\t\t\t\t* Mini-refrigerator \t\t\t* Mini-refrigerator\n ");
					printf("\t\t\t\t\t* Wireless internet access\t\t* Wireless internet access\n");
					printf("\t\t\t\t\t\t\t\t\t\t* Coffee and tea making facilities \n\n");
					while (1) { 
        				printf("Choose Indulgence: ");
        				if (scanf("%d", &indulgence) != 1) { 
            				while (getchar() != '\n');
           			 		printf("Invalid input. Please enter a valid integer.\n");
        				} else if (indulgence >= 1 && indulgence <= 3) {
							break;
						} else {
							printf("Invalid input. Please enter a number between 1 and 3.\n");
       					}
   					}
					printf("----------------------------------------------------------------------------------------------------------\n");
					printf("You will be accomodated in a \x1b[31mSQUAD TYPE 2\x1b[0m room.\n");
					if (indulgence == 1){
						func3211();
					}
					if (indulgence == 2){
						func3212();
					}
					if (indulgence == 3){
						func3213();
					}
					printf("----------------------------------------------------------------------------------------------------------\n");
				}
				if (comfort == 2) {
					printf("----------------------------------------------------------------------------------------------------------\n");
					printf("\nOption 1: \t\t\t\tOption 2:  \t\t\t\tOption 3:\n\n");
    				printf("For your Indulgence: \t\t\tFor your Indulgence: \t\t\tFor your Indulgence: \n\n");
    				printf("* 40-inch LED flat-screen \t\t* 40-inch LED flat-sceen \t\t* 40-inch LED flat-screen \n* Cable/Satellite TV \t\t\t* Cable/Satellite TV \t\t\t* Cable/Satellite TV\n");
    				printf("* Bottled water \t\t\t* Bottled water \t\t\t* Bottled water\n* In-room dining service \t\t* In-room dining service \t\t* In-room dining service \n");
					printf("\t\t\t\t\t* Mini-refrigerator \t\t\t* Mini-refrigerator\n ");
					printf("\t\t\t\t\t* Wireless internet access\t\t* Wireless internet access\n");
					printf("\t\t\t\t\t\t\t\t\t\t* Coffee and tea making facilities \n\n");
					while (1) { 
        				printf("Choose Indulgence: ");
        				if (scanf("%d", &indulgence) != 1) { 
            				while (getchar() != '\n');
           			 		printf("Invalid input. Please enter a valid integer.\n");
        				} else if (indulgence >= 1 && indulgence <= 3) {
							break;
						} else {
							printf("Invalid input. Please enter a number between 1 and 3.\n");
       					}
   					}
					printf("----------------------------------------------------------------------------------------------------------\n");
					printf("You will be accomodated in a \x1b[31mSQUAD TYPE 2\x1b[0m room.\n");
					if (indulgence == 1){
						func3221();
					}
					if (indulgence == 2){
						func3222();
					}
					if (indulgence == 3){
						func3223();
					}
					printf("----------------------------------------------------------------------------------------------------------\n");
				}
				if (comfort == 3) {
					printf("----------------------------------------------------------------------------------------------------------\n");
					printf("\nOption 1: \t\t\t\tOption 2:  \t\t\t\tOption 3:\n\n");
    				printf("For your Indulgence: \t\t\tFor your Indulgence: \t\t\tFor your Indulgence: \n\n");
    				printf("* 40-inch LED flat-screen \t\t* 40-inch LED flat-sceen \t\t* 40-inch LED flat-screen \n* Cable/Satellite TV \t\t\t* Cable/Satellite TV \t\t\t* Cable/Satellite TV\n");
    				printf("* Bottled water \t\t\t* Bottled water \t\t\t* Bottled water\n* In-room dining service \t\t* In-room dining service \t\t* In-room dining service \n");
					printf("\t\t\t\t\t* Mini-refrigerator \t\t\t* Mini-refrigerator\n ");
					printf("\t\t\t\t\t* Wireless internet access\t\t* Wireless internet access\n");
					printf("\t\t\t\t\t\t\t\t\t\t* Coffee and tea making facilities \n\n");
					while (1) { 
        				printf("Choose Indulgence: ");
        				if (scanf("%d", &indulgence) != 1) { 
            				while (getchar() != '\n');
           			 		printf("Invalid input. Please enter a valid integer.\n");
        				} else if (indulgence >= 1 && indulgence <= 3) {
							break;
						} else {
							printf("Invalid input. Please enter a number between 1 and 3.\n");
       					}
   					}
					printf("----------------------------------------------------------------------------------------------------------\n");
					printf("You will be accomodated in a \x1b[31mSQUAD TYPE 2\x1b[0m room.\n");
					if (indulgence == 1){
						func3231();
					}
					if (indulgence == 2){
						func3232();
					}
					if (indulgence == 3){
						func3233();
					}
					printf("----------------------------------------------------------------------------------------------------------\n");
				}
			}
    		if (type == 3){
    			printf("----------------------------------------------------------------------------------------------------------\n");
				printf("\nOption 1: \t\t\t\tOption 2:  \t\t\t\tOption 3:\n\n");
    			printf("==AMENITIES== \t\t\t\t==AMENITIES== \t\t\t\t==AMENITIES==\n\n");
    			printf("For your Comfort: \t\t\tFor your Comfort: \t\t\tFor your Comfort:\n\n");
    			printf("* Toilet amenities \t\t\t* Toilet amenities \t\t\t* Toilet amenities\n* Bath linen and towels \t\t* Bath linen and towels \t\t* Bath linen and towels \n* Hot and cold shower \t\t\t* Hot and cold shower \t\t\t* Hot and cold shower \n* Slippers \t\t\t\t* Slippers \t\t\t\t* Slippers \n\t\t\t\t\t* Hair Dryer \t\t\t\t* Hair Dryer \n\t\t\t\t\t* Bidet \t\t\t\t* Bidet \n\t\t\t\t\t\t\t\t\t\t* Bathrobes\n\n");
    			while (1) { 
        			printf("Select Comfort: ");
        			if (scanf("%d", &comfort) != 1) { 
            			while (getchar() != '\n');
           			 	printf("Invalid input. Please enter a valid integer.\n");
        			} else if (comfort >= 1 && comfort <= 3) {
						break;
					} else {
						printf("Invalid input. Please enter a number between 1 and 3.\n");
       				}
   				}
    			if (comfort == 1) {
    				printf("----------------------------------------------------------------------------------------------------------\n");
					printf("\nOption 1: \t\t\t\tOption 2:  \t\t\t\tOption 3:\n\n");
    				printf("For your Indulgence: \t\t\tFor your Indulgence: \t\t\tFor your Indulgence: \n\n");
    				printf("* 40-inch LED flat-screen \t\t* 40-inch LED flat-sceen \t\t* 40-inch LED flat-screen \n* Cable/Satellite TV \t\t\t* Cable/Satellite TV \t\t\t* Cable/Satellite TV\n");
    				printf("* Bottled water \t\t\t* Bottled water \t\t\t* Bottled water\n* In-room dining service \t\t* In-room dining service \t\t* In-room dining service \n");
					printf("\t\t\t\t\t* Mini-refrigerator \t\t\t* Mini-refrigerator\n ");
					printf("\t\t\t\t\t* Wireless internet access\t\t* Wireless internet access\n");
					printf("\t\t\t\t\t\t\t\t\t\t* Coffee and tea making facilities \n\n");
					while (1) { 
        				printf("Choose Indulgence: ");
        				if (scanf("%d", &indulgence) != 1) { 
            				while (getchar() != '\n');
           			 		printf("Invalid input. Please enter a valid integer.\n");
        				} else if (indulgence >= 1 && indulgence <= 3) {
							break;
						} else {
							printf("Invalid input. Please enter a number between 1 and 3.\n");
       					}
   					}
					printf("----------------------------------------------------------------------------------------------------------\n");
					printf("You will be accomodated in a \x1b[31mSQUAD TYPE 3\x1b[0m room.\n");
					if (indulgence == 1){
						func3311();
					}
					if (indulgence == 2){
						func3312();
					}
					if (indulgence == 3){
						func3313();
					}
					printf("----------------------------------------------------------------------------------------------------------\n");
				}
				if (comfort == 2) {
					printf("----------------------------------------------------------------------------------------------------------\n");
					printf("\nOption 1: \t\t\t\tOption 2:  \t\t\t\tOption 3:\n\n");
    				printf("For your Indulgence: \t\t\tFor your Indulgence: \t\t\tFor your Indulgence: \n\n");
    				printf("* 40-inch LED flat-screen \t\t* 40-inch LED flat-sceen \t\t* 40-inch LED flat-screen \n* Cable/Satellite TV \t\t\t* Cable/Satellite TV \t\t\t* Cable/Satellite TV\n");
    				printf("* Bottled water \t\t\t* Bottled water \t\t\t* Bottled water\n* In-room dining service \t\t* In-room dining service \t\t* In-room dining service \n");
					printf("\t\t\t\t\t* Mini-refrigerator \t\t\t* Mini-refrigerator\n ");
					printf("\t\t\t\t\t* Wireless internet access\t\t* Wireless internet access\n");
					printf("\t\t\t\t\t\t\t\t\t\t* Coffee and tea making facilities \n\n");
					while (1) { 
        				printf("Choose Indulgence: ");
        				if (scanf("%d", &indulgence) != 1) { 
            				while (getchar() != '\n');
           			 		printf("Invalid input. Please enter a valid integer.\n");
        				} else if (indulgence >= 1 && indulgence <= 3) {
							break;
						} else {
							printf("Invalid input. Please enter a number between 1 and 3.\n");
       					}
   					}
					printf("----------------------------------------------------------------------------------------------------------\n");
					printf("You will be accomodated in a \x1b[31mSQUAD TYPE 3\x1b[0m room.\n");
					if (indulgence == 1){
						func3321();
					}
					if (indulgence == 2){
						func3322();
					}
					if (indulgence == 3){
						func3323();
					}
					printf("----------------------------------------------------------------------------------------------------------\n");
				}
				if (comfort == 3) {
					printf("----------------------------------------------------------------------------------------------------------\n");
					printf("\nOption 1: \t\t\t\tOption 2:  \t\t\t\tOption 3:\n\n");
    				printf("For your Indulgence: \t\t\tFor your Indulgence: \t\t\tFor your Indulgence: \n\n");
    				printf("* 40-inch LED flat-screen \t\t* 40-inch LED flat-sceen \t\t* 40-inch LED flat-screen \n* Cable/Satellite TV \t\t\t* Cable/Satellite TV \t\t\t* Cable/Satellite TV\n");
    				printf("* Bottled water \t\t\t* Bottled water \t\t\t* Bottled water\n* In-room dining service \t\t* In-room dining service \t\t* In-room dining service \n");
					printf("\t\t\t\t\t* Mini-refrigerator \t\t\t* Mini-refrigerator\n ");
					printf("\t\t\t\t\t* Wireless internet access\t\t* Wireless internet access\n");
					printf("\t\t\t\t\t\t\t\t\t\t* Coffee and tea making facilities \n\n");
					while (1) { 
        				printf("Choose Indulgence: ");
        				if (scanf("%d", &indulgence) != 1) { 
            				while (getchar() != '\n');
           			 		printf("Invalid input. Please enter a valid integer.\n");
        				} else if (indulgence >= 1 && indulgence <= 3) {
							break;
						} else {
							printf("Invalid input. Please enter a number between 1 and 3.\n");
       					}
   					}
					printf("----------------------------------------------------------------------------------------------------------\n");
					printf("You will be accomodated in a \x1b[31mSQUAD TYPE 3\x1b[0m room.\n");
					if (indulgence == 1){
						func3331();
					}
					if (indulgence == 2){
						func3332();
					}
					if (indulgence == 3){
						func3333();
					}
					printf("----------------------------------------------------------------------------------------------------------\n");
				}
			}
	}
	if(num_guests > 4 && num_guests < 9) {
		printf("Family Suite type 1: \t\t\tFamily Suite type 2: \t\t\tFamily Suite type 3:\n\n50 sqm room \t\t\t\t55 sqm room \t\t\t\t60 sqm room\nCity view \t\t\t\tCity view \t\t\t\tCity view or Mayon view\nQueen-sized \t\t\t\tQueen-sized and Twin bed \t\tKing-sized bed \nAir-conditioned room \t\t\tAir-conditioned room \t\t\tAir-conditioned room\nNon-smoking \t\t\t\tNon-smoking \t\t\t\tNon-smoking \nBalcony \t\t\t\tBalcony \t\t\t\tBalcony \n\t\t\t\t\t\t\t\t\t\tLiving room \n\n");
		
		while (1) { 
        		printf("Select Type: ");
        		if (scanf("%d", &type) != 1) { 
            		while (getchar() != '\n');
           			printf("Invalid input. Please enter a valid integer.\n");
        		} else if (type >= 1 && type <= 3) {
					break;
				} else {
					printf("Invalid input. Please enter a number between 1 and 3.\n");
       			}
   			}
    		if (type == 1){
    			printf("----------------------------------------------------------------------------------------------------------\n");
				printf("\nOption 1: \t\t\t\tOption 2:  \t\t\t\tOption 3:\n\n");
    			printf("For your Comfort: \t\t\tFor your Comfort: \t\t\tFor your Comfort:\n\n");
    			printf("\n* Toilet Amenities \t\t\t* Toilet Amenities \t\t\t* Toilet Amenities\n* Bath linen and towels \t\t* Bath linen and towels \t\t* Bath linen and towels\n* Hairdryer \t\t\t\t* Hairdryer \t\t\t\t* Hairdryer\n* Hot and cold shower \t\t\t* Hot and cold shower \t\t\t* Hot and cold shower\n* Bidet \t\t\t\t* Bidet \t\t\t\t* Bidet\n* Slippers \t\t\t\t* Slippers \t\t\t\t* Slippers\n");
				printf("\t\t\t\t\t* Ensuite bathrooms \t\t\t* Ensuite bathrooms\n");
				printf("\t\t\t\t\t* Bathrobes \t\t\t\t* Bathrobes\n \t\t\t\t\t\t\t\t\t\t* Bath tub \n\n");
				while (1) { 
        			printf("Select Comfort: ");
        			if (scanf("%d", &comfort) != 1) { 
            			while (getchar() != '\n');
           			 	printf("Invalid input. Please enter a valid integer.\n");
        			} else if (comfort >= 1 && comfort <= 3) {
						break;
					} else {
						printf("Invalid input. Please enter a number between 1 and 3.\n");
       				}
   				}
    			if (comfort == 1){
    				printf("----------------------------------------------------------------------------------------------------------\n");
					printf("\nOption 1: \t\t\t\tOption 2:  \t\t\t\tOption 3:\n\n");
    				printf("For your Indulgence: \t\t\tFor your Indulgence: \t\t\tFor your Indulgence: \n\n");
    				printf("* 40-inch LED flat-screen (Bedroom) \t* 40-inch LED flat-screen (Bedroom) \t* 40-inch LED flat-screen (Bedroom)\n");
    				printf("* Cable/Satellite TV \t\t\t* Cable/Satellite TV \t\t\t* Cable/Satellite TV\n* Wireless internet access \t\t* Wireless internet access \t\t* Wireless internet access\n");
    				printf("* Bottled water \t\t\t* Bottled water \t\t\t* Bottled water \n* In-room dining service \t\t* In-room dining service \t\t* In-room dining service\n");
					printf("\t\t\t\t\t* Coffee and tea making facilities \t* Coffee and tea making facilities\n");
					printf("\t\t\t\t\t* Mini-refrigerator \t\t\t* Mini-refrigerator\n");
					printf("\t\t\t\t\t\t\t\t\t\t* 49-inch LED flat-screen (Living room)\n\n");
					while (1) { 
        				printf("Choose Indulgence: ");
        				if (scanf("%d", &indulgence) != 1) { 
            				while (getchar() != '\n');
           			 		printf("Invalid input. Please enter a valid integer.\n");
        				} else if (indulgence >= 1 && indulgence <= 3) {
							break;
						} else {
							printf("Invalid input. Please enter a number between 1 and 3.\n");
       					}
   					}
					printf("----------------------------------------------------------------------------------------------------------\n");
					printf("You will be accomodated in a \x1b[31mFAMILY TYPE 1\x1b[0m room.\n");
					if (indulgence == 1){
						func8111();
					}
					if (indulgence == 2){
						func8112();
					}
					if (indulgence == 3){
						func8113();
					}
					printf("----------------------------------------------------------------------------------------------------------\n");
				}
				if (comfort == 2){
					printf("----------------------------------------------------------------------------------------------------------\n");
					printf("\nOption 1: \t\t\t\tOption 2:  \t\t\t\tOption 3:\n\n");
					printf("For your Indulgence: \t\t\tFor your Indulgence: \t\t\tFor your Indulgence: \n\n");
    				printf("* 40-inch LED flat-screen (Bedroom) \t* 40-inch LED flat-screen (Bedroom) \t* 40-inch LED flat-screen (Bedroom)\n");
    				printf("* Cable/Satellite TV \t\t\t* Cable/Satellite TV \t\t\t* Cable/Satellite TV\n* Wireless internet access \t\t* Wireless internet access \t\t* Wireless internet access\n");
    				printf("* Bottled water \t\t\t* Bottled water \t\t\t* Bottled water \n* In-room dining service \t\t* In-room dining service \t\t* In-room dining service\n");
					printf("\t\t\t\t\t* Coffee and tea making facilities \t* Coffee and tea making facilities\n");
					printf("\t\t\t\t\t* Mini-refrigerator \t\t\t* Mini-refrigerator\n");
					printf("\t\t\t\t\t\t\t\t\t\t* 49-inch LED flat-screen (Living room)\n\n");
					while (1) { 
        				printf("Choose Indulgence: ");
        				if (scanf("%d", &indulgence) != 1) { 
            				while (getchar() != '\n');
           			 		printf("Invalid input. Please enter a valid integer.\n");
        				} else if (indulgence >= 1 && indulgence <= 3) {
							break;
						} else {
							printf("Invalid input. Please enter a number between 1 and 3.\n");
       					}
   					}
					printf("----------------------------------------------------------------------------------------------------------\n");
					printf("You will be accomodated in a \x1b[31mFAMILY TYPE 1\x1b[0m room.\n");
					if (indulgence == 1){
						func8111();
					}
					if (indulgence == 2){
						func8112();
					}
					if (indulgence == 3){
						func8113();
					}
					printf("----------------------------------------------------------------------------------------------------------\n");
				}
				if (comfort == 3){
					printf("----------------------------------------------------------------------------------------------------------\n");
					printf("\nOption 1: \t\t\t\tOption 2:  \t\t\t\tOption 3:\n\n");
					printf("For your Indulgence: \t\t\tFor your Indulgence: \t\t\tFor your Indulgence: \n\n");
    				printf("* 40-inch LED flat-screen (Bedroom) \t* 40-inch LED flat-screen (Bedroom) \t* 40-inch LED flat-screen (Bedroom)\n");
    				printf("* Cable/Satellite TV \t\t\t* Cable/Satellite TV \t\t\t* Cable/Satellite TV\n* Wireless internet access \t\t* Wireless internet access \t\t* Wireless internet access\n");
    				printf("* Bottled water \t\t\t* Bottled water \t\t\t* Bottled water \n* In-room dining service \t\t* In-room dining service \t\t* In-room dining service\n");
					printf("\t\t\t\t\t* Coffee and tea making facilities \t* Coffee and tea making facilities\n");
					printf("\t\t\t\t\t* Mini-refrigerator \t\t\t* Mini-refrigerator\n");
					printf("\t\t\t\t\t\t\t\t\t\t* 49-inch LED flat-screen (Living room)\n\n");
					while (1) { 
        				printf("Choose Indulgence: ");
        				if (scanf("%d", &indulgence) != 1) { 
            				while (getchar() != '\n');
           			 		printf("Invalid input. Please enter a valid integer.\n");
        				} else if (indulgence >= 1 && indulgence <= 3) {
							break;
						} else {
							printf("Invalid input. Please enter a number between 1 and 3.\n");
       					}
   					}
					printf("----------------------------------------------------------------------------------------------------------\n");
					printf("You will be accomodated in a \x1b[31mFAMILY TYPE 1\x1b[0m room.\n");
					if (indulgence == 1){
						func8111();
					}
					if (indulgence == 2){
						func8112();
					}
					if (indulgence == 3){
						func8113();
					}
					printf("----------------------------------------------------------------------------------------------------------\n");
				}
			}
			if (type == 2){
				printf("----------------------------------------------------------------------------------------------------------\n");
				printf("\nOption 1: \t\t\t\tOption 2:  \t\t\t\tOption 3:\n\n");
				printf("For your Comfort: \t\t\tFor your Comfort: \t\t\tFor your Comfort:\n\n");
    			printf("\n* Toilet Amenities \t\t\t* Toilet Amenities \t\t\t* Toilet Amenities\n* Bath linen and towels \t\t* Bath linen and towels \t\t* Bath linen and towels\n* Hairdryer \t\t\t\t* Hairdryer \t\t\t\t* Hairdryer\n* Hot and cold shower \t\t\t* Hot and cold shower \t\t\t* Hot and cold shower\n* Bidet \t\t\t\t* Bidet \t\t\t\t* Bidet\n* Slippers \t\t\t\t* Slippers \t\t\t\t* Slippers\n");
				printf("\t\t\t\t\t* Ensuite bathrooms \t\t\t* Ensuite bathrooms\n");
				printf("\t\t\t\t\t* Bathrobes \t\t\t\t* Bathrobes\n \t\t\t\t\t\t\t\t\t\t* Bath tub \n\n");
				while (1) { 
        			printf("Select Comfort: ");
        			if (scanf("%d", &comfort) != 1) { 
            			while (getchar() != '\n');
           			 	printf("Invalid input. Please enter a valid integer.\n");
        			} else if (comfort >= 1 && comfort <= 3) {
						break;
					} else {
						printf("Invalid input. Please enter a number between 1 and 3.\n");
       				}
   				}
    			if (comfort == 1){
    				printf("----------------------------------------------------------------------------------------------------------\n");
					printf("\nOption 1: \t\t\t\tOption 2:  \t\t\t\tOption 3:\n\n");
    				printf("For your Indulgence: \t\t\tFor your Indulgence: \t\t\tFor your Indulgence: \n\n");
    				printf("* 40-inch LED flat-screen (Bedroom) \t* 40-inch LED flat-screen (Bedroom) \t* 40-inch LED flat-screen (Bedroom)\n");
    				printf("* Cable/Satellite TV \t\t\t* Cable/Satellite TV \t\t\t* Cable/Satellite TV\n* Wireless internet access \t\t* Wireless internet access \t\t* Wireless internet access\n");
    				printf("* Bottled water \t\t\t* Bottled water \t\t\t* Bottled water \n* In-room dining service \t\t* In-room dining service \t\t* In-room dining service\n");
					printf("\t\t\t\t\t* Coffee and tea making facilities \t* Coffee and tea making facilities\n");
					printf("\t\t\t\t\t* Mini-refrigerator \t\t\t* Mini-refrigerator\n");
					printf("\t\t\t\t\t\t\t\t\t\t* 49-inch LED flat-screen (Living room)\n\n");
					while (1) { 
        				printf("Choose Indulgence: ");
        				if (scanf("%d", &indulgence) != 1) { 
            				while (getchar() != '\n');
           			 		printf("Invalid input. Please enter a valid integer.\n");
        				} else if (indulgence >= 1 && indulgence <= 3) {
							break;
						} else {
							printf("Invalid input. Please enter a number between 1 and 3.\n");
       					}
   					}
					printf("----------------------------------------------------------------------------------------------------------\n");
					printf("You will be accomodated in a \x1b[31mFAMILY TYPE 2\x1b[0m room.\n");
					if (indulgence == 1){
						func8111();
					}
					if (indulgence == 2){
						func8112();
					}
					if (indulgence == 3){
						func8113();
					}
					printf("----------------------------------------------------------------------------------------------------------\n");
				}
				if (comfort == 2){
					printf("----------------------------------------------------------------------------------------------------------\n");
					printf("\nOption 1: \t\t\t\tOption 2:  \t\t\t\tOption 3:\n\n");
					printf("For your Indulgence: \t\t\tFor your Indulgence: \t\t\tFor your Indulgence: \n\n");
    				printf("* 40-inch LED flat-screen (Bedroom) \t* 40-inch LED flat-screen (Bedroom) \t* 40-inch LED flat-screen (Bedroom)\n");
    				printf("* Cable/Satellite TV \t\t\t* Cable/Satellite TV \t\t\t* Cable/Satellite TV\n* Wireless internet access \t\t* Wireless internet access \t\t* Wireless internet access\n");
    				printf("* Bottled water \t\t\t* Bottled water \t\t\t* Bottled water \n* In-room dining service \t\t* In-room dining service \t\t* In-room dining service\n");
					printf("\t\t\t\t\t* Coffee and tea making facilities \t* Coffee and tea making facilities\n");
					printf("\t\t\t\t\t* Mini-refrigerator \t\t\t* Mini-refrigerator\n");
					printf("\t\t\t\t\t\t\t\t\t\t* 49-inch LED flat-screen (Living room)\n\n");
					while (1) { 
        				printf("Choose Indulgence: ");
        				if (scanf("%d", &indulgence) != 1) { 
            				while (getchar() != '\n');
           			 		printf("Invalid input. Please enter a valid integer.\n");
        				} else if (indulgence >= 1 && indulgence <= 3) {
							break;
						} else {
							printf("Invalid input. Please enter a number between 1 and 3.\n");
       					}
   					}
					printf("----------------------------------------------------------------------------------------------------------\n");
					printf("You will be accomodated in a \x1b[31mFAMILY TYPE 2\x1b[0m room.\n");
					if (indulgence == 1){
						func8111();
					}
					if (indulgence == 2){
						func8112();
					}
					if (indulgence == 3){
						func8113();
					}
				}
				if (comfort == 3){
					printf("----------------------------------------------------------------------------------------------------------\n");
					printf("\nOption 1: \t\t\t\tOption 2:  \t\t\t\tOption 3:\n\n");
					printf("For your Indulgence: \t\t\tFor your Indulgence: \t\t\tFor your Indulgence: \n\n");
    				printf("* 40-inch LED flat-screen (Bedroom) \t* 40-inch LED flat-screen (Bedroom) \t* 40-inch LED flat-screen (Bedroom)\n");
    				printf("* Cable/Satellite TV \t\t\t* Cable/Satellite TV \t\t\t* Cable/Satellite TV\n* Wireless internet access \t\t* Wireless internet access \t\t* Wireless internet access\n");
    				printf("* Bottled water \t\t\t* Bottled water \t\t\t* Bottled water \n* In-room dining service \t\t* In-room dining service \t\t* In-room dining service\n");
					printf("\t\t\t\t\t* Coffee and tea making facilities \t* Coffee and tea making facilities\n");
					printf("\t\t\t\t\t* Mini-refrigerator \t\t\t* Mini-refrigerator\n");
					printf("\t\t\t\t\t\t\t\t\t\t* 49-inch LED flat-screen (Living room)\n\n");
					while (1) { 
        				printf("Choose Indulgence: ");
        				if (scanf("%d", &indulgence) != 1) { 
            				while (getchar() != '\n');
           			 		printf("Invalid input. Please enter a valid integer.\n");
        				} else if (indulgence >= 1 && indulgence <= 3) {
							break;
						} else {
							printf("Invalid input. Please enter a number between 1 and 3.\n");
       					}
   					}
					printf("----------------------------------------------------------------------------------------------------------\n");
					printf("You will be accomodated in a \x1b[31mFAMILY TYPE 2\x1b[0m room.\n");
					if (indulgence == 1){
						func8111();
					}
					if (indulgence == 2){
						func8112();
					}
					if (indulgence == 3){
						func8113();
					}
				}
			}
			if (type == 3){
				printf("----------------------------------------------------------------------------------------------------------\n");
				printf("\nOption 1: \t\t\t\tOption 2:  \t\t\t\tOption 3:\n\n");
				printf("For your Comfort: \t\t\tFor your Comfort: \t\t\tFor your Comfort:\n\n");
    			printf("\n* Toilet Amenities \t\t\t* Toilet Amenities \t\t\t* Toilet Amenities\n* Bath linen and towels \t\t* Bath linen and towels \t\t* Bath linen and towels\n* Hairdryer \t\t\t\t* Hairdryer \t\t\t\t* Hairdryer\n* Hot and cold shower \t\t\t* Hot and cold shower \t\t\t* Hot and cold shower\n* Bidet \t\t\t\t* Bidet \t\t\t\t* Bidet\n* Slippers \t\t\t\t* Slippers \t\t\t\t* Slippers\n");
				printf("\t\t\t\t\t* Ensuite bathrooms \t\t\t* Ensuite bathrooms\n");
				printf("\t\t\t\t\t* Bathrobes \t\t\t\t* Bathrobes\n \t\t\t\t\t\t\t\t\t\t* Bath tub \n\n");
				while (1) { 
        			printf("Select Comfort: ");
        			if (scanf("%d", &comfort) != 1) { 
            			while (getchar() != '\n');
           			 	printf("Invalid input. Please enter a valid integer.\n");
        			} else if (comfort >= 1 && comfort <= 3) {
						break;
					} else {
						printf("Invalid input. Please enter a number between 1 and 3.\n");
       				}
   				}
    			if (comfort == 1){
    				printf("----------------------------------------------------------------------------------------------------------\n");
					printf("\nOption 1: \t\t\t\tOption 2:  \t\t\t\tOption 3:\n\n");
    				printf("For your Indulgence: \t\t\tFor your Indulgence: \t\t\tFor your Indulgence: \n\n");
    				printf("* 40-inch LED flat-screen (Bedroom) \t* 40-inch LED flat-screen (Bedroom) \t* 40-inch LED flat-screen (Bedroom)\n");
    				printf("* Cable/Satellite TV \t\t\t* Cable/Satellite TV \t\t\t* Cable/Satellite TV\n* Wireless internet access \t\t* Wireless internet access \t\t* Wireless internet access\n");
    				printf("* Bottled water \t\t\t* Bottled water \t\t\t* Bottled water \n* In-room dining service \t\t* In-room dining service \t\t* In-room dining service\n");
					printf("\t\t\t\t\t* Coffee and tea making facilities \t* Coffee and tea making facilities\n");
					printf("\t\t\t\t\t* Mini-refrigerator \t\t\t* Mini-refrigerator\n");
					printf("\t\t\t\t\t\t\t\t\t\t* 49-inch LED flat-screen (Living room)\n\n");
					while (1) { 
        				printf("Choose Indulgence: ");
        				if (scanf("%d", &indulgence) != 1) { 
            				while (getchar() != '\n');
           			 		printf("Invalid input. Please enter a valid integer.\n");
        				} else if (indulgence >= 1 && indulgence <= 3) {
							break;
						} else {
							printf("Invalid input. Please enter a number between 1 and 3.\n");
       					}
   					}
					printf("----------------------------------------------------------------------------------------------------------\n");
					printf("You will be accomodated in a \x1b[31mFAMILY TYPE 3\x1b[0m room.\n");
					if (indulgence == 1){
						func8111();
					}
					if (indulgence == 2){
						func8112();
					}
					if (indulgence == 3){
						func8113();
					}
					printf("----------------------------------------------------------------------------------------------------------\n");
				}
				if (comfort == 2){
					printf("----------------------------------------------------------------------------------------------------------\n");
					printf("\nOption 1: \t\t\t\tOption 2:  \t\t\t\tOption 3:\n\n");
					printf("For your Indulgence: \t\t\tFor your Indulgence: \t\t\tFor your Indulgence: \n\n");
    				printf("* 40-inch LED flat-screen (Bedroom) \t* 40-inch LED flat-screen (Bedroom) \t* 40-inch LED flat-screen (Bedroom)\n");
    				printf("* Cable/Satellite TV \t\t\t* Cable/Satellite TV \t\t\t* Cable/Satellite TV\n* Wireless internet access \t\t* Wireless internet access \t\t* Wireless internet access\n");
    				printf("* Bottled water \t\t\t* Bottled water \t\t\t* Bottled water \n* In-room dining service \t\t* In-room dining service \t\t* In-room dining service\n");
					printf("\t\t\t\t\t* Coffee and tea making facilities \t* Coffee and tea making facilities\n");
					printf("\t\t\t\t\t* Mini-refrigerator \t\t\t* Mini-refrigerator\n");
					printf("\t\t\t\t\t\t\t\t\t\t* 49-inch LED flat-screen (Living room)\n\n");
					while (1) { 
        				printf("Choose Indulgence: ");
        				if (scanf("%d", &indulgence) != 1) { 
            				while (getchar() != '\n');
           			 		printf("Invalid input. Please enter a valid integer.\n");
        				} else if (indulgence >= 1 && indulgence <= 3) {
							break;
						} else {
							printf("Invalid input. Please enter a number between 1 and 3.\n");
       					}
   					}
					printf("----------------------------------------------------------------------------------------------------------\n");
					printf("You will be accomodated in a \x1b[31mFAMILY TYPE 3\x1b[0m room.\n");
					if (indulgence == 1){
						func8111();
					}
					if (indulgence == 2){
						func8112();
					}
					if (indulgence == 3){
						func8113();
					}
					printf("----------------------------------------------------------------------------------------------------------\n");
				}
				if (comfort == 3){
					printf("----------------------------------------------------------------------------------------------------------\n");
					printf("\nOption 1: \t\t\t\tOption 2:  \t\t\t\tOption 3:\n\n");
					printf("For your Indulgence: \t\t\tFor your Indulgence: \t\t\tFor your Indulgence: \n\n");
    				printf("* 40-inch LED flat-screen (Bedroom) \t* 40-inch LED flat-screen (Bedroom) \t* 40-inch LED flat-screen (Bedroom)\n");
    				printf("* Cable/Satellite TV \t\t\t* Cable/Satellite TV \t\t\t* Cable/Satellite TV\n* Wireless internet access \t\t* Wireless internet access \t\t* Wireless internet access\n");
    				printf("* Bottled water \t\t\t* Bottled water \t\t\t* Bottled water \n* In-room dining service \t\t* In-room dining service \t\t* In-room dining service\n");
					printf("\t\t\t\t\t* Coffee and tea making facilities \t* Coffee and tea making facilities\n");
					printf("\t\t\t\t\t* Mini-refrigerator \t\t\t* Mini-refrigerator\n");
					printf("\t\t\t\t\t\t\t\t\t\t* 49-inch LED flat-screen (Living room)\n\n");
					while (1) { 
        				printf("Choose Indulgence: ");
        				if (scanf("%d", &indulgence) != 1) { 
            				while (getchar() != '\n');
           			 		printf("Invalid input. Please enter a valid integer.\n");
        				} else if (indulgence >= 1 && indulgence <= 3) {
							break;
						} else {
							printf("Invalid input. Please enter a number between 1 and 3.\n");
       					}
   					}
					printf("----------------------------------------------------------------------------------------------------------\n");
					printf("You will be accomodated in a \x1b[31mFAMILY TYPE 3\x1b[0m room.\n");
					if (indulgence == 1){
						func8111();
					}
					if (indulgence == 2){
						func8112();
					}
					if (indulgence == 3){
						func8113();
					}
					printf("----------------------------------------------------------------------------------------------------------\n");
				}
			}
	}
	return type;
}

bool name_exists(const char* name) {
    for (int room = 1; room < NUM_ROOMS; room++) {
        for (int i = 1; i < rooms[room].count; i++) {
            if (strcmp(rooms[room].reservations[i].name, name) == 0) {
                return true;
            }
        }
    }
    return false;
}

void reserve_room() {
    int room;
    Date check_in, check_out;
    char name[NAME_LEN];
    char phone[PHONE_LEN];
    int num_guests;

    bool name_valid = false;
    while (!name_valid) {
        printf("Enter your name: ");
        getchar(); 
        fgets(name, NAME_LEN, stdin);
        name[strcspn(name, "\n")] = 0;

        if (name_exists(name)) {
            printf("Name already exists. Please enter a different name.\n");
        } else {
            name_valid = true;
        }
    }

    bool valid_phone = false;
    while (!valid_phone) {
        printf("Enter your phone number (11 digits): ");
        fgets(phone, PHONE_LEN, stdin);
        phone[strcspn(phone, "\n")] = 0; 

        int len = strlen(phone);
        valid_phone = len == 11;
        for (int i = 0; i < len; i++) {
            if (!isdigit(phone[i])) {
                valid_phone = false;
                break;
            }
        }

        if (!valid_phone) {
            printf("Invalid phone number. Please enter exactly 11 digits.\n");
        }
    }

    Date current_date = get_current_date();

    bool valid_date = false;
    while (!valid_date) {
        printf("Enter check-in date (MM-DD-YYYY): ");
        scanf("%d-%d-%d", &check_in.month, &check_in.day, &check_in.year);

        if (date_is_less(check_in, current_date)) {
            printf("Check-in date must not be earlier than the current date.\n");
            continue;
        }
        
        printf("Enter check-out date (MM-DD-YYYY): "); 
        scanf("%d-%d-%d", &check_out.month, &check_out.day, &check_out.year);

        if (!is_date_valid(check_in, check_out)) {
            continue;
        }

        valid_date = true;
    }

    while (1) {
        printf("Enter number of guests (1 to 8): ");
        if (scanf("%d", &num_guests) != 1) {
        	while (getchar() != '\n');
            printf("Invalid number of guests. Please enter a number between 1 and 8.\n");
        } else if (num_guests >= 1 && num_guests <= 8){
        	break;
        } else {
            printf("Invalid number of guests. Please enter a number between 1 and 8.\n");
		}
    }
    
    printf("\n");
    int type_choice;
    
    if (num_guests == 1) {
        type_choice = 1;
    } else if (num_guests == 2) {
        type_choice = 2;
    } else if (num_guests > 2 && num_guests < 5) {
        type_choice = 3;
    } else if (num_guests > 4 && num_guests < 9) {
        type_choice = 4;
    }

    int subtype_choice = selection(type_choice, num_guests);

    RoomType required_type;
    switch (type_choice) {
        case 1:
            required_type = (RoomType)(SOLO1 + (subtype_choice - 1));
            break;
        case 2:
            required_type = (RoomType)(DUO1 + (subtype_choice - 1));
            break;
        case 3:
            required_type = (RoomType)(SQUAD1 + (subtype_choice - 1));
            break;
        case 4:
            required_type = (RoomType)(FAMILY1 + (subtype_choice - 1));
            break;
        default:
            printf("Invalid choice.\n");
            return;
    }

    bool room_found = false;
    int available_rooms[NUM_ROOMS];
    int available_count = 0;

    printf("Available rooms of the required subtype:\n");
    for (room = 1; room < NUM_ROOMS; room++) {
        if (rooms[room].type == required_type) {
            if (check_availability(room, check_in, check_out)) {
                printf("Room %d\n", room);
                available_rooms[available_count++] = room;
                room_found = true;
            } else {
                printf("\x1b[31m"); // ANSI escape code for red color
                printf("Room %d (Occupied)\x1b[0m\n", room); // Reset color after printing
            }
        }
    }

    if (!room_found) {
        printf("No available rooms of the required subtype for the specified dates.\n");
        return;
    }

    bool valid_room = false;
    while (!valid_room) {
    	while (1){
    		printf("Enter the room number you want to reserve: ");
        	if (scanf("%d", &room) != 1){
        		while (getchar() != '\n');
            	printf("Invalid room number. Please choose a room from the available options.\n");
			} else {
				break;
			}
		}
		
        for (int i = 0; i < available_count; i++) {
            if (room == available_rooms[i]) {
                valid_room = true;
                break;
            }
        }

        if (!valid_room) {
            printf("Invalid room number. Please choose a room from the available options.\n");
        }
    }

    if (make_reservation(room, check_in, check_out, name, phone, num_guests)) {
        printf("\n\n\nReservation confirmed for room %d from ", room);
        print_date(check_in);
        printf(" to ");
        print_date(check_out);
        printf(" with %d guest(s).\n", num_guests);
    } else {
        printf("Failed to make reservation for the selected room.\n");
    }
}

void print_availability() {
    int max_type_len = strlen("Type");
    int max_guest_len = strlen("Guest");
    int max_phone_len = strlen("Phone");
    char buffer[256];


    for (int i = 1; i < NUM_ROOMS; i++) {
        if (rooms[i].count > 0) {
            int type_len = strlen((rooms[i].type == SOLO1) ? "Solo Type 1" : 
                                  (rooms[i].type == SOLO2) ? "Solo Type 2" : 
                                  (rooms[i].type == SOLO3) ? "Solo Type 3" : 
                                  (rooms[i].type == DUO1) ? "Duo Type 1" : 
                                  (rooms[i].type == DUO2) ? "Duo Type 2" : 
                                  (rooms[i].type == DUO3) ? "Duo Type 3" : 
                                  (rooms[i].type == SQUAD1) ? "Squad Type 1" : 
                                  (rooms[i].type == SQUAD2) ? "Squad Type 2" : 
                                  (rooms[i].type == SQUAD3) ? "Squad Type 3" : 
                                  (rooms[i].type == FAMILY1) ? "Family Type 1" : 
                                  (rooms[i].type == FAMILY2) ? "Family Type 2" : "Family Type 3");
            if (type_len > max_type_len) max_type_len = type_len;

            for (int j = 1; j < rooms[i].count; j++) {
                int guest_len = strlen(rooms[i].reservations[j].name);
                if (guest_len > max_guest_len) max_guest_len = guest_len;

                int phone_len = strlen(rooms[i].reservations[j].phone);
                if (phone_len > max_phone_len) max_phone_len = phone_len;
            }
        }
    }


    sprintf(buffer, "---------%.*s------------------------------%.*s---%.*s--\n",
            max_type_len, "--------------------------------",
            max_guest_len, "--------------------------------",
            max_phone_len, "--------------------------------");
    printf("Available Rooms:\n");
    printf("%s", buffer);
    printf("| Room | %-*s |    Reservation Dates     | %-*s | %-*s |\n",
           max_type_len, "Type", max_guest_len, "Guest", max_phone_len, "Phone");
    printf("%s", buffer);

  
    for (int i = 1; i < NUM_ROOMS; i++) {
        if (rooms[i].count == 0) {
            printf("| %4d | %-*s | %24s | %-*s | %-*s |\n", i, max_type_len, "N/A", "N/A", max_guest_len, "N/A", max_phone_len, "N/A");
        } else {
            for (int j = 1; j < rooms[i].count; j++) {
                printf("| %4d | %-*s | %02d-%02d-%04d to %02d-%02d-%04d | %-*s | %-*s |\n", 
                       i, max_type_len,
                       (rooms[i].type == SOLO1) ? "Solo Type 1" : 
                       (rooms[i].type == SOLO2) ? "Solo Type 2" : 
                       (rooms[i].type == SOLO3) ? "Solo Type 3" : 
                       (rooms[i].type == DUO1) ? "Duo Type 1" : 
                       (rooms[i].type == DUO2) ? "Duo Type 2" : 
                       (rooms[i].type == DUO3) ? "Duo Type 3" : 
                       (rooms[i].type == SQUAD1) ? "Squad Type 1" : 
                       (rooms[i].type == SQUAD2) ? "Squad Type 2" : 
                       (rooms[i].type == SQUAD3) ? "Squad Type 3" : 
                       (rooms[i].type == FAMILY1) ? "Family Type 1" : 
                       (rooms[i].type == FAMILY2) ? "Family Type 2" : "Family Type 3",
                       rooms[i].reservations[j].check_in.month, rooms[i].reservations[j].check_in.day, rooms[i].reservations[j].check_in.year,
                       rooms[i].reservations[j].check_out.month, rooms[i].reservations[j].check_out.day, rooms[i].reservations[j].check_out.year,
                       max_guest_len, rooms[i].reservations[j].name, max_phone_len, rooms[i].reservations[j].phone);
            }
        }
    }
    printf("%s", buffer);
}

void save_reservations_to_file() {
    FILE *file = fopen("file.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    for (int i = 1; i < NUM_ROOMS; i++) {
        for (int j = 1; j < rooms[i].count; j++) {
            Reservation *res = &rooms[i].reservations[j];
            fprintf(file, "Room %d, Check-in: %02d-%02d-%04d, Check-out: %02d-%02d-%04d, Name: %s, Phone: %s, Guests: %d\n", 
                    i, res->check_in.month, res->check_in.day, res->check_in.year, 
                    res->check_out.month, res->check_out.day, res->check_out.year, 
                    res->name, res->phone, res->num_guests);
        }
    }

    fclose(file);
    printf("Reservations saved to file.\n");
}

void load_reservations_from_file() {
    FILE *file = fopen("file.txt", "r");
    if (file == NULL) {
        printf("Error opening file for reading!\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        int room_number, check_in_month, check_in_day, check_in_year, check_out_month, check_out_day, check_out_year, num_guests;
        char name[NAME_LEN], phone[PHONE_LEN];

        sscanf(line, "Room %d, Check-in: %d-%d-%d, Check-out: %d-%d-%d, Name: %[^,], Phone: %[^,], Guests: %d\n",
               &room_number, &check_in_month, &check_in_day, &check_in_year,
               &check_out_month, &check_out_day, &check_out_year,
               name, phone, &num_guests);

        if (room_number >= 1 && room_number < NUM_ROOMS && rooms[room_number].count < MAX_RESERVATIONS) {
            Reservation *res = &rooms[room_number].reservations[rooms[room_number].count];
            res->check_in.month = check_in_month;
            res->check_in.day = check_in_day;
            res->check_in.year = check_in_year;
            res->check_out.month = check_out_month;
            res->check_out.day = check_out_day;
            res->check_out.year = check_out_year;
            strncpy(res->name, name, NAME_LEN);
            strncpy(res->phone, phone, PHONE_LEN);
            res->num_guests = num_guests;
            rooms[room_number].count++;
        }
    }

    fclose(file);
    printf("Reservations loaded from file.\n");
}

void delete_guest() {
    char name[NAME_LEN];
    bool found = false;

    printf("Enter the guest name to delete the reservation: ");
    getchar();  // Clear newline character left in the buffer
    fgets(name, NAME_LEN, stdin);
    name[strcspn(name, "\n")] = 0;  // Remove newline character from the input

    for (int i = 1; i < NUM_ROOMS; i++) {
        for (int j = 1; j < rooms[i].count; j++) {
            if (strcmp(rooms[i].reservations[j].name, name) == 0) {
                found = true;
                // Shift all subsequent reservations one position up
                for (int k = j; k < rooms[i].count - 1; k++) {
                    rooms[i].reservations[k] = rooms[i].reservations[k + 1];
                }
                rooms[i].count--;  // Decrease the count of reservations
                printf("Reservation for %s has been deleted from room %d.\n", name, i);
                break;  // Exit the loop as reservation is found and deleted
            }
        }
        if (found) break;  // Exit the loop if reservation is found and deleted
    }

    if (!found) {
        printf("Reservation for %s not found.\n", name);
    }
}

int main() {
    initialize_rooms();
    load_reservations_from_file();

    int choice;

    while (1) {
        clear();
        printf("\n");
        printf("\t\t\t\t\t\t                        SEGE DADDY                       \n");
        printf("\t\t\t\t\t\t_________________________________________________________\n");
        printf("\t\t\t\t\t\t| Code |                  Program                       |\n");
        printf("\t\t\t\t\t\t|------|------------------------------------------------|\n");
        printf("\t\t\t\t\t\t| (1)  |Reserve Guest                                   |\n");
        printf("\t\t\t\t\t\t| (2)  |View Available Rooms                            |\n");
        printf("\t\t\t\t\t\t| (3)  |Display Guest                                   |\n");
        printf("\t\t\t\t\t\t| (4)  |Delete Guest                                    |\n");
        printf("\t\t\t\t\t\t| (5)  |Exit                                            |\n");
        printf("\t\t\t\t\t\t---------------------------------------------------------\n");
        printf("\n");
        printf("\t\t\t\t\t\tEnter your choice: ");
        scanf("%d", &choice);

        if (choice < 1 || choice > 5) {
            while (getchar() != '\n');
            printf("\t\t\t\t\t\t  Invalid input. Please enter a number between 1 and 5.\n");
            printf("\t\t\t\t\t\t  Press any key to continue...");
            getch();
            continue;
        }
        if (choice == 1) {
            clear();
            reserve_room();
            save_reservations_to_file(); // Save reservations after making a reservation
            printf("Press any key to get back to main menu.......");
            getch();
        }
		
        if (choice == 2) {
            clear();
            guest_list_menu();
        }

        if (choice == 3) {
            clear();
            print_availability(); 
            printf("Press any key to get back to main menu.......");
            getch();
        }
        
        if(choice == 4){
            clear();
            print_availability();
            delete_guest();
            save_reservations_to_file();
            printf("Press any key to get back to main menu.......");
            getch();
        }
        
        if(choice == 5){
            clear();
            save_reservations_to_file(); // Save reservations before exiting
            printf("Exiting....\n");
            break;
        }
    }
    return 0;
}
