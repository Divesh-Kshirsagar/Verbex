#include "Rivet/Parser.h"
#include <iostream>

namespace Rivet
{
    Parser::Parser(Lexer &lexer) : lexer(lexer)
    {
        getNextToken();
    }

    int Parser::getNextToken()
    {
        CurTok = lexer.getNextToken();
        return CurTok;
    }

    std::unique_ptr<ASTNode> Parser::LogError(const char *str)
    {
        ErrorCount++;
        std::cerr << "\n[Compile Error] -> " << str << "\n";
        std::cerr << "  --> At Line " << lexer.CurrentLine << ", Column " << lexer.CurrentColumn << "\n\n";
        return nullptr;
    }

    std::unique_ptr<ASTNode> Parser::LogErrorExpected(const char *expected, const char *context)
    {
        std::string msg = std::string("Expected '") + expected + "' " + context;
        return LogError(msg.c_str());
    }

    std::unique_ptr<ASTNode> Parser::ParseNumberExpr()
    {
        auto result = std::make_unique<NumberAST>(lexer.NumVal);
        getNextToken();
        return std::move(result);
    }

    std::unique_ptr<ASTNode> Parser::ParseIdentifierExpr()
    {
        std::string idName = lexer.IdentifierStr;

        getNextToken();

        if (CurTok != '(')
            return std::make_unique<VariableAST>(idName);

        getNextToken();

        std::vector<std::unique_ptr<ASTNode>> args;
        if (CurTok != ')')
        {
            while (true)
            {
                if (auto arg = ParseExpression())
                {
                    args.push_back(std::move(arg));
                }
                else
                {
                    return nullptr;
                }

                if (CurTok == ')')
                    break;

                if (CurTok != ',')
                    return LogErrorExpected("',' or ')'", "in argument list");

                getNextToken();
            }
        }

        getNextToken();

        return std::make_unique<CallAST>(idName, std::move(args));
    }

    std::unique_ptr<ASTNode> Parser::ParseIfStatement()
    {
        getNextToken();

        if (CurTok != '(')
            return LogErrorExpected("'('", "after 'if'");
        getNextToken();

        auto Cond = ParseExpression();
        if (!Cond)
            return nullptr;

        if (CurTok != ')')
            return LogErrorExpected("')'", "after condition");
        getNextToken();
        auto Then = ParseBlock();
        if (!Then)
            return nullptr;
        std::unique_ptr<ASTNode> Else = nullptr;
        if (CurTok == tok_else)
        {
            getNextToken();
            Else = ParseBlock();
            if (!Else)
                return nullptr;
        }
        return std::make_unique<IfAST>(std::move(Cond), std::move(Then), std::move(Else));
    }


    // Dummy implementations for now, to be filled in later
    // TODO: Replace temroary placeholder with actual parsing logic
    std::unique_ptr<ASTNode> Parser::ParseBlock()
    {
        if (CurTok != '{')
            return LogErrorExpected("{", "to start block");
        getNextToken();

        std::vector<std::unique_ptr<ASTNode>> Statements;

        while (CurTok != '}' && CurTok != tok_eof)
        {
            getNextToken();
        }

        if (CurTok != '}')
            return LogErrorExpected("}", "to end block");
        getNextToken();

        return std::make_unique<BlockAST>(std::move(Statements));
    }

    // Dummy implementations for now, to be filled in later
    // TODO: Replace temporary placeholder with actual parsing logic
    std::unique_ptr<ASTNode> Parser::ParseExpression()
    {
        if (CurTok == tok_number)
            return ParseNumberExpr();
        if (CurTok == tok_identifier)
            return ParseIdentifierExpr();
        return LogError("Unknown token when expecting an expression");
    }

    std::vector<std::unique_ptr<ASTNode>> Parser::ParseFile()
    {
        std::vector<std::unique_ptr<ASTNode>> Nodes;
        while (CurTok != tok_eof)
        {
            if (auto stmt = ParseStatement())
            {
                Nodes.push_back(std::move(stmt));
            }
            else
            {
                getNextToken();
            }
        }
        return Nodes;
    }

    std::unique_ptr<ASTNode> Parser::ParseStatement()
    {
        if (CurTok == tok_if)
            return ParseIfStatement();
        if (CurTok == '{')
            return ParseBlock();
        return LogError("Unknown token when expecting a statement");    
    }

}
