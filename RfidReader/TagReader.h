//
// Created by mehrsa on 12/19/2017.
//
#include <Windows.h>
#include "declaredll.h"
#include "MasterRD.h"
#include <string>

#ifndef RFIDREADER_TAGREADER_H
#define RFIDREADER_TAGREADER_H

using namespace std;

class TagReader {
    int baudRate;
    int port;
    int deviceId;
    int id;

    // last tag information
    short unsigned int tagType;
    unsigned char lengthOfSerialNumber;
    unsigned char tagSerialNumber[100];
    unsigned char tagModel = 0x52;
    unsigned char keyMode = 0x60;
    unsigned char key[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

    HINSTANCE RFID_LIBRARY = NULL;
    F_RF_INIT_COM rf_init_com;
    F_RF_REQUEST rf_request;
    F_RF_ANTICOLL rf_anticoll;
    F_RF_SELECT rf_select;
    F_RF_M1_AUTHENTICATION2 rf_M1_authentication2;
    F_RF_M1_READ rf_M1_read;


public:
    TagReader(int baudRate, int port, int id);

    bool initialComPort();

    virtual ~TagReader();

    bool selectNearTag();

    void readDataBlock(unsigned char blockNumber, unsigned char blockData[], unsigned char *dataLength);

public:

    int getBaudRate() const;

    void setBaudRate(int baudRate);

    int getPort() const;

    void setPort(int port);

    int getDeviceId() const;

    void setDeviceId(int deviceId);

    int getId() const;

    void setId(int id);


};

int TagReader::getBaudRate() const {
    return baudRate;
}

void TagReader::setBaudRate(int baudRate) {
    TagReader::baudRate = baudRate;
}

int TagReader::getPort() const {
    return port;
}

void TagReader::setPort(int port) {
    TagReader::port = port;
}

int TagReader::getDeviceId() const {
    return deviceId;
}

void TagReader::setDeviceId(int deviceId) {
    TagReader::deviceId = deviceId;
}

TagReader::TagReader(int baudRate, int port, int id) : baudRate(baudRate), port(port), id(id) {

    if (id == 1) {
        RFID_LIBRARY = LoadLibrary(".\\dll\\r1\\MasterRD.dll");
    }
    if (id == 2)
        RFID_LIBRARY = LoadLibrary(".\\dll\\r2\\MasterRD.dll");
    if (id == 3)
        RFID_LIBRARY = LoadLibrary(".\\dll\\r3\\MasterRD.dll");
    if (id == 4)
        RFID_LIBRARY = LoadLibrary(".\\dll\\r4\\MasterRD.dll");
    if (RFID_LIBRARY == NULL) {
        cout << "Load dll failure!";
		exit;
    } else {
        std::cout << "Library of reader " << id << " Loaded!" << endl;
    }
    rf_init_com = (F_RF_INIT_COM) GetProcAddress(RFID_LIBRARY, "rf_init_com");
    if (rf_init_com == NULL) {
        cout << "function rf_init_com GetProcAddress failure!"<< endl;
    }
    rf_request = (F_RF_REQUEST) GetProcAddress(RFID_LIBRARY, "rf_request");
    if (rf_request == NULL) {
        cout << "function rf_request GetProcAddress failure!"<< endl;
    }
    rf_anticoll = (F_RF_ANTICOLL) GetProcAddress(RFID_LIBRARY, "rf_anticoll");
    if (rf_anticoll == NULL) {
        cout << "function rf_anticoll GetProcAddress failure!"<< endl;
    }
    rf_select = (F_RF_SELECT) GetProcAddress(RFID_LIBRARY, "rf_select");
    if (rf_select == NULL) {
        cout << "function rf_select GetProcAddress failure!"<< endl;
    }

    rf_M1_authentication2 = (F_RF_M1_AUTHENTICATION2) GetProcAddress(RFID_LIBRARY, "rf_M1_authentication2");
    if (rf_M1_authentication2 == NULL) {
        cout << "function rf_M1_authentication2 GetProcAddress failure!"<< endl;
    }

    rf_M1_read = (F_RF_M1_READ) GetProcAddress(RFID_LIBRARY, "rf_M1_read");
    if (rf_M1_read == NULL) {
        cout << "function rf_M1_read GetProcAddress failure!"<< endl;
    }

}

bool TagReader::initialComPort() {

    int status = rf_init_com(port, baudRate);
    if (status != 0) {
        cout << "open the comm failure!"<< endl;
        return false;
    }
    return true;

}

bool TagReader::selectNearTag() {
    int status = rf_request(0, tagModel, &tagType);
    if (status != 0) {
        cout << "Request failure!"<< endl;

    }
    status = rf_anticoll(0, 0x04, tagSerialNumber, &lengthOfSerialNumber);
    if (status != 0) {
        cout << "Anticoll failure!"<< endl;
        return 0;
    }
    status = rf_select(0, tagSerialNumber, 4, &lengthOfSerialNumber);
    if (status != 0) {
        cout << "Select failure!"<< endl;
        return 0;
    }
    return 1;
}

void TagReader::readDataBlock(unsigned char blockNumber, unsigned char blockData[], unsigned char *dataLength) {

    // unsigned char blockData[100];
    // unsigned char dataLength;
    int status = rf_M1_authentication2(0, keyMode, blockNumber, key);
    if (status != 0) {
        cout << "Authentication Error";
    }
    status = rf_M1_read(0, blockNumber, blockData,
                        dataLength);// read data of blocknumber and put it in the blockdata . also put length of it in datalength
    if (status != 0) {
        cout << "Read Block Error";
    }
    // return blockData;
}

TagReader::~TagReader() {
    FreeLibrary(RFID_LIBRARY);

}

int TagReader::getId() const {
    return id;
}

void TagReader::setId(int id) {
    TagReader::id = id;
}


#endif //RFIDREADER_TAGREADER_H
