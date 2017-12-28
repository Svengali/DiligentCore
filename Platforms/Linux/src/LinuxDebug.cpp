/*     Copyright 2015-2017 Egor Yusov
 *  
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF ANY PROPRIETARY RIGHTS.
 *
 *  In no event and under no legal theory, whether in tort (including negligence), 
 *  contract, or otherwise, unless required by applicable law (such as deliberate 
 *  and grossly negligent acts) or agreed to in writing, shall any Contributor be
 *  liable for any damages, including any direct, indirect, special, incidental, 
 *  or consequential damages of any character arising as a result of this License or 
 *  out of the use or inability to use the software (including but not limited to damages 
 *  for loss of goodwill, work stoppage, computer failure or malfunction, or any and 
 *  all other commercial damages or losses), even if such Contributor has been advised 
 *  of the possibility of such damages.
 */

#include <csignal>
#include <iostream>

#include "LinuxDebug.h"
#include "FormatMessage.h"

using namespace Diligent;

void LinuxDebug :: AssertionFailed( const Char *Message, const char *Function, const char *File, int Line )
{
    auto AssertionFailedMessage = FormatAssertionFailedMessage(Message, Function, File, Line);
    OutputDebugMessage(DebugMessageSeverity::Error, AssertionFailedMessage.c_str());

    raise( SIGTRAP );
};


void LinuxDebug::OutputDebugMessage( DebugMessageSeverity Severity, const Char *Message )
{
    static const Char* const strSeverities[] = { "Info: ", "Warning: ", "ERROR: ", "CRITICAL ERROR: " };
    auto* MessageSevery = strSeverities[static_cast<int>(Severity)];
    String str = MessageSevery;
    str += Message;
    str += '\n';
    std::cerr << str;
}

void DebugAssertionFailed(const Diligent::Char* Message, const char* Function, const char* File, int Line)
{
    LinuxDebug :: AssertionFailed( Message, Function, File, Line );
}

void OutputDebugMessage(BasicPlatformDebug::DebugMessageSeverity Severity, const Diligent::Char* Message)
{
    LinuxDebug::OutputDebugMessage( Severity, Message );
}
