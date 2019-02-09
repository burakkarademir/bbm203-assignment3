#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <new>
#include <climits>
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <iostream>
#include <fstream>
struct footballerinfo{
    char footballer_name[100];
    char team_name[100];
    char away_team[100];
    int  goal_min;
    int match_id;
    int goal_num;//YASAKMIŞŞŞŞŞŞŞŞ
    struct footballerinfo *down;
    struct footballerinfo *up;
    struct footballerinfo *next;
    struct footballerinfo *previous;

};

struct lines{
	char line[100];
	char word[30];
};

struct teams{
	char team[100];
};

struct footballers{
	char footballer[100];
};

struct operations{
	char operation_footballer[100];
};

bool search(struct footballerinfo* head, char *x) 
{ 
    struct footballerinfo* current = head;  // Initialize current 
    while (current != NULL) 
    { 
        if (strcmp(current->footballer_name , x)==0) 
            return true; 
        current = current->next; 
    } 
    return false; 
} 



int find_line_number(char *argv[]){
	
    FILE *fptr;
    int lineNumber=0;
	
    if((fptr=fopen(argv[1],"r"))==NULL){
        exit(1);
    }
    else{
    	char line[100];
        /*This loop count number of all lines*/
        while(fgets(line, sizeof(line), fptr)) {
        	lineNumber++;
	} 
		
        fclose(fptr);
    }
    return lineNumber;
}


int find_operation_linenum(char *argv[]){
	
    FILE *fptr;
    int lineNumber=0;
	
    if((fptr=fopen(argv[2],"r"))==NULL){
        exit(1);
    }
    else{
    	char line[100];
        /*This loop count number of all lines*/
        while(fgets(line, sizeof(line), fptr)) {
        	lineNumber++;
	} 
		
        fclose(fptr);
    }
    return lineNumber;
}


void read_file(char *argv[], struct lines *lines){
    FILE *fptr;
    char line[100];
    
	if((fptr=fopen(argv[1],"r"))==NULL){
        exit(1);
    }
    
    else{
    	char *word=(char*)malloc(90);
    	int i=0;
        /*read file line by line and get lines*/
        while(fgets(line, sizeof(line), fptr)) {
            if(strcmp(line,"\r\n")!=0||strcmp(line,"\n")!=0){
                strcpy(lines[i].line,line);
                word= strtok (line,",");
                strcpy(lines[i].word,word);
                i++;
            }
	} 
        fclose(fptr);
    }	
}


void read_operation_file(char *argv[], struct operations *operations){
    FILE *fptr;
    char line[100];
    
	if((fptr=fopen(argv[2],"r"))==NULL){
        exit(1);
    }
    
    else{
    	int i=0;
        /*read file line by line and get lines*/
        while(fgets(line, sizeof(line), fptr)) {
            if(strcmp(line,"\r\n")!=0||strcmp(line,"\n")!=0){
                strcpy(operations[i].operation_footballer,line);
                i++;
            }
	} 
        fclose(fptr);
    }	
}



int largestElement(struct footballerinfo **head,std:: ofstream& filepointer) 
{ 
    
    struct footballerinfo *current = *head;
    struct footballerinfo *current2 = *head;

    int max = INT_MIN; 
  
    while (current != NULL) { 
  
        if (max < current->goal_num) 
            max = current->goal_num; 
        current = current->next; 
    } 
    filepointer << "2)GOAL SCORER\n";
    while(current2 != NULL){
        if(current2->goal_num==max){
            filepointer << current2->footballer_name<<std::endl;
        }
        current2=current2->next;
    }
    
    return max; 
} 


