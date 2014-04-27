#include <stdio.h>
#include <dos.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>





struct play{
char empire_char;
char player_name[15];
char player_handle[40];
int day;
int alive;
int alignment;
unsigned long int exp;
unsigned long int money;
unsigned long int bank;
int armor;
int location;
int hit_points;
int strength;
int defense;
int level;
int range_weapon;
int melee_weapon;
int energy_source;
int power_level;
int special_item1;
int special_item2;
int special_item3;
}player[25];


struct date d;

FILE *more,*evenmore;

void main(void){
int i;
int user;
int written;
/* int written2; */
printf("\nE-Man Cybernetics (c) 11/08/93 by Alexey Zilber\nFile Generator, and Unit Creator.\n");

if(access("users.dat",0)==0){ printf("users.dat already exists.\n"); exit(1); }


if((evenmore=fopen("users.dat","wb"))==NULL){ printf("Error opening users.dat!"); exit(2); }
getdate(&d);
d.da_day--;
for(i=0;i<=24;i++){
player[i].empire_char='A'+i;
strcpy(player[i].player_name,"EMPTY");
strcpy(player[i].player_handle,"JOHN DOE");
player[i].money=0x64;
player[i].day=d.da_day;
player[i].alive=0x00;
player[i].alignment=0x08;
player[i].armor=0x00;
player[i].range_weapon=0x00;
player[i].melee_weapon=0x00;
player[i].energy_source=0x00;
player[i].bank=0x00;
player[i].hit_points=0x00;
player[i].exp=0x00;
player[i].level=0x01;
player[i].strength=0x18;
player[i].defense=0x0D;
player[i].location=0x01;
player[i].power_level=0x00;
player[i].special_item1=0x00;
player[i].special_item2=0x00;
player[i].special_item3=0x00;
}
/* written2=0;
for(i=0; i<=24; i++){ */
written=fwrite(&player, sizeof(struct play),25,evenmore);
/* written2=written+written2; */
fclose(evenmore);
printf("Wrote %d units to file users.dat.\n\n",written);

printf("Files created.\n");
}

