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
// All parse interface code
//===========================================================================

#include "token.h"

#ifndef PARSER_H
#define PARSER_H

namespace vlark
{

    // Forward declaration of the ast class
    class ast;

    class parser
    {
    public:
        parser() = default;
        parser(const parser &) = delete;
        parser &operator=(const parser &) = delete;
        parser(parser &&) = delete;
        parser &operator=(parser &&) = delete;

        // Parse the code and return the abstract syntax tree
        [[nodiscard]] ast parse_code(const std::string_view code);

        [[nodiscard]] ast parse(const std::string_view filepath);
    };

}

#endif // PARSER_H