#include "stdio.h"
#include "graphics.h"
#include "stdlib.h"

main()
{
   struct
   {
     int c[2];
     int d[2];
   } a[4][4];
   int gdriver = DETECT, gmode, errorcode;

   for (int i=0; i<4; i++)
   {
     int x = rand() % (getmaxx()-10) + 5;
     int y = rand() % (getmaxy()-10) + 5;
     int dx = (rand() % 2)*2 - 1;
     int dy = (rand() % 2)*2 - 1;
     for(int j=0; j<4; j++)
     {
       a[i][j].c[1] = x++;
       a[i][j].c[2] = y++;
       a[i][j].d[1] = dx;
       a[i][j].d[2] = dy;
     }
   }
   initgraph(&gdriver, &gmode, "f:\\pgmlangs\\bcpp\\bgi");

   errorcode = graphresult();

   if (errorcode != grOk) {} /* an error occurred */

   cleardevice();
   setcolor(1);

while(1)
{
   for(int j=0; j<4; j++)
     for(int k=0; k<4; k++)
     {
       line(a[j][k].c[1],a[j][k].c[2],a[(j+1)%4][k].c[1],a[(j+1)%4][k].c[2]);
       if(a[j][k].c[1]+a[j][k].d[1]<0 || a[j][k].c[1]+a[j][k].d[1]>getmaxx())
	 a[j][k].d[1] = -a[j][k].d[1];
       if(a[j][k].c[2]+a[j][k].d[2]<0 || a[j][k].c[2]+a[j][k].d[2]>getmaxy())
	 a[j][k].d[2] = -a[j][k].d[2];
       a[j][k].c[1] += a[j][k].d[1];
       a[j][k].c[2] += a[j][k].d[2];
     }
}
   closegraph();
   return 0;
}
