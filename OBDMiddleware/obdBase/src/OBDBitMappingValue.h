#ifndef OBDBITMAPPINGVALUE_H_
#define OBDBITMAPPINGVALUE_H_

class OBDBitMappingValue
{
    public:
        OBDBitMappingValue();
        virtual ~OBDBitMappingValue();

        void interpretToValue(std::vector<uint8_t> input);
        void interpretToByteArray(double value);
};

#endif /* OBDBITMAPPINGVALUE_H_ */
