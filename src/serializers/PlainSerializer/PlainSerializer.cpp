//
// Created by ulkenauer on 14.11.2020.
//

#include <iostream>
#include <stack>
#include <list>

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

const std::string INDENT_UNIT = "    ";
const char EOL = '\n';

std::string PlainSerializer::serialize(AttributeTree attributes) {
    //    TODO: unwrap node serialization recursive call
    std::string serialized = std::string();
    std::string indentation = "";

    for(int i = 0; i < this->__indentation; i++) {
        indentation += INDENT_UNIT;
    }

    for(auto i = attributes.begin(); i != attributes.end(); i++) {

        const std::string key = i->first;
        const AttributeNode node = i->second;

        if(node.nodeType == __TYPE_NODE__) {
            auto child = (AttributeTree *) node.data.get();
            if(child == nullptr) {
                serialized += indentation + key + "[" + node.nodeType + "]" + ": " + "nil" + "\n";
            } else {
                this->__indentation++;
                serialized += indentation + key + "[" + node.nodeType + "]" + ": " + "\n" + this->serialize(*child);
                this->__indentation--;
//                serialized += this->serialize(child->getAttributes());
            }
        } else {
            serialized += indentation + key + "[" + node.nodeType + "]" + ": " + this->attributeSerializers[node.nodeType](node) + "\n";
        }

    }

    return serialized;
}
//ATTR_CHILD[__TYPE_NODE__]:
//    ATTR_CHILD[__TYPE_NODE__]:
//        ATTR_CHILD[__TYPE_NODE__]: nil
//        ATTR_NAME[__TYPE_STRING__]: child's child model
//        ATTR_QUANTITY[__TYPE_INTEGER__]: 22
//    ATTR_NAME[__TYPE_STRING__]: FOOBAR
//    ATTR_QUANTITY[__TYPE_INTEGER__]: 1336
//ATTR_NAME[__TYPE_STRING__]: CLONED
//ATTR_QUANTITY[__TYPE_INTEGER__]: 3

//std::stack<std::string> extractLevelLines(std::string serialized, int level)
//{
//    std::stack<std::string> levelAttributeStrings = std::stack<std::string>();
//
//    std::string::iterator lineStart = serialized.begin();
//
//    const int indentUnitLength = std::string(INDENT_UNIT).length();
//    const int iteratorCopyOffset = indentUnitLength * level;
//    int indentUnitIndex = 0;
//    int indentUnitRepeatCounter = 0;
//    bool measureIndent = true;
//
//    for(std::string::iterator i = lineStart; i != serialized.end(); i++) {
//        char s = *i;
//
//        if(measureIndent) {
//            if(INDENT_UNIT[indentUnitIndex] == s) {
//                indentUnitIndex++;
//
//                if(indentUnitIndex % indentUnitLength == 0) {
//                    indentUnitIndex = 0;
//                    indentUnitRepeatCounter++;
//                }
//            } else {
//                measureIndent = false;
//            }
//        }
//
//        if(s == EOL) {
//            if(indentUnitRepeatCounter == level) {
//                std::string substr = std::string(lineStart + iteratorCopyOffset, i);
//                levelAttributeStrings.push(substr);
//            }
//            indentUnitRepeatCounter = 0;
//            indentUnitIndex = 0;
//            lineStart = i+1;
//            measureIndent = true;
//        }
//    }
//
//    return levelAttributeStrings;
//
////    while (levelAttributeStrings.empty() == false) {
////        const std::string line = levelAttributeStrings.top();
////        levelAttributeStrings.pop();
////        // // // std::cout << line << std::endl;
////    }
////
////    return AttributeTree();
//}

