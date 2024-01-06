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
    case token_type::Invalid: return "<invalid>";
    case token_type::Left_Paren: return "(";
    case token_type::Right_Paren: return ")";
    case token_type::Left_Bracket: return "[";
    case token_type::Right_Bracket: return "]";
    case token_type::Colon: return ":";
    case token_type::Semi_Colon: return ";";
    case token_type::Comma: return ",";
    case token_type::Tick: return "'";
    case token_type::Double_Star: return "**";
    case token_type::Double_Arrow: return "=>";
    case token_type::Assign: return ":=";
    case token_type::Bar: return "|";
    case token_type::Box: return "<>";
    case token_type::Dot: return ".";
    case token_type::Block_Comment_Start: return "/*";
    case token_type::Block_Comment_End: return "*/";
    case token_type::Eof: return "<EOF>";
    case token_type::Newline: return "<newline>";
    case token_type::Line_Comment: return "<line-comment>";
    case token_type::Block_Comment_Text: return "<block-comment>";
    case token_type::Character: return "<character>";
    case token_type::Identifier: return "<identifier>";
    case token_type::Integer:
    case token_type::Integer_Letter: return "<integer>";
    case token_type::Real: return "<real>";
    case token_type::String: return "<string>";
    case token_type::Bit_String: return "<bit string>";
    case token_type::Equal: return "=";
    case token_type::Not_Equal: return "/=";
    case token_type::Less: return "<";
    case token_type::Less_Equal: return "<=";
    case token_type::Greater: return ">";
    case token_type::Greater_Equal: return ">=";
    case token_type::Match_Equal: return "?=";
    case token_type::Match_Not_Equal: return "?/=";
    case token_type::Match_Less: return "?<";
    case token_type::Match_Less_Equal: return "?<=";
    case token_type::Match_Greater: return "?>";
    case token_type::Match_Greater_Equal: return "?>=";
    case token_type::Plus: return "+";
    case token_type::Minus: return "-";
    case token_type::Ampersand: return "&";
    case token_type::Question_Mark: return "?";
    case token_type::Condition: return "??";
    case token_type::Double_Less: return "<<";
    case token_type::Double_Greater: return ">>";
    case token_type::Caret: return "^";
    case token_type::Star: return "*";
    case token_type::Slash: return "/";
    case token_type::Mod: return "mod";
    case token_type::Rem: return "rem";
    case token_type::And: return "and";
    case token_type::Or: return "or";
    case token_type::Xor: return "xor";
    case token_type::Nand: return "nand";
    case token_type::Nor: return "nor";
    case token_type::Xnor: return "xnor";
    case token_type::Abs: return "abs";
    case token_type::Access: return "access";
    case token_type::After: return "after";
    case token_type::Alias: return "alias";
    case token_type::All: return "all";
    case token_type::Architecture: return "architecture";
    case token_type::Array: return "array";
    case token_type::Assert: return "assert";
    case token_type::Attribute: return "attribute";
    case token_type::Begin: return "begin";
    case token_type::Block: return "block";
    case token_type::Body: return "body";
    case token_type::Buffer: return "buffer";
    case token_type::Bus: return "bus";
    case token_type::Case: return "case";
    case token_type::Component: return "component";
    case token_type::Configuration: return "configuration";
    case token_type::Constant: return "constant";
    case token_type::Disconnect: return "disconnect";
    case token_type::Downto: return "downto";
    case token_type::Else: return "else";
    case token_type::Elsif: return "elsif";
    case token_type::End: return "end";
    case token_type::Entity: return "entity";
    case token_type::Exit: return "exit";
    case token_type::File: return "file";
    case token_type::For: return "for";
    case token_type::Function: return "function";
    case token_type::Generate: return "generate";
    case token_type::Generic: return "generic";
    case token_type::Group: return "group";
    case token_type::Guarded: return "guarded";
    case token_type::If: return "if";
    case token_type::Impure: return "impure";
    case token_type::In: return "in";
    case token_type::Inertial: return "inertial";
    case token_type::Inout: return "inout";
    case token_type::Is: return "is";
    case token_type::Label: return "label";
    case token_type::Library: return "library";
    case token_type::Linkage: return "linkage";
    case token_type::Literal: return "literal";
    case token_type::Loop: return "loop";
    case token_type::Map: return "map";
    case token_type::New: return "new";
    case token_type::Next: return "next";
    case token_type::Not: return "not";
    case token_type::Null: return "null";
    case token_type::Of: return "of";
    case token_type::On: return "on";
    case token_type::Open: return "open";
    case token_type::Out: return "out";
    case token_type::Others: return "others";
    case token_type::Package: return "package";
    case token_type::Port: return "port";
    case token_type::Postponed: return "postponed";
    case token_type::Procedure: return "procedure";
    case token_type::Process: return "process";
    case token_type::Pure: return "pure";
    case token_type::Range: return "range";
    case token_type::Record: return "record";
    case token_type::Register: return "register";
    case token_type::Reject: return "reject";
    case token_type::Report: return "report";
    case token_type::Return: return "return";
    case token_type::Select: return "select";
    case token_type::Severity: return "severity";
    case token_type::Shared: return "shared";
    case token_type::Signal: return "signal";
    case token_type::Subtype: return "subtype";
    case token_type::Then: return "then";
    case token_type::To: return "to";
    case token_type::Transport: return "transport";
    case token_type::Type: return "type";
    case token_type::Unaffected: return "unaffected";
    case token_type::Units: return "units";
    case token_type::Until: return "until";
    case token_type::Use: return "use";
    case token_type::Variable: return "variable";
    case token_type::Wait: return "wait";
    case token_type::When: return "when";
    case token_type::While: return "while";
    case token_type::With: return "with";
    case token_type::Sll: return "sll";
    case token_type::Sla: return "sla";
    case token_type::Sra: return "sra";
    case token_type::Srl: return "srl";
    case token_type::Rol: return "rol";
    case token_type::Ror: return "ror";
    case token_type::Protected: return "protected";
    case token_type::Assume: return "assume";
    case token_type::Context: return "context";
    case token_type::Cover: return "cover";
    case token_type::Default: return "default";
    case token_type::Force: return "force";
    case token_type::Parameter: return "parameter";
    case token_type::Property: return "property";
    case token_type::Release: return "release";
    case token_type::Restrict: return "restrict";
    case token_type::Restrict_Guarantee: return "restrict_guarantee";
    case token_type::Sequence: return "sequence";
    case token_type::Inherit: return "inherit";
    case token_type::Vmode: return "vmode";
    case token_type::Vprop: return "vprop";
    case token_type::Vunit: return "vunit";
    case token_type::And_And: return "&&";
    case token_type::Bar_Bar: return "||";
    case token_type::Left_Curly: return "{";
    case token_type::Right_Curly: return "}";
    case token_type::Exclam_Mark: return "!";
    case token_type::Brack_Star: return "[*";
    case token_type::Brack_Plus_Brack: return "[+]";
    case token_type::Brack_Arrow: return "[->";
    case token_type::Brack_Equal: return "[=";
    case token_type::Bar_Arrow: return "|->";
    case token_type::Bar_Double_Arrow: return "|=>";
    case token_type::Minus_Greater: return "->";
    case token_type::Equiv_Arrow: return "<->";
    case token_type::Arobase: return "@";
    case token_type::Private: return "private";
    case token_type::View: return "view";
    default: return "Unknown Token";
    }
}

