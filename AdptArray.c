#include <stdio.h>
#include <stdlib.h>
#include "AdptArray.h"
#include <string.h>

#define initializeArray 0 //Defined for clear code

struct AdptArray_{

int sizeOfArray; //size of the array
PElement *dataArray; //the data of the array
COPY_FUNC copyFunc; //built-in function like books etc
DEL_FUNC delFunc; //built-in function like books etc
PRINT_FUNC printFunc; //built-in function like books etc

};

PAdptArray CreateAdptArray(COPY_FUNC copyFunc,DEL_FUNC delFunc,PRINT_FUNC printFunc) {

    PAdptArray adptArray = (PAdptArray) malloc(sizeof(struct AdptArray_)); //allocate memory for struck 
    if (adptArray == NULL) { //if allocate memory for struck fail
        return NULL;
    }

    adptArray->dataArray = (PElement) malloc(initializeArray * sizeof(PElement)); //allocate memory for data array(An array of generic pointers)
    if (adptArray->dataArray == NULL) { //if allocate memory for struck fail
        free(adptArray);
        return NULL;
    }


    adptArray->sizeOfArray = initializeArray; //size array = 0

    ///connect the built-in function -like books etc
    adptArray->copyFunc = copyFunc;
    adptArray->delFunc = delFunc;
    adptArray->printFunc = printFunc;


    return adptArray;

}

void DeleteAdptArray(PAdptArray adptArray) {

    if (adptArray == NULL){
    //printf("adptArray is already Null")
        return;}

    //delete the data of the array that not Null
    for (int i=0; i<adptArray->sizeOfArray; i++) {

        if (adptArray-> dataArray[i] == NULL) 
        {
            continue;
        }

        adptArray->delFunc(adptArray->dataArray[i]); //use the built function to free the data in this index
    }
    free(adptArray->dataArray); //free data of parray(frees the allocated memory)
    free(adptArray); //free parray(free the allocated memory)
}

Result SetAdptArrayAt(PAdptArray adptArray, int index, PElement pElement) {

    // check input 
    if(adptArray == NULL || index<0 || pElement == NULL){
        return FAIL; 
    }


    // if index is bigger than current array size -allocate more space for data array
    if(index >= adptArray->sizeOfArray){
        
        PElement* newDataArray = (PElement*)calloc(index + 1, sizeof(PElement));
       
        //if allocate memory fail
        if (newDataArray == NULL) {
            return FAIL;
        }

        //copy the old dataArray to the new one 
        //function memcpy:
        //newDataArray is a pointer to the memory location where the data will be copied to.
        //adptArray->dataArray is a pointer to the memory location where the data will be copied from.
        //n(THIRD PARAMETER)is the number of bytes to be copied.
        memcpy(newDataArray, adptArray->dataArray, (adptArray->sizeOfArray) * sizeof(PElement));
       
        //free the memory of the old one, and insert the new one 
        free(adptArray->dataArray);
        adptArray->dataArray = newDataArray; 

       
    }
    // if old element in the given index is not null so delete the Pelement 
    if ((adptArray->dataArray)[index] != NULL){
        adptArray->delFunc((adptArray->dataArray)[index]);
    }

    // copy the new given element into the given index 
    (adptArray->dataArray)[index] = adptArray->copyFunc(pElement); 

    // if we changed so update array size. 
    if(index >= adptArray->sizeOfArray){
        adptArray->sizeOfArray = index + 1;
    }

    return SUCCESS; 

}


PElement GetAdptArrayAt(PAdptArray adptArray, int index){
    
    // check input
    if ( index<0 || index>=(adptArray->sizeOfArray) || (adptArray->dataArray)[index] == NULL) {
        //printf("return null\n");
        return NULL;

    }
    
    return adptArray->copyFunc((adptArray->dataArray)[index]); 
}


int GetAdptArraySize(PAdptArray adptArray){

    if(adptArray == NULL) {
        return -1; 
    }
    
    return adptArray->sizeOfArray;
}


void PrintDB(PAdptArray adptArray){

    if (adptArray == NULL) {
        return;
    }

    //Goes through all elements in the DATA array that are not NULL and prints them
    for(int i=0 ; i< adptArray->sizeOfArray; i++)
    {
        if( adptArray->dataArray[i] != NULL){
            adptArray->printFunc(adptArray->dataArray[i]);
        }
    }

}