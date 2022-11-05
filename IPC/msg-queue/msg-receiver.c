/*
   Compile :
   $gcc msg-receiver.c -o msg-receiver -lrt
   flag -lrt : Link rt library, which stands for Real Extension Library
*/

#include <stdio.h>
#include <mqueue.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
   int md; /* msg queue descriptor */
   char *buffer;
   struct mq_attr msgattr;

   /* to open the message queue mq_open()
      the first arg : the name of the queue
      the second arg : the flags , only want to read the queue
    */
   md = mq_open("/my_queue", O_RDONLY);

   if (md == -1 )
   {
      perror("Open message queue");
      return 1;
   }

   /* to get the attributes of the message queue 
      using mq_getattr().
      Once we have the attributes of the message, we use
      its mq_msgsize() member to allocate memory for a message
      of that size using calloc()
   */
   if ( (mq_getattr(md, &msgattr)) == -1 )
   {
      perror("Get message attribute");
      return 1;
   }


   /* return a pointer to that memory, that's buffer */
   buffer = calloc(msgattr.mq_msgsize, sizeof(char));

   if (buffer == NULL)
   {
      fprintf(stderr, "Couldn't allocate memory");
      return 1;
   }

   /* 
   msgattr.mq_curmsgs : the number of messages currently
   in the queue
   */
   printf("%ld messages in queue\n", msgattr.mq_curmsgs);

   for (int i = 0; i < msgattr.mq_curmsgs; i++)
   {  // we receive a message using mq_receive
      if ( (mq_receive(md, buffer, msgattr.mq_msgsize, NULL)) == -1 )
      {
         perror("Message receive");
         return 1;
      }
      printf("%s\n", buffer); // print the message
      // reset the entire memory to NULL characters using memset()
      memset(buffer, '\0', msgattr.mq_msgsize); 
   }

   free(buffer);
   mq_close(md);
   mq_unlink("/my_queue");
   return 0;
}
