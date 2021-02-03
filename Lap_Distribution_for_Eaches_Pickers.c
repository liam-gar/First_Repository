#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//Program to distribute laps between pickers for a given shift to minimize traffic
//Author : Liam Garcia

/*
Assumptions :
-lap sizes are always between 15 and 50
-The last picker to arrive for their shift will begin their first lap before the first picker finishes their first lap
-Each picker will take a 1 hour break sometime during their shift
*/

void main(){
    int i,j,k=1,m,n,laps,pickers,starthour[100],startminute[100],lapDuration[100],minuteSort[100],Distribute[100],TempIndex,sum=0;
    float rate[100],TempRate,TempElement,size[100],minuteNotation[100],TempTime,TotalTime[100][100],LapDuration[100][100],Transpose[100][100],TempMatrix,Min;
    printf("\nInput the total number of laps for this shift : ");
    scanf("%d",&laps);
    printf("\n");
    //This for loop iterates from 1 to the total number of laps and appends the size of the lap to an array called size in no particular order
    for (i=1;i<=laps;i++){
        printf("Enter the size of lap number %d : ",i);
        scanf("%f",&size[i]);
        sum=sum+size[i];
    }    
    printf("\nTotal number of Orders is %d",sum);
    //if condition below checks if the total number of orders for the shift is evenly divisable by 240 and performs integer division if true to determine the number of pickers 
    if (sum%240==0){
        pickers=sum/240;
        printf("\nNumber of pickers in the warehouse for this shift : %d",pickers);
    }
    //if there is 1 lap or the total number of orders for the shift is less than 240, there will be only 1 picker in the warehouse
    else if(laps==1 || sum<240){
        pickers=1;
        printf("\nNumber of pickers in the warehouse for this shift : %d",pickers);       
    }
    //if the total number of orders is not evenly divisable by 240, the number of pickers is the integer division of the orders by 240 + 1. 
    else{
        pickers=sum/240+1;
        printf("\nNumber of pickers in the warehouse for this shift : %d",pickers);
    }
    printf("\n\n");
    if (pickers==1){
        printf("There will be no traffic today");
    }
    //block of code below will execute if there is more than 1 picker for the shift
    else{
        //for each picker working that shift, their picking rate is appended to an array called rate in no particular order
        for (i=1;i<=pickers;i++){
            printf("Enter the picking rate for picker number %d (cases/hour) : ",i);
            scanf("%f",&rate[i]);
        }
        printf("\n");
        //The estimated arrival time for each picker corresponding to the rate array is appended to arrays called start hour and start minute
        for (i=1;i<=pickers;i++){
            printf("Enter the start time for picker number %d (hh:mm) : ",i);
            scanf("%d:%d",&starthour[i],&startminute[i]);
        }
        //The starting times entered in the previous loop as hh:mm are converted to minutes and appended to array minuteNotation where midnight is zero
        for (i=1;i<=pickers;i++){
            minuteNotation[i]=starthour[i]*60+startminute[i];
        }
        //for loop sorts the pickers from first to last based on arrival time
        for(i=1;i<=pickers;i++){
            for(j=i;j<=pickers;j++){
                if(minuteNotation[j]<=minuteNotation[i]){
                    TempTime=minuteNotation[i];
                    minuteNotation[i]=minuteNotation[j];
                    minuteNotation[j]=TempTime;
                    TempRate=rate[i];
                    rate[i]=rate[j];
                    rate[j]=TempRate;
                }
            }
        } 
        //for loop below initializes the starting time of the first picker at 0 and the starting time of the remaining pickers are recalculated with reference to the first picker
        TempTime=minuteNotation[1];
        for(i=1;i<=pickers;i++){
            minuteNotation[i]=minuteNotation[i]-TempTime;
            rate[i]=rate[i]/60;
        }
        //The first row of matrix TotalTime is composed of the starting times for each picker 
        for(i=1;i<=pickers;i++){
            TotalTime[0][i]=minuteNotation[i];
        }
        //Algorithm below distributes the laps between the pickers such that there is the minimum amount of time between the front picker and the picker behind finishing their laps
        Min=100;
        for(i=1;i<=laps/pickers+laps%pickers;i++){
            for(j=1;j<=pickers;j++){
                if((j+(i-1)*pickers)>laps){
                    break;
                }
                for(m=1;m<=laps;m++){
                    if(j==1){
                        if(0<(size[m]/rate[1]+TotalTime[i-1][1]-TotalTime[i-1][pickers]),(size[m]/rate[1]+TotalTime[i-1][1]-TotalTime[i-1][pickers])<Min && size[m]!=0){
                            Min=size[m]/rate[1]+TotalTime[i-1][1]-TotalTime[i-1][pickers];
                            TempIndex=m;
                        } 
                        if(m==laps && Min==100){
                            for(n=1;n<=laps;n++){
                                if((size[n]/rate[1]+TotalTime[i-1][1]-TotalTime[i-1][pickers])<Min && size[n]!=0){
                                    Min=size[n]/rate[1]+TotalTime[i-1][1]-TotalTime[i-1][pickers];
                                    TempIndex=n;                                    
                                }
                                if(n==laps){
                                    TotalTime[i][1]=size[TempIndex]/rate[1]+TotalTime[i-1][1];
                                    size[TempIndex]=0;   
                                    Min=100;                                 
                                }
                            }
                        } 
                        else if(m==laps && Min!=100){
                            TotalTime[i][1]=size[TempIndex]/rate[1]+TotalTime[i-1][1];
                            size[TempIndex]=0;
                            Min=100;
                        }
                    }
                    else{
                        if(0<(size[m]/rate[1]+TotalTime[i-1][1]-TotalTime[i-1][pickers]),(size[m]/rate[j]+TotalTime[i-1][j]-TotalTime[i][j-1])<Min && size[m]!=0){
                            Min=size[m]/rate[j]+TotalTime[i-1][j]-TotalTime[i][j-1];
                            TempIndex=m;
                        } 
                        if(m==laps && Min==100){
                            for(n=1;n<=laps;n++){
                                if((size[n]/rate[j]+TotalTime[i-1][j]-TotalTime[i][j-1])<Min && size[n]!=0){
                                    Min=size[n]/rate[j]+TotalTime[i-1][j]-TotalTime[i][j-1];
                                    TempIndex=n;                                    
                                }
                                if(n==laps){
                                    TotalTime[i][1]=size[TempIndex]/rate[j]+TotalTime[i-1][j];
                                    size[TempIndex]=0;  
                                    Min=100;                                  
                                }
                            }
                        } 
                        else if(m==laps && Min!=100){
                            TotalTime[i][j]=size[TempIndex]/rate[j]+TotalTime[i-1][j];
                            size[TempIndex]=0;
                            Min=100;
                        }
                    }
                }
            }
        }
        //elements in the matrix are coverted from total time to lap duration
        for(i=1;i<=laps/pickers+laps%pickers;i++){
            for(j=1;j<=pickers;j++){
                if((j+(i-1)*pickers)>laps){
                    TotalTime[i][j]=0; 
                }
                else{
                    LapDuration[i][j]=TotalTime[i][j]-TotalTime[i-1][j];
                }
            }
        }
        //The transpose of the matrix is taken so that each row rather than column corresponds to the laps attributed to each picker
        if(laps%pickers==0){
            for(i=1;i<=pickers;i++){
                for(j=1;j<=laps/pickers;j++){
                    Transpose[i][j]=LapDuration[j][i];
                }
            } 
            printf("\n");
            printf("Distribution of Laps between Pickers to minimize Traffic : ");
            printf("\n\n");
            for(i=1;i<=pickers;i++){
                printf("Laps for Picker with rate %f : ",rate[i]*60);
                printf("\n\n");
                for(j=1;j<=laps/pickers;j++){
                    //arithmetic computation to convert lap duration to lap size
                    Distribute[k]=Transpose[i][j]*rate[i];
                    if(Distribute[k]<Transpose[i][j]*rate[i]){
                        Distribute[k]=Distribute[k]+1;
                    }
                    //prints the laps for each picker
                    printf("\t%d\n",Distribute[k]);
                    k++;
                }
                printf("\n");
            }
        }
        else{
            for(i=1;i<=pickers;i++){
                for(j=1;j<=laps/pickers+1;j++){
                    Transpose[i][j]=LapDuration[j][i];
                    printf("%f\t",Transpose[i][j]);
                }
                printf("\n");
            } 
            printf("\n");
            printf("Distribution of Laps between Pickers to minimize Traffic : ");
            printf("\n\n");
            for(i=1;i<=pickers;i++){
                printf("Laps for Picker with rate %f : ",rate[i]*60);
                printf("\n\n");
                for(j=1;j<=laps/pickers+1;j++){
                    //arithmetic computation to convert lap duration to lap size
                    Distribute[k]=Transpose[i][j]*rate[i];
                    if(Distribute[k]<Transpose[i][j]*rate[i]){
                        Distribute[k]=Distribute[k]+1;
                    }
                    if(Distribute[k]==0){
                        break;
                    }
                    //prints the laps for each picker
                    printf("\t%d\n",Distribute[k]);
                    k++;
                }
                printf("\n");
            }
        }
    }
} 