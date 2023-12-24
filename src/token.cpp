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
#include "token.h"

namespace vlark
{

    // Return the name of the token.
    template <typename T>
        requires std::is_same_v<T, std::string>
    std::string _asstr(token_type Token)
    {

        switch (Token)
        {
        case token_type::Invalid:
            return "<invalid>";
        case token_type::Left_Paren:
            return "(";
        case token_type::Right_Paren:
            return ")";
        case token_type::Left_Bracket:
            return "[";
        case token_type::Right_Bracket:
            return "]";
        case token_type::Colon:
            return ":";
        case token_type::Semi_Colon:
            return ";";
        case token_type::Comma:
            return ",";
        case token_type::Tick:
            return "'";
        case token_type::Double_Star:
            return "**";
        case token_type::Double_Arrow:
            return "=>";
        case token_type::Assign:
            return ":=";
        case token_type::Bar:
            return "|";
        case token_type::Box:
            return "<>";
        case token_type::Dot:
            return ".";
        case token_type::Block_Comment_Start:
            return "/*";
        case token_type::Block_Comment_End:
            return "*/";
        case token_type::Eof:
            return "<EOF>";
        case token_type::Newline:
            return "<newline>";
        case token_type::Line_Comment:
            return "<line-comment>";
        case token_type::Block_Comment_Text:
            return "<block-comment>";
        case token_type::Character:
            return "<character>";
        case token_type::Identifier:
            return "<identifier>";
        case token_type::Integer:
        case token_type::Integer_Letter:
            return "<integer>";
        case token_type::Real:
            return "<real>";
        case token_type::String:
            return "<string>";
        case token_type::Bit_String:
            return "<bit string>";
        case token_type::Equal:
            return "=";
        case token_type::Not_Equal:
            return "/=";
        case token_type::Less:
            return "<";
        case token_type::Less_Equal:
            return "<=";
        case token_type::Greater:
            return ">";
        case token_type::Greater_Equal:
            return ">=";
        case token_type::Match_Equal:
            return "?=";
        case token_type::Match_Not_Equal:
            return "?/=";
        case token_type::Match_Less:
            return "?<";
        case token_type::Match_Less_Equal:
            return "?<=";
        case token_type::Match_Greater:
            return "?>";
        case token_type::Match_Greater_Equal:
            return "?>=";
        case token_type::Plus:
            return "+";
        case token_type::Minus:
            return "-";
        case token_type::Ampersand:
            return "&";
        case token_type::Question_Mark:
            return "?";
        case token_type::Condition:
            return "??";
        case token_type::Double_Less:
            return "<<";
        case token_type::Double_Greater:
            return ">>";
        case token_type::Caret:
            return "^";
        case token_type::Star:
            return "*";
        case token_type::Slash:
            return "/";
        case token_type::Mod:
            return "mod";
        case token_type::Rem:
            return "rem";
        case token_type::And:
            return "and";
        case token_type::Or:
            return "or";
        case token_type::Xor:
            return "xor";
        case token_type::Nand:
            return "nand";
        case token_type::Nor:
            return "nor";
        case token_type::Xnor:
            return "xnor";
        case token_type::Abs:
            return "abs";
        case token_type::Access:
            return "access";
        case token_type::After:
            return "after";
        case token_type::Alias:
            return "alias";
        case token_type::All:
            return "all";
        case token_type::Architecture:
            return "architecture";
        case token_type::Array:
            return "array";
        case token_type::Assert:
            return "assert";
        case token_type::Attribute:
            return "attribute";
        case token_type::Begin:
            return "begin";
        case token_type::Block:
            return "block";
        case token_type::Body:
            return "body";
        case token_type::Buffer:
            return "buffer";
        case token_type::Bus:
            return "bus";
        case token_type::Case:
            return "case";
        case token_type::Component:
            return "component";
        case token_type::Configuration:
            return "configuration";
        case token_type::Constant:
            return "constant";
        case token_type::Disconnect:
            return "disconnect";
        case token_type::Downto:
            return "downto";
        case token_type::Else:
            return "else";
        case token_type::Elsif:
            return "elsif";
        case token_type::End:
            return "end";
        case token_type::Entity:
            return "entity";
        case token_type::Exit:
            return "exit";
        case token_type::File:
            return "file";
        case token_type::For:
            return "for";
        case token_type::Function:
            return "function";
        case token_type::Generate:
            return "generate";
        case token_type::Generic:
            return "generic";
        case token_type::Group:
            return "group";
        case token_type::Guarded:
            return "guarded";
        case token_type::If:
            return "if";
        case token_type::Impure:
            return "impure";
        case token_type::In:
            return "in";
        case token_type::Inertial:
            return "inertial";
        case token_type::Inout:
            return "inout";
        case token_type::Is:
            return "is";
        case token_type::Label:
            return "label";
        case token_type::Library:
            return "library";
        case token_type::Linkage:
            return "linkage";
        case token_type::Literal:
            return "literal";
        case token_type::Loop:
            return "loop";
        case token_type::Map:
            return "map";
        case token_type::New:
            return "new";
        case token_type::Next:
            return "next";
        case token_type::Not:
            return "not";
        case token_type::Null:
            return "null";
        case token_type::Of:
            return "of";
        case token_type::On:
            return "on";
        case token_type::Open:
            return "open";
        case token_type::Out:
            return "out";
        case token_type::Others:
            return "others";
        case token_type::Package:
            return "package";
        case token_type::Port:
            return "port";
        case token_type::Postponed:
            return "postponed";
        case token_type::Procedure:
            return "procedure";
        case token_type::Process:
            return "process";
        case token_type::Pure:
            return "pure";
        case token_type::Range:
            return "range";
        case token_type::Record:
            return "record";
        case token_type::Register:
            return "register";
        case token_type::Reject:
            return "reject";
        case token_type::Report:
            return "report";
        case token_type::Return:
            return "return";
        case token_type::Select:
            return "select";
        case token_type::Severity:
            return "severity";
        case token_type::Shared:
            return "shared";
        case token_type::Signal:
            return "signal";
        case token_type::Subtype:
            return "subtype";
        case token_type::Then:
            return "then";
        case token_type::To:
            return "to";
        case token_type::Transport:
            return "transport";
        case token_type::Type:
            return "type";
        case token_type::Unaffected:
            return "unaffected";
        case token_type::Units:
            return "units";
        case token_type::Until:
            return "until";
        case token_type::Use:
            return "use";
        case token_type::Variable:
            return "variable";
        case token_type::Wait:
            return "wait";
        case token_type::When:
            return "when";
        case token_type::While:
            return "while";
        case token_type::With:
            return "with";
        case token_type::Sll:
            return "sll";
        case token_type::Sla:
            return "sla";
        case token_type::Sra:
            return "sra";
        case token_type::Srl:
            return "srl";
        case token_type::Rol:
            return "rol";
        case token_type::Ror:
            return "ror";
        case token_type::Protected:
            return "protected";
        case token_type::Assume:
            return "assume";
        case token_type::Context:
            return "context";
        case token_type::Cover:
            return "cover";
        case token_type::Default:
            return "default";
        case token_type::Force:
            return "force";
        case token_type::Parameter:
            return "parameter";
        case token_type::Property:
            return "property";
        case token_type::Release:
            return "release";
        case token_type::Restrict:
            return "restrict";
        case token_type::Restrict_Guarantee:
            return "restrict_guarantee";
        case token_type::Sequence:
            return "sequence";
        case token_type::Inherit:
            return "inherit";
        case token_type::Vmode:
            return "vmode";
        case token_type::Vprop:
            return "vprop";
        case token_type::Vunit:
            return "vunit";
        case token_type::And_And:
            return "&&";
        case token_type::Bar_Bar:
            return "||";
        case token_type::Left_Curly:
            return "{";
        case token_type::Right_Curly:
            return "}";
        case token_type::Exclam_Mark:
            return "!";
        case token_type::Brack_Star:
            return "[*";
        case token_type::Brack_Plus_Brack:
            return "[+]";
        case token_type::Brack_Arrow:
            return "[->";
        case token_type::Brack_Equal:
            return "[=";
        case token_type::Bar_Arrow:
            return "|->";
        case token_type::Bar_Double_Arrow:
            return "|=>";
        case token_type::Minus_Greater:
            return "->";
        case token_type::Equiv_Arrow:
            return "<->";
        case token_type::Arobase:
            return "@";
        case token_type::Private:
            return "private";
        case token_type::View:
            return "view";
        default:
            return "Unknown Token";
        }
    }

    token_type close_paren_type(token_type ttype)
    {
        switch (ttype)
        {
            break;
        case token_type::Left_Bracket:
            return token_type::Right_Bracket;
        case token_type::Left_Paren:
            return token_type::Right_Paren;
        default:
            return token_type::Invalid;
        }
    }

    // Return the length of the substring matching [a-zA-Z0-9_]
    std::size_t get_name_len(const std::string &text)
    {
        auto nonMatchingCharPos = std::find_if_not(text.begin(), text.end(), [](char c)
                                                   { return std::isalnum(c) || c == '_'; });

        return (nonMatchingCharPos != text.end()) ? static_cast<std::size_t>(std::distance(text.begin(), nonMatchingCharPos)) : text.size();
    }

} // namespace vhdlsem