#include "Rivet/AST.h"
#include "Rivet/Lexer.h"
#include "Rivet/CodeGen.h"
#include <iostream>
#include <llvm/IR/Constant.h>

namespace Rivet
{
    void NumberAST::dump(int indent) const
    {
        printIndent(indent);
        std::cout << "Number: " << Val << std::endl;
    }
    llvm::Value *NumberAST::codegen()
    {
        return llvm::ConstantInt::get(*CompilerState.TheContext, llvm::APInt(32, Val, true));
    }

    void VariableAST::dump(int indent) const
    {
        printIndent(indent);
        std::cout << "Variable: " << Name << std::endl;
    }
    llvm::Value *VariableAST::codegen()
    {
        llvm::AllocaInst *Alloca = CompilerState.NamedValues[Name];
        if (!Alloca)
        {
            std::cerr << "Unknown variable name: " << Name << std::endl;
            return nullptr;
        }
        return CompilerState.Builder->CreateLoad(Alloca->getAllocatedType(), Alloca, Name.c_str());
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
        llvm::Value *InitValIR = nullptr;
        if (InitVal)
        {
            InitValIR = InitVal->codegen();
            if (!InitValIR)
                return nullptr;
        }
        else
        {
            // if they just wrote 0 to x we will default that to 0 so we shouldn't have garbage memory
            InitValIR = llvm::ConstantInt::get(*CompilerState.TheContext, llvm::APInt(32, 0, true));
        }
        llvm::AllocaInst *Alloca = CompilerState.Builder->CreateAlloca(llvm::Type::getInt32Ty(*CompilerState.TheContext), nullptr, Name);
        CompilerState.Builder->CreateStore(InitValIR, Alloca);
        CompilerState.NamedValues[Name] = Alloca;
        return Alloca;
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
        llvm::Value *L = LHS->codegen();
        llvm::Value *R = RHS->codegen();
        if (!L || !R)
            return nullptr; // Error in codegen of operands
        switch (Op)
        {
        // Arithemetic
        case '+':
            return CompilerState.Builder->CreateAdd(L, R, "addtmp");
        case '-':
            return CompilerState.Builder->CreateSub(L, R, "subtmp");
        case '*':
            return CompilerState.Builder->CreateMul(L, R, "multmp");
        case '/':
            return CompilerState.Builder->CreateSDiv(L, R, "divtmp");

        // Bitwise and logical
        case tok_and:
            return CompilerState.Builder->CreateAnd(L, R, "andtmp");
        case tok_or:
            return CompilerState.Builder->CreateOr(L, R, "ortmp");
        case tok_lsft:
            return CompilerState.Builder->CreateShl(L, R, "shltmp");
        case tok_rsft:
            return CompilerState.Builder->CreateAShr(L, R, "shrtmp");

        // equality
        case tok_eq:
        {
            llvm::Value *Cmp = CompilerState.Builder->CreateICmpEQ(L, R, "eqtmp");
            return CompilerState.Builder->CreateZExt(Cmp, llvm::Type::getInt32Ty(*CompilerState.TheContext), "booltmp");
        }
        case tok_neq:
        {
            llvm::Value *CmpNE = CompilerState.Builder->CreateICmpNE(L, R, "netmp");
            return CompilerState.Builder->CreateZExt(CmpNE, llvm::Type::getInt32Ty(*CompilerState.TheContext), "booltmp");
        }

        default:
            std::cerr << "Unknown binary operator: " << Op << std::endl;
            return nullptr;
        }
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