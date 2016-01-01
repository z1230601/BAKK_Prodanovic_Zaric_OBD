#ifndef OBDCOMMAND_H_
#define OBDCOMMAND_H_

#include <string>

class ObdCommand
{
    public:
        ObdCommand();
        virtual ~ObdCommand();

        //should not be void just for now till spcified
        void interpretReceivedBytes(uint8_t data[]);
        void convertToSendableByteArray();
        void getRequestString();



    private:
        std::string description_;
        unsigned int pid_;
        std::vector<unsigned int> sids_;
        std::map<unsigned int, bool> validity_mapping_;


};

#endif /* OBDCOMMAND_H_ */
