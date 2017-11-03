#include <iostream>

const int BUFFSIZE = 8;

class String {
public:
    String() : data_(nullptr), sso_(true) { }

    String(const char* arg) {
        size_t arg_len = strlen(arg);

        if(arg_len < BUFFSIZE){
            strcpy(buf_, arg);
            sso_ = true;
        }
        else{
            data_ = new char[arg_len + 1];
            strcpy(data_, arg);
            sso_ = false;
        }
    }

    ~String() {
        if(!sso_){
            delete[] data_;
        }
    }

    friend std::ostream& operator<<(std::ostream& str, const String& arg) {
        if (arg.sso_){
            str << arg.buf_;
        }
        else{
            str << arg.data_;
        }
        return str;
    }

private:
    char* data_;
    char buf_[BUFFSIZE];
    bool sso_;
};

int main(){
    String a;

    String b ("test");

    String c ("verylonglongtest");

    std::cout << b << "\n" << c << std::endl;

    return 0;
}
