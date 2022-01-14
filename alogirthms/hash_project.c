#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <locale.h>
#define charlimit 50

typedef struct person{
    char id[charlimit];
    char name[charlimit];
    char sname[charlimit];
    char date[charlimit];
    char city[charlimit];
}PERSON;


typedef struct cache_node{
    PERSON* person;
    struct cache_node* next;
    struct cache_node* prev;
}CACHE_NODE;



typedef struct hash_NODE{
    int flag;
    unsigned long long int index;
}HASH_NODE;



int poww(int x,int y){ // üst alma fonksiyonu
    register int i;
    register int result = 1;
    for(i = 0;i<y;i++){
        result *= x;
    }
    return result;
}

 unsigned long long int horner(char word[charlimit]){  // string değerini horner metodu ile integera çevirir
	unsigned long long int key = 0;
	int R = 31;
	int i,len = strlen(word);
	
	for(i = 0; i < len ; i++){
		key += (poww(R,(len-i-1))*word[i]);
	}
	return key;
}


void insert_table(HASH_NODE *hash_table, int m,  unsigned long long int key){ //table'a insert işlemi
	m = fun(m*10/6);
	int i = 0, hash_index = key%m;
	int hash2 = key%(m-1) +1;
	
	if(hash_table[hash_index].index == -1){
		hash_table[hash_index].index = key;
        hash_table[hash_index].flag = 0;
		printf("Insertion occured : %d. index %d\n", hash_index, hash_table[hash_index].index);
	}
	else{
		while(i<m && hash_table[hash_index].index != -1 && hash_table[hash_index].index != key){
			i++;
			hash_index = (key%m + i*hash2) % m;
		}
		if(i == m){
			printf("Table is full!\n");
            return -1;
		}
		else if(hash_table[hash_index].index == key){
			printf("Key already exists!\n");
            hash_table[hash_index].flag = 0;
		}
		else{
			hash_table[hash_index].index = key;
            hash_table[hash_index].flag = 0;
			printf("Insertion occured : %d. index %d\n", hash_index, hash_table[hash_index].flag);
		}
	}
}
int search_table(HASH_NODE*hash_table, int m,  unsigned long long int key){ // table'da değer aranır
	m = fun(m*10/6);
	int i = 0, hash_index = key%m;
	int hash2 = key%(m-1) + 1;
	
	if(hash_table[hash_index].index == -1){
		
        printf("for search: Key %d is not in table!\n",key);
        return -1;
	} 
	else{
		while(i<m && hash_table[hash_index].index != -1 && hash_table[hash_index].index != key){
			i++;
			hash_index = (key%m + i*hash2) % m;
		}
		if(i == m){
			printf("for search: Table is full and key is not in table!\n");
            return -1;
		}
		else if(hash_table[hash_index].index == key){
			printf("for search: Key is in %dth index!\n",hash_index);
            return hash_table[hash_index].flag;
            
		}
		else{
            
			printf("for search: Key %d is not in table!\n",key);

            return -1;
		}
	}
}

void search_table_inc(HASH_NODE*hash_table, int m,  unsigned long long int key,int flagset){
	m = fun(m*10/6);                                                // table'da değeri bulur ve linked listin kaçıncı elemanı olduğu olarak tutulan değeri flagset'e set eder.
	int i = 0, hash_index = key%m;
	int hash2 = key%(m-1) + 1;
	
	if(hash_table[hash_index].index == -1){
        hash_table[hash_index].flag = flagset;
        hash_table[hash_index].index = key;
        
	} 
	else{
		while(i<m && hash_table[hash_index].index != -1 && hash_table[hash_index].index != key){
			i++;
			hash_index = (key%m + i*hash2) % m;
		}
		if(i == m){
			
            
		}
		else if(hash_table[hash_index].index == -1){
			printf("for inc: Equesion is doing for initiliazition\n");
            hash_table[hash_index].flag = flagset;
            hash_table[hash_index].index = key;
            
		}
        else if(hash_table[hash_index].index == key){
            hash_table[hash_index].flag = flagset;
            
        }
	}
}

