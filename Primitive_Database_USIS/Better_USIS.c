// lecturers file: lecturer_id,name,surname,title
// lectures file : lecture_id,name,credit,quota,lecturer_id
// students file : student_id,name,surname,lecture_count,credit_count
// lecture_register : register_id,student_id,lecture_id,status,date

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#define charlimit 5000
#define maxcredit 25
#define maxlecture 10
#define buffersize 128
#define CLS system("cls")
typedef struct lecture{
	char id[charlimit];
	char name[charlimit];
	char credit[charlimit];
	char quota[charlimit];
	char lecturer_id[charlimit];
	
}LECTURE;

typedef struct { 
	char id[charlimit];
	char name[charlimit];   
	char surname[charlimit];
	char lecture_count[charlimit];
	char credit_count[charlimit];
}STUDENT;


typedef struct { 
	char id[charlimit];
	char name[charlimit];
	char surname[charlimit];
	char title[charlimit];
	
}LECTURER;
	
typedef struct lecture_register{ 
	char id[charlimit];
	char student_id[charlimit];
	char lecture_id[charlimit];
	char status[charlimit];
	char date[charlimit];
	
}REGISTER;

FILE* fileopen(char*,char*);
int id_generator(char*);
void add_student(STUDENT*,char*,char*);
void add_lecturer(LECTURER*,char*,char*);
void add_lecture(LECTURE*,char*,char*);
void del_lecturer(char*,char*);
void del_lecture(char*,char*);
void del_student(char*,char*);
void update_lecturer(char* ,char*);
void update_student(char*,char*);
void update_lecture(char*,char*);
int count_quota(char*,char*);
void lecture_register(char* ,char* ,char* , char* , char*,char*);
void add_register(char*,char*,char*,char*);
char* get_time();
void display_by_lecture(char*,char*,char*);
void display_by_student(char*,char*,char*);
void display_by_lecturer(char*,char*,char*);
void create_list(char*,char*,char*,char*,char*);
void press();
int main(){
	int c = 0;
																				
	char fstudent[charlimit] = "students.txt" ;
	char flecturer[charlimit] = "lecturers.txt" ;
	char flecture[charlimit] = "lectures.txt" ;								
	char fregister[charlimit] = "register.txt" ;															
	char fcounter[charlimit] = "counter.txt" ;
	char fcounter_register[charlimit] = "counter_register.txt" ;
	STUDENT* student;								
	LECTURER* lecturer;
	LECTURE* lecture;
	char* iddel;
	char* input = (char*)malloc(50*sizeof(char));	
	char* input2 = (char*)malloc(50*sizeof(char));
	
	printf("Welcome to Better USIS.\nPress any key to continue ...");
	getch();
	int exit_status = 1;
	while(exit_status){
		system("cls");
		printf("Enter the operation:\n "
		"0-)  Exit  \n"
		"1-)  Add Student \n"
		"2-)  Del Student \n"
		"3-)  Update Student \n"
		"4-)  Add Lecture \n"
		"5-)  Del Lecture \n"
		"6-)  Update Lecture \n"
		"7-)  Add Lecturer \n"
		"8-)  Del Lecturer \n"
		"9-)  Update Lecturer \n"
		"10-) Register to Lecture \n"
		"11-) Display students who takes lecture \n"
		"12-) Display lectures by lecturer that lecturer giving  \n"
		"13-) Display lectures by student that student taking  \n"
		"14-) Create file that includes all students taling lecture  \n"
		);
		printf("Operation :");
		scanf("%d",&exit_status);
        switch (exit_status) {
			CLS;
			
            case 0: 
                printf("Good by...");
                press();
                break;
            case 1:
                add_student(student,fcounter,fstudent);
                press();
                break;
			case 2:
				printf("Enter the id of student to delete : ");	
				scanf("%s",input);										
				del_student(fstudent,input);
                press();	
                
                break;
            case 3:
                printf("Enter the id of student to update : ");	
				scanf("%s",input);		
				update_student(fstudent,input);
				press();
                break;
            case 4:
                add_lecture(lecture,fcounter,flecture);
                press();
                break;
			case 5:
				printf("Enter the id of lecture to delete : ");	
				scanf("%s",input);	
                del_lecture(flecture,input);
                press();
                break;
            case 6:
            	printf("Enter the id of lecture to update : ");	
				scanf("%s",input);	
                update_lecture(flecture,input);
                press();
                break;
            case 7:
                add_lecturer(lecturer,fcounter,flecturer);
                press();
                break;
			case 8:
				printf("Enter the id of lecturer to delete : ");	
				scanf("%s",input);
                del_lecturer(flecturer,input);
                press();
                break;
            case 9:
                printf("Enter the id of lecturer to update : ");	
				scanf("%s",input);		
				update_lecturer(flecturer,input);
				press();
                break;
            case 10:
            	printf("Enter the student id to register a lecture: ");
				scanf("%s",input);
                printf("Enter the lecture id that student wants to register: ");
				scanf("%s",input2); 
				lecture_register(fregister,fstudent,flecture,input2,input,fcounter_register);
				press();
                break;
			case 11:
                printf("Enter the id of lecture to display students who are taking the lecture: ");
				scanf("%s",input);
				display_by_lecture(fregister,fstudent,input); 
                press();
                break;
            case 12:
                printf("Enter the id of lecturer to display lectures that lecturer is giving: ");
				scanf("%s",input);
				display_by_lecturer(flecture,flecturer,input);
				press();
                break;
            case 13:
                printf("Enter the id of student to display lectures that student is taking: ");
				scanf("%s",input);
				display_by_student(fregister,flecture,input);
				press();
                break;
			case 14:
                printf("Enter the id of lecturer to display lectures that lecturer is giving: ");
				scanf("%s",input);
				create_list(flecture,flecturer,fregister,fstudent,input);
                press();
                break;
            default:
                printf("Good By");
                exit_status = 0;
                press();
                break;
        } 

	}
	free(input);
	free(input2);
	return 0; 										
}			
	
