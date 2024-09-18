// Copyright (c) 2024 Rose Turing
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php

#ifndef H_BITCOIN_NAMES_RECORDS
#define H_BITCOIN_NAMES_RECORDS

#include <string>
#include <iostream>

class DomainRecord{

    private:
        std::string domain;

    public:
        std::string getDomain() const;
        void setDomain(const std::string& text);

        DomainRecord(std::string& domain);
        DomainRecord();

        virtual bool validate() = 0;

};

class AddressRecord : public DomainRecord{

    private:
        std::string address;

    public:
        std::string getAddress() const;
        void setAddress(const std::string& text);

        using DomainRecord::DomainRecord;
        AddressRecord(std::string& domain, std::string& address);

        bool operator==(const AddressRecord& a) const{
    return (this->getAddress() == a.getAddress()) && (this->getDomain() == a.getDomain());
}

        std::ostream& operator<<(std::ostream& os){
            os << this->getAddress() << " " << this->getDomain() << "\n";
            return os;
        }

        virtual bool validate() override = 0;
};

class IPv4Record : public AddressRecord{

    public:
        using AddressRecord::AddressRecord;
        bool validate() override;
};

class IPv6Record : public AddressRecord{

    public:
        using AddressRecord::AddressRecord;
        bool validate() override;
};

#endif //H_BITCOIN_NAMES_RECORDS
