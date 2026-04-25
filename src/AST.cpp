#include "Rivet/AST.h"
#include "Rivet/Lexer.h"
#include <iostream>

namespace Rivet
{
    void NumberAST::dump(int indent) const
    {
        printIndent(indent);
        std::cout << "Number: " << Val << std::endl;
    }
    llvm::Value *NumberAST::codegen()
    {
        return nullptr; // TODO: Implement codegen
    }

    void VariableAST::dump(int indent) const
    {
        printIndent(indent);
        std::cout << "Variable: " << Name << std::endl;
    }
    llvm::Value *VariableAST::codegen()
    {
        return nullptr; // TODO: Implement codegen
    }

    void VariableDeclAST::dump(int indent) const
    {
        printIndent(indent);
        std::cout << "Variable Declaration: " << Type << " " << Name;
        if (InitVal)
        {
            std::cout << " = ";
            InitVal->dump(0);
        }
        else
        {
            std::cout << " (uninitialized)" << std::endl;
        }
    }
    llvm::Value *VariableDeclAST::codegen()
    {
        return nullptr; // TODO: Implement codegen
    }

    void BinaryOpAST::dump(int indent) const
    {
        printIndent(indent);
        std::cout << "Binary Operation: " << Op << std::endl;
        LHS->dump(indent + 1);
        RHS->dump(indent + 1);
    }
    llvm::Value *BinaryOpAST::codegen()
    {
        return nullptr; // TODO: Implement codegen
    }

    void UnaryOpAST::dump(int indent) const
    {
        printIndent(indent);
        std::cout << "Unary Operation: " << Op << std::endl;
        Operand->dump(indent + 1);
    }
    llvm::Value *UnaryOpAST::codegen()
    {
        return nullptr; // TODO: Implement codegen
    }

    void BlockAST::dump(int indent) const
    {
        printIndent(indent);
        std::cout << "Block:" << std::endl;
        for (const auto &stmt : Statements)
        {
            stmt->dump(indent + 1);
        }
    }
    llvm::Value *BlockAST::codegen()
    {
        return nullptr; // TODO: Implement codegen
    }

    void IfAST::dump(int indent) const
    {
        printIndent(indent);
        std::cout << "If Statement:" << std::endl;
        printIndent(indent + 1);
        std::cout << "Condition:" << std::endl;
        Cond->dump(indent + 2);
        printIndent(indent + 1);
        std::cout << "Then:" << std::endl;
        Then->dump(indent + 2);
        if (Else)
        {
            printIndent(indent + 1);
            std::cout << "Else:" << std::endl;
            Else->dump(indent + 2);
        }
    }
    llvm::Value *IfAST::codegen()
    {
        return nullptr; // TODO: Implement codegen
    }

    void WhileAST::dump(int indent) const
    {
        printIndent(indent);
        std::cout << "While Loop:" << std::endl;
        printIndent(indent + 1);
        std::cout << "Condition:" << std::endl;
        Cond->dump(indent + 2);
        printIndent(indent + 1);
        std::cout << "Body:" << std::endl;
        Body->dump(indent + 2);
    }
    llvm::Value *WhileAST::codegen()
    {
        return nullptr; // TODO: Implement codegen
    }

    void CallAST::dump(int indent) const
    {
        printIndent(indent);
        std::cout << "Function Call: " << Callee << std::endl;
        for (const auto &arg : Args)
        {
            arg->dump(indent + 1);
        }
    }
    llvm::Value *CallAST::codegen()
    {
        return nullptr; // TODO: Implement codegen
    }
}