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
            preprocessor,
            comment,
            lib,
            dunit,
        };
        category cat;

        bool all_tokens_are_densely_spaced = true; // to be overridden in lexing if they're not

        source_line(std::string_view t = {}, category c = category::empty)
            : text{t}, cat{c}
        {
        }

        ssize_t indent() const { return std::find_if_not(text.begin(), text.end(), &isspace) - text.begin(); }
    };

    using lineno_t = int32_t;
    using colno_t = int32_t; // not int16_t... it can be >90,000 char line

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

    //
    //  error: represents a user-readable error message
    //
    //-----------------------------------------------------------------------
    //
    struct error_entry
    {
        source_position where;
        std::string msg;
        bool internal = false;
        bool fallback = false; // only emit this message if there was nothing better

        error_entry(source_position w, std::string_view m, bool i = false, bool f = false)
            : where{w}, msg{m}, internal{i}, fallback{f}
        {
        }

        auto operator==(error_entry const &that) -> bool { return where == that.where && msg == that.msg; }

        void print(auto &o, std::string const &file) const;
    };

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
                std::cout << "unknown args parsed "
                          << "\n";
                std::cout << help_string << "\n";
                exit(EXIT_SUCCESS);
            }

            for (const std::string_view arg : args)
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
                    if (options["--file"].empty() || options["-f"].empty())
                    {
                        std::cerr << "Error: --file option requires one or more file names." << std::endl;
                        return;
                    }

                    // todo: fix this later to handle multiple files
                    //  at the moment only 1 vhdl file can be processed at a time
                    for (const std::string_view fn : options["--file"])
                    {
                        filename = fn;
                        break;
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

} // namespace vhdlsem

#endif