#include <graphics.h>
#include<iostream>
#include <Windows.h>
#include "declaredll.h"
#include "MasterRD.h"
#include "TagReader.h"
#include<math.h>
#include<time.h>
#include<iostream>
#include<Windows.h>
#include<conio.h>
#include<stdio.h>
int node=1;
int counterstack=0;
int becareful=0;
#include <iostream>
#define secw 60
#define sech 60
#define traw 4.5
#define trah 4.5
#define objectlength 55
#define objectwidth 49
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
using namespace std;
int scale=2;
int a=0;
int p=1;
int start=1;
struct listnode {
int M;
int N;
int X;
int Y;
float PX;
float PY;
struct listnode *nextptr;
};
struct listnodecenter {
float centerx;
float centery;
struct listnodecenter *nextptr;
};
struct listnodecenterminmax {
float minmaxcenterx;
float minmaxcentery;
struct listnodecenterminmax *nextptr;
};

struct listnodecenteravg {
float avgcenterx;
float avgcentery;
struct listnodecenteravg *nextptr;
};

typedef struct listnodecenter centi;
typedef struct listnodecenter *centiptr;
typedef struct listnodecenterminmax centiminmax;
typedef struct listnodecenterminmax *centiptrminmax;
typedef struct listnodecenteravg centiavg;
typedef struct listnodecenteravg *centiptravg;
typedef struct listnode listnode;
typedef struct listnode *listnodeptr;
void delay(float);
int isempty2(centiptr sptr);
float sd(centiptr *sptr,int n);
int isempty3(centiptrminmax sptr);
int isempty4(centiptravg sptr);
void printlist3(centiptrminmax currentptr);
void printlist4(centiptravg currentptr);
float get3(centiptrminmax *sptr,int,char,char);
float get4(centiptravg*sptr,int,char,char);
void middle_conventer_minmax(centiptrminmax *minmax,listnodeptr *sptr);
void middle_conventer_avg(centiptravg *avg,listnodeptr *sptr);
void remov(listnodeptr *sptr,int,int,int,int,float,float);
int middle_conventer(centiptr *cent,listnodeptr *sptr);
float calculatepx(int,int,int,int);
void put3(centiptrminmax *sptr,float,float);
void put4(centiptravg *sptr,float,float);
float calculatepy(int,int,int,int);
// float findcenterx(listnodeptr *sptr,int start,int finish);
// float findcentery(listnodeptr *sptr,int start,int finish);
float get(listnodeptr *sptr,int,char);
float get2(centiptr *sptr,int,char,char);
int isempty(listnodeptr sptr);
void printlist(listnodeptr currentptr);
void printlist2(centiptr currentptr);
void put2(centiptr *sptr,float,float);
void put(listnodeptr *sptr,int,int,int,int,float ,float ); // IT IS GOING TO INCLUDE DATAS(M,N,X,Y) ---->
using namespace std;

