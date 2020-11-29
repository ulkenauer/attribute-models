#include <iostream>
#include "../../../../library.h"
#include <string>
#include "../models/Model.h"

int main()
{
    std::map<std::string, ISerializer*> knownSerializers;

    knownSerializers["plain"] = new PlainSerializer();

    std::string expected =    "ATTR_CHILD[__TYPE_NODE__]: \n"
                            "    ATTR_CHILD[__TYPE_NODE__]: nil\n"
                            "    ATTR_NAME[__TYPE_STRING__]: level 1\n"
                            "    ATTR_QUANTITY[__TYPE_INTEGER__]: 1\n"
                            "ATTR_NAME[__TYPE_STRING__]: level 0\n"
                            "ATTR_QUANTITY[__TYPE_INTEGER__]: 0\n";

    std::string original =  "ATTR_CHILD[__TYPE_NODE__]: \n"
                            "    ATTR_NAME[__TYPE_STRING__]: level 1\n"
                            "    ATTR_NAME_FOO[__TYPE_STRING__]: level 1\n"
                            "    ATTR_CHILD[__TYPE_NODE__]: \n"
                            "        ATTR_CHILD[__TYPE_NODE__]: \n"
                            "            ATTR_NAME[__TYPE_STRING__]: level3\n"
                            "            ATTR_QUANTITY[__TYPE_INTEGER__]: 3\n"
                            "        ATTR_NAME[__TYPE_STRING__]: level2\n"
                            "        ATTR_QUANTITY[__TYPE_INTEGER__]: 2\n"
                            "    ATTR_QUANTITY[__TYPE_INTEGER__]: 1\n"
                            "ATTR_NAME[__TYPE_STRING__]: level 0\n"
                            "ATTR_QUANTITY[__TYPE_INTEGER__]: 0\n";

    Model model = Model();

    model.fromAttributeTree(knownSerializers["plain"]->deserialize(original));
    model.child->child = nullptr;

    std::string result = knownSerializers["plain"]->serialize(model.toAttributeTree());

    std::cout << "Got model: " << std::endl << original << std::endl;

    std::cout << "Expected result: " << std::endl << expected << std::endl;

    std::cout << "Result after deserialization/serialization: " << std::endl << result << std::endl;

    std::cout << (result.compare(expected) == 0 ? "All went ok" : "Something is off") << std::endl;

    return 0;
}