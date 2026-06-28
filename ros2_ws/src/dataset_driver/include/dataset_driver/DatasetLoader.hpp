//Abstract interface
//Extracts raw data at sensor level

#pragma once

#include<string>

class DatasetLoader{
    public:
    //Destructor
    virtual ~DatasetLoader()=default;

    //Open the dataset
    virtual bool open(const std::string& path)=0;

    //Reset playback to beginning
    virtual bool reset()=0;

    //does next data exist in dataset?
    virtual bool hasNext() const = 0;
    private:
}