int main() {
	int	counterprint=0;
	float stop;
	float period;
	float numb;
    initwindow(800,600);
	listnodeptr startptr=NULL;
	centiptr center=NULL;
	centiptrminmax centerminmax=NULL;
	centiptravg centeravg=NULL;
	unsigned int choice;
	int item;
	char M='M',N='N',X='X',Y='Y';
	int temp;
	int m,n,x,y;
	float px,py;
	int checker1;
	int checker2;
	int checker3;
	int checker4;
    int baudRate=9600;
	int port1, port2, port3, port4;
	int prefer;
	char letter;

	printf("which one do you prefer:?  (1:contious  2:discreted)");
	scanf("%d",&prefer);
	if(prefer==1)
    {
	printf("How long does it read(second):");
	scanf("%f",&period);
	printf("enter number of read per second:");
	scanf("%f",&stop);
	numb=stop*period;
	stop=(float)1/stop;
    }
	int counter=1;

    std::cout << "Enter the Port 1: ";
    std::cin >> port1;
	// پارامتر 2 شماره پورت را مشخص میکند
	// پارامتر سوم شماره دستگاه را مشخص میکند
    TagReader reader1(baudRate, port1, 1);
    reader1.initialComPort();

    std::cout << "Enter the Port 2: ";
    std::cin >> port2;
    TagReader reader2(baudRate, port2, 2);
    reader2.initialComPort();

    std::cout << "Enter the Port 3: ";
    std::cin >> port3;
    TagReader reader3(baudRate, port3, 3);
    reader3.initialComPort();

    std::cout << "Enter the Port 4: ";
    std::cin >> port4;
    TagReader reader4(baudRate, port4, 4);
    reader4.initialComPort();

    unsigned char dataBlock[16];
    unsigned char lenghOfData;

	// M --> block 1
	// N --> block 2

	// X --> Block 5
	// Y --> Block 6
	if(prefer==2)
    {
    do {

	// مراحل خواند اطلاعات از دستگاه اول

    std::cout << "Reader 1 Data:" << endl;
    reader1.selectNearTag();

	// پارامتر اول شماره بلاکی که باید خواند شود را مشخص میکند
	// پارامتر دوم آرایه ای را مشخص میکند که اطلاعات خوانده شده باید در آن قرار گیرد
	// پارامتر سوم مشخص میکند ه چه مقدار اطلاعات خوانده شده
    std::cout<<"M = ";
	checker1=reader1.readDataBlock(1, dataBlock, &lenghOfData);
	if(!(checker1==-1 || checker1==-2)){
		// if checker==-2 there is Authentication error
		// if checker==-1 there is reading error
    for (int j = 0; j < (int) lenghOfData; j++) {   // it is going to be deleted
        std::cout << std::hex << (int) dataBlock[j];
		// این حلقه برای مشاهده تمام اطلاعات خوانده شده بکار میرود ولی
		// اطلاعات مورد نظر شما در بایت اول یا اندیس 0 ارایه داده قرار دارد
    }

	m=dataBlock[0];
	}
	std::cout<<endl<<"N = ";
	checker2=reader1.readDataBlock(2, dataBlock, &lenghOfData);
	if(!(checker2==-1 || checker2==-2)){  // it is going to be deleted
		// if checker==-2 there is Authentication error
		// if checker==-1 there is reading error
    for (int j = 0; j < (int) lenghOfData; j++) {  // it is going to be deleted
        std::cout << std::hex << (int) dataBlock[j];
    }

	n=dataBlock[0];

	}
	std::cout<<endl<<"X = ";
	checker3=reader1.readDataBlock(5, dataBlock, &lenghOfData);
    if(!(checker3==-1 || checker3==-2)){
		// if checker==-2 there is Authentication error
		// if checker==-1 there is reading error
	for (int j = 0; j < (int) lenghOfData; j++) { // it is going to be deleted
        std::cout << std::hex << (int) dataBlock[j];
    }

	x=dataBlock[0];

	}
 	std::cout<<endl<<"Y = ";
	checker4=reader1.readDataBlock(6, dataBlock, &lenghOfData);
    if(!(checker4==-1 || checker4==-2)){   // it is going to be deleted
		// if checker==-2 there is Authentication error
		// if checker==-1 there is reading error
        for (int j = 0; j < (int) lenghOfData; j++) { // it is going to be deleted
        std::cout << std::hex << (int) dataBlock[j];
    }

	y=dataBlock[0];

	}
    std::cout << std::endl;
   if(!((checker1==-1 || checker1==-2) || (checker2==-1 || checker2==-2) || (checker3==-1 || checker3==-2) || (checker4==-1 || checker4==-2)))

	{
    px=calculatepx(m,n,x,y);
	py=calculatepy(m,n,x,y);
	put(&startptr,m,n,x,y,px,py);
	node++;
	}

	else
	{
	put(&startptr,-1,-1,-1,-1,-1,-1);// sentical value in order to know that this tag cant read properly;
	node++;
	}

							////////////////////////////////////reader 1//////////////////////////////////////

	std::cout << "Reader 2 Data:" << endl;
    reader2.selectNearTag();

	// پارامتر اول شماره بلاکی که باید خواند شود را مشخص میکند
	// پارامتر دوم آرایه ای را مشخص میکند که اطلاعات خوانده شده باید در آن قرار گیرد
	// پارامتر سوم مشخص میکند ه چه مقدار اطلاعات خوانده شده
    std::cout<<"M = ";
	checker1=reader2.readDataBlock(1, dataBlock, &lenghOfData);
	if(!(checker1==-1 || checker1==-2)){
		// if checker==-2 there is Authentication error
		// if checker==-1 there is reading error
	   for (int j = 0; j < (int) lenghOfData; j++) {  // it is going to be deleted
        std::cout << std::hex << (int) dataBlock[j];
		// این حلقه برای مشاهده تمام اطلاعات خوانده شده بکار میرود ولی
		// اطلاعات مورد نظر شما در بایت اول یا اندیس 0 ارایه داده قرار دارد
    }

	m=dataBlock[0];

	}
	std::cout<<endl<<"N = ";
	checker2=reader2.readDataBlock(2, dataBlock, &lenghOfData);
	if(!(checker2==-1 || checker2==-2)){
		// if checker==-2 there is Authentication error
		// if checker==-1 there is reading error
    for (int j = 0; j < (int) lenghOfData; j++) { // it is going to be deleted
        std::cout << std::hex << (int) dataBlock[j];
    }

	n=dataBlock[0];

	}
	std::cout<<endl<<"X = ";
	checker3=reader2.readDataBlock(5, dataBlock, &lenghOfData);
    if(!(checker3==-1 || checker3==-2)){
		// if checker==-2 there is Authentication error
		// if checker==-1 there is reading error
	for (int j = 0; j < (int) lenghOfData; j++) { // it is going to be deleted
        std::cout << std::hex << (int) dataBlock[j];
    }

	x=dataBlock[0];

	}
 	std::cout<<endl<<"Y = ";
	checker4=reader2.readDataBlock(6, dataBlock, &lenghOfData);
    if(!(checker4==-1 || checker4==-2)){
		// if checker==-2 there is Authentication error
		// if checker==-1 there is reading error
			for (int j = 0; j < (int) lenghOfData; j++) { // it is going to be deleted
        std::cout << std::hex << (int) dataBlock[j];
    }

	y=dataBlock[0];

	}
    std::cout << std::endl;
	if(!((checker1==-1 || checker1==-2) || (checker2==-1 || checker2==-2) || (checker3==-1 || checker3==-2) || (checker4==-1 || checker4==-2)))

	{
	px=calculatepx(m,n,x,y);
	py=calculatepy(m,n,x,y);
	put(&startptr,m,n,x,y,px,py);
	node++;
	}
	else
	{
	put(&startptr,-1,-1,-1,-1,-1,-1);// sentical value in order to know that this tag cant read properly;
	node++;
	}

	                //////////////////////////////////////////////////reader 2/////////////////////////////////////////////////

	std::cout << "Reader 3 Data:" << endl;
    reader3.selectNearTag();

	// پارامتر اول شماره بلاکی که باید خواند شود را مشخص میکند
	//پارامتر دوم آرایه ای را مشخص میکند که اطلاعات خوانده شده باید در آن قرار گیرد
	// پارامتر سوم مشخص میکند ه چه مقدار اطلاعات خوانده شده
	std::cout<<"M = ";
	checker1=reader3.readDataBlock(1, dataBlock, &lenghOfData);
	if(!(checker1==-1 || checker1==-2)){
		// if checker==-2 there is Authentication error
		// if checker==-1 there is reading error
    for (int j = 0; j < (int) lenghOfData; j++) { // it is going to be deleted
        std::cout << std::hex << (int) dataBlock[j];
		// این حلقه برای مشاهده تمام اطلاعات خوانده شده بکار میرود ولی
		// اطلاعات مورد نظر شما در بایت اول یا اندیس 0 ارایه داده قرار دارد
    }

	m=dataBlock[0];

	}
	std::cout<<endl<<"N = ";
	checker2=reader3.readDataBlock(2, dataBlock, &lenghOfData);
	if(!(checker2==-1 || checker2==-2)){  // it is going to be deleted
		// if checker==-2 there is Authentication error
		// if checker==-1 there is reading error
    for (int j = 0; j < (int) lenghOfData; j++) {
        std::cout << std::hex << (int) dataBlock[j];
    }

	n=dataBlock[0];

	}
	std::cout<<endl<<"X = ";
	checker3=reader3.readDataBlock(5, dataBlock, &lenghOfData);
    if(!(checker3==-1 || checker3==-2)){
		// if checker==-2 there is Authentication error
		// if checker==-1 there is reading error
	for (int j = 0; j < (int) lenghOfData; j++) {
        std::cout << std::hex << (int) dataBlock[j];
    }

	x=dataBlock[0];

	}
 	std::cout<<endl<<"Y = ";
	checker4=reader3.readDataBlock(6, dataBlock, &lenghOfData);
    if(!(checker4==-1 || checker4==-2)){
		// if checker==-2 there is Authentication error
		// if checker==-1 there is reading error

			for (int j = 0; j < (int) lenghOfData; j++) { // it is going to be deleted
        std::cout << std::hex << (int) dataBlock[j];
    }

	y=dataBlock[0];

	}
    std::cout << std::endl;
    if(!((checker1==-1 || checker1==-2) || (checker2==-1 || checker2==-2) || (checker3==-1 || checker3==-2) || (checker4==-1 || checker4==-2)))

	{
	px=calculatepx(m,n,x,y);
	py=calculatepy(m,n,x,y);
	put(&startptr,m,n,x,y,px,py);
	node++;
	}
	else
	{
	put(&startptr,-1,-1,-1,-1,-1,-1);// sentical value in order to know that this tag cant read properly;
	node++;
	}

	                ///////////////////////////////////////////reader 3 ///////////////////////////////////////////////////////

	std::cout << "Reader 4 Data:" << endl;
    reader4.selectNearTag();

	// پارامتر اول شماره بلاکی که باید خواند شود را مشخص میکند
	// پارامتر دوم آرایه ای را مشخص میکند که اطلاعات خوانده شده باید در آن قرار گیرد
	// پارامتر سوم مشخص میکند ه چه مقدار اطلاعات خوانده شده
    std::cout<<"M = ";
	checker1=reader4.readDataBlock(1, dataBlock, &lenghOfData);
	if(!(checker1==-1 || checker1==-2)){
		// if checker==-2 there is Authentication error
		// if checker==-1 there is reading error
    for (int j = 0; j < (int) lenghOfData; j++) {  // it is going to be deleted
        std::cout << std::hex << (int) dataBlock[j];
		// این حلقه برای مشاهده تمام اطلاعات خوانده شده بکار میرود ولی
		// اطلاعات مورد نظر شما در بایت اول یا اندیس 0 ارایه داده قرار دارد
    }

	m=dataBlock[0];

	}
	std::cout<<endl<<"N = ";
	checker2=reader4.readDataBlock(2, dataBlock, &lenghOfData);
	if(!(checker2==-1 || checker2==-2)){
		// if checker==-2 there is Authentication error
		// if checker==-1 there is reading error
    for (int j = 0; j < (int) lenghOfData; j++) {  // it is going to be deleted
        std::cout << std::hex << (int) dataBlock[j];
    }

	n=dataBlock[0];

	}
	std::cout<<endl<<"X = ";
	checker3=reader4.readDataBlock(5, dataBlock, &lenghOfData);
    if(!(checker3==-1 || checker3==-2)){
		// if checker==-2 there is Authentication error
		// if checker==-1 there is reading error
	for (int j = 0; j < (int) lenghOfData; j++) {  // it is going to be deleted
        std::cout << std::hex << (int) dataBlock[j];
    }

	x=dataBlock[0];

	}
 	std::cout<<endl<<"Y = ";
	checker4=reader4.readDataBlock(6, dataBlock, &lenghOfData);
    if(!(checker4==-1 || checker4==-2)){
		// if checker==-2 there is Authentication error
		// if checker==-1 there is reading error

			for (int j = 0; j < (int) lenghOfData; j++) {  // it is going to be deleted
        std::cout << std::hex << (int) dataBlock[j];
    }

	y=dataBlock[0];

	}
    std::cout << std::endl;
    if(!((checker1==-1 || checker1==-2) || (checker2==-1 || checker2==-2) || (checker3==-1 || checker3==-2) || (checker4==-1 || checker4==-2)))

	{
	px=calculatepx(m,n,x,y);
	py=calculatepy(m,n,x,y);
	put(&startptr,m,n,x,y,px,py);
	node++;
	}
	else
	{
	put(&startptr,-1,-1,-1,-1,-1,-1);// sentical value in order to know that this tag cant read properly;
	node++;
	}
	counterstack++;  // use in funtion
	middle_conventer(&center,&startptr);
	middle_conventer_minmax(&centerminmax,&startptr);
	middle_conventer_avg(&centeravg,&startptr);
	start=start+4; //it is at the top of the code;
	counter=counter+1;
	counterprint++;
//	}

    scanf("%c",&letter);
    }while(letter=='\n');
    }


    if(prefer==1) {
	while(counter<=numb)
{
	printf("\n");


	// مراحل خواند اطلاعات از دستگاه اول
    std::cout << "Reader 1 Data:" << endl;
    reader1.selectNearTag();

	// پارامتر اول شماره بلاکی که باید خواند شود را مشخص میکند
	// پارامتر دوم آرایه ای را مشخص میکند که اطلاعات خوانده شده باید در آن قرار گیرد
	// پارامتر سوم مشخص میکند ه چه مقدار اطلاعات خوانده شده
    std::cout<<"M = ";
	checker1=reader1.readDataBlock(1, dataBlock, &lenghOfData);
	if(!(checker1==-1 || checker1==-2)){
		// if checker==-2 there is Authentication error
		// if checker==-1 there is reading error
	    for (int j = 0; j < (int) lenghOfData; j++) {   // it is going to be deleted
        std::cout << std::hex << (int) dataBlock[j];
		// این حلقه برای مشاهده تمام اطلاعات خوانده شده بکار میرود ولی
		// اطلاعات مورد نظر شما در بایت اول یا اندیس 0 ارایه داده قرار دارد
    }

	m=dataBlock[0];

	}
	std::cout<<endl<<"N = ";
	checker2=reader1.readDataBlock(2, dataBlock, &lenghOfData);
	if(!(checker2==-1 || checker2==-2)){  // it is going to be deleted
		// if checker==-2 there is Authentication error
		// if checker==-1 there is reading error
    for (int j = 0; j < (int) lenghOfData; j++) {  // it is going to be deleted
        std::cout << std::hex << (int) dataBlock[j];
    }

	n=dataBlock[0];

	}
	std::cout<<endl<<"X = ";
	checker3=reader1.readDataBlock(5, dataBlock, &lenghOfData);
    if(!(checker3==-1 || checker3==-2)){
		// if checker==-2 there is Authentication error
		// if checker==-1 there is reading error
	for (int j = 0; j < (int) lenghOfData; j++) { // it is going to be deleted
        std::cout << std::hex << (int) dataBlock[j];
    }

	x=dataBlock[0];

	}
 	std::cout<<endl<<"Y = ";
	checker4=reader1.readDataBlock(6, dataBlock, &lenghOfData);
    if(!(checker4==-1 || checker4==-2)){   // it is going to be deleted
		// if checker==-2 there is Authentication error
		// if checker==-1 there is reading error
        for (int j = 0; j < (int) lenghOfData; j++) { // it is going to be deleted
        std::cout << std::hex << (int) dataBlock[j];
    }

	y=dataBlock[0];

	}
    std::cout << std::endl;

	if(!((checker1==-1 || checker1==-2) || (checker2==-1 || checker2==-2) || (checker3==-1 || checker3==-2) || (checker4==-1 || checker4==-2)))

	{
	px=calculatepx(m,n,x,y);
	py=calculatepy(m,n,x,y);
	put(&startptr,m,n,x,y,px,py);
	node++;
	}

	else
	{
	put(&startptr,-1,-1,-1,-1,-1,-1);// sentical value in order to know that this tag cant read properly;
	node++;
	}

							////////////////////////////////////reader 1//////////////////////////////////////

	std::cout << "Reader 2 Data:" << endl;
    reader2.selectNearTag();

	// پارامتر اول شماره بلاکی که باید خواند شود را مشخص میکند
	// پارامتر دوم آرایه ای را مشخص میکند که اطلاعات خوانده شده باید در آن قرار گیرد
	// پارامتر سوم مشخص میکند ه چه مقدار اطلاعات خوانده شده
    std::cout<<"M = ";
	checker1=reader2.readDataBlock(1, dataBlock, &lenghOfData);
	if(!(checker1==-1 || checker1==-2)){
		// if checker==-2 there is Authentication error
		// if checker==-1 there is reading error
    for (int j = 0; j < (int) lenghOfData; j++) {  // it is going to be deleted
        std::cout << std::hex << (int) dataBlock[j];
		// این حلقه برای مشاهده تمام اطلاعات خوانده شده بکار میرود ولی
		// اطلاعات مورد نظر شما در بایت اول یا اندیس 0 ارایه داده قرار دارد
    }

	m=dataBlock[0];

	}
	std::cout<<endl<<"N = ";
	checker2=reader2.readDataBlock(2, dataBlock, &lenghOfData);
	if(!(checker2==-1 || checker2==-2)){
		// if checker==-2 there is Authentication error
		// if checker==-1 there is reading error
    for (int j = 0; j < (int) lenghOfData; j++) { // it is going to be deleted
        std::cout << std::hex << (int) dataBlock[j];
    }

	n=dataBlock[0];

	}
	std::cout<<endl<<"X = ";
	checker3=reader2.readDataBlock(5, dataBlock, &lenghOfData);
    if(!(checker3==-1 || checker3==-2)){
		// if checker==-2 there is Authentication error
		// if checker==-1 there is reading error
	for (int j = 0; j < (int) lenghOfData; j++) { // it is going to be deleted
        std::cout << std::hex << (int) dataBlock[j];
    }

	x=dataBlock[0];

	}
 	std::cout<<endl<<"Y = ";
	checker4=reader2.readDataBlock(6, dataBlock, &lenghOfData);
    if(!(checker4==-1 || checker4==-2)){
		// if checker==-2 there is Authentication error
		// if checker==-1 there is reading error
			for (int j = 0; j < (int) lenghOfData; j++) { // it is going to be deleted
        std::cout << std::hex << (int) dataBlock[j];
    }

	y=dataBlock[0];

	}
    std::cout << std::endl;

	if(!((checker1==-1 || checker1==-2) || (checker2==-1 || checker2==-2) || (checker3==-1 || checker3==-2) || (checker4==-1 || checker4==-2)))

	{
	px=calculatepx(m,n,x,y);
	py=calculatepy(m,n,x,y);
	put(&startptr,m,n,x,y,px,py);
	node++;
	}
	else
	{
	put(&startptr,-1,-1,-1,-1,-1,-1);// sentical value in order to know that this tag cant read properly;
	node++;
	}

	                //////////////////////////////////////////////////reader 2/////////////////////////////////////////////////

	std::cout << "Reader 3 Data:" << endl;
    reader3.selectNearTag();

	// پارامتر اول شماره بلاکی که باید خواند شود را مشخص میکند
	//پارامتر دوم آرایه ای را مشخص میکند که اطلاعات خوانده شده باید در آن قرار گیرد
	// پارامتر سوم مشخص میکند ه چه مقدار اطلاعات خوانده شده
    std::cout<<"M = ";
	checker1=reader3.readDataBlock(1, dataBlock, &lenghOfData);
	if(!(checker1==-1 || checker1==-2)){
		// if checker==-2 there is Authentication error
		// if checker==-1 there is reading error
    for (int j = 0; j < (int) lenghOfData; j++) { // it is going to be deleted
        std::cout << std::hex << (int) dataBlock[j];
		// این حلقه برای مشاهده تمام اطلاعات خوانده شده بکار میرود ولی
		// اطلاعات مورد نظر شما در بایت اول یا اندیس 0 ارایه داده قرار دارد
    }

	m=dataBlock[0];

	}
	std::cout<<endl<<"N = ";
	checker2=reader3.readDataBlock(2, dataBlock, &lenghOfData);
	if(!(checker2==-1 || checker2==-2)){  // it is going to be deleted
		// if checker==-2 there is Authentication error
		// if checker==-1 there is reading error
    for (int j = 0; j < (int) lenghOfData; j++) {
        std::cout << std::hex << (int) dataBlock[j];
    }

	n=dataBlock[0];

	}
	std::cout<<endl<<"X = ";
	checker3=reader3.readDataBlock(5, dataBlock, &lenghOfData);
    if(!(checker3==-1 || checker3==-2)){
		// if checker==-2 there is Authentication error
		// if checker==-1 there is reading error
	for (int j = 0; j < (int) lenghOfData; j++) {
        std::cout << std::hex << (int) dataBlock[j];
    }

	x=dataBlock[0];

	}
 	std::cout<<endl<<"Y = ";
	checker4=reader3.readDataBlock(6, dataBlock, &lenghOfData);
    if(!(checker4==-1 || checker4==-2)){
		// if checker==-2 there is Authentication error
		// if checker==-1 there is reading error

			for (int j = 0; j < (int) lenghOfData; j++) { // it is going to be deleted
        std::cout << std::hex << (int) dataBlock[j];
    }

	y=dataBlock[0];

	}
    std::cout << std::endl;

	if(!((checker1==-1 || checker1==-2) || (checker2==-1 || checker2==-2) || (checker3==-1 || checker3==-2) || (checker4==-1 || checker4==-2)))

	{
	px=calculatepx(m,n,x,y);
	py=calculatepy(m,n,x,y);
	put(&startptr,m,n,x,y,px,py);
	node++;
	}
	else
	{
	put(&startptr,-1,-1,-1,-1,-1,-1);// sentical value in order to know that this tag cant read properly;
	node++;
	}

	                ///////////////////////////////////////////reader 3 ///////////////////////////////////////////////////////

	std::cout << "Reader 4 Data:" << endl;
    reader4.selectNearTag();

	// پارامتر اول شماره بلاکی که باید خواند شود را مشخص میکند
	// پارامتر دوم آرایه ای را مشخص میکند که اطلاعات خوانده شده باید در آن قرار گیرد
	// پارامتر سوم مشخص میکند ه چه مقدار اطلاعات خوانده شده
    std::cout<<"M = ";
	checker1=reader4.readDataBlock(1, dataBlock, &lenghOfData);
	if(!(checker1==-1 || checker1==-2)){
		// if checker==-2 there is Authentication error
		// if checker==-1 there is reading error
    for (int j = 0; j < (int) lenghOfData; j++) {  // it is going to be deleted
        std::cout << std::hex << (int) dataBlock[j];
		// این حلقه برای مشاهده تمام اطلاعات خوانده شده بکار میرود ولی
		// اطلاعات مورد نظر شما در بایت اول یا اندیس 0 ارایه داده قرار دارد
    }

	m=dataBlock[0];

	}
	std::cout<<endl<<"N = ";
	checker2=reader4.readDataBlock(2, dataBlock, &lenghOfData);
	if(!(checker2==-1 || checker2==-2)){
		// if checker==-2 there is Authentication error
		// if checker==-1 there is reading error
    for (int j = 0; j < (int) lenghOfData; j++) {  // it is going to be deleted
        std::cout << std::hex << (int) dataBlock[j];
    }

	n=dataBlock[0];

	}
	std::cout<<endl<<"X = ";
	checker3=reader4.readDataBlock(5, dataBlock, &lenghOfData);
    if(!(checker3==-1 || checker3==-2)){
		// if checker==-2 there is Authentication error
		// if checker==-1 there is reading error
	for (int j = 0; j < (int) lenghOfData; j++) {  // it is going to be deleted
        std::cout << std::hex << (int) dataBlock[j];
    }

	x=dataBlock[0];

	}
 	std::cout<<endl<<"Y = ";
	checker4=reader4.readDataBlock(6, dataBlock, &lenghOfData);
    if(!(checker4==-1 || checker4==-2)){
		// if checker==-2 there is Authentication error
		// if checker==-1 there is reading error

			for (int j = 0; j < (int) lenghOfData; j++) {  // it is going to be deleted
        std::cout << std::hex << (int) dataBlock[j];
    }

	y=dataBlock[0];

	}
    std::cout << std::endl;

	if(!((checker1==-1 || checker1==-2) || (checker2==-1 || checker2==-2) || (checker3==-1 || checker3==-2) || (checker4==-1 || checker4==-2)))

	{

	px=calculatepx(m,n,x,y);
	py=calculatepy(m,n,x,y);
	put(&startptr,m,n,x,y,px,py);
	node++;
	}
	else
	{
	put(&startptr,-1,-1,-1,-1,-1,-1);// sentical value in order to know that this tag cant read properly;
	node++;
	}
	counterstack++;  // use in funtion

	middle_conventer(&center,&startptr);
	middle_conventer_minmax(&centerminmax,&startptr);
	middle_conventer_avg(&centeravg,&startptr);
	start=start+4; //it is at the top of the code;
	delay(stop);
	counter=counter+1;
	counterprint++;
}
}
	printlist(startptr);
	printlist2(center);
	printlist3(centerminmax);
	printlist4(centeravg);
	sd(&center,counterprint-becareful);
int i;
counterprint=counterprint-becareful;
for(i=1;i<counterprint;i++)
{
    setcolor(1);
	line(get2(&center,i,'C','X')*scale,get2(&center,i,'C','Y')*scale,get2(&center,i+1,'C','X')*scale,get2(&center,i+1,'C','Y')*scale);
	setcolor(2);
	line(get3(&centerminmax,i,'C','X')*scale,get3(&centerminmax,i,'C','Y')*scale,get3(&centerminmax,i+1,'C','X')*scale,get3(&centerminmax,i+1,'C','Y')*scale);
    setcolor(4);
    line(get4(&centeravg,i,'C','X')*scale,get4(&centeravg,i,'C','Y')*scale,get4(&centeravg,i+1,'C','X')*scale,get4(&centeravg,i+1,'C','Y')*scale);
}
getch();

	return 0;
}


	void remov(listnodeptr *sptr, int m,int n,int x,int y,float px,float py)
	{
		listnodeptr previousptr;
		listnodeptr currentptr;
		listnodeptr tempptr;
		if((m==(*sptr)->M)&&(n==(*sptr)->N)&&(x==(*sptr)->X)&&(y==(*sptr)->Y)&&(px==(*sptr)->PX)&&(py==(*sptr)->PY)) {
			tempptr=*sptr;
			*sptr=(*sptr)->nextptr;
			free(tempptr);
		}
		else {
			previousptr = *sptr;
			currentptr =(*sptr)->nextptr;
			while(currentptr != NULL && (currentptr->M != m)&&(currentptr->N != n)&&(currentptr->X != x)&&(currentptr->Y != y)&&(currentptr->PX != px)&&(currentptr->PY != py)) {
				previousptr=currentptr;
				currentptr = currentptr->nextptr;
			}
			if(currentptr != NULL)
			{
				tempptr=currentptr;
				previousptr->nextptr=currentptr->nextptr;
				free(tempptr);
			}
		}
	}
	int isempty(listnodeptr sptr)
	{
		return sptr==NULL;
	}
	void printlist(listnodeptr currentptr)
	{
		if(isempty(currentptr)) {
			//puts("");
		}
		else {
			while(currentptr != NULL) {
				printf("M:%-6d  N:%-6d  X:%-6d  Y:%-6d  PX:%-12f    PY:%-12f  \n",currentptr->M,currentptr->N,currentptr->X,currentptr->Y,currentptr->PX,currentptr->PY);
				currentptr = currentptr->nextptr;
			}
		puts("");
		}
	}

	int isempty2(centiptr sptr)
	{
		return sptr==NULL;
	}

    int isempty3(centiptrminmax sptr)
    {
        return sptr==NULL;
    }
    int isempty4(centiptravg sptr)
    {
        return sptr==NULL;
    }



	float get(listnodeptr *sptr,int n,char x)
	{
	//	int j=0;
        listnodeptr currentptrr;
		currentptrr=*sptr;
	//	while(currentptrr!=NULL)
	//	{
		//	currentptrr=currentptrr->nextptr;
		//	j++;
	   // }
	//	if(n>j || 1>n)
	//	 return;
		listnodeptr currentptr;
		currentptr=*sptr;
		if(isempty(currentptr)) {
	//		puts("list is empty.\n");
		}
		else {
			if(n>=1){
			for(int i=0;i<n-1;i++)
			{
			currentptr = currentptr->nextptr;
			}
			if(x=='M') {
		//	printf("%d\n",currentptr->M);
			return currentptr->M;
			}
			if(x=='N') {
		//	printf("%d\n",currentptr->N);
			return currentptr->N;
			}
			if(x=='X') {
	//		printf("%d\n",currentptr->X);
			return currentptr->X;
			}
				if(x=='Y') {
		//		printf("%d\n",currentptr->Y);
				return currentptr->Y;
				}
				if(x=='1') {
					return currentptr->PX;
				}
				if(x=='2') {
					return currentptr->PY;
				}
					}// for if
			} // for else
		} // end of function

	void put(listnodeptr *sptr,int m,int n,int x,int y,float px,float py)
	{
		listnodeptr newptr;
		listnodeptr previousptr;
		listnodeptr currentptr;
		newptr =( listnode* )malloc(sizeof(listnode));
		if(newptr !=NULL ) {
			newptr->M=m;
			newptr->N=n;
			newptr->X=x;
			newptr->Y=y;
			newptr->PX=px;
			newptr->PY=py;
			newptr->nextptr=NULL;
			previousptr=NULL;
			currentptr=*sptr;
			while(currentptr!=NULL) {
			previousptr=currentptr;
			currentptr=currentptr->nextptr;
			}
			if(previousptr==NULL)
			{
				newptr->nextptr=*sptr;
				*sptr=newptr;
			}

		else{
			previousptr->nextptr=newptr;
			newptr->nextptr=currentptr;
			}
		}
		else {
	//	printf("%d not inserted.no memory available.\n)",value);
		}
	}



