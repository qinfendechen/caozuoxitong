#include<stdio.h>
#include<signal.h>
#include<unistd.h>

void waiting(),stop(),alarming();
int wait_mark;
main()
{
	int p1,p2;
	if(p1=fork())
	{
		if(p2=fork())
		{
			wait_mark=1;
			signal(SIGINT,stop);
			signal(SIGALRM,alarming);
			waiting();

			kill(p1,16);
			kill(p2,17);
			
			wait(0);
			wait(0);
			printf("parent process(pid=%d)is killed!\n",getpid());
			exit(0);
		}
		else
		{
			wait_mark=1;
                        signal(17,stop);
                        signal(SIGINT,SIG_IGN);
			while(wait_mark!=0);
			lockf(1,1,0);
                        printf("child process2(pid=%d,ppid=%d) is killed by parent!\n",getpid(),getppid());
			lockf(1,0,0);
                        exit(0);
		}
	}
	else
	{
		wait_mark=1;
                signal(16,stop);
                signal(SIGINT,SIG_IGN);
                while(wait_mark!=0);
                lockf(1,1,0);
                printf("child process1(pid=%d,ppid=%d) is killed by parent!\n",getpid(),getppid());
                lockf(1,0,0);
                exit(0);
        }
}
void waiting()
{
	sleep(5);
	if(wait_mark!=0)
	kill(getpid(),SIGALRM);
}
void alarming()
{
	wait_mark=0;
}
void stop()
{
	wait_mark=0;
}