CACHE_NODE* temizle(CACHE_NODE* head){
    
    CACHE_NODE *tmp = head;  //tmp değişkeni yardımı ile head'den başlayarak liste sonuna kadar bütün elemanları free eder.
    while(head){
        tmp = head;
        head = head->next;
        free(tmp);
    }
    return NULL;
}

CACHE_NODE* sondanSil(CACHE_NODE *head,int m,HASH_NODE* hash_table){           //Linkli listenin sonuna ulaşıp sondaki elemanı
                                                    //Free ederek siler.
    CACHE_NODE *current = head;
    while(current->next){
        current = current->next;
    }
    char id[charlimit];
    strcpy(id, current->person->id);
    search_table_inc(hash_table,m,horner(id),-1);
    current->prev->next = NULL;
    free(current);
    
    return head;
}

CACHE_NODE* basaEkle(CACHE_NODE *head, CACHE_NODE *node, int *counter,HASH_NODE* hash_table,int m,PERSON* person){
    
    (*counter)++; //Başa eleman ekler ve linkli listedeki eleman sayısını tutan counter değişkenini bir artırır.
    char id[charlimit];
    strcpy(id,person->id);
    node->prev = NULL;
    node->next = head;
    head->prev = node;
    search_table_inc(hash_table,m,horner(id),0);
    return node;
}




CACHE_NODE * linkedlistalgo( int L, CACHE_NODE *head,int *counter,PERSON* data,HASH_NODE* hash_table){  //Asıl algoritmanın çalıştığı kısım.
    
    if(head == NULL){                                           //Başlangıçta veya temizledikten sonra head NULL olacağından
        head = (CACHE_NODE*)malloc(sizeof(CACHE_NODE));       //Head'i ilklendirme işi bu if bloğunun içinde yapılır.
        head->prev = NULL;
        head->next = NULL;
        head->person = data;
        (*counter)++;
        insert_table(hash_table,L,horner(data->id));
        
    }
    else{
       
        unsigned long long int key = horner(data->id);
        int flag = search_table(hash_table,L,key); //Değerin listede olup olmadığını kontrol eden fonksiyondan dönen değere göre aksiyon alır. Yoksa yaratır, varsa başta sonda veya ortada olma durumuna göre pointer işlemleri ve hashtable işlemleri yapılır
        printf("\nflag : %d\n",flag);         
		if(flag != -1){                    
            CACHE_NODE *tmp = head;
            for(int i = 0; i< flag; i++){
                tmp = tmp->next;
            }               
            if(tmp->prev != NULL && tmp->next != NULL){   
                head->prev = tmp;                                             
                tmp->prev->next = tmp->next;            //Başa alınacak eleman ortada ise ona uygun pointer işlemleri yapılır.
                tmp->next->prev = tmp->prev;
                tmp->next = head;
                tmp->prev = NULL;
                head = tmp;
                
                for(int i = 0;i<*counter; i++ ){
                
                search_table_inc(hash_table,L,horner(tmp->person->id),i) ;
				tmp = tmp->next;}
            }
            else if(tmp->next == NULL && tmp->prev == NULL){
                //Zaten başta ve tek başına ise pointerlar ile işlem yapılmaz.
            }
            else if(tmp->next == NULL){     //Eleman sonda ise duruma uygun pointer işlemleri uygulanır.
                head->prev = tmp;
                tmp->prev->next = NULL;
                tmp->next = head;
                tmp->prev = NULL;
                head = tmp;
                for(int i = 0;i<*counter; i++ ){
                
                search_table_inc(hash_table,L,horner(tmp->person->id),i) ;
				tmp = tmp->next;}
            }

        }
        else{                                                  //Elemanın listede olmadığı durumda girilen else durumunda
            CACHE_NODE *node;                                 //Yeni bir node için yer açılır, node başa eklenir ve ilklendirilir.
            node =(CACHE_NODE*)malloc(sizeof(CACHE_NODE));
            node->person = data;
            head =basaEkle(head,node,counter,hash_table,L,data);
			printf("yeni yaratma yapılıyor:  id: %s \n  ",head->person->id);
            

            head->person = data;
            CACHE_NODE *tmp = head;
            printf("counter = %d",*counter);
            for(int i = 0;i<*counter; i++ ){
                
                search_table_inc(hash_table,L,horner(tmp->person->id),i) ;
				tmp = tmp->next;}
             if(*counter > L){
                head = sondanSil(head,L,hash_table);             //Yeni eklenen eleman sonucu liste boyu verilen değeri aştı ise sondan eleman silinir.
                printf("silme islemi yapiliyor");
                (*counter)--;
            }  

        }
    }
    return head;
}