void put2(centiptr *sptr,float partx,float party)
	{
		centiptr newptr;
		centiptr previousptr;
		centiptr currentptr;
		newptr =( centi* )malloc(sizeof(centi));
		if(newptr !=NULL ) {
			newptr->centerx=partx;
			newptr->centery=party;
			newptr->nextptr=NULL;
			previousptr=NULL;
			currentptr=*sptr;
			while(currentptr!=NULL) {
			previousptr=currentptr;
			currentptr=currentptr->nextptr;
			}
			if(previousptr==NULL)
			{
				newptr->nextptr=*sptr;
				*sptr=newptr;
			}

		else{
			previousptr->nextptr=newptr;
			newptr->nextptr=currentptr;
			}
		}
		else {
	//	printf("%d not inserted.no memory available.\n)",value);
		}
	}


	void put3(centiptrminmax *sptr,float partx,float party)
	{
		centiptrminmax newptr;
		centiptrminmax previousptr;
		centiptrminmax currentptr;
		newptr =( centiminmax *)malloc(sizeof(centiminmax));
		if(newptr !=NULL ) {
			newptr->minmaxcenterx=partx;
			newptr->minmaxcentery=party;
			newptr->nextptr=NULL;
			previousptr=NULL;
			currentptr=*sptr;
			while(currentptr!=NULL) {
			previousptr=currentptr;
			currentptr=currentptr->nextptr;
			}
			if(previousptr==NULL)
			{
				newptr->nextptr=*sptr;
				*sptr=newptr;
			}

		else{
			previousptr->nextptr=newptr;
			newptr->nextptr=currentptr;
			}
		}
		else {
	//	printf("%d not inserted.no memory available.\n)",value);
		}
	}