//std::stack<std::string> extractLevelLines(std::string serialized, int level)
//{
//    std::stack<std::string> levelAttributeStrings = std::stack<std::string>();
//
//    std::string::iterator lineStart = serialized.begin();
//
//    const int indentUnitLength = std::string(INDENT_UNIT).length();
//    const int iteratorCopyOffset = indentUnitLength * level;
//    int indentUnitIndex = 0;
//    int indentUnitRepeatCounter = 0;
//    bool measureIndent = true;
//
//    for(std::string::iterator i = lineStart; i != serialized.end(); i++) {
//        char s = *i;
//
//        if(measureIndent) {
//            if(INDENT_UNIT[indentUnitIndex] == s) {
//                indentUnitIndex++;
//
//                if(indentUnitIndex % indentUnitLength == 0) {
//                    indentUnitIndex = 0;
//                    indentUnitRepeatCounter++;
//                }
//            } else {
//                measureIndent = false;
//            }
//        }
//
//        if(s == EOL) {
//            if(indentUnitRepeatCounter == level) {
//                std::string substr = std::string(lineStart + iteratorCopyOffset, i);
//                levelAttributeStrings.push(substr);
//            }
//            indentUnitRepeatCounter = 0;
//            indentUnitIndex = 0;
//            lineStart = i+1;
//            measureIndent = true;
//        }
//    }
//
//    return levelAttributeStrings;
//}


std::stack<std::string> extractAttributeParts(std::string serialized)
{
    std::stack<std::string> levelAttributeStrings = std::stack<std::string>();

    std::string::iterator lineStart = serialized.begin();

    const int indentUnitLength = std::string(INDENT_UNIT).length();
    int indentUnitIndex = 0;
    int indentUnitRepeatCounter = 0;
    bool measureIndent = true;

    for(std::string::iterator i = lineStart; i != serialized.end(); i++) {
        char s = *i;

        if(measureIndent) {
            if(INDENT_UNIT[indentUnitIndex] == s) {
                indentUnitIndex++;

                if(indentUnitIndex % indentUnitLength == 0) {
                    indentUnitIndex = 0;
                    indentUnitRepeatCounter++;
                }
            } else {
                measureIndent = false;
            }
        }

        if(s == EOL) {
            std::string substr = std::string(lineStart, i+1);
            if(indentUnitRepeatCounter == 0) {
                levelAttributeStrings.push(substr);
            } else {
                substr = levelAttributeStrings.top() + substr;
                levelAttributeStrings.pop();
                levelAttributeStrings.push(substr);
            }
            lineStart = i+1;
            indentUnitRepeatCounter = 0;
            indentUnitIndex = 0;
            measureIndent = true;
        }
    }

    return levelAttributeStrings;
}

//AttributeTree deserializePart(std::string serialized, std::string::iterator partBegin, std::string::iterator partEnd)
//{
//    return AttributeTree();
//}

struct ParsedPart
{
    std::string key;
    AttributeNode attributeNode;
};