void yazdir(CACHE_NODE *head){           //Linkli listelerde kullanılar klasik yazdırma işlemi uygulanmıştır.
                                                
    CACHE_NODE *current = head;
    while(current->next){
        printf(" id: %s, name: %s , surname: %s , birthday : %s , adress : %s \n",current->person->id,current->person->name,current->person->sname,current->person->date,current->person->city);
        current = current->next;
    }
    printf(" id: %s, name: %s , surname: %s , birthday : %s , adress : %s \n",current->person->id,current->person->name,current->person->sname,current->person->date,current->person->city);
}

FILE *fileopen(char *filename, char *x) // txt dosyasını açar ve fp döndürür
{
    FILE *fp; // file pointer
    fp = fopen(filename, x);
    if (!fp)
    {
        printf("The file could not be opened, program will be closed...");
        exit(0);
    }
    return fp;
}

int read_point(char *path, CACHE_NODE* head,HASH_NODE* hash_table,int m,int *counter) // elemanları PERSON structına okur ve değerleri linkedlistalgoya passler
{
    char *token; // storage the return value of strtok
    FILE *fp;
    fp = fileopen(path, "r");
    char *buffer = (char *)malloc(charlimit * sizeof(char)); // storage the return value of fgets
    register int i = 0;
    while (fgets(buffer, charlimit, fp) != NULL)
    {   
        PERSON* node = (PERSON*)malloc(sizeof(PERSON));
        
        token = strtok(buffer, " ");
        strcpy(node->id,token);
        
        token = strtok(NULL, " ");
        strcpy(node->name,token);
        token = strtok(NULL, " ");
        strcpy(node->sname,token);
        token = strtok(NULL, " ");
        strcpy(node->date,token);
        token = strtok(NULL, " ");
        strcpy(node->city,token);
        
        head = linkedlistalgo(m,head,counter,node,hash_table);
        yazdir(head);
        printf("\n");
        
        i++;
    }
    fclose(fp);
    free(buffer);
    return i; // i equals lenght + 1
} 

int isPrime(int n) // prime mı diye check eder.
{
    int i,j=0;
    for(i=1; i<=n; i++)
    {
        if(n%i == 0)
            j++;
    }
    if(j == 2)
        return 1;
    else if(j > 2)
        return 0;
}

int fun(unsigned int n) // N'den büyük prime değeri bulur
{
    int i=n+1;
    while(1)
    {
        if(isPrime(i))
            break;
        i++;
    }
    return i;
}




int main(){
    setlocale(LC_ALL, "Turkish");
    int i, m;
    printf("Programa hosgeldiniz, program aynı dizinde bulunan sample.txt dosyasından verileri okur,\n cache birazdan gireceğiniz değer kadar elemanı depolar\n cache olup olmadığını varsa kaçıncı sırada olduğu bilgilerini hash table da tutar...");
    printf("Please enter the size of cache: ");
    scanf("%d",&m);
    int h_s = fun(m*10/6); // cache_Size * loadfactor
    HASH_NODE* hash_table = (HASH_NODE*)malloc(h_s*sizeof(HASH_NODE));
	CACHE_NODE* head = NULL;
	for(i = 0 ; i<h_s ; i++){
		hash_table[i].index = -1; // hash table'da bir şey konmuş mu ilklendirmesi konmamış şeklinde yapıldı
	} 
    char path[charlimit] = "sample.txt"; // path
	int counter = 0; // cache de kaç eleman var ?
    

    read_point(path,head,hash_table,m,&counter); // okuma başlandı ve bu fnknin içinde linkedlist algo çağrıldı
    temizle(head); // cache'i freeledik
    return 0;   
}