void printlist2(centiptr currentptr)
	{

			while(currentptr != NULL) {
				printf("centerx: %-12f centery: %-12f\n",currentptr->centerx,currentptr->centery);
				currentptr = currentptr->nextptr;
			}
		puts("");
	}

void printlist3(centiptrminmax currentptr)
	{

			while(currentptr != NULL) {
				printf("minmaxcenterx:%-12f  minmaxcentery:%-12f\n",currentptr->minmaxcenterx,currentptr->minmaxcentery);
				currentptr = currentptr->nextptr;
			}
		puts("");
	}

	void printlist4(centiptravg currentptr)
	{

			while(currentptr != NULL) {
				printf("avgcenterx:%-12f  avgcentery:%-12f\n",currentptr->avgcenterx,currentptr->avgcentery);
				currentptr = currentptr->nextptr;
			}
		puts("");
	}



float calculatepx(int a,int b,int c,int d)
{
    float px;
    int m;
    int n;
    int x;
    int y;
    m=a;
    n=b;
    x=c;
    y=d;
    px=(m-1)*secw + (x-1)*traw + traw/2;
    return px;
}



float calculatepy(int a,int b,int c,int d)
{
    float py;
    int m;
    int n;
    int x;
    int y;
    m=a;
    n=b;
    x=c;
    y=d;
    py=(n-1)*sech + (y-1)*trah + trah/2;
    return py;
}
void delay(float number_of_seconds)
{
    // Converting time into milli_seconds
    float milli_seconds = 1000 * number_of_seconds;

    // Stroing start time
    clock_t start_time = clock();

    // looping till required time is not acheived
    while (clock() < start_time + milli_seconds)
        ;
}
//start=1;//global variable
int middle_conventer(centiptr *center,listnodeptr *sptr)
{
float temp1;
int counter=0;
int x;
float temp2;
float xport1,xport2,xport3,xport4,yport1,yport2,yport3,yport4;
double cosa,sina;
//xport1=get(sptr,node,'1');//
//tempx=get(sptr,node-4,'1');// یکی قبلی: node
//tempy=get(sptr,node-4,'2');//یکی قبلی: node
//if() // ایا همه ی فقط یک تگ خوانده شده؟
//if(counterstack==0) //بله ایا قبل از این مرکزی وجود داشته؟
// ...اگر بله بود: یعنی هیچ داده قبلی ندارم و با نصف
//خیر رابطه ریاضی خودت.
//cx=get2(center,counterstack,'C','X')
//cy=get2(center,counterstack,'C','Y');
xport1=get(sptr,start,'1');
xport2=get(sptr,start+1,'1');
xport3=get(sptr,start+2,'1');
xport4=get(sptr,start+3,'1');
yport1=get(sptr,start,'2');
yport2=get(sptr,start+1,'2');
yport3=get(sptr,start+2,'2');
yport4=get(sptr,start+3,'2');

//printf("\n\n %f       %f       %f      %f\n\n",xport1,xport2,xport3,xport4,yport1,yport2,yport3,yport4);


 if(xport1!=-1 &&xport2!=-1&&xport3!=-1&&xport4!=-1)
 {
temp1=(float)(xport1+xport2+xport3+xport4)/4;
temp2=(float)(yport1+yport2+yport3+yport4)/4;
put2(center,temp1,temp2);
//printf("1");
return 1;

 }



if(xport1!=-1 && xport2!=-1 && xport3!=-1 && xport4==-1)
{
temp1=(xport1+xport3)/2;
temp2=(yport1+yport2)/2;
put2(center,temp1,temp2);
//printf("1");
return 1;

}



if(xport1!=-1 && xport2!=-1 && xport3==-1 && xport4!=-1)
{
temp1=(xport2+xport4)/2;
temp2=(yport2+yport4)/2;
put2(center,temp1,temp2);
//printf("1");
return 1;

}



if(xport1!=-1 && xport2==-1 && xport3!=-1 && xport4!=-1)
{
temp1=(xport1+xport3)/2;
temp2=(yport1+yport2)/2;
put2(center,temp1,temp2);
//printf("1");
return 1;

}



if(xport1==-1 && xport2!=-1 && xport3!=-1 && xport4!=-1)
{
temp1=(xport2+xport4)/2;
temp2=(yport2+yport4)/2;
put2(center,temp1,temp2);
//printf("1");
return 1;

}



if(xport1!=-1 && xport2==-1 && xport3!=-1 && xport4==-1)
{
temp1=(xport1+xport3)/2;
temp2=(yport1+yport3)/2;
put2(center,temp1,temp2);
//printf("1");
return 1;

}



if(xport1==-1 && xport2!=-1 && xport3==-1 && xport4!=-1)
{
temp1=(xport2+xport4)/2;
temp2=(yport2+yport4)/2;
put2(center,temp1,temp2);
//printf("1");
return 1;

}



if(xport1!=-1 && xport2!=-1 && xport3==-1 && xport4==-1)
{
	if(xport1==xport2 && yport1> yport2)
	{
		temp1=xport1-objectlength/2;
		temp2=(yport1+yport2)/2;
		put2(center,temp1,temp2);
	//	printf("1");
	return 1;

	}

if(xport1==xport2 && yport1 < yport2)
	{
		temp1=xport1+objectlength/2;
		temp2=(yport1+yport2)/2;
		put2(center,temp1,temp2);
	//	printf("1");
		return 1;
}
if(xport1<xport2 && yport1 == yport2)
	{
		temp1=(xport1+xport2)/2;
		temp2=yport1-objectlength/2;
		put2(center,temp1,temp2);
	//	printf("1");
		return 1;

}
if(xport1>xport2 && yport1 == yport2)
	{
		temp1=(xport1+xport2)/2;
		temp2=yport1+objectlength/2;
		put2(center,temp1,temp2);
	//	printf("1");
		return 1;

}
if(xport1!=xport2 && yport1!=yport2)
{
sina=(yport2-yport1)/objectwidth;
cosa=(xport2-xport1)/objectwidth;
temp1=cosa*(objectwidth/2)-sina*(-objectlength/2)+xport1;
temp2=sina*(objectwidth/2)+cosa*(-objectlength/2)+yport1;
put2(center,temp1,temp2);
//printf("1");
return 1;
	}
}



if(xport1==-1 && xport2==-1 && xport3!=-1 && xport4!=-1)
{
	if(xport3==xport4 && yport3> yport4)
	{
		temp1=xport3-objectlength/2;
		temp2=(yport3+yport4)/2;
		put2(center,temp1,temp2);
	//	printf("1");
	return 1;

	}

if(xport3==xport4 && yport3 < yport4)
	{
		temp1=xport3+objectlength/2;
		temp2=(yport3+yport4)/2;
		put2(center,temp1,temp2);
	//	printf("1");
		return 1;

}
if(xport3<xport4 && yport3 == yport4)
	{
		temp1=(xport3+xport4)/2;
		temp2=yport3-objectlength/2;
		put2(center,temp1,temp2);
	//	printf("1");
return 1;
}
if(xport3>xport4 && yport3 == yport4)
	{
		temp1=(xport3+xport4)/2;
		temp2=yport3+objectlength/2;
		put2(center,temp1,temp2);
	//	printf("1");
return 1;
}
if(xport3!=xport4 && yport3!=yport4)
{
sina=(yport4-yport3)/objectwidth;
cosa=(xport4-xport3)/objectwidth;
temp1=cosa*(objectwidth/2)-sina*(-objectlength/2)+xport3;
temp2=sina*(objectwidth/2)+cosa*(-objectlength/2)+yport3;
put2(center,temp1,temp2);
//printf("1");
return 1;

	}
}



if(xport1==-1 && xport2!=-1 && xport3!=-1 && xport4==-1)
{
	if(xport3==xport2 && yport3> yport2)
	{
		temp1=xport3+objectwidth/2;
		temp2=(yport3+yport2)/2;
		put2(center,temp1,temp2);
	//	printf("1");
	return 1;
	}

if(xport3==xport2 && yport3 < yport2)
	{
		temp1=xport3-objectwidth/2;
		temp2=(yport3+yport2)/2;
		put2(center,temp1,temp2);
		//printf("1");
return 1;
}
if(xport3<xport2 && yport3 == yport2)
	{
		temp1=(xport3+xport2)/2;
		temp2=yport3+objectwidth/2;
		put2(center,temp1,temp2);
	//	printf("1");
return 1;
}
if(xport3>xport2 && yport3 == yport2)
	{
		temp1=(xport3+xport2)/2;
		temp2=yport3-objectwidth/2;
		put2(center,temp1,temp2);
		//printf("1");
return 1;
}
if(xport3!=xport2 && yport3!=yport2)
{
sina=(yport3-yport2)/objectlength;
cosa=(xport3-xport2)/objectlength;
temp1=cosa*(objectlength/2)-sina*(-objectwidth/2)+xport2;
temp2=sina*(objectlength/2)+cosa*(-objectwidth/2)+yport2;
put2(center,temp1,temp2);
//printf("1");
return 1;
}
}


if(xport1!=-1 && xport2==-1 && xport3==-1 && xport4!=-1)
{
	if(xport1==xport4 && yport1> yport4)
	{
		temp1=xport1+objectwidth/2;
		temp2=(yport1+yport4)/2;
		put2(center,temp1,temp2);
	//	printf("1");
	return 1;
	}

if(xport1==xport4 && yport1 < yport4)
	{
		temp1=xport1-objectwidth/2;
		temp2=(yport1+yport4)/2;
		put2(center,temp1,temp2);
	//	printf("1");
return 1;
}
if(xport1<xport4 && yport1 == yport4)
	{
		temp1=(xport1+xport4)/2;
		temp2=yport1+objectwidth/2;
		put2(center,temp1,temp2);
	//	printf("1");
return 1;
}
if(xport1>xport4 && yport1 == yport4)
	{
		temp1=(xport1+xport4)/2;
		temp2=yport1-objectwidth/2;
		put2(center,temp1,temp2);
	//	printf("1");
return 1;
}
if(xport1!=xport4 && yport1!=yport4)
{
sina=(yport1-yport4)/objectlength;
cosa=(xport1-xport4)/objectlength;
temp1=cosa*(objectlength/2)-sina*(-objectwidth/2)+xport4;
temp2=sina*(objectlength/2)+cosa*(-objectwidth/2)+yport4;
put2(center,temp1,temp2);
//printf("1");
return 1;
}
}


if(xport1!=-1 && xport2==-1 && xport3==-1 && xport4==-1)
{
x=node-4;
	while(x-4>0   &&     get(sptr,x-4,'1')==-1)
{
    counter++;
	x=x-4;
}
if(counter==0 && x<4)
{
temp1=objectlength/2+get(sptr,node-4,'1');
temp2=objectwidth/2+get(sptr,node-4,'2');
put2(center,temp1,temp2);
//printf("9");
}
else
{
float ax=(get(sptr,node-4,'1')-get(sptr,x,'1'))/(counter+1)+get2(center,counterstack,'C','X');
float ay=(get(sptr,node-4,'2')-get(sptr,x,'2'))/(counter+1)+get2(center,counterstack,'C','Y');
put2(center,ax,ay);
//printf("8");
}
return 1;
}

if(xport1==-1 && xport2!=-1 && xport3==-1 && xport4==-1)
{
    counter=0;
 x=node-3;
	while(x-4>0   &&     get(sptr,x-4,'1')==-1)
    {
	counter++;
	x=x-4;
	}
if(counter==0 && x<4)
{
temp1=objectlength/2+get(sptr,node-4,'1');
temp2=-objectwidth/2+get(sptr,node-4,'2');
put2(center,temp1,temp2);
//printf("7");
}
else
{
float ax=(get(sptr,node-4,'1')-get(sptr,x,'1'))/(counter+1)+get2(center,counterstack,'C','X');
float ay=(get(sptr,node-4,'2')-get(sptr,x,'2'))/(counter+1)+get2(center,counterstack,'C','Y');
put2(center,ax,ay);
//printf("6");
}
return 1;
}
if(xport1==-1 && xport2==-1 && xport3!=-1 && xport4==-1)
{
    counter=0;
    x=node-2;
	while(x-4>0   &&     get(sptr,x-4,'1')==-1)
{counter++;
	x=x-4;
}
if(counter==0 &&  x<4)
{
temp1=-objectlength/2+get(sptr,node-4,'1');
temp2=-objectwidth/2+get(sptr,node-4,'2');
put2(center,temp1,temp2);
//printf("5");
}
else
{
float ax=(get(sptr,node-4,'1')-get(sptr,x,'1'))/(counter+1)+get2(center,counterstack,'C','X');
float ay=(get(sptr,node-4,'2')-get(sptr,x,'2'))/(counter+1)+get2(center,counterstack,'C','Y');
put2(center,ax,ay);
//printf("4");
}
return 1;
}
if(xport1==-1 && xport2==-1 && xport3==-1 && xport4!=-1)
{

    counter=0;
    x=node-1;
	while(x-4>0   &&     get(sptr,x-4,'1')==-1)
{counter++;
	x=x-4;
}
if(counter==0 && x<4)
{
temp1=-objectlength/2+get(sptr,node-4,'1');
temp2=objectwidth/2+get(sptr,node-4,'2');
put2(center,temp1,temp2);
//printf("3");
}
else
{

float ax=(get(sptr,node-4,'1')-get(sptr,x,'1'))/(counter+1)+get2(center,counterstack,'C','X');
float ay=(get(sptr,node-4,'2')-get(sptr,x,'2'))/(counter+1)+get2(center,counterstack,'C','Y');
put2(center,ax,ay);
//printf("2");
}
return 1;
}

if(xport1==-1&&xport2==-1&&xport3==-1&&xport4==-1)
{
becareful++;
return -1;
}
}