void addFootballer(struct lines line,struct footballerinfo **head,struct footballerinfo **last){

    if(search(*head,line.word)){
        
        struct footballerinfo *newFootballer2= (struct footballerinfo*)malloc(sizeof(struct footballerinfo));
        sscanf(line.line, "%[^,] , %[^,] , %[^,] , %d , %d",newFootballer2->footballer_name,newFootballer2->team_name,newFootballer2->away_team,&newFootballer2->goal_min,&newFootballer2->match_id);
        struct footballerinfo *ptr2 = *head;
        while(strcmp(ptr2->footballer_name,newFootballer2->footballer_name)!=0) {
            ptr2 = ptr2->next;
        }
        ptr2->up=NULL;
        ptr2->goal_num++;
        newFootballer2->down=NULL;
        while (ptr2->down != NULL) {
            ptr2 = ptr2->down;
        }
        ptr2->down = newFootballer2; 
        newFootballer2->up=ptr2;
        return;   
            
    }
    else{
        struct footballerinfo *newFootballer= (struct footballerinfo*)malloc(sizeof(struct footballerinfo));
        struct footballerinfo *current = *head;
        newFootballer->goal_num=0;
        sscanf(line.line, "%[^,] , %[^,] , %[^,] , %d , %d",newFootballer->footballer_name,newFootballer->team_name,newFootballer->away_team,&newFootballer->goal_min,&newFootballer->match_id);
        newFootballer->down = NULL;  
        newFootballer->next = NULL; 
        newFootballer->goal_num++;
       
        if (*head == NULL) 
        { 
            newFootballer->previous = NULL; 
           *head =newFootballer ; 
           return; 
        }   
        while (current->next != NULL) 
            current = current->next;
        current->next = newFootballer; 
        newFootballer->previous=current;
        return;
    }


}

void hattrick_finder(struct footballerinfo **head,std:: ofstream& filepointer){
        struct footballerinfo *current = *head;
        struct footballerinfo *current2;
        struct footballerinfo *current3;
        filepointer << "3)THE NAMES OF FOOTBALLERS WHO SCORED HAT-TRICK\n";
        while(current != NULL){
            current3=current;
            while(current3 != NULL){
                int match=0;
                current2=current3->down;
                while(current2 != NULL){ 

                    if(strcmp(current3->away_team,current2->away_team)==0 && strcmp(current3->team_name,current2->team_name)==0 && current3->match_id==current2->match_id){

                        match++;
                      
                    }
                    current2=current2->down;
                }
                if(match==2){
                    filepointer << current3->footballer_name<<std::endl;
                    match=0;
                }
                current3=current3->down;
            }
            
            current=current->next;
    }
}

void print_teamlist(struct footballerinfo **head, struct teams *teams, int line_number,std:: ofstream& filepointer){
    
    struct footballerinfo *current = *head;
    int i=0;
    int k;
    filepointer <<"4)LIST OF TEAMS\n";
    LOOP:while(current !=NULL){
        
        for(k=0;k<i;k++){
            if(strcmp(teams[k].team,current->team_name)==0){
                    current=current->next;
                    goto LOOP;   
                
            }
        }

            strcpy(teams[i].team,current->team_name);
            current=current->next;
            i++;       
    }
    
    for(k=0;k<i;k++){
        filepointer <<teams[k].team<<std::endl;
    }
    
   
}

using namespace std;

void print_footballers(struct footballerinfo **head, struct footballers *footballers, int line_number,std:: ofstream& filepointer){
    
    struct footballerinfo *current = *head;
    int i=0;
    int k;
    std::string temp,list[100];
    filepointer <<"5)LIST OF FOOTBALLERS\n";
    LOOP:while(current !=NULL){
        
        for(k=0;k<i;k++){
            if(strcmp(footballers[k].footballer,current->footballer_name)==0){
                    current=current->next;
                    goto LOOP;   
                
            }
        }
            (list[i]=current->footballer_name);
            strcpy(footballers[i].footballer,current->footballer_name);
            current=current->next;
            i++;       
    }
    
    int element_num=i;
    for(int i = 0; i < element_num-1; ++i)
       for( int j = i+1; j <element_num; ++j)
       {
          if(list[i] > list[j])
          {
            temp = list[i];
            list[i] = list[j];
            list[j] = temp;
          }
    }
      for(k=0;k<i;k++){
       filepointer <<list[k]<<std::endl;

      }
   
}


