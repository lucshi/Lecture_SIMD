#include <string.h>
#include <stdio.h>
#include <time.h>


int main()
{
   char str[5000];
   char dest[5000];
   int i =0;
   int max = 1<<28;
   while(i<1){
        memset(str, 'a', 4000);
        i++;
   }
   printf("%c\n",str[2999]);
   i = 0;
   clock_t       start = clock();
   while(i<max){
        memcpy(dest, str, 3000);
        i++;
   }
   double duration = clock() - start;
   printf("duration is %f\n ms", duration/1000);
   return 0;

}

