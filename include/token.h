// Copyright(c) 2023 Dennis Addo

// MIT License

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

//===========================================================================
//  Token - Analyzer
//===========================================================================

#include "ast.hpp"
#include "utils.h"
#include <cassert>

#ifndef TOKEN_H
#define TOKEN_H

//-----------------------------------------------------------------------
//
//  Token_type: represents the type of a token
//
//-----------------------------------------------------------------------
//
namespace vlark
{

enum class token_type : std::int16_t
{
    Invalid, //-- current_token is not valid.

    Eof, //-- End of file.
    Newline,

    Block_Comment_Start, //--  Start of a block comment (/*)
    Block_Comment_End,   //--  End of a block comment (*/)

    Block_Comment_Text, //--  Text within a block comment (no newline)

    // --- Source_type
    //   --  These tokens represent text in the source whose exact meaning needs
    //   --  extra data (like the value of an integer, the exact identifier...).
    Line_Comment, //--  End of line comment (--)
    Character,    // character literal
    Identifier,
    Integer,
    Real,
    String,

    /*  --  This token corresponds to a base specifier followed by bit_value.
        --  The base specifier is stored in Name_Buffer/Name_Length like an
        --  identifier (in lowercase), the String8_Id contains the expanded bit
        --  value.
    */
    Bit_String,

    //--  An integer immediately followed by a letter.  This is used by to
    //--  scan vhdl 2008 (and later) bit string with a length.
    Integer_Letter,

    // -- source type end here --------

    // --  Delimiters
    Left_Paren,    //-- (
    Right_Paren,   //-- )
    Left_Bracket,  //-- [
    Right_Bracket, //-- ]
    Colon,         //-- :
    Semi_Colon,    //-- ;
    Comma,         //-- ,
    Double_Arrow,  //-- =>
    Tick,          //-- '
    Double_Star,   //-- **
    Assign,        //-- :=
    Bar,           //-- |
    Box,           //-- <>
    Dot,           //-- .

    // Equal_Equal, //-- == (AMS Vhdl)

    //-- relational_operator
    Equal,         //-- =
    Not_Equal,     //-- /=
    Less,          //-- <
    Less_Equal,    //-- <=
    Greater,       //-- >
    Greater_Equal, //-- >=

    Match_Equal,         //-- ?=
    Match_Not_Equal,     //-- ?/=
    Match_Less,          //-- ?<
    Match_Less_Equal,    //-- ?<=
    Match_Greater,       //-- ?>
    Match_Greater_Equal, //-- ?>=

    //-- sign token
    Plus,      //-- +
    Minus,     //-- -
               //-- and adding_operator
    Ampersand, //-- &

    //--  VHDL 2008
    Question_Mark,  //-- ?
    Condition,      //-- ??
    Double_Less,    //-- <<
    Double_Greater, //-- >>
    Caret,          //-- ^

    //--  PSL
    And_And,          //-- &&
    Bar_Bar,          //-- ||
    Left_Curly,       //-- {
    Right_Curly,      //-- }
    Exclam_Mark,      //-- !
    Brack_Star,       //-- [*
    Brack_Plus_Brack, //-- [+]
    Brack_Arrow,      //-- [->
    Brack_Equal,      //-- [=
    Bar_Arrow,        //-- |->
    Bar_Double_Arrow, //-- |=>
    Minus_Greater,    //-- ->
    Equiv_Arrow,      //-- <->
    Arobase,          //-- @

    //-- multiplying operator
    Star,  //-- *
    Slash, //-- /
    Mod,   //-- mod
    Rem,   //-- rem

    //--  miscellaneous operator
    Abs,
    Not,

    //-- Key words
    Access,
    After,
    Alias,
    All,
    Architecture,
    Array,
    Assert,
    Attribute,

    Begin,
    Block,
    Body,
    Buffer,
    Bus,

    Case,
    Component,
    Configuration,
    Constant,

    Disconnect,
    Downto,

    Else,
    Elsif,
    End,
    Entity,
    Exit,

    File,
    For,
    Function,

    Generate,
    Generic,
    Guarded,

    If,
    In,
    Inout,
    Is,

    Label,
    Library,
    Linkage,
    Loop,

    Map,

    New,
    Next,
    Null,

    Of,
    On,
    Open,
    Others,
    Out,

    Package,
    Port,
    Procedure,
    Process,

    Range,
    Record,
    Register,
    Report,
    Return,

    Select,
    Severity,
    Signal,
    Subtype,

    Then,
    To,
    Transport,
    Type,

    Units,
    Until,
    Use,

    Variable,

    Wait,
    When,
    While,
    With,

    //-- logical token:
    And,
    Or,
    Xor,
    Nand,
    Nor,

    //--  Tokens below this line are key words in vhdl93 but not in vhdl87
    //--  Note: xnor is the first one, as it is a logical token.
    Xnor,

    Group,
    Impure,
    Inertial,
    Literal,
    Postponed,
    Pure,
    Reject,
    Shared,
    Unaffected,

    //-- shift_operator
    Sll,
    Sla,
    Sra,
    Srl,
    Rol,
    Ror,

    //--  Added by vhdl 2000:
    Protected,

    //--  Added by vhdl 2008:
    Assume,
    Context,
    Cover,
    Default,
    Force,
    Parameter,
    Property,
    Release,
    Restrict,
    Restrict_Guarantee,
    Sequence,
    Inherit,
    Vmode,
    Vprop,
    Vunit,

    //--  Added by vhdl 2019
    Private,
    View,
};

//-----------------------------------------------------------------------
//
//  token: represents a single token
//  every token has details meta-data to help letter with AST parser
//
//-----------------------------------------------------------------------
//
class token
{
public:
    [[nodiscard]] token(std::string_view sz, token_position p, token_type type)
        : sv{sz}
        , pos{p}
        , tok_type{type}
    {
    }

    std::string_view as_string_view() const
    {
        assert(sv.data());
        return sv;
    }

    operator std::string_view() const { return as_string_view(); }

    bool operator==(token const& t) const { return operator std::string_view() == t.operator std::string_view(); }

    bool operator==(std::string_view s) const { return s == this->operator std::string_view(); }

    std::string to_string() const { return std::string{sv}; }

    friend auto& operator<<(auto& o, token const& t) { return o << std::string_view(t); }

    void position_col_shift(colno_t offset)
    {
        assert(pos.colno + offset > 0);
        pos.colno += offset;
    }

    token_position position() const { return pos; }

    std::size_t length() const { return sv.size(); }

    token_type type() const { return tok_type; }

    void set_type(token_type l) { tok_type = l; }

    auto remove_prefix_if(std::string_view prefix)
    {
        if (sv.size() > prefix.size() && sv.starts_with(prefix))
        {
            sv.remove_prefix(prefix.size());
        }
    }

private:
    std::string_view sv;
    token_position pos;
    token_type tok_type;
};

token_type close_paren_type(token_type ttype);
std::size_t get_name_len(const std::string& text);
std::deque<token> tokenize_lines(sourceBuffer& sbfile);

} // namespace vlark

#endif // TOKEN_H