FILE* fileopen(char* filename,char* x ){
	FILE* fp;
	fp = fopen(filename,x);
	if(!fp){
		printf("The file could not be opened, program will be closed...");
		exit(0);
	}
	return fp;
}


void add_student(STUDENT* student,char* fcounter,char* fstudent){
	FILE* fp;
	fp = fileopen(fstudent,"a+");
	student = (STUDENT*)malloc(sizeof(STUDENT));
	printf("Enter the necessary informations belong to stundent in the following format: Name Surname");
	scanf("%s %s",student->name,student->surname);	
	strncpy(student->lecture_count, "0",sizeof(student->lecture_count));
	strncpy(student->credit_count, "0",sizeof(student->credit_count));
	itoa(id_generator(fcounter),student->id,10);
	fprintf(fp,"%s,%s,%s,%s,%s\n",student->id,student->name,student->surname,student->lecture_count,student->credit_count);	
	printf("Student added. id: %s name: %s surname: %s lecture_count: %s credit_count: %s ",student->id,student->name,student->surname,student->lecture_count,student->credit_count);
	fclose(fp);	
	free(student);
	}
																				


void del_student(char* fstudent,char* iddel){
	register int i = 0;
	register int flag;
	FILE* fp;
	int len = 0;
	fp = fileopen(fstudent,"r");
	char* buffer = (char*)malloc(charlimit*2*sizeof(char));
	while(fgets(buffer,sizeof(buffer)*200,fp) != NULL){
		len++;
	}rewind(fp);
	STUDENT* studentfile = (STUDENT*)malloc(len*10*sizeof(STUDENT));
	while(fgets(buffer,2000,fp) != NULL){	
   	sscanf(buffer,"%[^,],%[^,],%[^,],%[^,],%[^,\n]",studentfile[i].id,studentfile[i].name,studentfile[i].surname,studentfile[i].credit_count,studentfile[i].lecture_count);
	i++;
}	
	fclose(fp);
	fp = fileopen(fstudent,"w");
	register int j;
		
	for(j = 0;j<len;j++){
		
		if(strcmp(iddel,studentfile[j].id) != 0){
		fprintf(fp,"%s,%s,%s,%s,%s\n",studentfile[j].id,studentfile[j].name,studentfile[j].surname,studentfile[j].credit_count,studentfile[j].lecture_count);	
		}
	}
	printf("Student deleted.");
	free(studentfile);
	free(buffer);
	fclose(fp);
	
}

