#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>



struct univ{
char uniname[30];
int n_empires;
}univer;


struct play{
char empire_char;
char player_name[15];
char empire_name[20];
int score; int networth;
int army_morale;
int people_morale;
int spy_morale;
int money;
int food;

int grunts; int borgs; int robots; int univ_soldiers;

int f14s; int f15s; int stealth_bombers; int research_craft;

int carriers; int battleships; int submarines;

int space_carriers; int baseships; int fighters;

int missle_bases; int force_fields; int deflector_shields; int nucleics;

int research_points;
int war_res; int elect_res; int nucleic_res; int space_res; int air_res; int shield_res;
int f14_power; int f15_power; int stealth_power; int rcraft_power; int grunt_power; int robot_power;
int usoldier_power; int bship_power; int submarine_power; int fighter_power;

int money_p;
int food_p;
int tourism_p;
int ore_p;
int gov_p;
int mil_p;
int spy_p;
int university_p;
}player[25];

struct exist{
char player_name[15];
int alive;
int played_yet;
}stats[24];

FILE *out,*more,*evenmore;

void main(void){
int i;
int user;
int written;
printf("\nSecret Agent Wars (c) 11/08/93 by Alexey Zilber\nFile Generator, and Empire Creator.\n");
if(access("users.num",0)==0){ printf("users.num already exists.\n"); exit(1); }

if((out=fopen("users.num","wb"))==NULL){ printf("Error opening users.num!"); exit(2); }
user=0x00;
written=fwrite(&user,sizeof(user),1,out);
fclose(out);
printf("Wrote %d bytes to file users.num \n\n",written);
if(access("users.lst",0)==0){ printf("users.lst already exists.\n"); exit(1); }

if((more=fopen("users.lst","wb"))==NULL){ printf("Error opening users.lst!"); exit(2); }

for(i=0;i<=24;i++){
strcpy(stats[i].player_name,"NO PLAYER");
stats[i].alive=0x00;
stats[i].played_yet=0x00;
}

written=fwrite(&stats,sizeof(stats),25,more);
fclose(more);
printf("Written %d bytes to file users.lst \n\n",written);


if(access("users.dat",0)==0){ printf("users.dat already exists.\n"); exit(1); }

if((evenmore=fopen("users.dat","wb"))==NULL){ printf("Error opening users.dat!"); exit(2); }
for(i=0;i<=24;i++){
player[i].empire_char='A'+i;
strcpy(player[i].player_name,"NO PLAYER");
strcpy(player[i].empire_name,"NO EMPIRE YET");
player[i].score=0x01;
player[i].networth=0x01;
player[i].army_morale=0x64;
player[i].people_morale=0x64;
player[i].spy_morale=0x64;
player[i].money=0x3e8;
player[i].food=0x3e8;

player[i].grunts=0x64; player[i].borgs=0x34; player[i].robots=0x64; player[i].univ_soldiers=0x64;

player[i].f14s=0x34; player[i].f15s=0x34; player[i].stealth_bombers=0x34; player[i].research_craft=0x00;

player[i].carriers=0x10; player[i].battleships=0x01; player[i].submarines=0x01;

player[i].space_carriers=0x01; player[i].baseships=0x00; player[i].fighters=0x01;

player[i].missle_bases=0x0F; player[i].force_fields=0x00; player[i].deflector_shields=0x00; player[i].nucleics=0x00;

player[i].research_points=0x00;
player[i].war_res=0x00; player[i].elect_res=0x00; player[i].nucleic_res=0x00; player[i].space_res=0x00; player[i].air_res=0x00; player[i].shield_res=0x00;
player[i].f14_power=0x01; player[i].f15_power=0x01; player[i].stealth_power=0x01; player[i].rcraft_power=0x00; player[i].grunt_power=0x02; player[i].robot_power=0x01;
player[i].usoldier_power=0x01; player[i].bship_power=0x00; player[i].submarine_power=0x00; player[i].fighter_power=0x00;

player[i].money_p=0x02;
player[i].food_p=0x01;
player[i].tourism_p=0x02;
player[i].ore_p=0x00;
player[i].gov_p=0x01;
player[i].mil_p=0x01;
player[i].spy_p=0x00;
player[i].university_p=0x00;

}

written=fwrite(&player, sizeof(player),25,evenmore);
fclose(evenmore);
printf("Wrote %d bytes to file users.dat.\n\n",written);

printf("Files created.\n");
}