void print_operation1(struct footballerinfo **head, struct operations *operations,std:: ofstream& filepointer){
    filepointer <<"6)MATCHES OF GIVEN FOOTBALLER\n";
    char footballer1[100];
    char footballer2[100];
    sscanf(operations->operation_footballer, "%[^,] , %[^,]",footballer1,footballer2);
    struct footballerinfo *current = *head;
    struct footballerinfo *current2 ;
    
    char *footballer2_without_newline=strtok(footballer2,"\n");
    while(current !=NULL){
        if(strcmp(current->footballer_name,footballer1)==0){
            current2=current;
            filepointer <<"Matches of ";
            filepointer <<footballer1<<std::endl;
            while(current2!=NULL){
                filepointer <<"Footballer Name: ";
                filepointer <<footballer1;
                filepointer <<",Away Team: ";
                filepointer <<current2->away_team;
                filepointer <<",Min of Goal: ";
                filepointer <<current2->goal_min;
                filepointer <<",Match ID: ";
                filepointer <<current2->match_id<<std::endl;
                current2=current2->down;
            }
        }
         current=current->next;

    }
    current = *head;
    while(current !=NULL){
        if(strcmp(current->footballer_name,footballer2_without_newline)==0){
            current2=current;
            filepointer <<"Matches of ";
            filepointer <<footballer2<<std::endl;
            while(current2!=NULL){
                filepointer <<"Footballer Name: ";
                filepointer <<footballer2;
                filepointer <<",Away Team: ";
                filepointer <<current2->away_team;
                filepointer <<",Min of Goal: ";
                filepointer <<current2->goal_min;
                filepointer <<",Match ID: ";
                filepointer <<current2->match_id<<std::endl;
                current2=current2->down;
            }            
        }
        current=current->next;

    }
        
   
}


void print_operation2(struct footballerinfo **head, struct operations *operations,int line_number,std:: ofstream& filepointer){
    struct operations3{
	char operation_footballer3[100];
        int match_id;
    };
    struct operations3 *operations3=(struct operations3 *)malloc(line_number*sizeof( struct operations3));
    filepointer <<"7)ASCENDING ORDER ACCORDING TO MATCH ID\n";
    char footballer1[100];
    char footballer2[100];
    sscanf(operations[1].operation_footballer, "%[^,] , %[^,]",footballer1,footballer2);
    struct footballerinfo *current = *head;
    struct footballerinfo *current2 ;
    int i=0;
    int k;
    char *footballer2_without_newline=strtok(footballer2,"\n");
    while(current !=NULL){
        if(strcmp(current->footballer_name,footballer1)==0){
            current2=current;
            LOOP:while(current2!=NULL){
                for(k=0;k<line_number;k++){
                    if(strcmp(operations3[k].operation_footballer3,current2->footballer_name)==0 && operations3[i].match_id==current2->match_id){
                        current2=current2->down;
                        goto LOOP;
                    }
                }
                strcpy(operations3[i].operation_footballer3,current2->footballer_name);
                operations3[i].match_id=current2->match_id;               
                filepointer <<"footballer Name: ";
                filepointer <<footballer1;
                filepointer <<",Match ID: ";
                filepointer <<current2->match_id<<std::endl;

                current2=current2->down;
            }
        }
        current=current->next;
        i++;
    }
    current = *head;
    i=0;
    while(current !=NULL){
        if(strcmp(current->footballer_name,footballer2_without_newline)==0){
            current2=current;
            LOOP2:while(current2!=NULL){
                for(k=0;k<line_number;k++){
                    if(strcmp(operations3[k].operation_footballer3,current2->footballer_name)==0 && operations3[i].match_id==current2->match_id){
                        current2=current2->down;
                        goto LOOP2;
                    }
                }
                strcpy(operations3[i].operation_footballer3,current2->footballer_name);
                operations3[i].match_id=current2->match_id;  
                filepointer <<"footballer Name: ";
                filepointer <<footballer2;
                filepointer <<",Match ID: ";
                filepointer <<current2->match_id<<std::endl;
                current2=current2->down;
            }            
        }
        current=current->next;
        i++;
    }
        
}