void add_lecturer(LECTURER* lecturer,char* fcounter,char* flecturer){
	FILE* fp;
	fp = fileopen(flecturer,"a+");
	lecturer = (LECTURER*)malloc(sizeof(LECTURER));
	printf("Enter the necessary informations belong to lecturer in the following format Name Surname Title :");
	scanf("%s %s %s",lecturer->name,lecturer->surname,lecturer->title);	

	itoa(id_generator(fcounter),lecturer->id,10);
	fprintf(fp,"%s,%s,%s,%s\n",lecturer->id,lecturer->name,lecturer->surname,lecturer->title);	
	printf("id: %s name: %s surname: %s title: %s",lecturer->id,lecturer->name,lecturer->surname,lecturer->title);
	fclose(fp);	
	free(lecturer);
	}
	
void del_lecturer(char* flecturer,char* iddel){
	register int i = 0;
	int flag;
	FILE* fp;
	fp = fileopen(flecturer,"r");
	int len = 0;
	char* buffer = (char*)malloc(200*sizeof(char));
	while(fgets(buffer,sizeof(buffer)*200,fp) != NULL){	
	len++;
}	rewind(fp);
	LECTURER* lecturerfile = (LECTURER*)malloc(len*10*sizeof(STUDENT));
	while(fgets(buffer,sizeof(buffer)*200,fp) != NULL){	
   	sscanf(buffer,"%[^,],%[^,],%[^,],%[^, \n]",lecturerfile[i].id,lecturerfile[i].name,lecturerfile[i].surname,lecturerfile[i].title);
	i++;
}							
	fclose(fp);
	fp = fileopen(flecturer,"w");
	register int j;
		
	for(j = 0;j<len;j++){		
		if(strcmp(iddel,lecturerfile[j].id) != 0){
		fprintf(fp,"%s,%s,%s,%s\n",lecturerfile[j].id,lecturerfile[j].name,lecturerfile[j].surname,lecturerfile[j].title);			
	}
	}
	free(lecturerfile);
	printf("Lecturer deleted.");
	fclose(fp);	
	free(buffer);
}	

void add_lecture(LECTURE* lecture,char* fcounter,char* flecture){
	FILE* fp;
	fp = fileopen(flecture,"a+");
	lecture = (LECTURE*)malloc(sizeof(LECTURE));
	printf("Enter the necessary informations belong to lecture in the following format Name credit quota lecturer_id : ");
	scanf("%s %s %s %s",lecture->name,lecture->credit,lecture->quota,lecture->lecturer_id);	

	itoa(id_generator(fcounter),lecture->id,10);
	fprintf(fp,"%s,%s,%s,%s,%s\n",lecture->id,lecture->name,lecture->credit,lecture->quota,lecture->lecturer_id);	
	printf("Lecture added. id: %s name: %s credit: %s quota: %s lecture_id: %s",lecture->id,lecture->name,lecture->credit,lecture->quota,lecture->lecturer_id);
	fclose(fp);	
	free(lecture);
	}
	
void del_lecture(char* flecture,char* iddel){
	register int i = 0;
	register int flag;
	register int len = 0;

	FILE* fp;
	fp = fileopen(flecture,"r");
	char* buffer = (char*)malloc(buffersize*sizeof(char));
	while(fgets(buffer,sizeof(buffer)*200,fp) != NULL){	
	len++;
}	rewind(fp);
	LECTURE* lecturefile = (LECTURE*)malloc(len*2*sizeof(LECTURE));
	while(fgets(buffer,sizeof(buffer)*200,fp) != NULL){	
   	sscanf(buffer,"%[^,],%[^,],%[^,],%[^,],%[^, \n]",lecturefile[i].id,lecturefile[i].name,lecturefile[i].credit,lecturefile[i].quota,lecturefile[i].lecturer_id);
	i++;
}							
	fclose(fp);
	fp = fileopen(flecture,"w+");
	register int j;
		
	for(j = 0;j<i;j++){
		
		if(strcmp(iddel,lecturefile[j].id) != 0){
		fprintf(fp,"%s,%s,%s,%s,%s\n",lecturefile[j].id,lecturefile[j].name,lecturefile[j].credit,lecturefile[j].quota,lecturefile[j].lecturer_id);		
	}
	}
	printf("Lecture deleted.");	
	free(lecturefile);
	free(buffer);
	fclose(fp);
}