ParsedPart parsePart(std::string part)
{
    const std::string MARK__TYPE_STRING__ = "[" + __TYPE_STRING__ + "]: ";
    const std::string MARK__TYPE_INTEGER__ = "[" + __TYPE_INTEGER__ + "]: ";
    const std::string MARK__TYPE_DOUBLE__ = "[" + __TYPE_DOUBLE__ + "]: ";
    const std::string MARK__TYPE_NODE__ = "[" + __TYPE_NODE__ + "]: ";
    const std::string MARK__TYPE_NODE_NIL__ = "[" + __TYPE_NODE__ + "]: nil";

    ParsedPart parsedPart = ParsedPart();
    parsedPart.key = std::string();
    parsedPart.attributeNode = AttributeNode();

    int lineEnd = part.find("\n");
    if(lineEnd != std::string::npos) {
        std::string substr = std::string(part.begin(), part.begin() + lineEnd);
        auto markPos = std::string::npos;
        if(markPos == std::string::npos) {
            markPos = substr.find(MARK__TYPE_STRING__);
            if (markPos != std::string::npos) {
                parsedPart.attributeNode.nodeType = __TYPE_STRING__;
                parsedPart.attributeNode.data = std::make_shared<std::string>(
                        part.begin() + markPos + MARK__TYPE_STRING__.length(), part.begin() + lineEnd);
//                // std::cout << part.end() - (part.begin() + lineEnd) << std::endl;
            }
        }

        if(markPos == std::string::npos) {
            markPos = substr.find(MARK__TYPE_INTEGER__);
            if(markPos != std::string::npos) {
                parsedPart.attributeNode.nodeType = __TYPE_INTEGER__;
                parsedPart.attributeNode.data = std::make_shared<int>(std::stoi(std::string(part.begin() + markPos + MARK__TYPE_INTEGER__.length(), part.begin() + lineEnd)));
//                // std::cout << part.end() - (part.begin() + lineEnd) << std::endl;
            }
        }

        if(markPos == std::string::npos) {
            markPos = substr.find(MARK__TYPE_DOUBLE__);
            if(markPos != std::string::npos) {
                parsedPart.attributeNode.nodeType = __TYPE_DOUBLE__;
                parsedPart.attributeNode.data = std::make_shared<int>(std::stod(std::string(part.begin() + markPos + MARK__TYPE_DOUBLE__.length(), part.begin() + lineEnd)));
//                // std::cout << part.end() - (part.begin() + lineEnd) << std::endl;
            }
        }

        if(markPos == std::string::npos) {
            markPos = substr.find(MARK__TYPE_NODE_NIL__);
            if (markPos != std::string::npos) {
                parsedPart.attributeNode.nodeType = __TYPE_NODE__;
                parsedPart.attributeNode.data = nullptr;
//                parsedPart.key = "ATTR_CHILD";
                parsedPart.key = std::string(substr.begin(), substr.begin() + markPos);//"ATTR_CHILD";
//                // std::cout << markPos;
//                parsedPart.key = std::string(substr.begin(), substr.begin() + markPos);
//                // std::cout << std::string(substr.begin(), substr.begin() + markPos);
//                // std::cout << substr.end() - (substr.begin() + markPos) << std::endl;
                return parsedPart;
            }
        }

        if(markPos == std::string::npos) {
            markPos = substr.find(MARK__TYPE_NODE__);
            if(markPos != std::string::npos) {
                parsedPart.attributeNode.nodeType = __TYPE_NODE__;
                parsedPart.attributeNode.data = nullptr;

                if(part.length() > lineEnd) {
                    std::string childAttributesPart = std::string(part.begin() + lineEnd + 1, part.end());
                    std::list<std::string> newLines = std::list<std::string>();
                    std::string::iterator newLineStart = childAttributesPart.begin();
                    for(std::string::iterator i = newLineStart; i != childAttributesPart.end(); i++) {
//                        // std::cout << (newLineStart > childAttributesPart.end()) << std::endl;
                        const char s = *i;
                        if(s == '\n') {
                            std::string newLine = std::string(newLineStart + INDENT_UNIT.length(), i+1);
//                            // // std::cout << newLine << std::endl;
                            newLines.push_back(newLine);
                            newLineStart = i+1;
                        }
//                        // std::cout << (newLineStart > childAttributesPart.end()) << std::endl;
                    }

                    childAttributesPart = "";
                    for (std::list<std::string>::iterator i = newLines.begin(); i != newLines.end(); ++i) {
                        childAttributesPart += *i;
                    }
//                    while(newLines.empty() == false) {
//                        childAttributesPart += newLines.top();
//                        newLines.pop();
//                    }

                    // // std::cout << "childAttributesPart: " << std::endl << childAttributesPart << std::endl << std::endl;

                    auto extracted = extractAttributeParts(childAttributesPart);
//                    auto extracted2 = extractAttributeParts(childAttributesPart);
//                    while(extracted2.empty() == false) {
//                        std::string extractedString = extracted2.top();
//                        // // std::cout << "extractedString: \n" <<  extractedString << std::endl;
//                        extracted2.pop();
//                    }

                    std::shared_ptr<AttributeTree> pTree = std::make_shared<AttributeTree>();

                    while (extracted.empty() == false) {
                        ParsedPart parsedPartChild = parsePart(extracted.top());
                        (*pTree)[parsedPartChild.key] = parsedPartChild.attributeNode;
                        extracted.pop();
                    }
                    auto ser = PlainSerializer();
                    // std::cout << "extracted so far: \n" << ser.serialize((*pTree)) << std::endl;

                    parsedPart.attributeNode.data = pTree;
                }

            }
        }

        parsedPart.key = std::string(substr.begin(), substr.begin() + markPos);
    }

    return parsedPart;
}

AttributeTree PlainSerializer::deserialize(std::string serialized) {

    auto extracted = extractAttributeParts(serialized);
    AttributeTree tree = AttributeTree();

    while (extracted.empty() == false) {
        ParsedPart parsedPart = parsePart(extracted.top());
        tree[parsedPart.key] = parsedPart.attributeNode;
        extracted.pop();
    }

    auto ser = PlainSerializer();
    // std::cout << "extracted so far: \n" << ser.serialize(tree) << std::endl;

    return tree;
}
