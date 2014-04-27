#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>





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

FILE *out,*even;

void main(void){
int i;
int user;
int written;
printf("\nSecret Agent Wars (c) 11/08/93 by Alexey Zilber\nGame List Generator.\n");

if((even=fopen("users.dat","rb"))==NULL){ printf("Error opening users.dat!"); exit(2); }
written=fread(&player,sizeof(player),1,even);
fclose(even);
printf("Read %d types.\n",written);
if((out=fopen("game.lst","wt"))==NULL){ printf("Error opening game.lst!"); exit(2); }

fprintf(out,"\t\t\t   Secret Agent Wars\t\t\t\n\t\t\t-:-The First Chapter-:-\t\t\t\n");
fprintf(out,"컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴\n");
fprintf(out,"       EMPIRE NAME                          SCORE       NET WORTH\n");
fprintf(out,"컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴\n");
for(i=0;i<=24;i++){
fprintf(out,"%c-     ",player[i].empire_char);
fprintf(out,"%s\t\t\t      ",player[i].empire_name);
fprintf(out,"%d\t            ",player[i].score);
fprintf(out,"%d\n",player[i].networth);
/*
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
*/
fprintf(out,"컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴\n");
}
fclose(out);

printf("Files created.\n");
}

