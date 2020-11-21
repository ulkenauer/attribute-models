//
// Created by ulkenauer on 14.11.2020.
//

#include "../../attribute/types.h"

#include "PlainSerializer.h"
#include "../../attribute/HasAttributes.h"

std::string serialize__TYPE_STRING__(AttributeNode node)
{
    return * (std::string*) node.data.get();
}

std::string serialize__TYPE_INTEGER__(AttributeNode node)
{
//    throw -1;
    return std::to_string(* (int *) node.data.get());
}

std::string serialize__TYPE_DOUBLE__(AttributeNode node)
{
    return std::to_string(* (double *) node.data.get());
}

std::string serialize__TYPE_NODE__(AttributeNode node)
{
//    if(node.data == nullptr) {
//        return "nullptr";
//    }
//    return "object";
    throw -1;
    return "";
}

PlainSerializer::PlainSerializer()
{
    this->attributeSerializers = std::map<std::string, AttributeSerializer>();
    this->attributeSerializers[__TYPE_STRING__] = &serialize__TYPE_STRING__;
    this->attributeSerializers[__TYPE_INTEGER__] = &serialize__TYPE_INTEGER__;
    this->attributeSerializers[__TYPE_DOUBLE__] = &serialize__TYPE_DOUBLE__;
    this->attributeSerializers[__TYPE_NODE__] = &serialize__TYPE_NODE__;
}

std::string PlainSerializer::serialize(AttributeTree attributes) {
    //    TODO: unwrap node serialization recursive call
    std::string serialized = std::string();
    std::string indentation = "";

    for(int i = 0; i < this->__indentation; i++) {
        indentation += "    ";
    }

    for(auto i = attributes.begin(); i != attributes.end(); i++) {

        const std::string key = i->first;
        const AttributeNode node = i->second;

        if(node.nodeType == __TYPE_NODE__) {
            auto child = (HasAttributes *) node.data.get();
            if(child == nullptr) {
                serialized += indentation + key + "[" + node.nodeType + "]" + ": " + "nil" + "\n";
            } else {
                this->__indentation++;
                serialized += indentation + key + "[" + node.nodeType + "]" + ": " + "\n" + this->serialize(child->getAttributes());
                this->__indentation--;
//                serialized += this->serialize(child->getAttributes());
            }
        } else {
            serialized += indentation + key + "[" + node.nodeType + "]" + ": " + this->attributeSerializers[node.nodeType](node) + "\n";
        }

    }

    return serialized;
}

AttributeTree PlainSerializer::deserialize(std::string serialized) {
    throw -1;
    return AttributeTree();
}
