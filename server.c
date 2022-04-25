#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include<unistd.h>
float knapsack(int weight[], int profit[]) {
   float x[20], tp = 0;
   int i, j, u;
   u = 10;
   int n=4;
   for (i = 0; i < n; i++)
      x[i] = 0.0;
 
   for (i = 0; i < n; i++) {
      if (weight[i] > u)
         break;
      else {
         x[i] = 1.0;
         tp = tp + profit[i];
         u = u - weight[i];
      }
   }
 
   if (i < n)
      x[i] = u / weight[i];
 
   tp = tp + (x[i] * profit[i]);
 
   return tp;
}
int m2=10,n2=6;
int max(int a, int b)
{
    return (a > b)? a : b;
}
int lcs( char *X, char *Y, int m, int n )
{
    if (m == 0 || n == 0)
        return 0;
    if (X[m-1] == Y[n-1])
        return 1 + lcs(X, Y, m-1, n-1);
    else
        return max(lcs(X, Y, m, n-1), lcs(X, Y, m-1, n));
}
int main(int agrc,char *argv[]){

        int sockfd;int var,var1;int s1,s2;
        char a[]="abcdefghijklmnopqrstuvwxyz";
        FILE *c1,*c2;
        c1=fopen("/home/ec2-user/environment/Project/client1","w+");
        c2=fopen("/home/ec2-user/environment/Project/client2","w+");
        int z=sizeof(a)-1;
        struct sockaddr_in serverAddr;int var3;int score1=0,score2=0;
        int g1[4],g2[4];char g3[10],n[6],g4[10],n8[6];int g5[4];int g6[4];
        int l,y,var2,l2;
        int newSocket,newSocket2,x;
        struct sockaddr_in newAddr;
        int ans1,ans2;
        float profit=knapsack(g1,g2);
       socklen_t addr_size;
        char buffer[1024];

        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        memset(&serverAddr, '\0', sizeof(serverAddr));

        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(atoi(argv[1]));
        serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

        bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
        
        listen(sockfd, 5);
        int g=fork();
        if(g==0)
        {
        newSocket = accept(sockfd, NULL, NULL);
        printf("Connected with client socket number 1\n");
        while(1)
        {
        recv(newSocket,&s1,sizeof(s1),0);
        if(s1==0)
        {
            send(newSocket,&score1,sizeof(score1),0);
           break;
        }
        else if(s1==1)
        {
            printf("client1 requested fractional knapsack\n");
            for(int i=0;i<4;i++)
        {
            g1[i]=rand()%10;
            if(g1[i]==0)
              g1[i]=g1[i]+1;
        }
        for(int i=0;i<4;i++)
        {
            g2[i]=rand()%10;
            if(g2[i]==0)
               g2[i]=g2[i]+2;
        }
           send(newSocket, &g1, sizeof(g1), 0);
           send(newSocket, &g2, sizeof(g2), 0);
           float profit=knapsack(g1,g2);
           int a1=(int)profit;
           recv(newSocket,&ans1,sizeof(ans1),0);
           send(newSocket,&a1,sizeof(a1),0);
           fprintf(c1,"client1 requested knapsack\n");
           fprintf(c1,"Weights :");
           for(int i=0;i<4;i++)
           {
               fprintf(c1,"%d ",g1[i]);
           }
           fprintf(c1,"\nProfits :");
           for(int i=0;i<4;i++)
           {
               fprintf(c1,"%d ",g2[i]);
           }
           fprintf(c1,"\nMaximum profit calcualted by server:%d\n",a1);
           fprintf(c1,"Maximum profit calcualted by client:%d\n",ans1);
           if(ans1==a1)
           {
               score1=score1+1;
              fprintf(c1,"status:Client won the game\n");
           }
            else
               fprintf(c1,"status:Client Loss the game\n");
        }
        else
        {
            printf("client1 requested LCS\n");
              for(int i=0;i<10;i++)
               {
                  y=rand()%z;
                  g3[i]=a[y];
               }
            for(int i=0;i<7;i++)
            {
                y=rand()%z;
                n[i]=a[y];
            }
            send(newSocket,&g3,sizeof(g3),0);
            send(newSocket,&n,sizeof(n),0);
            recv(newSocket,&l,sizeof(l),0);
            int ms1=lcs(g3,n,m2,n2);
           send(newSocket,&ms1,sizeof(ms1),0);
           fprintf(c1,"client1 requested LCS\n");
           fprintf(c1,"String1 :");
           for(int i=0;i<10;i++)
           {
               fprintf(c1,"%c",g3[i]);
           }
           fprintf(c1,"\nString2 :");
           for(int i=0;i<6;i++)
           {
               fprintf(c1,"%c",n[i]);
           }
           fprintf(c1,"\nServer calculated LCS value is %d\n",ms1);
           fprintf(c1,"Client calcualted LCS value is %d\n",l);
           if(ms1==l)
           {
               score1=score1+1;
               fprintf(c1,"Status:Client won the game\n");
           }
           else
           {
               fprintf(c1,"Status:Client loss the game\n");
           }
           
        }
        }
        fprintf(c1,"Total Score is %d",score1);
        printf("Score sent to Client1 Successfully and client1 exited\n");
       }
       else
        {
         newSocket2 = accept(sockfd, NULL, NULL);
         printf("Connected with client socket number 2\n");
         while(1)
         {
        recv(newSocket2,&s2,sizeof(s2),0);
        if(s2==0)
        {
            send(newSocket2,&score2,sizeof(score2),0);
           break;
        }
        else if(s2==1)
        {
            printf("client2 requested fractional knapsack\n");
         for(int i=0;i<4;i++)
         {
            g5[i]=rand()%10;
            if(g5[i]==0)
                g5[i]=g5[i]+2;
         }
         for(int i=0;i<4;i++)
         {
            g6[i]=rand()%10;
             if(g6[i]==0)
                 g6[i]=g6[i]+4;
         }
            send(newSocket2, &g5, sizeof(g5), 0);
            send(newSocket2, &g6, sizeof(g6), 0);
            recv(newSocket2,&ans2,sizeof(ans2),0);
            float profit2=knapsack(g5,g6);
            int a2=(int)profit2;
           send(newSocket2,&a2,sizeof(a2),0);
           fprintf(c2,"Client2 selected Knapsack\n");
           fprintf(c2,"Weights :");
           for(int i=0;i<4;i++)
           {
               fprintf(c2,"%d ",g5[i]);
           }
           fprintf(c2,"\nProfits :");
           for(int i=0;i<4;i++)
           {
               fprintf(c2,"%d ",g6[i]);
           }
           fprintf(c2,"\nMaximum profit calcualted by the Server is %d\n",a2);
           fprintf(c2,"Maximum profit calcuated by the client is %d\n",ans2);
           if(a2==ans2)
           {
               score2=score2+1;
               fprintf(c2,"Status:Client won the game\n");
           }
           else
           {
               fprintf(c2,"Status:Client Loss the game\n");
           }
        }
        else
        {
            printf("client2 requested LCS\n");
               for(int i=0;i<10;i++)
               {
                  y=rand()%z;
                  g4[i]=a[y];
               }
            for(int i=0;i<7;i++)
            {
                y=rand()%z;
                n8[i]=a[y];
            }
            send(newSocket2,&g4,sizeof(g4),0);
            send(newSocket2,&n8,sizeof(n8),0);
            recv(newSocket2,&l2,sizeof(l2),0);
            int ms2=lcs(g4,n8,m2,n2);
           send(newSocket2,&ms2,sizeof(ms2),0);
           fprintf(c2,"Client requested LCS\n");
           fprintf(c2,"String1 :");
           for(int i=0;i<10;i++)
               fprintf(c2,"%c",g4[i]);
            for(int i=0;i<6;i++)
                fprintf(c2,"%c",n8[i]);
            fprintf(c2,"Server calculated LCS value is %d\n",ms2);
            fprintf(c2,"Client calcualted LCS value is %d\n",l2);
            if(ms2==l2)
            {
                score2=score2+1;
                fprintf(c2,"Status:Client won the game\n");
            }
            else
                fprintf(c2,"Status:Client Loss the game\n");
        }
        }
        fprintf(c2,"Score :%d",score2);
        printf("score sent to client2 successfully and client2 exited\n");
        }
}