float get2(centiptr *sptr,int n,char ch,char ch2)
{
	//	int j=0;
        centiptr currentptr;
		currentptr=*sptr;
	//	while(currentptrr!=NULL)
	//	{
		//	currentptrr=currentptrr->nextptr;
		//	j++;
	   // }
	//	if(n>j || 1>n)
	//	 return;
		if(isempty2(currentptr)) {
	//		puts("list is empty.\n");
		}
		else {
			if(n>=1){
			for(int i=0;i<n-1;i++)
			{
			currentptr = currentptr->nextptr;
			}
			if(ch=='C' && ch2=='X') {
		//	printf("%d\n",currentptr->M);
				return currentptr->centerx;
			}
			if(ch=='C' && ch2=='Y') {
		//	printf("%d\n",currentptr->N);
			return currentptr->centery;
			}
					}// for if
			} // for else

}

float get3(centiptrminmax *sptr,int n,char ch,char ch2)
{
	//	int j=0;
        centiptrminmax currentptr;
		currentptr=*sptr;
	//	while(currentptrr!=NULL)
	//	{
		//	currentptrr=currentptrr->nextptr;
		//	j++;
	   // }
	//	if(n>j || 1>n)
	//	 return;
		if(isempty3(currentptr)) {
	//		puts("list is empty.\n");
		}
		else {
			if(n>=1){
			for(int i=0;i<n-1;i++)
			{
			currentptr = currentptr->nextptr;
			}
			if(ch=='C' && ch2=='X') {
		//	printf("%d\n",currentptr->M);
				return currentptr->minmaxcenterx;
			}
			if(ch=='C' && ch2=='Y') {
		//	printf("%d\n",currentptr->N);
			return currentptr->minmaxcentery;
			}
					}// for if
			} // for else

}

