//*****************************************************************
// File:   Logger.hpp
// Author: J. Ezpeleta-Unizar
// Date:   March 2017
// Coms:   A (monitor) class for the concurrent access to log files
//         The interesting thing is the way a FIFO access is granted to
//         the monitor. See class code
//*****************************************************************

#pragma once

#include <atomic>
#include <chrono>
#include <condition_variable>
#include <fstream>
#include <iostream>
#include <map>
#include <mutex>
#include <sstream>
#include <thread>
#include <vector>

class Logger {
  private:
    //----- for mutex access to monitor functions
    std::mutex mtx;
    //----- message buffer
    const int MAX_MESS = 4096; //buffer bound
    int nMess;                 //number of messages in the buffer
    std::string *messages;     //message buffer
    //----- to output messages
    std::string logName;   //the name of the log file
    std::ofstream logFile; //stream to the log file>
    bool echoed;           //Should the message be echoed?
    std::ostream *echo;    //stream for echoed messages
    //----- for handling the order of arrival
    std::atomic<uint64_t> ticketCounter; //increments one per process and access
    uint64_t next;                       //next ticket value having acces right
    //each waiting process will add the pair <numTicket,condVar> and then lock on the second component
    std::map<uint64_t, std::condition_variable *> waitingMap;
    //----------------------------------------------------------
    //Pre:
    //Post: Creates the log file. If it already exists, its contents are emptied.
    void createLogFile() {

        logFile.open(logName);
        if (logFile.fail()) {
            std::runtime_error("Problems with file " + logName + "\n");
        }
        logFile.exceptions(logFile.exceptions() | std::ios::failbit | std::ifstream::badbit);

        logFile << HEADER << std::endl;
        logFile.close();
    }
    //-------------------------
    //Pre:
    //Post: Saves the contents of "messages" into the log file and clears it
    void save() {

        logFile.open(logName, std::ios::out | std::ios::app);
        if (logFile.fail()) {
            std::runtime_error("Problems with file " + logName + "\n");
        }
        logFile.exceptions(logFile.exceptions() | std::ios::failbit | std::ifstream::badbit);

        for (size_t i = 0; i < nMess; i++) {
            logFile << messages[i] << std::endl;
        }
        nMess = 0;
        logFile.close();
    }
    //-------------------------
    //Pre:
    //Post: Splits "s" using "sep" as the separator char, and returns
    //      the vector of the components
    std::vector<std::string> split(const std::string &s, char sep) {
        std::vector<std::string> elems;
        std::string el;
        std::istringstream seqEls(s);
        while (std::getline(seqEls, el, sep)) {
            elems.push_back(el);
        }
        return elems;
    }
    //-------------------------
    //log file header, describing event structure
    //according to the requirements of the DLTL model checker
    const std::string HEADER = "ID,event,sectionID,val,procID,ts,ticket";

  public:
    //------------------------- constructor
    //Pre:
    //Post: Creates the logger and associates the message ouput to the file "logName"
    //for non-echoed messages
    Logger(std::string logName) : logName(logName) {

        messages = new std::string[MAX_MESS];
        echoed = false;
        ticketCounter = 1;
        next = 1;
        nMess = 0;
        createLogFile();
    }

    //Pre:
    //Post: creates the logger and associates the message ouput to the file "logName".
    //      Messages, besides stored in the f, will be echoed.
    //      Usually, "echo" will be either "cout" or "cerr", but it is not mandatory
    Logger(std::string logName, std::ostream &echo) : logName(logName), echo(&echo) {

        messages = new std::string[MAX_MESS];
        echoed = true;
        ticketCounter = 1;
        next = 1;
        nMess = 0;
        createLogFile();
    }

    //------------------------- destructor
    //Pre:
    //Post: free everything
    ~Logger() {
        save();            //write pending messages
        delete[] messages; //free buffer memory
    }

    //-------------------------
    //Pre:
    //Post: Adds a new message to the log (in a buffered way)
    //      ";" and "\n" chars are separators, indicating different events in the string
    void addMessage(std::string mess) {

        uint64_t myTicket;
        const uint64_t uno(1);
        std::chrono::nanoseconds ns;
        std::condition_variable *theCond;
        std::map<uint64_t, std::condition_variable *>::iterator it;
        //----------------------------------------------------------
        //Next two sentences are "thread safe"
        //Next sentence provides a unique ticket for the thread
        myTicket = atomic_fetch_add(&ticketCounter, uno);
        ns = std::chrono::duration_cast<std::chrono::nanoseconds>(
            std::chrono::system_clock::now().time_since_epoch());

        //----------------------------------------------------------
        //Ensure mutex access to data
        std::unique_lock<std::mutex> lck(mtx);

        //Is it my turn?
        if (myTicket != next) { //No: I have to lock and wait
            theCond = new std::condition_variable();

            std::pair<uint64_t, std::condition_variable *> thePair(myTicket, theCond);
            waitingMap.insert(thePair);
            //locking me in my own var condition
            theCond->wait(lck);

            //find me, and remove me from the queue
            it = waitingMap.find(myTicket);
            waitingMap.erase(it);
            //My condition var is not needed any more
            delete theCond;
        }
        //It's my turn: myTicket=next
        //If buffer is full, save it
        if (nMess == MAX_MESS) {
            save();
        }

        const char SEP = ',';
        const std::string ID("idUnico");

        std::vector<std::string> event_list = split(mess, ';');
        for (size_t i = 0; i < event_list.size(); i++) {
            std::stringstream ss;
            ss << ID << SEP << event_list[i] << SEP << std::this_thread::get_id() << SEP << ns.count() << SEP << myTicket;
            messages[nMess] = ss.str();
            nMess++;
            if (echoed) {
                *echo << ss.str() << std::endl;
            }
        }

        next++;
        //Look for the next turn process
        it = waitingMap.find(next);
        if (it != waitingMap.end()) { //Is the next waiting?
            it->second->notify_one();
        }
    }
};
