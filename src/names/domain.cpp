//Copyright (c) 2024 Rose Turing

#include "applications.h"
#include "domain.h"
#include "records.h"
#include <string>
#include <list>

std::string Domain::getName(){
    return name;
}

void Domain::setName(const std::string& text){
    this->name = text;
}

std::list<IPRecord> Domain::getIPs(){
    return this->ips;
}

void Domain::setIPs(const std::list<IPRecord> ips){
    this->ips = ips;
}
        
std::list<NSRecord> Domain::getNSs(){
    return this->namespaces;
}

void Domain::setNSs(const std::list<NSRecord> nss){
    this->namespaces = nss;
}

Domain::Domain(const std::string& name){

}


