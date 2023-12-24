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
// AST base code
//===========================================================================

#include <iostream>

#ifndef AST_BASE_H
#define AST_BASE_H

namespace vlark
{
    class ast
    {
    public:
        ast() = default;
        ast(const ast &) = delete;
        ast &operator=(const ast &) = delete;
        ast(ast &&) = delete;
        ast &operator=(ast &&) = delete;
    };

}

#endif // AST_BASE_H