#include <iostream>
#include <Windows.h>
#include "declaredll.h"
#include "MasterRD.h"
#include "TagReader.h"

using namespace std;

int main() {

    int baudRate=9600;
    int port1, port2, port3, port4;
    std::cout << "Enter the Port 1: ";
    std::cin >> port1;
	// پارامتر 2 شماره پورت را مشخص میکند
	// پارامتر سوم شماره دستگاه را مشخص میکند.
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

	
	// مراح خواند اطلاعات از دستگاه اول
    std::cout << "Reader 1 Data:" << endl;
    reader1.selectNearTag();
	
	// پارامتر اول شماره بلاکی که باید خواند شود را مشخص میکند
	// پارامتر دوم آرایه ای را مشخص میکند که اطلاعات خوانده شده باید در آن قرار گیرد
	// پارامتر سوم مشخص میکند ه چه مقدار اطلاعات خوانده شده
    reader1.readDataBlock(1, dataBlock, &lenghOfData);
	std::cout<<"M = ";
    for (int j = 0; j < (int) lenghOfData; j++) {
        std::cout << std::hex << (int) dataBlock[j];
		// این حلقه برای مشاهده تمام اطلاعات خوانده شده بکار میرود ولی 
		// اطلاعات مورد نظر شما در بایت اول یا اندیس 0 ارایه داده قرار دارد
    }
	std::cout<<endl<<"N = ";
	reader1.readDataBlock(2, dataBlock, &lenghOfData);
    for (int j = 0; j < (int) lenghOfData; j++) {
        std::cout << std::hex << (int) dataBlock[j];
    }
	std::cout<<endl<<"X = ";
	reader1.readDataBlock(5, dataBlock, &lenghOfData);
    for (int j = 0; j < (int) lenghOfData; j++) {
        std::cout << std::hex << (int) dataBlock[j];
    }
	std::cout<<endl<<"Y = ";
	reader1.readDataBlock(6, dataBlock, &lenghOfData);
    for (int j = 0; j < (int) lenghOfData; j++) {
        std::cout << std::hex << (int) dataBlock[j];
    }
    std::cout << std::endl;
	
	// مراحل خظ 42 تا 64 برای سه دستگاه دیگر باید گنجانده شود
	
	

    return 0;
}