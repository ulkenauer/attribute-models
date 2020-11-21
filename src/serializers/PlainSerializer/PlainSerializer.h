//
// Created by ulkenauer on 14.11.2020.
//

#ifndef UNTITLED_PLAINSERIALIZER_H
#define UNTITLED_PLAINSERIALIZER_H


#include "../ISerializer.h"

class PlainSerializer : public virtual ISerializer {
private:
    std::map<std::string, AttributeSerializer> attributeSerializers;

    int __indentation = 0;
public:
    PlainSerializer();

    std::string serialize(AttributeTree attributes) override;

    AttributeTree deserialize(std::string serialized) override;
};


#endif //UNTITLED_PLAINSERIALIZER_H
