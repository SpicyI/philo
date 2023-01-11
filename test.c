#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
 #include <sys/time.h>
#include "src/include/philo.h"

// static pthread_t th[5];

// void *
// tfunc (void *ptr)
// {       /* remove this to test it without the sleep */
//   while (1)
//   {
// 	usleep(100);
// 	printf("y\n");
//   }
  
// }

// void
// test ()
// {
//   int i;
//   memset (th, 0, 5 * sizeof (pthread_t));

//   for (i = 0; i < 5; i++)
//     {
//       if (pthread_create (&th[i], NULL, tfunc, NULL) < 0)
//         perror ("pthread_create");
//     }

//   for (i = 0; i < 5; i++)
//     {
//       if (pthread_join (th[i], NULL) < 0)
//         perror ("pthread_join");
//     }
// }

// int
// main (int argc, char **argv)
// {
//   while (1)
//     {
//       test ();
//     }
//   exit (0);
// }

// #include <stdio.h>
// #include <errno.h>
// int main(void)
// {
  
//   printf("-----%d\n",usleep(1000020));
// }


// while ()

// usleep(1000);

// expected gettime() + 1000

// gettime() ==  


int main(void){
    struct timeval  s;
    struct timeval  e;

    gettimeofday(&s,NULL);
    usleep(200*998);
    gettimeofday(&e,NULL);
    printf("======%d\n",timer(&s,&e));
    return 0;
}


