float get4(centiptravg*sptr,int n,char ch,char ch2)
{
	//	int j=0;
        centiptravg currentptr;
		currentptr=*sptr;
	//	while(currentptrr!=NULL)
	//	{
		//	currentptrr=currentptrr->nextptr;
		//	j++;
	   // }
	//	if(n>j || 1>n)
	//	 return;
		if(isempty4(currentptr)) {
	//		puts("list is empty.\n");
		}
		else {
			if(n>=1){
			for(int i=0;i<n-1;i++)
			{
			currentptr = currentptr->nextptr;
			}
			if(ch=='C' && ch2=='X') {
		//	printf("%d\n",currentptr->M);
				return currentptr->avgcenterx;
			}
			if(ch=='C' && ch2=='Y') {
		//	printf("%d\n",currentptr->N);
			return currentptr->avgcentery;
			}
					}// for if
			} // for else

}


void put4(centiptravg *sptr,float partx,float party)
	{
		centiptravg newptr;
		centiptravg previousptr;
		centiptravg currentptr;
		newptr =( centiavg *)malloc(sizeof(centiavg));
		if(newptr !=NULL ) {
			newptr->avgcenterx=partx;
			newptr->avgcentery=party;
			newptr->nextptr=NULL;
			previousptr=NULL;
			currentptr=*sptr;
			while(currentptr!=NULL) {
			previousptr=currentptr;
			currentptr=currentptr->nextptr;
			}
			if(previousptr==NULL)
			{
				newptr->nextptr=*sptr;
				*sptr=newptr;
			}

		else{
			previousptr->nextptr=newptr;
			newptr->nextptr=currentptr;
			}
		}
		else {
	//	printf("%d not inserted.no memory available.\n)",value);
		}
	}






