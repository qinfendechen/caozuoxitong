#include<stdio.h>
#include<signal.h>
#include<unistd.h>

int pid1,pid2;
int EndFlag=0;
int pf1=0;
int pf2=0;

void IntDelete()
{
	kill(pid1,16);
	kill(pid2,17);
}

void Int1()
{
	printf("child process1(pid=%d,ppid=%d) is killed by parent!\n",getpid(),getppid());
	exit(0);
}
void Int2()
{
        printf("child process2(pid=%d,ppid=%d) is killed by parent!\n",getpid(),getppid());
        exit(0);
}
main()
{
	int exitpid;
	if(pid1=fork())
	{
		if(pid2=fork())
		{
			signal(SIGINT,IntDelete);
			waitpid(-1,&exitpid,0);
			waitpid(-1,&exitpid,0);
			printf("parent process(pid=%d)is killed!\n",getpid());
			exit(0);
		}
		else
		{
                        signal(SIGINT,SIG_IGN);
			signal(17,Int2);
			pause();
		}
	}
	else
	{
		signal(SIGINT,SIG_IGN);
                signal(16,Int1);
                pause();
        }
}
