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

#include <iostream>
#include <algorithm>
#include <cctype>
#include <cstdint>
#include <string>
#include <string_view>
#include <vector>
#include <unordered_map>
#include <iomanip>
#include <deque>

#ifndef UTILS_H
#define UTILS_H

namespace vlark
{

    struct source_line
    {
        std::string text;

        enum class category
        {
            empty,
            comment,      // --
            multii_com_s, // /**/
            multii_com,   // is part of the comments
            multi_com_e,
            raw
        };
        category cat;

        source_line(std::string_view t = {}, category c = category::empty)
            : text{t}, cat{c}
        {
        }

        // ssize_t indent() const { return std::find_if_not(text.begin(), text.end(), &isspace) - text.begin(); }
    };

    using lineno_t = int32_t;
    using colno_t = int32_t;

    struct source_position
    {
        lineno_t lineno; // offset into program source
        colno_t colno;   // offset into line column

        source_position(lineno_t l = 1, colno_t c = 1)
            : lineno{l}, colno{c}
        {
        }

        auto operator<=>(source_position const &) const = default;

        auto to_string() const -> std::string { return "(" + std::to_string(lineno) + "," + std::to_string(colno) + ")"; }
    };

    bool is_empty_line(std::string_view line);

    inline constexpr std::string_view help_string = R"(
Usage: vlark [flags] <input>
    Flags:
        -f,<file>:          specify the vhdl file you want to parse.
        --print-ast:        print the AST before codegen, after transforms.
        -h, --help:         print this help message.
        -v, --version:      print version and license information.
)";

    // cmdline handler -- simple and dumb

    class CmdLine
    {
    public:
        CmdLine(int argc, char *argv[]) : args(argv + 1, argv + argc)
        {
            parseArgs();
        }

        void processArgs()
        {
            if (args.empty())
            {
                std::cout << "unknown args parsed empty"
                          << "\n";
                std::cout << help_string << "\n";
                exit(EXIT_SUCCESS);
            }

            for (auto &[arg, opt] : options)
            {
                if (arg == "-h" || arg == "--help")
                {
                    opt_help = true;
                    std::cout << help_string << "\n";
                    return;
                }
                else if (arg == "-v" || arg == "--version")
                {
                    opt_version = true;
                    gen_version();
                    return;
                }
                else if (arg == "-f" || arg == "--file")
                {
                    // Check if the option has values
                    if (opt.empty())
                    {
                        std::cerr << "Error: --file option requires one or more file names." << std::endl;
                        std::cerr << "given 2" << options["-f"][0] << "\n";
                        return;
                    }
                    else
                    { // support multiple files later
                        filename = opt[0];
                    }
                }
                else
                {
                    std::cout << "unknown args ----> " << arg << "\n";
                    std::cout << help_string << "\n";
                    exit(EXIT_SUCCESS);
                }
            }
        }
        bool opt_help = false;
        bool opt_version = false;

        std::string_view geet_filename() const { return filename; }

    private:
        std::string filename{};

        std::vector<std::string_view> args; // Vector of string_view to store command-line arguments
        std::unordered_map<std::string_view, std::vector<std::string_view>> options;

        void parseArgs()
        {
            std::string_view currentOption;

            for (const std::string_view arg : args)
            {
                if (arg.starts_with('-'))
                {
                    // Check if the argument is an option
                    currentOption = arg;
                    options[currentOption]; // Initialize the option in the map
                }
                else
                {
                    // Add the argument to the current option's values
                    options[currentOption].push_back(arg);
                }
            }

            processArgs();
        }

        void gen_version()
        {
            std::string a = __DATE__;
            std::string b = __TIME__;

            const char *month_codes[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

            int day = std::stoi(a.substr(4, 2));
            const char *month = month_codes[(std::find(std::begin(month_codes), std::end(month_codes), a.substr(0, 3)) - std::begin(month_codes))];
            int year = std::stoi(a.substr(7)) - 15;

            int hour = std::stoi(b.substr(0, 2));
            int minute = std::stoi(b.substr(3, 2));

            std::cout << "\"" << year << month << std::setw(2) << std::setfill('0') << day << ":"
                      << std::setw(2) << std::setfill('0') << hour
                      << std::setw(2) << std::setfill('0') << minute << "\"" << std::endl;
        }

        void print_version()
        {
            std::cout << "\nvlark version v0.3.0   Build ";
            gen_version();

            std::cout << "\nCopyright(c) Dennis Addo   All rights reserved\n"
                      << "\nMIT License"
                      << "\n  No commercial use"
                      << "\nAbsolutely no warranty - try at your own risk\n";
        }

        // Delete copy constructor and copy assignment operator
        CmdLine(const CmdLine &) = delete;
        CmdLine &operator=(const CmdLine &) = delete;
    };

    //
    //
    //-----------------------------------------------------------------------
    //
    //  sourceBuffer: Source_buffer is an in-memory of the complete source file.
    //  breaken down into lines
    //-----------------------------------------------------------------------
    //
    class sourceBuffer
    {
        std::deque<source_line> lines{};
        std::string filename;

        static const int max_line_len = 98'000;

        bool load(std::string const &filename);

    public:
        //-----------------------------------------------------------------------
        //  Constructor (maybe default will be better)
        //
        //
        sourceBuffer(const std::string &file) : filename(file)
        {
            load(filename);
        }

        std::deque<source_line> &get_lines()
        {
            return lines;
        }

        std::deque<source_line> const &get_lines() const
        {
            return lines;
        }

        //  No copying
        //
        sourceBuffer(sourceBuffer const &) = delete;
        sourceBuffer &operator=(sourceBuffer const &) = delete;
        sourceBuffer(sourceBuffer &&) = delete;
        sourceBuffer &operator=(sourceBuffer &&) = delete;
    };

} // namespace vlark

#endif