std::string token_tostr(token_type token)
{
    return _asstr<std::string>(token);
}

token_type close_paren_type(token_type ttype)
{
    switch (ttype)
    {
        break;
    case token_type::Left_Bracket: return token_type::Right_Bracket;
    case token_type::Left_Paren: return token_type::Right_Paren;
    default: return token_type::Invalid;
    }
}

// Return the length of the substring matching [a-zA-Z0-9_]
std::size_t get_name_len(const std::string& text)
{
    auto nonMatchingCharPos =
        std::find_if_not(text.begin(), text.end(), [](char c) { return std::isalnum(c) || c == '_'; });

    return (nonMatchingCharPos != text.end())
               ? static_cast<std::size_t>(std::distance(text.begin(), nonMatchingCharPos))
               : text.size();
}

bool is_valid_identifier(std::string_view token)
{
    if (token.empty() || !std::isalpha(token[0]))
    {
        return false;
    }

    auto st = std::isdigit(token[0]) || token.starts_with('_');
    return !st;
}

// This handles are reserved names and also identifiers
// Identifiers are the last option checked here if all reserved names are exhausted
//
bool handle_names(std::deque<token>& tokens, std::string_view sbstr, size_t lineno, size_t col_no)
{
    if (sbstr.empty())
    {
        return false;
    }

    static const std::unordered_map<std::string_view, token_type> keyword_map = {
        {"use", token_type::Use},
        {"alias", token_type::Alias},
        {"architecture", token_type::Architecture},
        {"begin", token_type::Begin},
        {"body", token_type::Body},
        {"constant", token_type::Constant},
        {"downto", token_type::Downto},
        {"if", token_type::If},
        {"else", token_type::Else},
        {"elsif", token_type::Elsif},
        {"end", token_type::End},
        {"entity", token_type::Entity},
        {"generate", token_type::Generate},
        {"in", token_type::In},
        {"library", token_type::Library},
        {"out", token_type::Out},
        {"port", token_type::Port},
        {"of", token_type::Of},
        {"others", token_type::Others},
        {"package", token_type::Package},
        {"procedure", token_type::Procedure},
        {"process", token_type::Process},
        {"return", token_type::Return},
        {"signal", token_type::Signal},
        {"then", token_type::Then},
        {"to", token_type::To},
        {"variable", token_type::Variable},
        {"default", token_type::Default},
        {"parameter", token_type::Parameter},
        {"and", token_type::And},
        {"or", token_type::Or},
        {"xor", token_type::Xor},

        // Add more keywords and token types as needed
    };

    auto it = keyword_map.find(sbstr);
    if (it != keyword_map.end())
    {
        tokens.emplace_back(sbstr, token_position(lineno, col_no), it->second);
        return true;
    }
    else
    {
        if (is_valid_identifier(sbstr))
        {
            tokens.emplace_back(sbstr, token_position(lineno, col_no), token_type::Identifier);

            return true;
        }
        std::cerr << "token not valid keyword: " << sbstr << " \n";
    }

    return false;
}

