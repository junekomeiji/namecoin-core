// Copyright (c) 2024 Rose Turing

#include "records.h"
#include "applications.h"
#include <string>
 
std::string Record::getDomain(){
    return domain;
}

void Record::setDomain(const std::string& text){
    domain = text;
}

Record::Record(std::string& domain){
    this->domain = domain;
}

std::string IPRecord::getIPV4(){
    return IPV4;    
}

std::string IPRecord::getIPV6(){
    return IPV6;    
}

void IPRecord::setIPV4(const std::string& text){
    if(IsValidIPV4(text)){
        this->IPV4 = text;
    }
}

void IPRecord::setIPV6(const std::string& text){
    if(IsValidIPV6(text)){
        this->IPV6 = text;
    }
}
        
IPRecord::IPRecord(std::string& domain, std::string& ip)
    :Record(domain)
{
    if(IsValidIPV4(ip)){
        this->IPV4 = ip;
    } else if(IsValidIPV6(ip)){
        this->IPV6 = ip;
    }
}

bool IPRecord::validate() {
    return IsValidIPV4(this->IPV4) | IsValidIPV6(this->IPV6);
}


