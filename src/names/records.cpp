// Copyright (c) 2024 Rose Turing

#include <records.h>
#include <applications.h>

class Record {
    
    private:
        std::string domain;

    public:

        std::string getDomain(){
            return domain;
        }

        void setDomain(const std::string& text){
            domain = text;
        }

        Record(std::string& domain){
            this->domain = domain;
        }

        virtual bool validate();

};

class IPRecord : public Record{
 
    private:
        std::string IPV4;
        std::string IPV6;

    //TODO: setter, getter, 

    public:

        std::string getIPV4(){
            return IPV4;    
        }

        std::string getIPV6(){
            return IPV6;    
        }

        void setIPV4(const std::string& text){
            if(IsValidIPV4(text){
                text = IPV4;
            }
        }

        void setIPV6(const std::string& text){
            if(IsValidIPV6(text){
                text = IPV6;
            }
        }
        
        IPRecord(std::string& domain, std::string& ip){
            this.setDomain(domain);
            if(IsValidIPV4(ip)){
                this->IPV4 = ip;
            } else if(IsValidIPV6(ip)){
                this->IPV6 = ip;
            }
        }

        bool validate(){
            return IsValidIPV4(this->IPV4) | IsValidIPV6(this->IPV6)
        }

};
