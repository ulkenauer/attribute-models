#include <iostream>
#include "../../../library.h"
#include <fstream>
#include <streambuf>
#include "models/Model.h"

int main()
{
    std::map<std::string, ISerializer*> knownSerializers;

    knownSerializers["plain"] = new PlainSerializer();

//    std::string a = "ATTR_CHILD[__TYPE_NODE__]: \n"
//                    "    ATTR_CHILD[__TYPE_NODE__]: nil\n"
//                    "    ATTR_NAME[__TYPE_STRING__]: child model\n"
//                    "    ATTR_QUANTITY[__TYPE_INTEGER__]: 1336\n"
//                    "ATTR_NAME[__TYPE_STRING__]: qwerty\n"
//                    "ATTR_QUANTITY[__TYPE_INTEGER__]: 3\n";

//    std::string a = "ATTR_CHILD[__TYPE_NODE__]: \n"
//                    "    ATTR_NAME[__TYPE_STRING__]: level 1\n"
//                    "    ATTR_NAME_FOO[__TYPE_STRING__]: level 1\n"
//                    "    ATTR_CHILD[__TYPE_NODE__]: \n"
//                    "        ATTR_CHILD[__TYPE_NODE__]: \n"
//                    "            ATTR_NAME[__TYPE_STRING__]: level3\n"
//                    "            ATTR_QUANTITY[__TYPE_INTEGER__]: 3\n"
//                    "        ATTR_NAME[__TYPE_STRING__]: level2\n"
//                    "        ATTR_QUANTITY[__TYPE_INTEGER__]: 2\n"
//                    "    ATTR_QUANTITY[__TYPE_INTEGER__]: 1\n"
//                    "ATTR_NAME[__TYPE_STRING__]: level 0\n"
//                    "ATTR_QUANTITY[__TYPE_INTEGER__]: 0\n";

    const std::string filename = "serialized.txt";
    std::ifstream t(filename);
    std::string str;

    t.seekg(0, std::ios::end);
    str.reserve(t.tellg());
    t.seekg(0, std::ios::beg);

    std::cout << str << std::endl;
    str.assign((std::istreambuf_iterator<char>(t)),
               std::istreambuf_iterator<char>());

    AttributeTree tree = knownSerializers["plain"]->deserialize(str);

    Model m1 = Model();

     m1.fromAttributeTree(knownSerializers["plain"]->deserialize(str));
//    std::cout << m1.child->child->child->name   << std::endl;

//    m1.child->child = nullptr;

    m1.child->child = std::make_shared<Model>();
    m1.child->child->quantity = 666;
    m1.child->child->name = "bruh momento";

    t.close();

    m1.quantity++;

    std::ofstream out(filename);
    out << knownSerializers["plain"]->serialize(m1.toAttributeTree());
    out.close();

//    std::ofstream out("output.txt");
//    out << knownSerializers["plain"]->serialize(m1.child->toAttributeTree());
//    out.close();

    return 0;
}

//int main()
//{
//
//    std::map<std::string, ISerializer*> knownSerializers;
//
//    knownSerializers["plain"] = new PlainSerializer();
//
//    std::string a = "ATTR_CHILD[__TYPE_NODE__]: \n"
//                    "    ATTR_CHILD[__TYPE_NODE__]: nil\n"
//                    "    ATTR_NAME[__TYPE_STRING__]: child model\n"
//                    "    ATTR_QUANTITY[__TYPE_INTEGER__]: 1336\n"
//                    "ATTR_NAME[__TYPE_STRING__]: qwerty\n"
//                    "ATTR_QUANTITY[__TYPE_INTEGER__]: 3\n";
//
////    std::cout << a;
//
//    Model m1 = Model();
//    auto attr = knownSerializers["plain"]->deserialize(a);
////    auto serialized2 = knownSerializers["plain"]->serialize(attr);
////    auto attr2 = *(AttributeTree*) attr["ATTR_CHILD"].data.get();
////    std::cout << "ATTR_CHILD: : " << attr2["ATTR_CHILD"].data.get() << "\n";
////    std::cout << "ATTR_CHILD: : " << attr2["ATTR_CHILD"].data << "\n";
////    for(auto i = attr2.begin(); i != attr2.end(); i++) {
////        std::cout << i->first << std::endl;
////    }
////    std::cout << *(int*)attr["ATTR_QUANTITY"].data.get();
////    std::cout << *(std::string*)attr["ATTR_NAME"].data.get();
//    m1.fromAttributeTree(attr);
////    std::cout << *(std::string*)attr["ATTR_NAME"].data.get();
////    std::cout << serialized2;
////    m1.fromAttributeTree(knownSerializers["plain"]->deserialize(a));
//    std::cout<<m1.name;
//    std::cout<<m1.quantity;
//
//    std::cout<<m1.child->name;
//    std::cout<<m1.child->quantity;
//
//    return 0;
//
//    Model model;
//    Model templateModel;
//    auto child = std::make_shared<Model>();
////    auto grandChild = std::make_shared<Model>();
//
//    Model second;
//
//    model.name = "asdfg";
//    model.quantity = 4;
//
//    templateModel.name = "qwerty";
//    templateModel.quantity = 3;
//
//    child->name = "child model";
//    child->quantity = 1336;
//
////    grandChild->name = "grandChild model";
////    grandChild->quantity = 333;
//
//    model.child = child;
////    child->child = grandChild;
//
//    std::cout << model.name << " " << model.quantity << std::endl;
//    model.fromAttributeTree(templateModel.toAttributeTree());
//    std::cout << model.name << " " << model.quantity << std::endl;
//
//    auto serialized = knownSerializers["plain"]->serialize(model.toAttributeTree());
//    std::cout << knownSerializers["plain"]->serialize(model.toAttributeTree()) << std::endl << std::endl << std::endl;
//    std::cout << knownSerializers["plain"]->serialize(knownSerializers["plain"]->deserialize(serialized)) << std::endl << std::endl << std::endl;
//    return 0;
//
//    try {
//        std::cout << knownSerializers["plain"]->serialize(model.toAttributeTree()) << std::endl;
//    } catch (int ex) {
//        std::cout << ex << std::endl;
//    }
//
//    second.fromAttributeTree(model.toAttributeTree());
//    second.name = "CLONED";
//    second.child->name = "FOOBAR";
//
//    child = std::make_shared<Model>();
//    child->name = "child's child model";
//    child->quantity = 22;
//
//    second.child->child = child;
//
//    std::cout << "second" << std::endl;
//    std::cout << knownSerializers["plain"]->serialize(second.toAttributeTree()) << std::endl;
//
//    std::cout << "first again" << std::endl;
//    std::cout << knownSerializers["plain"]->serialize(model.toAttributeTree()) << std::endl;
//
//    return 0;
//}