void update_student(char* fstudent,char* iddel){
	FILE* fp;
	fp = fileopen(fstudent,"r");
	register int len = 0;
	register int j ;
	register int i = 0;
	char* buffer = (char*)malloc(sizeof(char)*charlimit*50);
	while(fgets(buffer,sizeof(buffer)*20,fp) != NULL){	
	len++;
}	rewind(fp);
	STUDENT* studentfile = (STUDENT*)malloc(1+len*10*sizeof(STUDENT));
	while(fgets(buffer,sizeof(buffer)*50,fp) != NULL){
	sscanf(buffer,"%[^,],%[^,],%[^,],%[^,],%[^, \n]",studentfile[i].id,studentfile[i].name,studentfile[i].surname,studentfile[i].credit_count,studentfile[i].lecture_count);
	i++;	
}
	fclose(fp);
	fp = fileopen(fstudent,"w");
	for(j= 0;j<len;j++){
		if(strcmp(iddel,studentfile[j].id) == 0){
			printf("enter the new name of student: ");
			scanf("%s",studentfile[j].name);	
			printf("enter the new surname of student: ");
			scanf("%s",studentfile[j].surname);
			fprintf(fp,"%s,%s,%s,%s,%s\n",studentfile[j].id,studentfile[j].name,studentfile[j].surname,studentfile[j].credit_count,studentfile[j].lecture_count);	
		}
		else{
			fprintf(fp,"%s,%s,%s,%s,%s\n",studentfile[j].id,studentfile[j].name,studentfile[j].surname,studentfile[j].credit_count,studentfile[j].lecture_count);
		}
	
	}
	printf("Student updated.");
	free(studentfile);
	free(buffer);
	fclose(fp);
}

void update_lecturer(char* flecturer,char* iddel){
	FILE* fp;
	fp = fileopen(flecturer,"r");
	register int len = 0;
	register int j ;
	register int i = 0;
	char* buffer = (char*)malloc(sizeof(char)*charlimit*50);
	while(fgets(buffer,sizeof(buffer)*20,fp) != NULL){	
	len++;
}	rewind(fp);
	LECTURER* lecturerfile = (LECTURER*)malloc(1+len*10*sizeof(LECTURER));
	while(fgets(buffer,sizeof(buffer)*50,fp) != NULL){
	sscanf(buffer,"%[^,],%[^,],%[^,],%[^, \n]",lecturerfile[i].id,lecturerfile[i].name,lecturerfile[i].surname,lecturerfile[i].title);
	i++;	
}
	fclose(fp);
	fp = fileopen(flecturer,"w");
	for(j= 0;j<len;j++){
		if(strcmp(iddel,lecturerfile[j].id) == 0){
			printf("enter the new name of lecturer: ");
			scanf("%s",lecturerfile[j].name);	
			printf("enter the new surname of lecturer: ");
			scanf("%s",lecturerfile[j].surname);
			printf("enter the new title of lecturer: ");
			scanf("%s",lecturerfile[j].title);
			fprintf(fp,"%s,%s,%s,%s\n",lecturerfile[j].id,lecturerfile[j].name,lecturerfile[j].surname,lecturerfile[j].title);	
			}
		else{
			fprintf(fp,"%s,%s,%s,%s\n",lecturerfile[j].id,lecturerfile[j].name,lecturerfile[j].surname,lecturerfile[j].title);	
		}
	}
	printf("lecturer updated.");
	free(lecturerfile);
	free(buffer);
	fclose(fp);
}

void update_lecture(char* flecture,char* iddel){
	FILE* fp;
	fp = fileopen(flecture,"r");
	register int len = 0;
	register int j ;
	register int i = 0;
	char* buffer = (char*)malloc(sizeof(char)*charlimit*50);
	while(fgets(buffer,sizeof(buffer)*20,fp) != NULL){	
	len++;
}	rewind(fp);


	LECTURE* lecturefile = (LECTURE*)malloc(1+len*10*sizeof(LECTURE));
	while(fgets(buffer,sizeof(buffer)*50,fp) != NULL){
	sscanf(buffer,"%[^,],%[^,],%[^,],%[^,],%[^, \n]",lecturefile[i].id,lecturefile[i].name,lecturefile[i].credit,lecturefile[i].quota,lecturefile[i].lecturer_id);
	i++;	
}
	fclose(fp);
	fp = fileopen(flecture,"w");
	for(j= 0;j<len;j++){
		if(strcmp(iddel,lecturefile[j].id) == 0){
			printf("enter the new name of lecture: ");
			scanf("%s",lecturefile[j].name);
			fprintf(fp,"%s,%s,%s,%s,%s\n",lecturefile[j].id,lecturefile[j].name,lecturefile[j].credit,lecturefile[j].quota,lecturefile[j].lecturer_id);
		}
		else{
			fprintf(fp,"%s,%s,%s,%s,%s\n",lecturefile[j].id,lecturefile[j].name,lecturefile[j].credit,lecturefile[j].quota,lecturefile[j].lecturer_id);
		}
	}
	printf("Lecture updated.");
	free(lecturefile);
	free(buffer);
	fclose(fp);
}

