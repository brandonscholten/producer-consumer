#ifndef TABLE_HPP
#define TABLE_HPP

//This file contains the class for a table ADT which will be used
//to visualize the producer and consumer's actions 

#include <vector>
#include <string>
#include <iostream>

class table {
    public:
        table() : data(0) {};
        table(const std::string&);  //string constructor
        table(const table&);        //copy constructor

        void addColumn(const std::string&);             //add a column with name provided
        void removeColumn(const std::string&);          //remove the column containing name provided
        void pushRow(const std::vector<std::string>&);  //add a row to the bottom of the table
        int getSize();                                  //return the number of rows in the table
        std::vector<std::string> popRow();              //remove a row from the top of the table and return it
        std::ostream& display(std::ostream&) const;     //display the state of the table to the provided ostream

        table& operator=(table);                        //assignment operator
        std::vector<std::string>& operator[](int);      //Accessor/Modifier
        std::vector<std::string> operator[](int) const; //Accessor
        table& operator+=(const table&);                //+= operator
        bool operator==(const table&) const;            //check if tables are equal

    private:
        std::vector<std::vector<std::string>> data; 
};
table operator+(table, const table&);
bool operator!=(const table&, const table&);

#endif
