// bdldfp_intelimpwrapper.t.cpp                                       -*-C++-*-
#include <bdldfp_intelimpwrapper.h>

#include <bsls_platform.h>

#include <bsl_iostream.h>
#include <bsl_cstdlib.h>
#include <bsl_cstring.h>

using namespace BloombergLP;
using bsl::cout;
using bsl::cerr;
using bsl::flush;
using bsl::endl;
using bsl::atoi;

#if !defined(BSLS_PLATFORM_OS_WINDOWS)
// ============================================================================
//                                 TEST PLAN
// ----------------------------------------------------------------------------
//                                  Overview
//                                  --------
// The component under test wraps and includes the Intel DFP headers in a
// specific build mode.
//
// Global Concerns:
//: o Intel Headers are included correctly
//: o No #define detritus is left behind
//
// TBD:
// ----------------------------------------------------------------------------
// CREATORS
//
// MANIPULATORS
//
// ACCESSORS
//
// FREE OPERATORS
//
// TRAITS
// ----------------------------------------------------------------------------
// [ 4] Macro clean environment
// [ 3] Simple function call tests
// [ 2] Intel Decimal types sanity test
// [ 1] Include Sanity Test
// ----------------------------------------------------------------------------


// ============================================================================
//                      STANDARD BDE ASSERT TEST MACROS
// ----------------------------------------------------------------------------

static int testStatus = 0;

static void aSsErT(int c, const char *s, int i)
{
    if (c) {
        cout << "Error " << __FILE__ << "(" << i << "): " << s
             << "    (failed)" << endl;
        if (testStatus >= 0 && testStatus <= 100) ++testStatus;
    }
}
#define ASSERT(X) { aSsErT(!(X), #X, __LINE__); }

// ============================================================================
//                  STANDARD BDE LOOP-ASSERT TEST MACROS
// ----------------------------------------------------------------------------

