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

#include "ast.hpp"
#include "parser.hpp"
#include <ranges>

namespace vlark
{

    ast parser::parse(const std::string_view filepath)
    {
        vlark::sourceBuffer sbufferFile;

        auto status = sbufferFile.load(std::string(filepath));

        if (!status)
        {
            return ast();
        }

        int count = 0;
        for (auto &line : sbufferFile.get_lines())
        {
            std::cout << "Line " << count << ": [ " << static_cast<int>(line.cat) << " ]  " << line.text << std::endl;
            count++;
        }

        // Implement the parsing logic here
        // This is just a placeholder
        std::cout << "Parsing code: " << filepath << std::endl;

        // Return a placeholder ast for demonstration purposes
        return ast();
    }

} // namespace vlark
