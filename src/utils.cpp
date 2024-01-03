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
// Common Utils used throughout the code
//===========================================================================

#include "utils.h"
#include <cassert>
#include <fstream>
#include <iterator>
#include <ostream>

namespace vlark
{

//-----------------------------------------------------------------------
//  load: extract line-by-line file content
//
bool sourceBuffer::load(std::string const& fname)
{
    std::ifstream in{fname};
    if (!in.is_open())
    {
        return false;
    }
    // use c++ string later if possible
    char buf[max_line_len];

    auto skip_space = [&](std::string_view v) -> size_t {
        auto cl_in = std::ranges::find_if(v.begin(), v.end(), [](char ch) { return !std::isspace(ch); });
        return std::distance(v.begin(), cl_in);
    };

    while (in.getline(&buf[0], max_line_len))
    {
        std::string_view nstr(&buf[skip_space(buf)]);

        //  Handle preprocessor source separately, they're outside the language
        //
        if (is_empty_line(buf))
        {
            lines.emplace_back(&buf[0], source_line::category::empty);
        }
        else if (nstr.starts_with('-') && nstr.starts_with("--"))
        {
            lines.emplace_back(&buf[0], source_line::category::comment);
        }
        else if (nstr.starts_with('/') && nstr.starts_with("/*"))
        {
            lines.emplace_back(&buf[0], source_line::category::multii_com_s);
            auto cmult = false;
            while (!cmult && in.getline(&buf[0], max_line_len))
            {
                std::string_view str(&buf[0]);
                cmult = str.find("*/") != std::string_view::npos;
                if (cmult)
                {
                    lines.emplace_back(&buf[0], source_line::category::multi_com_e);
                    break;
                }
                lines.emplace_back(&buf[0], source_line::category::multii_com);
            }
        }
        else
        {
            lines.emplace_back(&buf[0], source_line::category::raw);
        }
    }

    //   prevent buffer overflow
    //  Make sure we are safe
    if (in.gcount() >= max_line_len - 1)
    {
        std::cerr << "source line too long - length must be less than ";
        return false;
    }

    //  This shouldn't be possible, so check it anyway
    //
    if (!in.eof())
    {
        std::cerr << "unexpected error reading source lines - did not reach EOF";
        return false;
    }

    return true;
}

bool is_empty_line(std::string_view line)
{
    return std::ranges::all_of(line.begin(), line.end(), [](char c) { return std::isspace(c) || c == '\n'; });
}

} // namespace vlark
