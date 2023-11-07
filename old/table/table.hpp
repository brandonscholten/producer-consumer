#ifndef TABLE_HPP
#define TABLE_HPP

//This file contains the class for a table ADT which will be used
//to visualize the producer and consumer's actions 

#include <vector>
#include <string>
#include <iostream>

//TODO: create a struct to serialize data such that it can be used with IPC
//      https://stackoverflow.com/questions/53866421/interprocess-communication-passing-c-style-structs-vs-c-objects


class table {
    public:
        table(const std::string&);  //string constructor
        table(const table&);        //copy constructor

        void addColumn(const std::string&);             //add a column with name provided
        void removeColumn(const std::string&);          //remove the column containing name provided
        void pushRow( const std::vector<std::string>&);         //add a row to the bottom of the table
        int getSize();                                  //return the number of rows in the table
        std::vector<std::string> popRow();              //remove a row from the top of the table and return it
        std::ostream& display(std::ostream&);           //display the state of the table to the provided ostream

        table& operator=(table);                        //assignment operator
        std::vector<std::string>& operator[](int);      //Accessor/Modifier
        std::vector<std::string> operator[](int) const; //Accessor
        table& operator+=(table&);                      //+= operator
        bool operator==(const table&) const;            //check if tables are equal

    private:
        std::vector<std::vector<std::string>> data = std::vector<std::vector<std::string>>(10); 
};
table operator+(table, const table&);
bool operator!=(const table&, const table&);

#endif
