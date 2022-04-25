#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
void main(int argc,char* argv[]){

        int clientSocket;int profit;int var;int ci;int score;
        struct sockaddr_in serverAddr;
        int buffer1[4],buffer2[4];
        char buffer3[10],buffer4[6];
        int andl,ands;
        clientSocket = socket(AF_INET, SOCK_STREAM, 0);

        memset(&serverAddr, '\0', sizeof(serverAddr));
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(atoi(argv[2]));
        serverAddr.sin_addr.s_addr = inet_addr(argv[1]);

        connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
        printf("Welcome to algortim Guess Game\n");
        printf("Connected to Game Server\n");
        printf("here we are going to solve 2 famous algorithms\n");
        printf("1)Fractional knapsack\n");
        printf("2)LCS\n");
        printf("Fractional Knapsack:The main objective is fiiling the knapsack"
                "That maximizes the total profit earned,here the the total capacity of knapsack is 10\n\n");
        printf("LCS:A subsequence is a sequence that appears in the same relative order"
        ",but not necessarily contiguous");
        while(1)
        {
        printf("press 1 for knapsack and 2 for LCS and 0 for exiting the game");
        scanf("%d",&ci);
        send(clientSocket,&ci,sizeof(ci),0);
        if(ci==0)
        {
            recv(clientSocket,&score,sizeof(score),0);
            printf("Your total score is %d\n",score);
            printf("Thanks for playing the game");
            break;
        }
        if(ci==1)
        {
        recv(clientSocket, &buffer1, sizeof(buffer1), 0);
        recv(clientSocket, &buffer2, sizeof(buffer2), 0);

        printf("\nweights: ");
        for(int i=0;i<4;i++)
        {
            printf("%d ",buffer1[i]);
        }
        printf("\n");
        printf("profits: ");
        for(int i=0;i<4;i++)
        {
            printf("%d ",buffer2[i]);
        }
        printf("enter the total profit");
        scanf("%d",&profit);
        send(clientSocket,&profit,sizeof(profit),0);
        recv(clientSocket,&var,sizeof(var),0);
        if(var!=profit)
            printf("sorry better luck next time value is %d\n",var);

        else
            printf("congrtulations you won the game\n");
        }
        else
        {
            recv(clientSocket,&buffer3,sizeof(buffer3),0);
            recv(clientSocket,&buffer4,sizeof(buffer4),0);
            printf("\nStringA: ");
            for(int i=0;i<10;i++)
            {
                printf("%c",buffer3[i]);
            }
            printf("\nStringB: ");
            for(int i=0;i<6;i++)
            {
                printf("%c",buffer4[i]);
            }
            printf("\nenter the LCS value ");
            scanf("%d",&andl);
            send(clientSocket,&andl,sizeof(andl),0);
            recv(clientSocket,&ands,sizeof(ands),0);
            if(ands==andl)
                printf("congrats you won the game\n");
            else
                printf("better luck nexttime value is %d\n",ands);
        }
        }
}
