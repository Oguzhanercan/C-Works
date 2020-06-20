#include <stdio.h>
#include <time.h>
#define array_number 3 // zaman karmaşıklığı ölçülecek array sayısı
#define range 10000 // range değeri non_repeating_array fonksiyonunda 0 ile range değeri arasında sayı üretınminde kullanmamız gereken durumlardan dizi elemanlarını üretirken kullandığımız border değeridir.
#define on 10 //1 ile 10 arasında değer üretirken sınır olarak kullandığımız makro. Değiştirilmesi durumunda dizideki eleman sayısı aralığı değişecektir.



void non_repeating_array (int array_size, int array[array_size],int border){ // dizide tekrar etmeyen rastgele sayılar oluşturmak için fonksiyon. Rastgele dizi elemanları ve rastgelere dizi üretmek için kullanıyoruz.
	int i = 0;
	int j;
	int k;
	for(j=0;j<array_size;j++){
        array[j]=rand()%(border-1)+1;//range  değerine göre modunu almamız 0 ile range arasında bir random sayı üretmemizi sağlar. Dizi eleman sayısını kullanırken 0 istemediğimiz bir değer olduğu için 1 ekliyoruz.Modunu alırken yaptığımız çıkarma işlemi ise sınırımızı aşmaması için.
    }
    while(i<array_size){
        int r=rand()%(border-1)+1;

        for (k = 0; k < i; k++)
        {
            if(array[k]==r){
        		break;
            }
        }
        if(k==i){
            array[i++]=r;
        }
    }
}

void swap(int *a, int *b){ // yer değiştirme işlemi için yazdığımız fonksiyon.

	
	*b= *a+*b;
	*a = *b-*a;
	*b = *b-*a;	}

void shaker(int array_size,int array[array_size]){
	int flag = 0; // flag değeri ile dizinin sıralanıp sıralanmamış olduğunu kontrol edeceğiz.
	int i;
	int j;
	int first_index = 0;
	int last_index = array_size-1;//first ve last index ile dizide  kontrol edeceğimiz kontrol aralığını düzenleyeceğiz.
	
	while(flag == 0){
		flag = 1; 
		for(i = first_index;i<last_index;i++){
			if(array[i]>array[i+1]){
				swap(&array[i],&array[i+1]);// İlk indisinden başlayıp ileriye doğru bir sonraki indisteki elemanla kıyaslayarak yer değiştirme işlemi yapıyoruz.
				flag = 0;//değişim olduysa döngünün devam etmesi için flag değerini 0' eşitliyoruz.
			}
		}
		
		if(flag == 1){
			break;// eğer flag değeri forward shake kısmında değişmediyse dizimiz sıralıdır bu yüzden döngüyü kırabiliriz.
		}
		
		last_index -=1 ;//en büyük elemanı en sona yerleştirdiğimiz için son indisde işlem yapmaya ihtiyaç duymuyoruz.
		for(i = last_index;i>first_index;i--){
			if(array[i]<array[i-1]){
				swap(&array[i],&array[i-1]);// Son indisinden başlayıp geriye doğru bir önceki indisteki elemanla kıyaslayarak yer değiştirme işlemi yapıyoruz.
				flag = 0;//değişim olduysa döngünün devam etmesi için flag değerini 0' eşitliyoruz.
			}
		}
		first_index += 1;//en küçük elemanı en başa yerleştirdiğimiz için ilk indisde işlem yapmaya ihtiyaç duymuyoruz.
	}
}




int main(){
	
	
	int aee[array_number] ;//Bu dizi random bir şekilde üretilir. Dizilerdeki eleman sayılarını belirler.Zaman karmaşıklığında görsel anlaşılırlığın net olması amacıyla shaker sort ile sıralanmış bir dizidir.
	double times[array_number];// Bu dizide dizilerin ne kadar sürede sıralandığı tutulur.
	
	int i;
	int j;
	clock_t start;
	clock_t stop;
	
	srand(time(NULL));
	
	non_repeating_array(array_number,aee,on);//aee dizi tekrar etmeyecek bir şekilde üretilir.
	shaker(array_number,aee);// aee dizisi küçükten büyüğe sıralanır.
	for(i=0;i<array_number;i++){
		
		int array[(aee[i]*1000)];//aee dizisindeki elemanı 1000 ile çarpmamızın sebebi küçük miktarda dizi elemanı için zamanı ölçmeye kalktığımızda 0 değerini görüyor olmamızdır.
		
		non_repeating_array((aee[i]*1000),array,range);// tekrar etmeyen dizi oluşturulur.(Tekrar edip etmemesi önemli değil algoritma her şartta çalışır.)
		
		
		printf("\n%d. arrayin sıralanmamış hali : \n",i+1);
		for(j=0;j<(aee[i]*1000);j++){
        printf("%5d ",array[j]);//sıralanmamış array 
		}
		
		start = clock();
		shaker((aee[i]*1000),array);
		stop = clock();// fonksiyonun öncesi ve sonrasına atadığımız bu değerler ile bir alt satırda çıkarma işlemi yapıp 1000 ile çarparak milisaniye cinsinden sıralanma süresini ölçeriz.
		
		double a = ((double)(stop - start)/CLOCKS_PER_SEC)*1000;
		times[i] = a; // her bir zaman değerini ileride kullanmak için listeye depoluyoruz.
		
		printf("\n%d. arrayin sıralanmış hali : \n",i+1);
		for(j=0;j<(aee[i]*1000);j++){
        printf("%5d ",array[j]);//sıralanmış array 
		}
		
		
	}
	printf("\n\n\n");

	for(j=0;j<array_number;j++){
        printf("%d elemanli %d. arrayin siralanma suresi (ms): %lf \n",(aee[j]*1000),j+1,times[j]);// arraylarin sıralanma süreleri
		}
		
		printf("\n\n\n");
		printf("--------------Time complexity graphic--------------\n\n ");
	for(i=0;i<array_number;i++){
		printf("\n");
		printf("%d. ARRAY TIME COMPLEXİTY : ",i+1);
		for(j=0;j<times[i]/10;j++){
			printf("<>");
		}
		
	}
	return 0 ;
}
