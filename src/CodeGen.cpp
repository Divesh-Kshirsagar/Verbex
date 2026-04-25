#include "Rivet/CodeGen.h"

namespace Rivet
{
    CodeGenContext CompilerState;

    void CodeGenContext::Initialize()
    {
        TheContext = std::make_unique<llvm::LLVMContext>();
        Builder = std::make_unique<llvm::IRBuilder<>>(*TheContext);
        TheModule = std::make_unique<llvm::Module>("Rivet Bare Metal Module", *TheContext);
    }

}
