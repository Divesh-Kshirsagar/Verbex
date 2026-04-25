#ifndef RIVET_CODEGEN_H
#define RIVET_CODEGEN_H

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>
#include <memory>

namespace Rivet
{
    struct CodeGenContext
    {
        std::unique_ptr<llvm::LLVMContext> TheContext;
        std::unique_ptr<llvm::IRBuilder<>> Builder;
        std::unique_ptr<llvm::Module> TheModule;

        void Initialize();
    };
    
    // Expposes the global compiler state for codegen, which includes the LLVM context, IR builder, and module. This is used by the codegen methods of AST nodes to generate LLVM IR.
    extern CodeGenContext CompilerState;
}

#endif
