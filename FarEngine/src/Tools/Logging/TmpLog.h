#pragma once
#include <iostream>
#include <stdio.h>

#define ANSI_COLOR_RED          "\x1b[31m"
#define ANSI_COLOR_BOLD_RED     "\x1b[1;31m"
#define ANSI_COLOR_GREEN        "\x1b[32m"
#define ANSI_COLOR_BOLD_GREEN   "\x1b[1;32m"
#define ANSI_COLOR_YELLOW       "\x1b[33m"
#define ANSI_COLOR_BOLD_YELLOW  "\x1b[1;33m"
#define ANSI_COLOR_BLUE         "\x1b[34m"
#define ANSI_COLOR_BOLD_BLUE    "\x1b[1;34m"
#define ANSI_COLOR_MAGENTA      "\x1b[35m"
#define ANSI_COLOR_BOLD_MAGENTA "\x1b[1;35m"
#define ANSI_COLOR_CYAN         "\x1b[36m"
#define ANSI_COLOR_BOLD_CYAN    "\x1b[1;36m"
#define ANSI_COLOR_RESET        "\x1b[0m"

#define FAR_RED(...) printf(ANSI_COLOR_RED __VA_ARGS__ ANSI_COLOR_RESET "\n")
#define FAR_BRED(...) printf(ANSI_COLOR_BOLD_RED __VA_ARGS__ ANSI_COLOR_RESET "\n")
#define FAR_GREEN(...) printf(ANSI_COLOR_GREEN __VA_ARGS__ ANSI_COLOR_RESET "\n")
#define FAR_BGREEN(...) printf(ANSI_COLOR_BOLD_GREEN __VA_ARGS__ ANSI_COLOR_RESET "\n")
#define FAR_YELLOW(...) printf(ANSI_COLOR_YELLOW __VA_ARGS__ ANSI_COLOR_RESET "\n")
#define FAR_BYELLOW(...) printf(ANSI_COLOR_BOLD_YELLOW __VA_ARGS__ ANSI_COLOR_RESET "\n")
#define FAR_BLUE(...) printf(ANSI_COLOR_BLUE __VA_ARGS__ ANSI_COLOR_RESET "\n")
#define FAR_BBLUE(...) printf(ANSI_COLOR_BOLD_BLUE __VA_ARGS__ ANSI_COLOR_RESET "\n")
#define FAR_MAGENTA(...) printf(ANSI_COLOR_MAGENTA __VA_ARGS__ ANSI_COLOR_RESET "\n")
#define FAR_BMAGENTA(...) printf(ANSI_COLOR_BOLD_MAGENTA __VA_ARGS__ ANSI_COLOR_RESET "\n")
#define FAR_CYAN(...) printf(ANSI_COLOR_CYAN __VA_ARGS__ ANSI_COLOR_RESET "\n")
#define FAR_BCYAN(...) printf(ANSI_COLOR_BOLD_CYAN __VA_ARGS__ ANSI_COLOR_RESET "\n")

