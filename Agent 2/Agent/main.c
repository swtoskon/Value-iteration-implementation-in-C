//
//  main.c
//  Agent
//
//  Created by SOTIRIS KONSTANTAKOS on 21/1/20.
//  Copyright © 2020 SOTIRIS KONSTANTAKOS. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#define ROWS 3;
#define COLS 4;
enum actions{up,right,down,left};

double prob1=0.8;
double prob2=0.1;
double prob3=0.1;
double reward = -0.04;
double discount = 1;

void actions1(int i,int j,enum actions act,double env[3][4],double *sum);
void poss_actions(double env[3][4],enum actions act,int position[2],double f[4]);


int main(int argc, const char * argv[]) {
    int i=0;
    int j=0;
    enum actions act;
    act=up;
    double env[3][4];
    double sum=0.0;
    
    for(i=0; i<3; i++){
        for(j=0; j<4; j++){
            env[i][j]= 0;
        }
        
    }
    
    env[0][3]=1.0;
    env[1][3]=-1.0;
    double max = 0.0;
    int k;
    int l;
        
    for(l=0; l<100; l++){
    for(i=0; i<3; i++){
        for(j=0; j<4; j++){
            if((i==0 &&j==3) || (i==1 &&j==3) || (i==1 &&j==1) ){
              
                continue;
            }
            else{
                 max=0.0;
            for(k=0; k<4; k++){
               actions1(i,j,k,env,&sum);
      
                   if(sum>max)
                        max = sum;
        
            }
                env[i][j] = reward + discount * max;
            }
            
    
    }
       
    }
    }
    
    for(i=0; i<3; i++){
        for(j=0; j<4; j++){
            printf("%0.3f ",env[i][j]);
        }
        printf("\n");
        
    }
    
    
    int position[2]={2,0};
    double f[4];
    int p=0;
    int counter=0;
    int path[14];
    double visited[3][4];
    double value_visited[3][4];
    int c=0;
    int m;
      while(position[0]!=0 || position[1]!=3){
         double min =100;
      for(i=0; i<4; i++){
    poss_actions(env, i, position, f);
          if(f[i]<min ) {
            min =f[i];
              p = i;
          }
          else{
              if(f[i]!=2){
              visited[position[0]][position[1]]=1;
                value_visited[position[0]][position[1]]=f[i];
              c++;
                  
          }
          }
    }
        
        path[counter] = p;
        counter++;
        if(p==0){
            position[0] --;
        }
        else if(p==1){
            position[1]++;
        }
        else if(p==2){
            position[0]++;
        }
        else{
            position[1]--;
        }
          for(k=0; k<c; k++){
              for(l=0; l<3; l++){
                  for(m=0; m<4; m++){
                      if(visited[l][m]==1){
                          if (value_visited[l][m]<min) {
                              min=value_visited[l][m];
                              position[0]=l;
                              position[1]=m;
                          }
                      }
                  }
              }
              
          }
         
         
      }
    for (i=0; i<counter; i++) {
        if(path[i]==0)
            printf("%s -> ","up");
        else if(path[i]==1)
            printf("%s -> ","right ");
        else if(path[i]==2)
            printf("%s -> ","down ");
        else
            printf("%s -> ","left");
        }
    printf("Final state \n");
    return 0;
}

void actions1(int i,int j,enum actions act,double env[3][4],double *sum){
    int position[2]={i,j};
    
    if (act==0) {
        int noiseR[2]={position[0],position[1]+1};
        int noiseL[2]={position[0],position[1]-1};
        position[0]--;
        if (position[0]<0 || (position[0]==1 && position[1]==1))
            position[0]++;
    
        if(noiseR[1]>3 || (noiseR[0]==1 && noiseR[1]==1) ){
            noiseR[1]--;
        }
        
        if(noiseL[1]<0 || (noiseL[0]==1 && noiseL[1]==1)){
            noiseL[1]++;
        }
         *sum = prob1 * env[position[0]][position[1]] +prob2*env[noiseR[0]][noiseR[1]] +prob3 *env[noiseL[0]][noiseL[1]];
        
    }
    else if(act==1){
        
        int noiseUp[2]={position[0]-1,position[1]};
        int noiseD[2]={position[0]+1,position[1]};
        position[1]++;
        if(position[1]>3 || (position[0]==1 && position[1]==1))
            position[1]--;
        if(noiseUp[0]<0 || (noiseUp[0]==1 && noiseUp[1]==1) ){
            noiseUp[0]++;
        }
        if(noiseD[0]> 2 || (noiseD[0]==1 && noiseD[1]==1) ){
            noiseD[0]--;
        }
       * sum = prob1 * env[position[0]][position[1]] +prob2*env[noiseUp[0]][noiseUp[1]] +prob3 *env[noiseD[0]][noiseD[1]];
     
       
    }
     else if (act==2) {
        int noiseR[2]={position[0],position[1]+1};
        int noiseL[2]={position[0],position[1]-1};
        position[0]++;
        if (position[0]>2  || (position[0]==1 && position[1]==1))
            position[0]--;
        
        if(noiseR[1]>3 || (noiseR[0]==1 && noiseR[1]==1) ){
            noiseR[1]--;
        }
        
        if(noiseL[1]<0 || (noiseL[0]==1 && noiseL[1]==1)){
            noiseL[1]++;
        }
         * sum = prob1 * env[position[0]][position[1]] +prob2*env[noiseR[0]][noiseR[1]] +prob3 *env[noiseL[0]][noiseL[1]];
        
    }
     else{
         
         int noiseUp[2]={position[0]-1,position[1]};
         int noiseD[2]={position[0]+1,position[1]};
         position[1]--;
         if(position[1]<0 || (position[0]==1 && position[1]==1))
             position[1]++;
         if(noiseUp[0]<0 || (noiseUp[0]==1 && noiseUp[1]==1) ){
             noiseUp[0]++;
         }
         if(noiseD[0]> 2 || (noiseD[0]==1 && noiseD[1]==1) ){
             noiseD[0]--;
         }
         
         * sum = prob1 * env[position[0]][position[1]] +prob2*env[noiseUp[0]][noiseUp[1]] +prob3 *env[noiseD[0]][noiseD[1]];
         
         
     }
    
}




void poss_actions(double env[3][4],enum actions act,int position[2],double f[4]){
    if(act==0){
        int new_pos[2] = {position[0] - 1,position[1]};
        if(new_pos[0]<0 || (new_pos[0]==1 && new_pos[1]==1)){
            f[act]=2;
    }
        else{
            f[act]= 1 -env[new_pos[0]][new_pos[1]]  ;
        }
    }
        else if(act==1 ){
            int new_pos[2] = {position[0] ,position[1] + 1};
            if(new_pos[1]>3 || (new_pos[0]==1 && new_pos[1]==1)){
                f[act]=2;
            }
            else{
                f[act]= 1 - env[new_pos[0]][new_pos[1]];
            }
}
        else  if(act==2 ){
            int new_pos[2] = {position[0] + 1,position[1]};
            if(new_pos[0]>2 || (new_pos[0]==1 && new_pos[1]==1)){
                f[act]=2;
            }
            else{
                f[act]=  1- env[new_pos[0]][new_pos[1]] ;
            }

        }
        else  {
            int new_pos[2] = {position[0] ,position[1]-1};
            if(new_pos[1]<0 || (new_pos[0]==1 && new_pos[1]==1)){
                f[act]=2;
            }
            else{
                f[act]=1 - env[new_pos[0]][new_pos[1]] ;
            }
    

        }
}