void middle_conventer_minmax(centiptrminmax *center,listnodeptr *sptr)
{
float tempx,tempy;
float	X[4],Y[4],maxx,minn,counter=0;
int i;
X[0]=get(sptr,start,'1');
X[1]=get(sptr,start+1,'1');
X[2]=get(sptr,start+2,'1');
X[3]=get(sptr,start+3,'1');
Y[0]=get(sptr,start,'2');
Y[1]=get(sptr,start+1,'2');
Y[2]=get(sptr,start+2,'2');
Y[3]=get(sptr,start+3,'2');

for(int i=0;i<=3;i++)
{if(X[i]!=-1)
counter++;}

if(counter==0)
return; // all are invalid

for(int i=0;i<=3;i++)
{
    if(X[i]!=-1)
    {
     minn=X[i];
    }
    break;
}
maxx=0;
for(int i=0;i<=3;i++)
{
    if(X[i]>maxx && (X[i]!=-1))
    {
        maxx=X[i];
    }
    if(X[i]<minn  && (X[i]!=-1))
    {
        minn=X[i];
    }
}
tempx=(maxx+minn)/2;

for(int i=0;i<=3;i++)
{
    if(Y[i]!=-1)
    {
     minn=Y[i];
    }
    break;
}
maxx=0;
for(int i=0;i<=3;i++)
{
    if(Y[i]>maxx && (Y[i]!=-1))
    {
        maxx=Y[i];
    }
    if(Y[i]<minn  &&  (Y[i]!=-1))
    {
        minn=Y[i];
    }

}
tempy=(maxx+minn)/2;
//printf("kkk  %f   ",tempy);
put3(center,tempx,tempy);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void middle_conventer_avg(centiptravg *avg,listnodeptr *sptr)
{
float counterx=0,countery=0,temp,sum=0, X[4],Y[4];
float tempx,tempy;

X[0]=get(sptr,start,'1');
X[1]=get(sptr,start+1,'1');
X[2]=get(sptr,start+2,'1');
X[3]=get(sptr,start+3,'1');
Y[0]=get(sptr,start,'2');
Y[1]=get(sptr,start+1,'2');
Y[2]=get(sptr,start+2,'2');
Y[3]=get(sptr,start+3,'2');


for(int i=0;i<=3;i++)
if(X[i]!=-1)
counterx++;


for(int i=0;i<=3;i++)
if(Y[i]!=-1)
countery++;



if(counterx==0)
return;
if(countery==1)
{
    for(int i=0;i<=3;i++)
    {
            if(X[i]!=-1)
            {
             tempx=X[i];
             tempy=Y[i];
             put4(avg,tempx,tempy);
            }
    }

}


else
{
for(int i=0;i<=3;i++)
for(int j=0;j<=2;j++)
if(X[i]>X[j])
{
temp=X[i];
X[i]=X[j];
X[j]=temp;
}


for(int i=0;i<=3;i++)
for(int j=0;j<=2;j++)
if(Y[i]>Y[j])
{
temp=Y[i];
Y[i]=Y[j];
Y[j]=temp;
}


for(int i=counterx-1;i>=0;i--)
{
	sum=sum+X[i];
}
tempx=sum/counterx;





sum=0;
for(int i=countery-1;i>=0;i--)
{
	sum=sum+Y[i];
}
tempy=sum/countery;
put4(avg,tempx,tempy);
}
}






float sd(centiptr *sptr,int n)
{
    if(n>0){
    float avgx=0;
    float avgy=0;
    int numberstack;
    int i,j,k;
    float temp,temp2,varx=0,vary=0;
    numberstack=n;
    for(j=1;j<=numberstack;j++)
    {
        avgx=avgx+get2(sptr,j,'C','X');
    }
    avgx=(float)avgx/numberstack;
    for(k=1;k<=numberstack;k++)
    {
        avgy=avgy+get2(sptr,k,'C','Y');
    }
    avgy=(float)avgy/numberstack;

    for(i=1;i<=numberstack;i++)
    {
    temp=get2(sptr,i,'C','X')-avgx;
    temp=temp*temp;
    varx=varx+temp;
    }
    varx=(float)varx/numberstack;
    for(i=1;i<=numberstack;i++)
    {
    temp2=get2(sptr,i,'C','Y')-avgy;
    temp2=temp2*temp2;
    vary=vary+temp2;
    }
    vary=(float)vary/numberstack;
    printf("\n SD(for x): %f  \n SD (for y): %f \n",sqrt(varx),sqrt(vary));
}
else
{
    printf("no invalid center for calculating SD");
}
}
