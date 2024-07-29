// Copyright (c) 2024 Rose Turing

#ifndef H_BITCOIN_NAMES_RECORDS
#define H_BITCOIN_NAMES_RECORDS

#include <string>

class Record{

    private:
        std::string domain;

    public:

        std::string getDomain();
        void setDomain(const std::string& text);

        Record(std::string& domain);
        
        virtual bool validate();
};

class IPRecord : public Record{
    
    private:
        std::string IPV4;
        std::string IPV6;

    public:
        std::string getIPV4();
        std::string getIPV6();
        
        void setIPV4(const std::string& text);
        void setIPV6(const std::string& text);

        IPRecord(std::string& domain, std::string& ip);

        bool validate();
};

#endif //H_BITCOIN_NAMES_RECORDS
