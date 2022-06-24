#include "include/ArgsParser.hpp"

ArgsParser::ArgsParser(const string& schema, const char* args[]) 
{
    if(schema.empty())
        throw EmptySchemaIsDisallowedException();
}