void find_add_tokens(std::deque<token>& tokens, source_line& line, size_t lineno)
{
    std::string_view carr(line.text);
    size_t ori_len = line.text.size();
    size_t lo = 0;

    while ((ori_len > lo) && (carr[lo] != '\n'))
    {
        /* code */
        char ch = carr[lo];
        if (std::isspace(ch) || ch == '\r')
        {
            lo++;
            continue;
        }

        switch (ch)
        {
            // clang-format off
            case '0':
            case '1': case '2': case '3': 
            case '4': case '5': case '6': 
            case '7': case '8': case '9':
            // clang-format on
            // Handle numeric characters
            std::cerr << ch << " -> Sorry, Integers not implemented yet.\n";
            break;

        case ':': tokens.emplace_back(carr.substr(lo, 1), token_position(lineno, lo), token_type::Colon); break;
        case '=': tokens.emplace_back(carr.substr(lo, 1), token_position(lineno, lo), token_type::Equal); break;
        case '.': tokens.emplace_back(carr.substr(lo, 1), token_position(lineno, lo), token_type::Dot); break;
        case ';': tokens.emplace_back(carr.substr(lo, 1), token_position(lineno, lo), token_type::Semi_Colon); break;
        case ',': tokens.emplace_back(carr.substr(lo, 1), token_position(lineno, lo), token_type::Comma); break;

        case '|': tokens.emplace_back(carr.substr(lo, 1), token_position(lineno, lo), token_type::Bar); break;
        case ')': tokens.emplace_back(carr.substr(lo, 1), token_position(lineno, lo), token_type::Right_Paren); break;
        case '(': tokens.emplace_back(carr.substr(lo, 1), token_position(lineno, lo), token_type::Left_Paren); break;
        case '[': tokens.emplace_back(carr.substr(lo, 1), token_position(lineno, lo), token_type::Left_Bracket); break;
        case ']': tokens.emplace_back(carr.substr(lo, 1), token_position(lineno, lo), token_type::Right_Bracket); break;
        case '\'':
            tokens.emplace_back(carr.substr(lo, 1), token_position(lineno, lo), token_type::Right_Bracket);
            break;
        case '+': tokens.emplace_back(carr.substr(lo, 1), token_position(lineno, lo), token_type::Plus); break;
        case '-': tokens.emplace_back(carr.substr(lo, 1), token_position(lineno, lo), token_type::Minus); break;
        case '^': tokens.emplace_back(carr.substr(lo, 1), token_position(lineno, lo), token_type::Caret); break;

        default:
            if (('A' <= ch && ch <= 'Z') || (('a' <= ch && ch <= 'z')) || (ch == '_'))
            {
                // let extract the reserved keywords and identifiers
                auto tk_len = get_name_len(&carr[lo]);
                auto status = handle_names(tokens, carr.substr(lo, tk_len), lineno, lo);
                lo += status ? tk_len - 1 : 0;
            }
            else
            {
                std::cerr << "Token Unknown " << ch << " \n";
            }
            break;
        }

        lo++; // next char
    }
}

std::deque<token> tokenize_lines(sourceBuffer& sbfile)
{
    auto lines = sbfile.get_lines();
    std::deque<token> tokenlist;
    if (lines.empty())
    {
        std::cerr << "[error]: sourceBufferFile has empty lines of raw data: " << sbfile.get_fpath() << " \n";
        exit(EXIT_FAILURE);
    }

    size_t count_line = 1;
    for (auto& line : lines)
    {
        if (line.cat == source_line::category::raw)
        {
            find_add_tokens(tokenlist, line, count_line);
        }
        count_line++;
    }

    return tokenlist;
}

} // namespace vlark