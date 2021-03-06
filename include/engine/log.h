/*
 MIT License
 
 Copyright (c) 2017 SAE Institute Switzerland AG
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */

#ifndef SFGE_LOG_H
#define SFGE_LOG_H

#include <iostream>
#include <string>

#include <engine/utility.h>

namespace sfge
{
/**
* \brief Log takes the different message from different parts of the program and write them in the console
*/
class Log : public Singleton<Log>
{
public:
	/**
	* \brief takes the reference to a string and output it to cout
	* \param msgText The message to be written in cout
	*/
	void Msg(const std::string& msgText);
	/**
	* \brief takes the reference to a string and output it to cerr
	* \param errorText The message to be written in cerr
	*/
	void Error(const std::string& errorText);
};
}
#endif // SFGE_LOG_H
