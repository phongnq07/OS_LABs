/*
   A program that opens and creates a file descriptor for shared memory and
   also maps the memory
   We'll write and retrieve an array of three floating-point numbers
   $gcc shm-writer-floatNums.c -o  shm-writer-floatNums -lrt
*/

#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define DATASIZE 128

int main(void)
{
   int fd;
   float *addr;
   // A file descriptor - memid contains the name of the memory-mapped descriptor
   const char memid[] = "/my_memory";

   const float numbers[3] = { 3.14, 2.718, 1.202};

   /* create shared memory file descriptor */
   if ( (fd = shm_open(memid, 
      O_RDWR | O_CREAT, 0600)) == -1)
   {
      perror("Can't open memory fd");
      return 1;
   }

	/* truncate memory to DATASIZE */
	if ( (ftruncate(fd, DATASIZE)) == -1 )
   {
      perror("Can't truncate memory");
      return 1;
   }

   // mapping the shared memory space
   // there's a total of six arguments to the memory mapping function, mmap()
   /* map memory using our file descriptor */
   addr = mmap(NULL, DATASIZE, PROT_WRITE, 
      MAP_SHARED, fd, 0);
   /*
      The first arg : the memory address, set to NULL - meaning the kernel will take care of it
      The second arg : the size of the memory area
      The third arg : the protection the memory area. we will set it to write and read
      The fourth arg : our flags, we set to shared and anonymous - meaning
                        it can be shared among processes and won't be backed by a file
      The fifth arg : a file descriptor
      The last arg : the offset, we will set to 0
   */
   
   if (addr == MAP_FAILED)
   {
      perror("Memory mapping failed");
      return 1;
   }

   /* copy data to memory */
   memcpy(addr, numbers, sizeof(numbers));

   /* wait for enter */
   printf("Hit enter when finished ");
   getchar();
   /* clean up */
   munmap(addr, DATASIZE);
   shm_unlink(memid);
   return 0;
}