void lecture_register(char* fregister,char* fstudent,char* flecture, char* lecture_id, char*student_id,char* fcounter_register){
	FILE* fp_lecture;
	FILE* fp;
	fp_lecture = fileopen(flecture,"r");
	int len_lecture = 0;
	int len_student = 0;
	register int j ;
	register int i = 0;
	char* buffer = (char*)malloc(sizeof(char)*charlimit*50);
	while(fgets(buffer,sizeof(buffer)*20,fp_lecture) != NULL){	
	len_lecture++;
}	rewind(fp_lecture);
	
	LECTURE* lecturefile = (LECTURE*)malloc(1+len_lecture*10*sizeof(LECTURE));
	while(fgets(buffer,sizeof(buffer)*50,fp_lecture) != NULL){
	sscanf(buffer,"%[^,],%[^,],%[^,],%[^,],%[^, \n]",lecturefile[i].id,lecturefile[i].name,lecturefile[i].credit,lecturefile[i].quota,lecturefile[i].lecturer_id);
	i++;	
}	
	int flag = 0;
	int idx;
	int counter = count_quota(lecture_id,fregister);
	for(j= 0;j<len_lecture;j++){
		if(strcmp(lecture_id,lecturefile[j].id) == 0){
			if(counter<atoi(lecturefile[j].quota)){
			
				flag = 1;
				idx = j;}
			else{
				printf("The lecture quota is full");
				return;
			}
	}
		else if(j == len_lecture-1 && flag == 0){
			printf("Lecture does not exist");
			return;
		}
	}	
	fclose(fp_lecture);
	fp_lecture = fileopen(flecture,"w");
	if(flag){
		len_student = 0;
		fp = fileopen(fstudent,"r");
		while(fgets(buffer,sizeof(buffer)*20,fp) != NULL){	
			len_student++;
		}	rewind(fp);
		STUDENT* studentfile = (STUDENT*)malloc(1+len_student*10*sizeof(STUDENT));
		i = 0;
		while(fgets(buffer,sizeof(buffer)*50,fp) != NULL){
		sscanf(buffer,"%[^,],%[^,],%[^,],%[^,],%[^, \n]",studentfile[i].id,studentfile[i].name,studentfile[i].surname,studentfile[i].credit_count,studentfile[i].lecture_count);
		i++;	
		}
		fclose(fp);
		fp = fileopen(fstudent,"w");
		int idx2 ;
		for(j= 0;j<len_student;j++){
			if(strcmp(student_id,studentfile[j].id) == 0){		
				idx2 = j;	
				flag = 0;
				}}
			if(flag ==0){				
				if(atoi(studentfile[j].credit_count)+atoi(lecturefile[idx].credit)<= maxcredit && atoi(studentfile[j].lecture_count)+1<= maxlecture ){
					itoa(atoi(lecturefile[idx].quota)+1,lecturefile[idx].quota,10);
					for(j= 0;j<len_lecture;j++){
						fprintf(fp_lecture,"%s,%s,%s,%s,%s\n",lecturefile[j].id,lecturefile[j].name,lecturefile[j].credit,lecturefile[j].quota,lecturefile[j].lecturer_id);
					}	
					char a[60];
					itoa(atoi(studentfile[idx2].credit_count)+atoi(lecturefile[idx].credit),studentfile[idx2].credit_count,10);
					itoa(atoi(studentfile[idx2].lecture_count)+1,studentfile[idx2].credit_count,10);
					for(j= 0;j<len_student;j++){
						fprintf(fp,"%s,%s,%s,%s,%s\n",studentfile[j].id,studentfile[j].name,studentfile[j].surname,studentfile[j].credit_count,studentfile[j].lecture_count);
					}
					
					add_register(fregister,fcounter_register,lecturefile[idx].id,studentfile[idx2].id );
					printf("Student registered.");				
				}}
				else{
				printf("Student does not exist");
				}			
	fclose(fp);
	fclose(fp_lecture);
	free(buffer);
	free(studentfile);
	free(lecturefile);
}
} 

