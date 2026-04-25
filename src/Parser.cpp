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
            auto Stmt = ParseStatement();
            if (Stmt)
            {
                Statements.push_back(std::move(Stmt));
            }
        }

        if (CurTok != '}')
            return LogErrorExpected("}", "to end block");
        getNextToken();

        return std::make_unique<BlockAST>(std::move(Statements));
    }

    std::unique_ptr<ASTNode> Parser::ParseExpression()
    {
        std::unique_ptr<ASTNode> LHS;
        if (CurTok == tok_number)
            LHS = ParseNumberExpr();
        else if (CurTok == tok_identifier)
            LHS = ParseIdentifierExpr();
        else if (CurTok == '(')
            LHS = ParseParenExpr();
        else
            return LogError("Unknown token when expecting an expression");

        if (!LHS)
            return nullptr;
        return ParseBinOpRHS(0, std::move(LHS));
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
        if (CurTok == ';')
        {
            getNextToken();
            return std::make_unique<BlockAST>(std::vector<std::unique_ptr<ASTNode>>{});
        }

        auto Expr = ParseExpression();
        if (!Expr)
            return nullptr;
        if (CurTok != ';')
            return LogErrorExpected("';'", "after expression");
        getNextToken();
        return Expr;
    }

    std::unique_ptr<ASTNode> Parser::ParseParenExpr()
    {
        if (CurTok != '(')
            return LogErrorExpected("'('", "to start expression");
        getNextToken();
        auto V = ParseExpression();
        if (!V)
            return nullptr;
        if (CurTok != ')')
            return LogErrorExpected("')'", "to end expression");
        getNextToken();
        return V;
    }

    int Parser::GetTokPrecedence()
    {
        if (CurTok < 0)
        {
            switch (CurTok)
            {
            case tok_eq:
            case tok_neq:
                return 10;
            case tok_and:
                return 5;
            case tok_or:
                return 4;
            case tok_lsft:
            case tok_rsft:
                return 20;
            default:
                return -1;
            }
        }
        else
        {
            switch (CurTok)
            {
            case '+':
            case '-':
                return 20;
            case '*':
            case '/':
                return 40;
            default:
                return -1;
            }
        }
    }

    std::unique_ptr<ASTNode> Parser::ParseBinOpRHS(int ExprPrec, std::unique_ptr<ASTNode> LHS)
    {
        while (true)
        {
            int TokPrec = GetTokPrecedence();

            if (TokPrec < ExprPrec)
                return LHS;

            int BinOp = CurTok;
            getNextToken();

            std::unique_ptr<ASTNode> RHS;

            if (CurTok == tok_number)
                RHS = ParseNumberExpr();
            else if (CurTok == tok_identifier)
                RHS = ParseIdentifierExpr();
            else if (CurTok == '(')
                RHS = ParseParenExpr();
            else
                return LogError("Unexpected token when parsing binary operator RHS");

            if (!RHS)
                return nullptr;

            int NextPrec = GetTokPrecedence();
            if (TokPrec < NextPrec)
            {
                RHS = ParseBinOpRHS(TokPrec + 1, std::move(RHS));
                if (!RHS)
                    return nullptr;
            }

            LHS = std::make_unique<BinaryOpAST>(BinOp, std::move(LHS), std::move(RHS));
        }
    }
}
