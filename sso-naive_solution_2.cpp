#include <iostream>

const int BUFFSIZE = 8;

class String {
public:
    String() : sso_(true) { }

    String(const char* arg) {
        size_t arg_len = strlen(arg);

        if(arg_len < BUFFSIZE){
            strcpy(changeable_buffer_.short_, arg);
            sso_ = true;
        }
        else{
            changeable_buffer_.long_ = new char[arg_len + 1];
            strcpy(changeable_buffer_.long_, arg);
            sso_ = false;
        }
    }

    ~String() {
        if(!sso_){
            delete [] changeable_buffer_.long_;
        }
    }

    friend std::ostream& operator<<(std::ostream& str, const String& arg) {
        if (arg.sso_) {
            str << arg.changeable_buffer_.short_;
        }
        else{
            str << arg.changeable_buffer_.long_;
        }
        return str;
    }

private:
    union Buffer{
        Buffer() : long_(nullptr) { }

        char* long_;
        char short_[BUFFSIZE];
    } changeable_buffer_;

    bool sso_;
};

int main(){

    String a;

    String b ("test");

    String c ("verylonglongtest");

    std::cout << b << "\n" << c << std::endl;

    return 0;
}
