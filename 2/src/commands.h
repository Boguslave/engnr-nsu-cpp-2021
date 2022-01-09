#pragma once

#include "../../libs/SafeInt/SafeInt.hpp"
#include <algorithm>
#include <charconv>
#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <stack>
//#include <stdexcept>
//#include <string>
#include <sstream>
//#include <utility>

class StackException : public std::exception
{
public:
    std::string text = "Error! ";

public:
    virtual std::string what() = 0;
};

class WrongArgument : public StackException
{
public:
    WrongArgument()
    {
        text += " Wrong argument ";
    }

    std::string what() override
    {
        return text;
    }
};

class EmptyStack : public StackException
{
public:
    EmptyStack()
    {
        text += " Stack is empty ";
    }

    std::string what() override
    {
        return text;
    }
};

class FewElementError : public StackException
{
public:
    FewElementError()
    {
        text += " in few element ";
    }

    std::string what() override
    {
        return text;
    }
};

class UnknownCommand : public StackException
{
public:
    UnknownCommand()
    {
        text += " Unknown command ";
    }

    std::string what() override
    {
        return text;
    }
};

class OverflowException : public StackException
{
public:
    OverflowException()
    {
        text += " Owerflow happened ";
    }

    std::string what() override
    {
        return text;
    }
};

class DivisionByZero : public StackException
{
public:
    DivisionByZero()
    {
        text += " Division By Zero ";
    }

    std::string what() override
    {
        return text;
    }
};

class CustomException : public SafeIntException
{
public:
    static void SafeIntOnOverflow();
};

struct ContextExecution
{
    std::stack<SafeInt<int64_t, CustomException>> stack;
    std::map<std::string, SafeInt<int64_t, CustomException>> variables;
};

class Command
{
public:
    explicit Command(std::string &args) { params = args; }

    virtual void
    command(ContextExecution &context_execution) = 0;

    virtual ~Command() = default;

protected:
    std::string params;
};

class PopException : public EmptyStack
{
public:
    PopException()
    {
        text += " POP operation failed ";
    }

    std::string what() override
    {
        return text;
    }
};

class Pop : public Command
{
public:
    explicit Pop(std::string &args);

    void
    command(ContextExecution &context_execution) override;
};

class PushException : public WrongArgument
{
public:
    PushException()
    {
        text += " PUSH operation failed ";
    }

    std::string what() override
    {
        return text;
    }
};

class Push : public Command
{
public:
    explicit Push(std::string &args);

    void
    command(ContextExecution &context_execution) override;
};

class PeekException : public EmptyStack
{
public:
    PeekException()
    {
        text += " PEEK operation failed ";
    }

    std::string what() override
    {
        return text;
    }
};

class Peek : public Command
{
public:
    explicit Peek(std::string &args);

    void
    command(ContextExecution &context_execution) override;
};

class AbsException : public EmptyStack
{
public:
    AbsException()
    {
        text += " ABS operation failed ";
    }

    std::string what() override
    {
        return text;
    }
};

class Abs : public Command
{
public:
    explicit Abs(std::string &args);

    void
    command(ContextExecution &context_execution) override;
};

class PlusException : public FewElementError
{
public:
    PlusException()
    {
        text += " PLUS operation failed ";
    }

    std::string what() override
    {
        return text;
    }
};

class Plus : public Command
{
public:
    explicit Plus(std::string &args);

    void
    command(ContextExecution &context_execution) override;
};

class MinusException : public FewElementError
{
public:
    MinusException()
    {
        text += " MINUS operation failed ";
    }

    std::string what() override
    {
        return text;
    }
};

class Minus : public Command
{
public:
    explicit Minus(std::string &args);

    void
    command(ContextExecution &context_execution) override;
};

class MultiplyException : public FewElementError
{
public:
    MultiplyException()
    {
        text += " MUL operation failed ";
    }

    std::string what() override
    {
        return text;
    }
};

class Multiply : public Command
{
public:
    explicit Multiply(std::string &args);

    void
    command(ContextExecution &context_execution) override;
};

class DivisionException : public FewElementError
{
public:
    DivisionException()
    {
        text += "DIV operation failed ";
    }

    std::string what() override
    {
        return text;
    }
};

class Division : public Command
{
public:
    explicit Division(std::string &args);

    void
    command(ContextExecution &context_execution) override;
};

class PrintException : public EmptyStack
{
public:
    PrintException()
    {
        text += " PRINT operation failed ";
    }

    std::string what() override
    {
        return text;
    }
};

class Print : public Command
{
public:
    explicit Print(std::string &args);

    void
    command(ContextExecution &context_execution) override;
};

class ReadException : public WrongArgument
{
public:
    ReadException()
    {
        text += " READ operation failed ";
    }

    std::string what() override
    {
        return text;
    }
};

class Read : public Command
{
public:
    explicit Read(std::string &args);

    void command(ContextExecution &context_execution) override;
};

class Comment : public Command
{
public:
    explicit Comment(std::string &args);

    void command(ContextExecution &context_execution) override;
};

class StackCalc
{
    ContextExecution context_execution;

public:
    void command(std::unique_ptr<Command> cmd);

    Command *read_command(std::string &command_line);

    std::map<std::string, SafeInt<int64_t, CustomException>> FindResult()
    {
        return context_execution.variables;
    }
};

StackCalc ReadFromStream(std::istream &str);

StackCalc OneCommandRead();