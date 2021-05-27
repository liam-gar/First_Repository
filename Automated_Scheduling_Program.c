#include<stdlib.h>
#include<stdio.h>
#include<string.h>

//Title : Automated Scheduling Program 
//Author : Liam Garcia
//Purpose : Intended for scheduling altar servers, ideally with 2 experienced servers and 1 trainee per week

void main(){
    int num_servers,i,j,k,l,m,num_experienced,num_trainees,column[255],row,trainee[255],weeks,experience[255],not_avail[255][255],scheduled[255][255],conflict_exp,conflict_tra,scheduled_exp,scheduled_tra,first_experienced,second_experienced,third_experienced,first_trainee,second_trainee,third_trainee;
    int index_first_experienced,index_second_experienced,index_third_experienced,index_first_trainee,index_second_trainee,index_third_trainee;
    char name[255][255],response[255],avail_input[255][255];
    printf("\nHow many weeks are there? : ");
    scanf("%d",&weeks);
    printf("How many servers are there? : ");
    scanf("%d",&num_servers);
    printf("\n");
    for(int i=1;i<=num_servers;i++){
        printf("Enter the name of server number %d : ",i);
        scanf("%s",&name[i]);
    }
    printf("\n");
    num_experienced=0,num_trainees=0;
    for(i=1;i<=num_servers;i++){
        printf("For which weeks is %s not available? : ",name[i]);
        scanf("%s",&avail_input[i]);
        printf("Is %s experienced? (Y/N) : ",name[i]);
        scanf("%s",&response[i]);
        if(response[i]=='Y'){
            num_experienced++;
            experience[num_experienced]=i;
        }
        else{
            num_trainees++;
            trainee[num_trainees]=i;
        }
    }
    for(row=1;row<=num_servers;row++){
        column[row]=1;
        for(i=0;i<255;i++){
            //Test case 1 : Single element 1 digit array
            if(i==0 && avail_input[row][i+1]!=',' && avail_input[row][i+1]!='0' && avail_input[row][i+1]!='1' && avail_input[row][i+1]!='2' && avail_input[row][i+1]!='3' && avail_input[row][i+1]!='4' && avail_input[row][i+1]!='5' && avail_input[row][i+1]!='6' && avail_input[row][i+1]!='7' && avail_input[row][i+1]!='8' && avail_input[row][i+1]!='9'){
                not_avail[row][column[row]]=avail_input[row][i]-'0';
                break;
            } 
            //Test case 2 : Single element 2 digit array
            else if(i==0 && avail_input[row][i+1]!=',' && avail_input[row][i+2]!=',' && avail_input[row][i+2]!='0' && avail_input[row][i+2]!='1' && avail_input[row][i+2]!='2' && avail_input[row][i+2]!='3' && avail_input[row][i+2]!='4' && avail_input[row][i+2]!='5' && avail_input[row][i+2]!='6' && avail_input[row][i+2]!='7' && avail_input[row][i+2]!='8' && avail_input[row][i+2]!='9'){
                not_avail[row][column[row]]=(avail_input[row][i]-'0')*10+(avail_input[row][i+1]-'0');
                break;
            }
            //Test case 3 : Multielement array, first element is single digit
            else if(i==0 && avail_input[row][i+1]==','){
                not_avail[row][column[row]]=avail_input[row][i]-'0';
                column[row]++;
            } 
            //Test case 4 : Multielement array, first element is double digit
            else if(i==0 && avail_input[row][i+1]!=',' && avail_input[row][i+2]==','){
                not_avail[row][column[row]]=(avail_input[row][i]-'0')*10+(avail_input[row][i+1]-'0');
                column[row]++;
            }
            //Test case 5 : Multielement array, inner element is single digit
            else if(avail_input[row][i-1]==',' && avail_input[row][i+1]==','){
                not_avail[row][column[row]]=avail_input[row][i]-'0';
                column[row]++;
            }
            //Test case 6 : Multielement array, inner element is double digit
            else if(avail_input[row][i-1]==',' && avail_input[row][i+1]!=',' && avail_input[row][i+2]==','){
                not_avail[row][column[row]]=(avail_input[row][i]-'0')*10+(avail_input[row][i+1]-'0');
                column[row]++;
            }
            //Test case 7 : Final element is single digit
            else if(avail_input[row][i-1]==',' && avail_input[row][i+1]!=',' && avail_input[row][i+1]!='0' && avail_input[row][i+1]!='1' && avail_input[row][i+1]!='2' && avail_input[row][i+1]!='3' && avail_input[row][i+1]!='4' && avail_input[row][i+1]!='5' && avail_input[row][i+1]!='6' && avail_input[row][i+1]!='7' && avail_input[row][i+1]!='8' && avail_input[row][i+1]!='9'){
                not_avail[row][column[row]]=avail_input[row][i]-'0';
                break;
            }
            //Test case 8 : Final element is double digit
            else if(avail_input[row][i-1]==',' && avail_input[row][i+1]!=',' && avail_input[row][i+2]!=',' && avail_input[row][i+2]!='0' && avail_input[row][i+2]!='1' && avail_input[row][i+2]!='2' && avail_input[row][i+2]!='3' && avail_input[row][i+2]!='4' && avail_input[row][i+2]!='5' && avail_input[row][i+2]!='6' && avail_input[row][i+2]!='7' && avail_input[row][i+2]!='8' && avail_input[row][i+2]!='9'){
                not_avail[row][column[row]]=(avail_input[row][i]-'0')*10+(avail_input[row][i+1]-'0');
                break;
            }
        }
    } 
    for(i=1;i<=weeks;i++){
        scheduled_exp=0;
        scheduled_tra=0;
        for(j=1;j<=num_experienced;j++){
            conflict_exp=0;
            for(k=1;k<=column[experience[j]];k++){
                if(not_avail[experience[j]][k]==i){
                    conflict_exp++;
                    break;
                }
            }
            if(conflict_exp==0){
                scheduled_exp++;
                if(scheduled_exp==1){
                    index_first_experienced=j;
                    first_experienced=experience[index_first_experienced];
                }
                else if(scheduled_exp==2){
                    index_second_experienced=j;
                    second_experienced=experience[index_second_experienced];
                    break;
                }
            }
        }
        if(scheduled_exp==2){
            if(index_first_experienced==index_second_experienced-1){
                if(index_first_experienced+2<=num_experienced){
                    for(l=index_first_experienced+2;l<=num_experienced;l++){
                        experience[l-2]=experience[l];
                    }
                }
            }
            else{
                for(l=index_first_experienced+1;l<index_second_experienced;l++){
                    experience[l-1]=experience[l];
                }
                for(l=index_second_experienced+1;l<=num_experienced;l++){
                    experience[l-2]=experience[l];
                }          
            }
            scheduled[i][1]=first_experienced;
            experience[num_experienced-1]=scheduled[i][1];
            scheduled[i][2]=second_experienced;
            experience[num_experienced]=scheduled[i][2];
            for(j=1;j<=num_trainees;j++){
                conflict_tra=0;
                for(k=1;k<=column[trainee[j]];k++){
                    if(not_avail[trainee[j]][k]==i){
                        conflict_tra++;
                        break;
                    }
                }
                if(conflict_tra==0){
                    scheduled_tra++;
                    index_first_trainee=j;
                    first_trainee=trainee[index_first_trainee];
                    for(m=index_first_trainee+1;m<=num_trainees;m++){
                        trainee[m-1]=trainee[m];
                    }
                    scheduled[i][3]=first_trainee;
                    trainee[num_trainees]=scheduled[i][3];
                    break;
                }
            }
        }
        if(scheduled_exp==1){
            if(index_first_experienced<num_experienced){
                for(l=index_first_experienced+1;l<=num_experienced;l++){
                    experience[l-1]=experience[l];
                }
            }
            scheduled[i][1]=first_experienced;
            for(j=1;j<=num_trainees;j++){
                conflict_tra=0;
                for(k=1;k<=column[trainee[j]];k++){
                    if(not_avail[trainee[j]][k]==i){
                        conflict_tra++;
                        break;
                    }
                }
                if(conflict_tra==0){
                    scheduled_tra++;
                    if(scheduled_tra==1){
                        index_first_trainee=j;
                        first_trainee=trainee[index_first_trainee];
                    }
                    else if(scheduled_tra==2){
                        index_second_trainee=j;
                        second_trainee=trainee[index_second_trainee];
                        break;
                    }
                }
            }
            if(scheduled_tra==1){
                if(index_first_trainee<num_trainees){
                    for(l=index_first_trainee+1;l<=num_trainees;l++){
                        trainee[l-1]=trainee[l];
                    }
                }
                scheduled[i][2]=first_trainee;
                trainee[num_trainees]=scheduled[i][2];
            }
            if(scheduled_tra==2){
                if(index_first_trainee==index_second_trainee-1){
                    if(index_first_trainee+2<=num_trainees){
                        for(l=index_first_trainee+2;l<=num_trainees;l++){
                            trainee[l-2]=trainee[l];
                        }
                    }
                }
                else{
                    for(l=index_first_trainee+1;l<index_second_trainee;l++){
                        trainee[l-1]=trainee[l];
                    }
                    for(l=index_second_trainee+1;l<=num_trainees;l++){
                        trainee[l-2]=trainee[l];
                    }          
                }
                scheduled[i][2]=first_trainee;
                trainee[num_trainees-1]=scheduled[i][2];
                scheduled[i][3]=second_trainee;
                trainee[num_trainees]=scheduled[i][3];
            }
        } 
        if(scheduled_exp==0){
            for(j=1;j<=num_trainees;j++){
                conflict_tra=0;
                for(k=1;k<=column[trainee[j]];k++){
                    if(not_avail[trainee[j]][k]==i){
                        conflict_tra++;
                        break;
                    }
                }
                if(conflict_tra==0){
                    scheduled_tra++;
                    if(scheduled_tra==1){
                        index_first_trainee=j;
                        first_trainee=trainee[index_first_trainee];
                    }
                    else if(scheduled_tra==2){
                        index_second_trainee=j;
                        second_trainee=trainee[index_second_trainee];
                    }
                    else if(scheduled_tra==3){
                        index_third_trainee=j;
                        third_trainee=trainee[index_third_trainee];
                        break;
                    }
                }
            }
            if(scheduled_tra==1){
                if(index_first_trainee<num_trainees){
                    for(l=index_first_trainee+1;l<=num_trainees;l++){
                        trainee[l-1]=trainee[l];
                    }
                }
                scheduled[i][1]=first_trainee;
                trainee[num_trainees]=scheduled[i][1];
            }
            if(scheduled_tra==2){
                if(index_first_trainee==index_second_trainee-1){
                    if(index_second_trainee+1<=num_trainees){
                        for(l=index_second_trainee+1;l<=num_trainees;l++){
                            trainee[l-2]=trainee[l];
                        }
                    }
                }
                else{
                    for(l=index_first_trainee+1;l<index_second_trainee;l++){
                        trainee[l-1]=trainee[l];
                    }
                    for(l=index_second_trainee+1;l<=num_trainees;l++){
                        trainee[l-2]=trainee[l];
                    }          
                }
                scheduled[i][1]=first_trainee;
                trainee[num_trainees-1]=scheduled[i][1];
                scheduled[i][2]=second_trainee;
                trainee[num_trainees]=scheduled[i][2];
            }
            if(scheduled_tra==3){
                if(index_first_trainee==index_second_trainee-1 && index_second_trainee==index_third_trainee-1){
                    if(index_third_trainee<num_trainees){
                        for(l=index_third_trainee+1;l<=num_trainees;l++){
                            trainee[l-3]=trainee[l];
                        }
                    }
                }
                else if(index_first_trainee==index_second_trainee-1 && index_second_trainee!=index_third_trainee-1){
                    for(l=index_second_trainee+1;l<index_third_trainee;l++){
                        trainee[l-2]=trainee[l];
                    }
                    if(index_third_trainee+1<num_trainees){
                        for(l=index_third_trainee+1;l<=num_trainees;l++){
                            trainee[l-3]=trainee[l];
                        }   
                    }       
                }
                else if(index_first_trainee!=index_second_trainee-1 && index_second_trainee==index_third_trainee-1){
                    for(l=index_first_trainee+1;l<index_second_trainee;l++){
                        trainee[l-1]=trainee[l];
                    }
                    if(index_third_trainee<num_trainees){
                        for(l=index_third_trainee+1;l<=num_trainees;l++){
                            trainee[l-3]=trainee[l];
                        }
                    }
                }
                else if(index_first_trainee!=index_second_trainee-1 && index_second_trainee!=index_third_trainee-1){
                    for(l=index_first_trainee+1;l<index_second_trainee;l++){
                        trainee[l-1]=trainee[l];
                    }
                    for(l=index_second_trainee+1;l<index_third_trainee;l++){
                        trainee[l-2]=trainee[l];
                    }
                    if(index_third_trainee+1<num_trainees){
                        for(index_third_trainee+1;l<num_trainees;l++){
                            trainee[l-3]=trainee[l];
                        }
                    }
                }
                scheduled[i][1]=first_trainee;
                trainee[num_trainees-2]=scheduled[i][1];
                scheduled[i][2]=second_trainee;
                trainee[num_trainees-1]=scheduled[i][2];
                scheduled[i][3]=third_trainee;
                trainee[num_trainees]=scheduled[i][3];
            }
        }
        if(scheduled_tra==0){
            if(scheduled_exp==2 && index_second_experienced!=num_experienced){
                for(j=index_second_experienced-1;j<=num_experienced-2;j++){
                    conflict_exp=0;
                    for(k=1;k<=column[experience[j]];k++){
                        if(not_avail[experience[j]][k]==i){
                            conflict_exp++;
                            break;
                        }
                    }
                    if(conflict_exp==0){
                        scheduled_exp++;
                        index_third_experienced=j;
                        third_experienced=experience[index_third_experienced];
                        break;
                    }
                }
            }
        }
        if(scheduled_exp==3){
            for(l=index_third_experienced+1;l<=num_experienced-2;l++){
                experience[l-1]=experience[l];
            }
            scheduled[i][3]=third_experienced;
            experience[num_experienced]=scheduled[i][3];
            experience[num_experienced-1]=scheduled[i][2];
            experience[num_experienced-2]=scheduled[i][1];
        } 
    }
    printf("\n----------------------------------------------------------------\n\n");
    for(i=1;i<=weeks;i++){
        printf("Week %d Servers : %s,%s,%s\n",i,name[scheduled[i][1]],name[scheduled[i][2]],name[scheduled[i][3]]);
    }
    printf("\n"); 
}