void print_operation3(struct footballerinfo **head, struct operations *operations,int line_number,std:: ofstream& filepointer){
    struct operations2{
	char operation_footballer2[100];
        int match_id;
    };
    struct operations2 *operations2=(struct operations2 *)malloc(line_number*sizeof( struct operations2));
    filepointer <<"8)DESCENDING ORDER ACCORDING TO MATCH ID\n";
    char footballer1[100];
    char footballer2[100];
    sscanf(operations[2].operation_footballer, "%[^,] , %[^,]",footballer1,footballer2);
    struct footballerinfo *current = *head;
    struct footballerinfo *current2 ;
    int i=0;
    int k;
    char *footballer2_without_newline=strtok(footballer2,"\n");
    while(current !=NULL){    
        if(strcmp(current->footballer_name,footballer1)==0){
            current2=current;
            while(current2->down!=NULL){
                current2=current2->down;
            }
            LOOP:while(current2!=NULL){
                for(k=0;k<line_number;k++){
                    if(strcmp(operations2[k].operation_footballer2,current2->footballer_name)==0 && operations2[i].match_id==current2->match_id){
                        current2=current2->up;
                        goto LOOP;
                    }
                }
                strcpy(operations2[i].operation_footballer2,current2->footballer_name);
                operations2[i].match_id=current2->match_id;
                filepointer <<"footballer Name: ";
                filepointer <<footballer1;
                filepointer <<",Match ID: ";
                filepointer <<current2->match_id<<std::endl;
                current2=current2->up;
            }
        }
             current=current->next;
        i++;
    }
    current = *head;
    i=0;
    while(current !=NULL){    
        if(strcmp(current->footballer_name,footballer2_without_newline)==0){
            current2=current;
            while(current2->down!=NULL){
                current2=current2->down;
            }
            LOOP2:while(current2!=NULL){
                for(k=0;k<line_number;k++){
                    if(strcmp(operations2[k].operation_footballer2,current2->footballer_name)==0 && operations2[i].match_id==current2->match_id){
                        current2=current2->up;
                        goto LOOP2;
                    }
                }
                strcpy(operations2[i].operation_footballer2,current2->footballer_name);
                operations2[i].match_id=current2->match_id;                
                filepointer <<"footballer Name: ";
                filepointer <<footballer2;
                filepointer <<",Match ID: ";
                filepointer <<current2->match_id<<std::endl;
                current2=current2->up;
            }            
        }
        current=current->next;
        i++;
    }
        
   
}

using namespace std;


int main(int argc, char *argv[]) {
    ofstream filepointer;
    filepointer.open (argv[3]);
    
    int i, j=0,line_number=find_line_number(argv);
    int operation_line_number=find_operation_linenum(argv);

    struct footballerinfo *head=NULL ,*last=NULL;

    struct lines *lines=(struct lines *)malloc(line_number*sizeof( struct lines));
    struct teams *teams=(struct teams *)malloc(line_number*sizeof( struct teams));
    struct footballers *footballers=(struct footballers *)malloc(line_number*sizeof( struct footballers));
    struct operations *operations=(struct operations *)malloc(operation_line_number*sizeof( struct operations));

    read_file(argv, lines);
    read_operation_file(argv,operations);

    for(i=0;i<line_number;i++){
        addFootballer(lines[i],&head,&last);
    }
    
    
    char footballer_name2[100];
    char team_name2[100];
    char away_team2[100];
    int  goal_min2;
    int match_id2;
    int score_first_half=0;
    int score_second_half=0;
    for(i=0;i<line_number;i++){
        sscanf(lines[i].line, "%[^,] , %[^,] , %[^,] , %d , %d",footballer_name2,team_name2,away_team2,&goal_min2,&match_id2);
        if(goal_min2<46){
            score_first_half++;
        }
        else if(goal_min2>45){
            score_second_half++;

        }
    }

    if(score_first_half>score_second_half){
        filepointer << "1)THE MOST SCORED HALF\n";
        filepointer << "0\n";
    }
    if(score_first_half<score_second_half){
        filepointer << "1)THE MOST SCORED HALF\n";
        filepointer << "1\n";
    }
    if(score_first_half==score_second_half){
        filepointer << "1)THE MOST SCORED HALF\n";
        filepointer << "1\n";
    }
    largestElement(&head,filepointer);
    hattrick_finder(&head,filepointer);
    print_teamlist(&head,teams,line_number,filepointer);
    print_footballers(&head,footballers,line_number,filepointer);
    print_operation1(&head,operations,filepointer);
    print_operation2(&head,operations,line_number,filepointer);
    print_operation3(&head,operations,line_number,filepointer);
    
}
