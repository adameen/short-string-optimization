#include <iostream>
#include <string.h>

const int BUFFSIZE = 8;

class String {
public:
    String() { }

    String(const char* arg) {
        size_t arg_len = strlen(arg);

        if(arg_len < BUFFSIZE){
            //copy in reverse order
            for(int i = 0; i < BUFFSIZE; i++){
                if(i > arg_len){
                    changeable_buffer_.short_[i] = 0;
                }
                else{
                    changeable_buffer_.short_[i] = arg[arg_len-i];
                }
            }
            changeable_buffer_.short_[0] = 1;
            // leaving the last (first according to saved place) bit as 1
        }
        else{
            changeable_buffer_.long_ = new char[arg_len + 1];
            strcpy(changeable_buffer_.long_, arg);
        }
    }

    ~String() {
        if(On_heap()){
            delete [] changeable_buffer_.long_;
        }
    }

    friend std::ostream& operator<<(std::ostream& str, /* const */ String& arg){
        if (!arg.On_heap()) {
            for(int i = BUFFSIZE-1; i > 0; i--){
                if(arg.changeable_buffer_.short_[i] != 0){
                    str << arg.changeable_buffer_.short_[i];
                }
            }
        }
        else{
            str << arg.changeable_buffer_.long_;
        }
        return str;
    }


private:
    bool On_heap() const {
        // little endian so the last_byte is the first byte of address
        const uint8_t* last_byte = reinterpret_cast<const uint8_t*>(&changeable_buffer_);
        return ( !((*last_byte) & 1) );
    }

    union Buffer{
        Buffer() : long_(nullptr) { }

        char* long_;
        char short_[BUFFSIZE]; // initialized with 0
    } changeable_buffer_;
};

int main(){

    String a;

    String b ("G");

    String c ("verylonglongtest");

    std::cout << b << "\n" << c << std::endl;

    return 0;
}
