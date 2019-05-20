#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <istream>

void TrimLeadingWhiteSpace( std::string & str );
void ReadKeyValueAsInt( std::istream & dataStream, int & outValue );
void ReadKeyValueAsString( std::istream & dataStream, std::string & outValue );

#endif // UTILS_H
