// Copyright(c) 2023 Dennis Addo

// MIT License

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "parser.hpp"

int main(int argc, char *argv[])
{
    vlark::CmdLine cmdline(argc, argv);

    if (cmdline.opt_help)
    {
        return EXIT_SUCCESS;
    }

    if (cmdline.opt_version)
    {
        return EXIT_SUCCESS;
    }

    vlark::parser parser;

    parser.parse(cmdline.geet_filename());

    std::cout << "ok not working well here am I \n";
    return 0;
}