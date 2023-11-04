//This file contains the implementation of the table class

#include "table.hpp"
#include <vector>
#include <string>
#include <iostream>

//expects a comma separated list: "example, example, example"
//pushes a vector ["example", "example", "example"] onto data
table::table(const std::string& input){
    //create result vector
    std::vector<std::string> result;
    //vector population loop
    size_t i = 0;
    while (input[i] != 0) {
        //element variable (populated until a comma is encountered)
        std::string element = "";
        if (input[i] == ',') {
            result.push_back(element);
            element = "";
        }
        element.push_back(input[i]);
        ++i;
    }
    //push result to data
    data.push_back(result);
}

//copy constructor makes a deep copy of original.data
table::table(const table& original){
    for (size_t i = 0; i < original.data.size(); ++i) {
        data.push_back(original.data[i]);
    }
}

//adds a column to the table with a specified name
//the rest of the rows are blank by default
void table::addColumn(const std::string& name) {
    std::vector<std::vector<std::string>>::iterator iter = data.begin();
    //push back header
    (*iter).push_back(name);
    ++iter;
    //add extra empty element to the rest of the table
    for (iter; iter < data.end(); ++iter) {
        (*iter).push_back("");
    }
}

//finds a column with a given name and removes it from the table
void table::removeColumn(const std::string& name){
    //find index of the column with a given name
    size_t index = 0;
    for (index; index < data.size(); ++index) {
        if (data[0][index] == name) {break;}
    }
    //return if name is not in the header row
    if (index == data.size()) {return;}
    //remove column from each row
    std::vector<std::vector<std::string>>::iterator iter = data.begin();
    ++iter;//skip header row
    for (iter; iter < data.end(); ++iter) {
        (*iter).erase((*iter).begin()+index);
    }
}

//pushes a vector to data
//adds additional empty elements to match columns
//truncates row if there are too many elements
//TODO: overload for std::string comma separated list 
void table::pushRow(const std::vector<std::string>& row) {
    std::vector<std::string> result = row;
    //match vector to data
    if (row.size() > data[0].size()){
        result.erase(result.begin()+data.size(), result.end());
    } else if (row.size() < data[0].size()) {
        for (size_t i = result.size(); i < data[0].size(); ++i) {
            result.push_back("");
        }
    }
    data.push_back(result);
}

std::vector<std::string> table::popRow(){
    std::vector<std::string> result = data[1];
    data.erase(data.begin()+1);
    return result;
}

//displays the table in the ostream provided
std::ostream& table::display(std::ostream& out) const {
    //find the length of the longest string in the table
    int longest = 0;
    std::vector<std::vector<std::string>>::iterator iti = data.begin();
    for (iti; iti < data.end(); ++iti) {
        std::vector<std::string>::iterator itj = (*iti).begin();
        for (itj; itj < (*iti).end(); ++itj) {
            if ((*itj).length() > longest) {longest = (*itj).length();}
        }
    }
    //display the table 
    //header row
    out << "+"; 
    for (size_t i = 0; i < (longest+2)*data[0].size(); ++i) {out << "-";}
    out << "+";
    out << std::endl;
    out << "| ";
    std::vector<std::string>::iterator ith = data[0].begin();
    for (ith; ith < data[0].end(); ++ith) {
        out << *ith;
        for (size_t i = 0; i < longest-(*ith).length(); ++i) {
            out << " ";
        }
        out << " | ";
    }
    out << std::endl;
    out << "+";
    for (size_t i = 0; i < (longest+2)*data[0].size(); ++i) {out << "-";}
    out << "+";
    out << std::endl;
    //all other rows
    std::vector<std::vector<std::string>>::iterator iti = data.begin();
    ++iti;//skip header row
    for (iti; iti < data.end(); ++iti) {
        std::vector<std::string>::iterator itj = (*iti).begin();
        out << "| ";
        for (itj; itj < (*iti).end(); ++itj) {
            out << *itj;
            for (size_t i = 0; i < longest-(*ith).length(); ++i) {
                out << " ";
            }
            out << " | ";
        }
        out << std::endl;
    }
    out << "+";
    for (size_t i = 0; i < (longest+2)*data[0].size(); ++i) {out << "-";}
    out << "+";
    out << std::endl;
    return out;
}

table& table::operator=(table rhs){
    data = rhs.data;
    return *this;
}

std::vector<std::string>& table::operator[](int index){
    return data[index]; 
}

std::vector<std::string> table::operator[](int index) const {
    return data[index];
}

table& table::operator+=(const table& rhs) {
    std::vector<std::vector<std::string>>::iterator iter = rhs.data.begin();
    for (iter; iter < rhs.data.end(); ++iter) {
        data.push_back(*iter);
    }
    return *this;
}

bool table::operator==(const table& rhs) const {
    if (rhs.data.size() != data.size()) {return false;}
    if (rhs.data[0].size() != data[0].size()) {return false;}
    for (size_t i = 0; i < data.size(); ++i) {
        for (size_t j = 0; j < data[0].size(); ++j) {
            if (rhs.data[i][j] != data[i][j]) {return false;}
        }
    }
    return true;
}

table operator+(table lhs, const table& rhs){
    table result(lhs);
    return result += rhs;
}

bool operator!=(const table& lhs, const table& rhs) {
    return !(lhs == rhs);
}

int table::getSize() {
    return data.size();
}
