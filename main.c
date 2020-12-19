#include <unistd.h> 
#include <sys/types.h> 
#include <errno.h> 
#include <stdio.h> 
#include <sys/wait.h> 
#include <stdlib.h> 
#include<time.h>


/*
 Preamble of PROBLEM 1: This project does several things — first it goes through every number 1-10000 and checks which numbers are both prime AND have digits which add to 11. From there, it adds them to a file. Interestingly, the file has to close and open every single time things are added to it ("a") function for append.
 During this time, the system keeps track how long it takes
 For the second part of the project, we use processes to divide up the process as we take 10 files from 1-1000, 1001-2000,..., etc. to add each value to the file. During this time we are also using the time() function to keep track of everything.
 
 Sunny Dhindsa project 5 CSO due 20 December 2020 PROBLEM 1
 */

int check_prime(int a)
{
   int c;
 
   for ( c = 2 ; c <= a - 1 ; c++ )
   { 
      if ( a%c == 0 )
     return 0;
   }
   return 1;
}

int check_digits(int i)
{
	int sum = 0 ; 
	while (i != 0)
	{
		sum = sum + (i % 10) ; 
		i = i/10 ; 
	}
	if (sum == 11)
	{
		return 1 ; 
	}
	else
		return 0 ; 
}

int main()
{
	FILE *fp ; 
	fp = fopen("masterFile.txt", "w") ; 
	fclose(fp) ; 
	//clock_t start, end;
	double cpu_time_used ;
	//start = clock() ;

    time_t start = time(NULL) ;

	int i = 1 ; 
	for (i = 1; i<=100000; i++)
	{
		if (check_prime(i) && check_digits(i))
		{  
			//here we write into the file! ;)

			fp = fopen("masterFile.txt", "a") ; 
			fprintf(fp, "%d\n", i) ; 
			fclose(fp) ; 
			
		}
	}
    time_t end = time(NULL) ;
	cpu_time_used = ((double)(end-start)) ; 
	printf("Time: %f seconds\n", cpu_time_used) ;

	//part 2: restarting clock and forking everything!! 
	clock_t start1, end1 ; 
	i = 1 ; 

	//double cpu_time_used1 ;
	//start = clock() ;
    start = time(NULL) ;
    
	pid_t pid, ppid ;
    int status ;
    
	int process = 1 ; 
	while (process<11)
{

	pid = fork() ; 
	if (pid == 0) //checks if child process yuh
	{
		//printf("hello") ; this is for debugging
		FILE *fp1 ; 
		char filename[100] ; 
		char filenum[10] ; 
		sprintf(filenum, "%d", process) ; //converts to string
		strcpy(filename, "file") ; 
		strcat(filename, filenum) ; 
		strcat(filename, ".txt") ; 

		fp1 = fopen(filename, "w") ; 
		fclose(fp1) ; 

		for (i = (10000*(process-1)+1); i<=(process*10000); i++)
		{
			if (check_prime(i) && check_digits(i))
			{
				//printf("%d", 10000*(process-1)+1) ;
				//printf("%d", check_digits(10001)) ; 
				//printf("%d", check_prime(10001)) ;  
				fp1 = fopen(filename, "a") ; 
				fprintf(fp1, "%d\n", i) ; 
				fclose(fp1) ; 
			}

		}
		

		exit(0) ; 
	}
	process++ ; 
}




//fclose(superFile) ;
FILE *fp2, *fp3 ;
    int b = 1 ;

    while((ppid = wait(&status) >0)) ;

for (b = 1; b<11; b++)
{
	//we do the same formatting for the text files but we do %d, i for each index
	//from there, we have a while loop to read to the end of each file and then copy each line 
	//to the "superFile"
	//make sure to close after each while loop is done!
	fp2 = fopen("superFile.txt", "a") ;

	char filename[100] ; 
	char filenum[10] ; 
	sprintf(filenum, "%d", i) ; //converts to string
	strcpy(filename, "file") ; 
	strcat(filename, filenum) ; 
	strcat(filename, ".txt") ; 

	fp3 = fopen(filename, "r") ;

    char info ;
    char buffer ;
    
    while((buffer = fgetc(fp3))!=EOF)
    {
        fputc(buffer,fp3) ;
    }

	//while ((info == fgetc(fp3)) != EOF)
    //{
      //  fputc(info, fp2) ;
   // }
    fclose(fp3) ;


}
    end = time(NULL) ;
cpu_time_used = ((double)(end - start)) ; 
printf("Time: %f seconds\n", cpu_time_used) ;
return 1 ; 

}