int id_generator(char* file){
	FILE* fp;
	int b;
	char *a = (char*)malloc(charlimit*sizeof(char));
	fp = fileopen(file,"r+");
	fscanf(fp,"%[^\n]", a);
	fclose(fp);
	fp = fopen(file,"w");
	b = atoi(a);
	b++;
	fprintf(fp,"%d",b); 
	fclose(fp);
	free(a);
	return b;
}

int count_quota(char* lecture_id,char* fregister){
	FILE* fp;
	register int counter = 0;
	register int len;
	register int j;
	register int i;
	fp = fileopen(fregister,"r");
	char* buffer = (char*)malloc(sizeof(char)*charlimit*50);
	while(fgets(buffer,sizeof(buffer)*20,fp) != NULL){	
	len++;
}	rewind(fp);

	REGISTER* registerfile = (REGISTER*)malloc(1+len*10*sizeof(REGISTER));
	while(fgets(buffer,sizeof(buffer)*50,fp) != NULL){
	sscanf(buffer,"%[^,],%[^,],%[^,],%[^, \n]",registerfile[i].id,registerfile[i].student_id,registerfile[i].lecture_id,registerfile[i].date);
	i++;	
}	
	
	for(j= 0;j<len;j++){
		if(strcmp(lecture_id,registerfile[j].lecture_id) == 0){
			counter++;
	}}
	
	fclose(fp);
	return counter;
}

void add_register(char* fregister,char* fcounter_register,char* lecture_id,char* student_id ){

	FILE* fp;
	fp = fileopen(fregister,"a+");
	REGISTER* registerr = (REGISTER*)malloc(sizeof(REGISTER));
	char* t = (char*)malloc(charlimit*sizeof(char));
	t = get_time();
	strcpy(registerr->date,t);
	strcpy(registerr->status,"1");
	strcpy(registerr->lecture_id,lecture_id);
	strcpy(registerr->student_id,student_id);
	itoa(id_generator(fcounter_register),registerr->id,10);
	fprintf(fp,"%s,%s,%s,%s,%.24s\n",registerr->id,registerr->student_id,registerr->lecture_id,registerr->status,registerr->date);	
	fclose(fp);	
	free(registerr);
	free(t);
	}


	
char* get_time(){
	char* t = (char *)malloc(charlimit*sizeof(char));
	if(t!=NULL){
		time_t date;
		time(&date);
		sprintf(t,"%s",ctime(&date));
	}
	return t;
}


void display_by_lecture(char* fregister,char* fstudent,char* lecture_id){
	FILE* fp;
	FILE* fp_student;
	fp = fileopen(fregister,"r");
	fp_student= fileopen(fstudent,"r");
	register int counter =0;
	register int flag = 0;
	REGISTER* registerr = (REGISTER*)malloc(sizeof(REGISTER));
	STUDENT* student = (STUDENT*)malloc(sizeof(STUDENT));
	char* buffer = (char*)malloc(sizeof(char)*charlimit*50);
	while(fgets(buffer,sizeof(buffer)*20,fp) != NULL){	
		sscanf(buffer,"%[^,],%[^,],%[^,],%[^, \n]",registerr->id,registerr->student_id,registerr->lecture_id,registerr->status);
		if(atoi(registerr->lecture_id) == atoi(lecture_id) && atoi(registerr->status) == 1){
			flag = 0;
			rewind(fp_student);
			while(fgets(buffer,sizeof(buffer)*20,fp_student) != NULL && flag == 0){
				sscanf(buffer,"%[^,],%[^,],%[^, \n]",student->id,student->name,student->surname);
				if(atoi(registerr->student_id) == atoi(student->id )){
					printf("%d. %s %s\n",++counter,student->name,student->surname);
					flag = 1;
				}
			}
		}}
	if(counter == 0){
		printf("There is no student that takes the given lecture.");
	}
	fclose(fp);
	free(registerr);
	free(student);
	free(buffer);
}
void display_by_student(char* fregister,char* flecture,char* student_id){
	FILE* fp;
	FILE* fp_lecture;
	fp = fileopen(fregister,"r");
	fp_lecture = fileopen(flecture,"r");
	register int counter =0;
	register int flag = 0;
	REGISTER* registerr = (REGISTER*)malloc(sizeof(REGISTER));
	LECTURE* lecture = (LECTURE*)malloc(sizeof(LECTURE));
	char* buffer = (char*)malloc(sizeof(char)*charlimit*50);
	while(fgets(buffer,sizeof(buffer)*20,fp) != NULL){	
		sscanf(buffer,"%[^,],%[^,],%[^,],%[^, \n]",registerr->id,registerr->student_id,registerr->lecture_id,registerr->status);
		if(atoi(registerr->student_id) == atoi(student_id) && atoi(registerr->status) == 1){
			flag = 0;
			rewind(fp_lecture);
			while(fgets(buffer,sizeof(buffer)*20,fp_lecture) != NULL && flag == 0){
				sscanf(buffer,"%[^,],%[^, \n]",lecture->id,lecture->name);
				if(atoi(registerr->lecture_id) == atoi(lecture->id )){
					printf("%d. %s\n",++counter,lecture->name);
					flag = 1;
				}
			}
		}}
	if(counter == 0){
		printf("There is no lecture that student takes.");
	}
	fclose(fp);
	free(registerr);
	free(lecture);
	free(buffer);}
	
