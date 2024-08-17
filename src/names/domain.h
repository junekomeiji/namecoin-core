//Copyright (c) 2024 Rose Turing

#ifndef H_BITCOIN_NAMES_DOMAIN
#define H_BITCOIN_NAMES_DOMAIN

#include <string>
#include "applications.h"
#include "records.h"
#include <list>

class Domain{
    
    private:
        std::string name;
        std::list<IPv4Record> ipv4s;
        std::list<IPv6Record> ipv6s;
        std::list<NSRecord> namespaces;

    public:
        std::string getName();
        void setName(const std::string& text);

        std::list<IPv4Record> getIPv4s();
        void setIPv4s(const std::list<IPv4Record> ipv4s);
        
        std::list<IPv6Record> getIPv6s();
        void setIPv6s(const std::list<IPv6Record> ipv6s);

        std::list<NSRecord> getNSs();
        void setNSs(const std::list<NSRecord> nss);


        Domain(const std::string& name);

};

#endif //H_BITCOIN_NAMES_DOMAIN
