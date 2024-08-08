//Copyright (c) 2024 Rose Turing

#ifndef H_BITCOIN_NAMES_DOMAIN
#define H_BITCOIN_NAMES_RECORDS

#include <string>
#include "applications.h"
#include "records.h"
#include <list>

class Domain{
    
    private:
        std::string name;
        std::list<IPRecord> ips;
        std::list<NSRecord> namespaces;

    public:
        std::string getName();
        void setName(const std::string& text);

        std::list<IPRecord> getIPs();
        void setIPs(const std::list<IPRecord> ips);
        
        std::list<NSRecord> getNSs();
        void setNSs(const std::list<NSrecord> nss);
};

#endif //H_BITCOIN_NAMES_DOMAI
