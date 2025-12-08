#include <iostream>
#include <sstream>
#include <string>
#include <cctype>

class numfilterbuf : public std::streambuf {
private:
    std::istream *in;
    std::ostream *out;
    
    int elem ; 
    
protected:
    virtual int overflow(int c) override {
        
        if (c == traits_type::eof()) {
            return traits_type::eof();
        }
        
        if (std::isdigit(static_cast<unsigned char>(c)) || std::isspace(static_cast<unsigned char>(c))) {
            out->put(static_cast<char>(c));
            return c;
        }
        
        return c; 
    }
    
  
    
   
    virtual int uflow() override {
        int c = underflow();
        if (c != traits_type::eof()) {
            elem = traits_type::eof(); 
        }
        return c;
    }
     
    virtual int underflow() override {
        if (elem == traits_type::eof()) {
            while (true) {
                int c = in->get();
                if (c == traits_type::eof()) {
                    return traits_type::eof();
                }
                
                
                if (std::isdigit(static_cast<unsigned char>(c)) || std::isspace(static_cast<unsigned char>(c))) {
                    elem = c;
                    return elem;
                }
              
            }
        }
        return elem;
    }
    
public:
    numfilterbuf(std::istream &_in, std::ostream &_out)
        : in(&_in), out(&_out), elem(traits_type::eof())
    {}
};

int main(int argc, char **argv){
    const char str1[] = "a 12 w 3 2 ehws 7";
    std::istringstream str(str1);
    
    numfilterbuf buf(str, std::cout); 
    std::iostream numfilter(&buf); 
    
    std::string val;
    std::getline(numfilter, val);
    numfilter.clear(); 
    
    std::cout << "Original: '" << str1 << "'" << std::endl;
    std::cout << "Read from numfilter: '" << val << "'" << std::endl;
    
    return 0;
}
