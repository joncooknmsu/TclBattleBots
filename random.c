/*
 *
 *  VERY bad demo C battlebot
 *
 *
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(int argc,char **argv)
{
   char line[256], *action;
   int xpos, ypos, direction, speed, fuel, damage, damagetype;
   int scan, objectid, posangle, distance, dirangle;
   int speedchange, dirchange;
   FILE *log;

   /* change to zero to avoid creating a debugging log */
   if (1)
      log = fopen("bot.log","w");
   else
      log = 0;
   
   while (fgets(line,sizeof(line),stdin))
   {
      /* if logging, log this input line */
      if (log)
         fputs(line,log);
      /* parse the input line */
      sscanf(line,"%d %d %d %d %d %d %d",&xpos, &ypos, &direction, 
             &speed, &fuel, &damage, &damagetype);
      /* get second input line */
      fgets(line,sizeof(line),stdin);
      /* log it if necessary */
      if (log)
         fputs(line,log);
      /* if a scan result is reported, then parse it */
      scan = (int) line[0];
      if (scan)
         sscanf(line+2,"%d %d %d %d", &objectid, &posangle, &distance, 
                &dirangle);
      /* randomly change our speed, and avoid maxing it out */
      speedchange = rand()%3 - 1;
      if (speed > 8)
         speedchange = -1;
      else if (speed < -8)
         speedchange = 1;
      /* randomly change direction */
      dirchange = rand()%3 - 1;
      /* output the changes to the game server */
      printf("%d %d\n", dirchange, speedchange);
      /* log our output if necessary */
      if (log)
         fprintf(log, "  %d %d\n", dirchange, speedchange);
      /* if we scanned a bot, then fire at it, else scan again */
      if (scan && objectid==2)
         action = "fire";
      else
         action = "scan";
      /* output our action line to the game server */
      printf("%s\n",action);
      /* very important -- flush stdout */
      fflush(stdout);
      /* log the action, if we are logging */
      if (log) {
         fprintf(log, "  %s\n",action);
         fflush(log);
      }
   }
   /* close log file if we are logging */
   if (log)
      fclose(log);
   return 0;
}

