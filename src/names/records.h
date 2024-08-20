// Copyright (c) 2024 Rose Turing

#ifndef H_BITCOIN_NAMES_RECORDS
#define H_BITCOIN_NAMES_RECORDS

#include <string>

class DomainRecord{

    private:
        std::string domain;

    public:

        std::string getDomain();
        void setDomain(const std::string& text);

        DomainRecord(std::string& domain);
        DomainRecord();

        virtual bool validate() = 0;

};

class IPv4Record : public DomainRecord{

    private:
        std::string address;

    public:
        std::string getIPv4Address();
        void setIPv4Address(const std::string& text);

        IPv4Record(std::string& domain, std::string& address);
        IPv4Record(std::string& domain);
        IPv4Record();

        bool validate() override;
};

class IPv6Record : public DomainRecord{

    private:
        std::string address;

    public:
        std::string getIPv6Address();
        void setIPv6Address(const std::string& text);

        IPv6Record(std::string& domain, std::string& address);
        IPv6Record(std::string& domain);
        IPv6Record();

        bool validate() override;
};

#endif //H_BITCOIN_NAMES_RECORDS
