#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <ctime>
#include "main.h"

using namespace std;

// How the queries are distributed matters more than the actual input size

int main(int argc, const char * argv[]) {
    
    try{
        
        string filename = argv[1];
        int element;
        int numOfElements;
        int numOfQueries;
        int query;
        
        // Open file
        ifstream inputFile;
        inputFile.open(filename.c_str());
        
        if(!inputFile){
            cerr << "Unable to open file" << endl;
        }
        
        // Read in number of elements
        inputFile >> numOfElements;
        
        // Make ordered list and MTF list
        MtfList <int> mList;
        OrderedList <int> ordList(numOfElements);
        
        // Insert elements from documents into both lists
        for( int i = 0; i < numOfElements; i++){
            inputFile >> element;
            mList.insert(element);
            ordList.insert(element);
        }
        
        // Sort ordered list
        ordList.mergeSort(0, (ordList.size() - 1));
        
        // Read number of queries
        inputFile >> numOfQueries;
         
        // Declare time variables
        clock_t mtfStart;
        clock_t mtfEnd;
        double mtfTotalTime = 0;
        
        clock_t ordStart;
        clock_t ordEnd;
        double ordTotalTime = 0;
        
        cout << fixed << setprecision(8);
        
        // Read queries
        for( int i = 0; i < numOfQueries; i++ ){
            inputFile >> query;
            
            mtfStart = clock();
            mList.searchMove(query);
            mtfEnd = clock();
            mtfTotalTime += ((double)(mtfEnd - mtfStart)/CLOCKS_PER_SEC);
            
            ordStart = clock();
            ordList.binSearch(query);
            ordEnd = clock();
            ordTotalTime += ((double)(ordEnd - ordStart)/CLOCKS_PER_SEC);
        }
    
        cout << "MTF Time: " << mtfTotalTime << endl;
        cout << "Ordered List Time: " << ordTotalTime << endl;
        
        
        cout << "Faster List: ";
        if( mtfTotalTime < ordTotalTime){
            cout << "MTF List" << endl;
        }
        else if(ordTotalTime < mtfTotalTime){
            cout << "Ordered List" << endl;
        }
        else{
            cout << "Same speed" << endl;
        }
        
        // Other Potential Time Checker
        
        /*
         chrono::high_resolution_clock::time_point mtfStart;
         chrono::high_resolution_clock::time_point mtfEnd;
         chrono::duration<double> mtfTotalTime = chrono::duration_cast<chrono::duration<double>>(mtfEnd - mtfStart);
         
         chrono::high_resolution_clock::time_point ordStart;
         chrono::high_resolution_clock::time_point ordEnd;
         chrono::duration<double> ordTotalTime = chrono::duration_cast<chrono::duration<double>>(ordEnd - ordStart);
         
         // Read queries
         for( int i = 0; i < numOfQueries; i++ ){
         inputFile >> query;
         
         mtfStart = chrono::high_resolution_clock::now();
         mList.searchMove(query);
         mtfEnd = chrono::high_resolution_clock::now();
         mtfTotalTime += chrono::duration_cast<chrono::duration<double>>(mtfEnd - mtfStart);
         
         ordStart = chrono::high_resolution_clock::now();
         ordList.binSearch(query);
         ordEnd = chrono::high_resolution_clock::now();
         ordTotalTime += chrono::duration_cast<chrono::duration<double>>(ordEnd - ordStart);
         }
         
         cout << "MTF Time: " << mtfTotalTime.count() << endl;
         cout << "Ordered List Time: " << ordTotalTime.count() << endl;
         
         
         cout << "Faster List: ";
         if( mtfTotalTime.count() < ordTotalTime.count()){
         cout << "MTF List" << endl;
         }
         else if(ordTotalTime.count() < mtfTotalTime.count()){
         cout << "Ordered List" << endl;
         }
         else{
         cout << "Same speed" << endl;
         }
         */
        
        
        return 0;
        
        
    } // try
    
    catch ( NoSuchObject& e ){
        cout << e.what() << endl;
    }
    catch ( invalid_argument& e ){
        cout << "Invalid argument: " << e.what() << endl;
    } // catch
    catch ( logic_error& e ){
        cout << "Logic error: " << e.what() << endl;
    } // catch
    catch ( bad_alloc& e){
        cout << "Bad alloc: " << e.what() << endl;
    }
    catch (...){
        cout << "Unkown exception!" << endl;
    } // catch
    
    return 0;
    
}
