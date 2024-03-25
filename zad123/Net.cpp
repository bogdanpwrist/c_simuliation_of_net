#include "Net.h"
#include "Logs.h"
using namespace std;

#define DEF_FRAME_SIZE 100

Net::Net() {
    this->frame_size = DEF_FRAME_SIZE;
    Logs::logcreatenetsucces();
}

Net::Net(int file_size, int frame_size, char** get_buffers) {
    this->file_size = file_size;
    this->frame_size = frame_size;
    this->get_buffers = get_buffers;
    this->send_buffers = new char* [iter() + 1];
    Logs::logcreatenetsucces();
    
}

Net::~Net() {
    Logs::logdeletenetsucces();
    delete[] send_buffers; // Usu� send_buffers, ale nie get_buffers, poniewa� nie zosta� zaalokowany dynamicznie
}

void Net::set_get_buffers(char** get_buffers) {
    this->get_buffers = get_buffers;
    Logs::logset();
}

char*** Net::get_send_buffers() {
    Logs::logget();
    return &this->send_buffers;
}

int Net::get_frame_size() {
    Logs::logget();
    return this->frame_size;
}

int Net::get_file_size() {
    Logs::logget();
    return this->file_size;
}

void Net::set_frame_size(int frame_size) {
    this->frame_size = frame_size;
    Logs::logset();
}

void Net::set_file_size(int file_size) {
    this->file_size = file_size;
    Logs::logset();
}

void Net::randoming() {
    Logs::logstartrndomingframes();
    //int arraySize = /*sizeof(get_buffers) / sizeof(get_buffers[0]);*/ this->iter(); // Poprawka
    //random_device rd;
    //mt19937 gen(rd()); // U�yj generatora liczb pseudolosowych z <random>
    //uniform_int_distribution<> distr(0, arraySize - 1);
    
    int* myArray = new int[iter()+1];
    for (int i = 0; i < iter()+1; ++i) {
        bool isUnique;
        do {
            isUnique = true;
            myArray[i] = std::rand() % (iter()+1); // Adjust the range as needed
            for (int j = 0; j < i; ++j) {
                if (myArray[i] == myArray[j]) {
                    isUnique = false;
                    break;
                }
            }
        } while (!isUnique);
    }
    cout << "\n\n\n\n\n\n\n\n\n";
    for (int i = 0; i < iter() + 1; i++)
        this->send_buffers[myArray[i]] = this->get_buffers[i];
    /*for (int i = 0; i <= iter(); i++)
        for (int j = 0; j < this->frame_size; j++)
            cout << send_buffers[i][j];*/
    delete[] myArray;
    //for (int i = iter(); i > 0; --i) {
    //    int j = distr(gen); // U�yj dystrybucji pseudolosowej zamiast rand()
    //    char* temp = this->get_buffers[i];
    //    this->get_buffers[i] = this->get_buffers[j];
    //    this->get_buffers[j] = temp;
    //}
    //this->set_get_buffers(get_buffers);
    Logs::logrndomingframes();
}

int Net::iter() {
    return file_size / frame_size;
}

void Net::send_to_receiver() {
    // Implementacja funkcji send_to_receiver()
}
