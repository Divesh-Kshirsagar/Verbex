# include <iostream>
#include <string>
#include "Rivet/Lexer.h"
#include "Rivet/Parser.h"
#include "Rivet/CodeGen.h"

using namespace Rivet;

// TODO: Try to use better error messages cause the current ones are pretty bad, especially for syntax errors. Maybe include line/column info in the error messages? --- IGNORE ---
int main(int argc, char** argv) {
    
    if (argc < 2) {
        std::cerr << "Fatal Error: No input file provided.\n";
        std::cerr << "Usage: rivet <source_file.rvt> [--dump-ast]\n";
        return 1;
    }

    std::string filename = argv[1];
    bool dumpAST = false;
    if (argc >= 3 && std::string(argv[2]) == "--dump-ast") {
        dumpAST = true;
    }

    std::cout << "Rivet Compiler - Compiling " << filename << "...\n";

    Lexer lexer(filename);
    Parser parser(lexer);

    auto astNodes = parser.ParseFile();

    if(astNodes.empty()) {
        std::cerr << "Error: No AST nodes generated. Compilation failed.\n";
        return 1;
    }

    if (dumpAST) {
        std::cout << "\n============================\n";
        std::cout << "       ABSTRACT SYNTAX TREE   \n";
        std::cout << "\n============================\n";


        for (const auto& node : astNodes) {
            node->dump(0);
        }

        std::cout << "\n============================\n";

    }

    // These are just placeholders for now, as codegen is not implemented yet
    if(parser.ErrorCount > 0) {
        std::cerr << "Compilation failed with " << parser.ErrorCount << " error(s).\n";
        return 1;
    }

    CompilerState.Initialize();
    std::cout << "Rivet Compiler initialized.\n";

    for (const auto& node : astNodes) {
        if(llvm::Value* val = node->codegen()) {
            //successfully generated code for this node
        } else {
            std::cerr << "Error: Code generation failed for an AST node.\n";
            return 1;
        }
    }
    

    std::cout << "============================\n";
    std::cout << "           LLVM IR          \n";
    std::cout << "============================\n";
    CompilerState.TheModule->print(llvm::outs(), nullptr);
    std::cout << "============================\n";
    return 0;
}