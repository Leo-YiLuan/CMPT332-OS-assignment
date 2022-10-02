#include "kernel/types.h"
#include "user.h"

int i;

int testNumprocs(int n){
  	int tempid;
	for (i = 0; i < n; i++) {
		tempid = fork();
		/* child in an infinite loop make parent possible
 		 * to count all process*/
		if (tempid==0) {
			while(1);
   	 	}else if (tempid == -1) {
   			printf("Fail to create new process\n" );
   		}
  	}	
  	return numprocs();
}


int main(int argc, char *argv[])
{
    int procNum=0;
    int expect=0;
    int result=testNumprocs(procNum);
	int totalProcs = procNum;
    if(result!=expect){
        printf("Error: test of %d processes expect to get: %d, but"
		" get: %d\n", totalProcs, expect, result);
 	}else{
		printf("The return of numprocs() is: %d,  expect: %d\n",
		result, totalProcs);
	}
	
    procNum=5;
    expect+=5;
    result=testNumprocs(procNum);
	totalProcs += procNum;
    if (result!=expect){
         printf("Error: test of creating: %d more processes expect to get: %d,"
		" but get: %d\n", totalProcs, expect, result);
 	}
	else{
		printf("The return of numprocs() is: %d,  expect: %d\n",
		result, totalProcs);
	}
    procNum=10;
    expect+=10;
    result=testNumprocs(procNum);
	totalProcs += procNum;
    if(result!=expect){
         printf("Error: test of creating: %d more processes expect to get: %d,"
		" but get: %d\n", totalProcs, expect, result);
 	}
	else{
		printf("The return of numprocs() is: %d,  expect: %d\n",
		result, totalProcs);
	}
    procNum=20;
    expect+=20;
    result=testNumprocs(procNum);
	totalProcs += procNum;
    if(result!=expect){
         printf("Error: test of creating: %d more processes expect to get: %d,"
		" but get: %d\n", totalProcs, expect, result);
 	}
	else{
		printf("The return of numprocs() is: %d,  expect: %d\n",
		result, totalProcs);
	}
    procNum=11;
    expect+=11;
    result=testNumprocs(procNum);
	totalProcs += procNum;
    if(result!=expect){
         printf("Error: test of creating: %d more processes expect to get: %d,"
		" but get: %d\n", totalProcs, expect, result);
 	}
	else{
		printf("The return of numprocs() is: %d,  expect: %d\n",
		result, totalProcs);
	}
    procNum=10;
    expect+=10;
    result=testNumprocs(procNum);
	totalProcs += procNum;
    if(result!=expect){
         printf("Error: test of creating: %d more processes expect to get: %d,"
		" but get: %d\n", totalProcs, expect, result);
 	}
	else{
		printf("The return of numprocs() is: %d,  expect: %d\n",
		result, totalProcs);
	}
	 return 0;
}
