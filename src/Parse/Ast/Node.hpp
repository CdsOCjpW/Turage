#ifndef SIMLAN_PARSE_AST_NODE_HPP
#define SIMLAN_PARSE_AST_NODE_HPP

#include "Visitor.hpp"

#include <Simlan/Typedef/Typedef.hpp>

namespace Simlan :: Parse :: Ast {
    using basic_node = Node<EAstNodeType::Base>;
    template<EAstNodeType Itype>
    using nodeptr = shared<Node<Itype>>;

    template<>
    struct Node<EAstNodeType::Program> 
        : public Node<EAstNodeType::Base>, public Area {
        void Accept(Visitor* visitor) override;
        List<nodeptr<EAstNodeType::Statement>> stmts;
    };

    template<>
    struct Node<EAstNodeType::Statement> : public Node<EAstNodeType::Base> { };
    template<>
    struct Node<EAstNodeType::Expression> : public Node<EAstNodeType::Base> { };

    template<>
    struct Node<EAstNodeType::Block> 
        : public Node<EAstNodeType::Statement>, public Area {
        void Accept(Visitor* visitor) override;
    };

    template<>
    struct Node<EAstNodeType::Expression_Stmt> : public Node<EAstNodeType::Statement> {
        void Accept(Visitor* visitor) override;
        nodeptr<EAstNodeType::Expression> expr;
    };

    template<>
    struct Node<EAstNodeType::IfElse_Stmt> : public Node<EAstNodeType::Statement> {
        void Accept(Visitor* visitor) override;
    };

    template<>
    struct Node<EAstNodeType::While_Stmt> : public Node<EAstNodeType::Statement> {
        void Accept(Visitor* visitor) override;
    };

    template<>
    struct Node<EAstNodeType::For_Stmt> : public Node<EAstNodeType::Statement> {
        void Accept(Visitor* visitor) override;
    };

    template<>
    struct Node<EAstNodeType::Mid_Expr> : public Node<EAstNodeType::Expression> {
        void Accept(Visitor* visitor) override;
        // left Kid && Right Kid
        nodeptr<EAstNodeType::Expression> Lkd, Rkd;
        enum class EOperator : uint8_t {
            Invalid = 0,
            Add, Sub, Mul, Div, Mod,
            Less, Greater, 
            LessEqual, GreaterEqual, 
            Equal, Not,
            Assign,
        } oprt;
    };

    template<>
    struct Node<EAstNodeType::Assign_Expr> : public Node<EAstNodeType::Mid_Expr> {
        void Accept(Visitor* visitor) override;
    };


    template<>
    struct Node<EAstNodeType::Primary_Expr> : public Node<EAstNodeType::Expression> {
        void Accept(Visitor* visitor) override;
        nodeptr<EAstNodeType::Expression> expr;
    };

    template<>
    struct Node<EAstNodeType::Number> : public Node<EAstNodeType::Expression> {
        void Accept(Visitor* visitor) override;
        // TODO: 使用具备类型的数据量
        uint64_t value;
    };
}

#endif // ! SIMLAN_PARSE_AST_NODE_HPP