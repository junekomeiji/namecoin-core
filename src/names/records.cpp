// Copyright (c) 2024 Rose Turing

#include "records.h"
#include "applications.h"
#include <string>
 
std::string DomainRecord::getDomain(){
    return domain;
}

void DomainRecord::setDomain(const std::string& text){
    domain = text;
}

DomainRecord::DomainRecord(std::string& domain){
    this->domain = domain;
}

DomainRecord::DomainRecord(){
    this->domain = "";
}

std::string IPv4Record::getIPv4Address(){
    return address;    
}

void IPv4Record::setIPv4Address(const std::string& text){
    this->address = text;
}
       
IPv4Record::IPv4Record(std::string& domain, std::string& address)
    :DomainRecord(domain)
{
    this->address = address;
}

IPv4Record::IPv4Record(std::string& domain)
    :DomainRecord(domain)
{
    this->address = "";
}

IPv4Record::IPv4Record()
    :DomainRecord()
{
    this->address = "";
}

bool IPv4Record::validate() {
    return IsValidIPV4(this->address);
}

std::string IPv6Record::getIPv6Address(){
    return address;    
}

void IPv6Record::setIPv6Address(const std::string& text){
    this->address = text;
}
 
IPv6Record::IPv6Record(std::string& domain, std::string& address)
    :DomainRecord(domain)
{
    this->address = address;
}

IPv6Record::IPv6Record(std::string& domain)
    :DomainRecord(domain)
{
    this->address = "";
}

IPv6Record::IPv6Record()
    :DomainRecord()
{
    this->address = "";
}

bool IPv6Record::validate() {
    return IsValidIPV6(this->address);
}

std::string NSRecord::getNS(){
    return this->ns;
}

void NSRecord::setNS(const std::string& text){
    this->ns = text;
}

NSRecord::NSRecord(std::string& domain, std::string& ns)
    :DomainRecord(domain)
{
    this->ns = ns;
}

NSRecord::NSRecord(std::string& domain)
    :DomainRecord(domain)
{
    this->ns = "";
}

NSRecord::NSRecord()
    :DomainRecord()
{
    this->ns = "";
}

//TODO: jeremy my man i have no idea how to validate this
bool NSRecord::validate(){
    return false;
}
 