void display_by_lecturer(char* flecture,char* flecturer,char* lecturer_id){
	FILE* fp;
	fp = fileopen(flecture,"r");
	register int counter =0;
	register int flag = 0;
	LECTURE* lecture = (LECTURE*)malloc(sizeof(LECTURE));
	char* buffer = (char*)malloc(sizeof(char)*charlimit*50);
	while(fgets(buffer,sizeof(buffer)*20,fp) != NULL){	
		sscanf(buffer,"%[^,],%[^,],%[^,],%[^,],%[^, \n]",lecture->id,lecture->name,lecture->credit,lecture->quota,lecture->lecturer_id);
		if(atoi(lecture->lecturer_id) == atoi(lecturer_id)){
			printf("%d. %s id: %s\n",++counter,lecture->name,lecture->id);
			}
		}
	if(counter == 0){
		printf("There is no lecture that lecturer gives.");
	}
	fclose(fp);
	free(lecture);
	free(buffer);}

void create_list(char* flecture,char* flecturer,char* fregister,char* fstudent,char* lecturer_id){ 
	display_by_lecturer(flecture,flecturer,lecturer_id);
	FILE* fp_student;
	FILE* fp_register;
	FILE* fp_new_file;
	fp_student = fileopen(fstudent,"r");
	fp_register = fileopen(fregister,"r");
	int input ;
	int flag ;
	int counter = 0;
	printf("Enter the id of lecture to create text file that includes students who are taking the lecture :");
	scanf("%d",&input);
	char* input_s = (char*)malloc(sizeof(char)*charlimit);
	itoa(input,input_s,10);
	char* list = (char*)malloc(sizeof(char)*charlimit);
	strcpy(list,"_list.txt");
	strcat(input_s,list);
	fp_new_file = fileopen(input_s,"w");
	fclose(fp_new_file);
	fp_new_file = fileopen(input_s,"a");
	char* buffer = (char*)malloc(sizeof(char)*charlimit*50);
	REGISTER* registerr = (REGISTER*)malloc(sizeof(REGISTER));
	STUDENT* student = (STUDENT*)malloc(sizeof(STUDENT));
	while(fgets(buffer,sizeof(buffer)*20,fp_register) != NULL){	
		sscanf(buffer,"%[^,],%[^,],%[^,],%[^, \n]",registerr->id,registerr->student_id,registerr->lecture_id,registerr->status);
		if( atoi(registerr->lecture_id) == input && atoi(registerr->status) == 1){
			flag = 0;
			rewind(fp_student);
			while(fgets(buffer,sizeof(buffer)*20,fp_student) != NULL && flag == 0){
				sscanf(buffer,"%[^,],%[^,],%[^, \n]",student->id,student->name,student->surname);
				if(atoi(registerr->student_id) == atoi(student->id )){
					fprintf(fp_new_file,"%d,%s,%s\n",++counter,student->name,student->surname);
					flag = 1;
				}
			}
		
		}
}}
void press(){
	printf("Press any key to continue");
	getch();
}
