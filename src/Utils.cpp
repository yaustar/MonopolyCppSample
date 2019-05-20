#include "Utils.h"

#include <algorithm>

// From: http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
void TrimLeadingWhiteSpace( std::string & str )
{
	str.erase(str.begin(), std::find_if(str.begin(), str.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
}

void ReadKeyValueAsInt( std::istream & dataStream, int & outValue )
{
	std::string line;
	if( std::getline(dataStream, line) )
	{
		TrimLeadingWhiteSpace( line );
		if( "{" == line )
		{
			dataStream >> outValue;

			while( std::getline(dataStream, line) )
			{
				TrimLeadingWhiteSpace( line );
				if( "}" == line )
				{
					break;
				}
			}
		}
	}
}

void ReadKeyValueAsString( std::istream & dataStream, std::string & outValue )
{
	std::string line;
	if( std::getline(dataStream, line) )
	{
		TrimLeadingWhiteSpace( line );
		if( "{" == line )
		{
			if( std::getline(dataStream, line) )
			{
				TrimLeadingWhiteSpace( line );
				outValue = line;
			}

			while( std::getline(dataStream, line) )
			{
				TrimLeadingWhiteSpace( line );
				if( "}" == line )
				{
					break;
				}
			}
		}
	}
}