#define LOOP_ASSERT(I,X) { \
   if (!(X)) { cout << #I << ": " << I << "\n"; aSsErT(1, #X, __LINE__); }}

#define LOOP2_ASSERT(I,J,X) { \
   if (!(X)) { cout << #I << ": " << I << "\t" << #J << ": " \
              << J << "\n"; aSsErT(1, #X, __LINE__); } }

#define LOOP3_ASSERT(I,J,K,X) { \
   if (!(X)) { cout << #I << ": " << I << "\t" << #J << ": " << J << "\t" \
              << #K << ": " << K << "\n"; aSsErT(1, #X, __LINE__); } }

#define LOOP4_ASSERT(I,J,K,L,X) { \
   if (!(X)) { cout << #I << ": " << I << "\t" << #J << ": " << J << "\t" << \
       #K << ": " << K << "\t" << #L << ": " << L << "\n"; \
       aSsErT(1, #X, __LINE__); } }

#define LOOP5_ASSERT(I,J,K,L,M,X) { \
   if (!(X)) { cout << #I << ": " << I << "\t" << #J << ": " << J << "\t" << \
       #K << ": " << K << "\t" << #L << ": " << L << "\t" << \
       #M << ": " << M << "\n"; \
       aSsErT(1, #X, __LINE__); } }

#define LOOP6_ASSERT(I,J,K,L,M,N,X) { \
   if (!(X)) { cout << #I << ": " << I << "\t" << #J << ": " << J << "\t" << \
       #K << ": " << K << "\t" << #L << ": " << L << "\t" << \
       #M << ": " << M << "\t" << #N << ": " << N << "\n"; \
       aSsErT(1, #X, __LINE__); } }

// ============================================================================
//                  SEMI-STANDARD TEST OUTPUT MACROS
// ----------------------------------------------------------------------------

#define P(X) cout << #X " = " << (X) << endl; // Print identifier and value.
#define Q(X) cout << "<| " #X " |>" << endl;  // Quote identifier literally.
#define P_(X) cout << #X " = " << (X) << ", " << flush; // 'P(X)' without '\n'
#define T_ cout << "\t" << flush;             // Print tab w/o newline.
#define L_ __LINE__                           // current Line number

// ============================================================================
//                  GLOBAL TYPEDEFS/CONSTANTS FOR TESTING
// ----------------------------------------------------------------------------

// ============================================================================
//                              MAIN PROGRAM
// ----------------------------------------------------------------------------

int main(int argc, char* argv[])
{
    int            test = argc > 1 ? atoi(argv[1]) : 0;
    int         verbose = argc > 2;
    int     veryVerbose = argc > 3;
    int veryveryVerbose = argc > 4;


    cout << "TEST " << __FILE__ << " CASE " << test << endl;;

    switch (test) { case 0:
      case 4: {
        // --------------------------------------------------------------------
        // MACRO CLEAN ENVIRONMENT
        //
        // Concerns:
        //: 1 The various macros used in configuring, tuning, and compiling the
        //:   Intel DFP headers are disabled after inclusion.
        //
        // Plan:
        //: 1 Follow a pattern of '#ifdef <MACRO>',
        //:   'ASSERT(false && "<MACRO>   still declared");', and '#endif' in
        //:   confirming that each macro is disabled. (C-1)
        //
        // Testing:
        //   Macro clean environment
        // --------------------------------------------------------------------
        if (verbose) cout << std::endl
                          << "MACRO CLEAN ENVIRONMENT" << std::endl
                          << "=======================" << std::endl;

        #ifdef DECIMAL_CALL_BY_REFERENCE
        ASSERT(false && "DECIMAL_CALL_BY_REFERENCE still declared");
        #endif

        #ifdef DECIMAL_GLOBAL_ROUNDING
        ASSERT(false && "DECIMAL_GLOBAL_ROUNDING still declared");
        #endif

        #ifdef DECIMAL_GLOBAL_EXCEPTION_FLAGS
        ASSERT(false && "DECIMAL_GLOBAL_EXCEPTION_FLAGS still declared");
        #endif

        #ifdef BDLDFP_INTELIMPWRAPPER_FAKE_DEFINE_LINUX
        ASSERT(false &&
                    "BDLDFP_INTELIMPWRAPPER_FAKE_DEFINE_LINUX still declared");
        #endif

        #ifndef BID_BIG_ENDIAN
        ASSERT(false && "BID_BIG_ENDIAN setting for Intel was not defined.");
        #else
        #  ifdef BSLS_PLATFORM_IS_BIG_ENDIAN
        const bool big_endian = true;
        #  elif defined(BSLS_PLATFORM_IS_LITTLE_ENDIAN)
        const bool big_endian = false;
        #  else
        ASSERT(false &&
               "One of big or little endian should have been available"
               " in bsls_platform");
        const bool big_endian = false;
        #  endif
        ASSERT(BID_BIG_ENDIAN == big_endian
                       && "BID_BIG_ENDIAN was not set to the correct setting");
        #endif


      } break;
      case 3: {
        // --------------------------------------------------------------------
        // SIMPLE FUNCTION CALL TESTS
        //   Ensure that we can call functions expected in the Intel DFP
        //   library, and that the ones we call behave reasonably.
        //
        // Concerns:
        //:  1 Intel function prototypes are declared, and are available for
        //:    use.
        //
        // Plan:
        //:  1 Declare variables of the various 'BID_UINTXX' types and call
        //:    some initialization for them. (C-1)
        //:
        //:  2 Compute a simple arithmetic sum for some 'BID_UINTXX' variables.
        //:    (C-1)
        //:
        //:  3 Verify the results of the simple arithmetic computation. (C-1)
        //
        // Testing:
        //   Simple function call tests
        // --------------------------------------------------------------------
        if (verbose) cout << std::endl
                          << "SIMPLE FUNCTION CALL TESTS" << std::endl
                          << "==========================" << std::endl;

        BID_UINT64  doubleDecimal = __bid64_from_int32( 42);
        BID_UINT128   quadDecimal = __bid128_from_int32(42);

        BID_UINT32  singleDecimal2 = __bid32_from_int32( 10);
        BID_UINT64  doubleDecimal2 = __bid64_from_int32( 10);
        BID_UINT128   quadDecimal2 = __bid128_from_int32(10);

        BID_UINT64  doubleDecimalResult = __bid64_from_int32( 52);
        BID_UINT128   quadDecimalResult = __bid128_from_int32(52);

        BID_UINT64  doubleDecimalComputed;
        BID_UINT128   quadDecimalComputed;

        doubleDecimalComputed = __bid64_add( doubleDecimal, doubleDecimal2);
          quadDecimalComputed = __bid128_add(  quadDecimal,   quadDecimal2);

        ASSERT(__bid64_quiet_equal( doubleDecimalResult,
                                    doubleDecimalComputed));
        ASSERT(__bid128_quiet_equal(  quadDecimalResult,
                                      quadDecimalComputed));
      } break;
      case 2: {
        // --------------------------------------------------------------------
        // INTEL DECIMAL TYPES SANITY TEST
        //   Ensure that we can call instantiate variables from the Intel
        //   libary.
        //
        // Concerns:
        //:  1 Intel Decimal types are declared, and are available for use.
        //
        // Plan:
        //:  1 Declare variables of the various 'BID_UINTXX' types and call
        //:    some initialization for them. (C-1)
        //:
        //:  2 Call 'memcmp' on differently initialized variables to verify
        //:    that their representations are distinct. (C-1)
        //
        // Testing:
        //   Intel Decimal types sanity test
        // --------------------------------------------------------------------
        if (verbose) cout << std::endl
                          << "INTEL DECIMAL TYPES SANITY TEST" << std::endl
                          << "===============================" << std::endl;

        // The intel library types work correctly if different values have
        // different bit patterns.

        BID_UINT32  singlePrecisionDecimalStorage = __bid32_from_int32( 42);
        BID_UINT64  doublePrecisionDecimalStorage = __bid64_from_int32( 42);
        BID_UINT128   quadPrecisionDecimalStorage = __bid128_from_int32(42);

        BID_UINT32  singlePrecisionDecimalStorage2 = __bid32_from_int32( 47);
        BID_UINT64  doublePrecisionDecimalStorage2 = __bid64_from_int32( 47);
        BID_UINT128   quadPrecisionDecimalStorage2 = __bid128_from_int32(47);

        ASSERT(bsl::memcmp(&singlePrecisionDecimalStorage,
                           &singlePrecisionDecimalStorage2,
                            sizeof(BID_UINT32)));

        ASSERT(bsl::memcmp(&doublePrecisionDecimalStorage,
                           &doublePrecisionDecimalStorage2,
                            sizeof(BID_UINT64)));

        ASSERT(bsl::memcmp(&  quadPrecisionDecimalStorage,
                           &  quadPrecisionDecimalStorage2,
                            sizeof(BID_UINT128)));
      } break;
      case 1: {
        // --------------------------------------------------------------------
        // INCLUDE SANITY TEST
        //   Find some evidence that the Intel headers are included.
        //   libary.
        //
        // Concerns:
        //:  1 Intel Decimal headers are included.
        //
        // Plan:
        //:  1 Declare a variable of 'BID_UINT64', which should be defined in
        //:    the Intel headers. (C-1)
        //
        // Testing:
        //   Include Sanity Test
        // --------------------------------------------------------------------
        if (verbose) cout << std::endl
                          << "INCLUDE SANITY TEST" << std::endl
                          << "===================" << std::endl;

        // The Intel library makes the BID_UINT64 type an integer.  This test
        // merely gives witness to the intel header inclusion by using one of
        // its types in a specific way.

        BID_UINT64 simpleDecimal;
        simpleDecimal = 42;
      } break;
      default: {
        cerr << "WARNING: CASE `" << test << "' NOT FOUND." << endl;
        testStatus = -1;
      }
    }

    if (testStatus > 0) {
        cerr << "Error, non-zero test status = " << testStatus << "." << endl;
    }

    return testStatus;
}

#else // !defined(BSLS_PLATFORM_OS_WINDOWS)

int main()
{
    return -1;
}

#endif // !defined(BSLS_PLATFORM_OS_WINDOWS)

// ----------------------------------------------------------------------------
// Copyright (C) 2014 Bloomberg L.P.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
// ----------------------------- END-OF-FILE ----------------------------------