#include <iostream>
#include <string>
#include "DES.h"
#include <fstream>
#include <memory.h>
using namespace std;


char key[] = "123456";
void ENCRYPT_test(){
    ifstream in;
    ofstream out;
    in.open("../test", ios::binary);
    in.seekg(0, std::ios::end);
    long  originlength = in.tellg();
    long length = (originlength+7)/8*8+8;
    cout<<"en file length::"<<originlength<<endl;
    in.seekg(0, std::ios::beg);
    char *buffer = new char[length];
    char *out1 = new char[length];
    memcpy(buffer,&originlength,1);
    memcpy(out1,&originlength,1);
    memset(&buffer[8],'\0',length-8);
    in.read(&buffer[8], length-8);
    in.close();

    Des des;
    des.Des_Go(out1, buffer, length, key, 6, ENCRYPT);
    out.open("../result", ios::binary);
    out.write(out1,length);
    out.close();
    delete buffer;
    delete out1;
//    delete out2;
}
void DECRYPT_test(){

    ifstream in;
    ofstream out;
    in.open("../result", ios::binary);
    in.seekg(0, std::ios::end);
    long  originlength = in.tellg();
    cout<<"de file length::"<<originlength<<endl;
    long length = (originlength+7)/8*8+8;
    in.seekg(0, std::ios::beg);
    char *buffer = new char[length];
    char *out1 = new char[length];
    memset(buffer,0,length);
    in.read(buffer, length);
    in.close();

    Des des;
    des.Des_Go(out1, buffer, length, key, 6, DECRYPT);
    long num;
    memcpy(&num,out1,8);
    out.open("../result2", ios::binary);
    out.write(&out1[8],num);
    out.close();
    delete buffer;
    delete out1;
}
int main() {
    cout<<sizeof(long)<<endl;
    ENCRYPT_test();
    DECRYPT_test();
    return 0;

}