//char __lg_output[512];
//#define FAR_LOG(...) sprintf(__lg_output, ANSI_COLOR_MAGENTA "FarEngine:" ANSI_COLOR_RESET ANSI_COLOR_BOLD_CYAN "Log:\t\t" ANSI_COLOR_RESET ANSI_COLOR_CYAN __VA_ARGS__ ANSI_COLOR_RESET "\n"); std::cout << output;
//#define FAR_LOG(...) printf(ANSI_COLOR_MAGENTA "FarEngine:" ANSI_COLOR_RESET ANSI_COLOR_BOLD_CYAN "Log:\t\t" ANSI_COLOR_RESET ANSI_COLOR_CYAN __VA_ARGS__ ANSI_COLOR_RESET "\n")//; fflush(stdout);
//#define FAR_DEBUG(...) printf(ANSI_COLOR_MAGENTA "FarEngine:" ANSI_COLOR_RESET ANSI_COLOR_BOLD_GREEN "Debug:\t" ANSI_COLOR_RESET ANSI_COLOR_GREEN __VA_ARGS__ ANSI_COLOR_RESET "\n")//; fflush(stdout);
//#define FAR_WARN(...) printf(ANSI_COLOR_MAGENTA "FarEngine:" ANSI_COLOR_RESET ANSI_COLOR_BOLD_YELLOW "Warn:\t\t" ANSI_COLOR_RESET ANSI_COLOR_YELLOW __VA_ARGS__ ANSI_COLOR_RESET "\n")//; fflush(stdout);
//#define FAR_ERROR(...) printf(ANSI_COLOR_MAGENTA "FarEngine:" ANSI_COLOR_RESET ANSI_COLOR_BOLD_RED "Error:\t" ANSI_COLOR_RESET ANSI_COLOR_RED __VA_ARGS__ ANSI_COLOR_RESET "\n")//; fflush(stdout);
#define INIT ANSI_COLOR_RED ANSI_COLOR_RESET
#define FAR_LOG(...) std::cout << ANSI_COLOR_MAGENTA << "FarEngine:" << ANSI_COLOR_RESET << ANSI_COLOR_BOLD_CYAN <<"Log:\t\t"<< ANSI_COLOR_RESET<<  ANSI_COLOR_CYAN << __VA_ARGS__ << ANSI_COLOR_RESET << std::endl;
#define FAR_DEBUG(...) std::cout << ANSI_COLOR_MAGENTA << "FarEngine:" << ANSI_COLOR_RESET << ANSI_COLOR_BOLD_GREEN <<"Debug:\t" <<ANSI_COLOR_RESET << ANSI_COLOR_GREEN << __VA_ARGS__ << ANSI_COLOR_RESET << std::endl;
#define FAR_WARN(...) std::cout << ANSI_COLOR_MAGENTA << "FarEngine:" << ANSI_COLOR_RESET << ANSI_COLOR_BOLD_YELLOW<< "Warn:\t\t"<< ANSI_COLOR_RESET<<  ANSI_COLOR_YELLOW << __VA_ARGS__ << ANSI_COLOR_RESET << std::endl;
#define FAR_ERROR(...) std::cout << ANSI_COLOR_MAGENTA << "FarEngine:" << ANSI_COLOR_RESET << ANSI_COLOR_BOLD_RED <<"Error:\t" <<ANSI_COLOR_RESET << ANSI_COLOR_RED << __VA_ARGS__ << ANSI_COLOR_RESET << std::endl;

//#define STDFAR_LOG(...) printf(ANSI_COLOR_MAGENTA "FarEngine:" ANSI_COLOR_RESET ANSI_COLOR_BOLD_CYAN "Debug:\t" ANSI_COLOR_RESET ANSI_COLOR_CYAN __VA_ARGS__ ANSI_COLOR_RESET "\n")//; fflush(stdout);
//#define STDFAR_DEBUG(...) printf(ANSI_COLOR_MAGENTA "FarEngine:" ANSI_COLOR_RESET ANSI_COLOR_BOLD_GREEN "Debug:\t" ANSI_COLOR_RESET ANSI_COLOR_GREEN __VA_ARGS__ ANSI_COLOR_RESET "\n")//; fflush(stdout);
//#define STDFAR_WARN(...) printf(ANSI_COLOR_MAGENTA "FarEngine:" ANSI_COLOR_RESET ANSI_COLOR_BOLD_YELLOW "Debug:\t" ANSI_COLOR_RESET ANSI_COLOR_YELLOW __VA_ARGS__ ANSI_COLOR_RESET "\n")//; fflush(stdout);
//#define STDFAR_ERROR(...) printf(ANSI_COLOR_MAGENTA "FarEngine:" ANSI_COLOR_RESET ANSI_COLOR_BOLD_RED "Warn:\t\t" ANSI_COLOR_RESET ANSI_COLOR_RED __VA_ARGS__ ANSI_COLOR_RESET "\n")//; fflush(stdout);