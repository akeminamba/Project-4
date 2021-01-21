#include <iostream>
#include <string>
#include <cmath>    // abs()

#include "BookBot.h"
using namespace std;

// Global static variables
static int testCount = 0;
static const int testTotal = 7;
static const string GREEN = "\033[32m";
static const string RED = "\033[31m";
static const string RESET = "\033[0m";

// Prototypes
bool assertTrue(const string& nameOfTest, bool actual);
bool assertEquals(const string & nameOfTest, double expected, double actual);

template <typename T, typename U>
bool assertEquals(const string & nameOfTest, const T & expected, const U & actual);

template <typename T, typename U>
bool assertVectorEquals(const string& nameOfTest, const vector<T>& expected, const vector<U>& actual);


// Main
int main(int argc, char const *argv[]) {
    BookBot bot(92870);
    assertTrue("Punctuation 01", bot.isEndPunctuation(".", 0));
    assertTrue("Punctuation 02", bot.isEndPunctuation("?", 0));
    assertTrue("Punctuation 03", bot.isEndPunctuation("!", 0));

    BookBot Frankenstein(17);
    Frankenstein.readIn("Frankenstein or The Modern Prometheus by Mary Shelley.txt");
    BookBot SleepyHollow(18);
    SleepyHollow.readIn("The Legend of Sleep Hollow by Washington Irving.txt");

    vector<string> expected;
    expected.push_back("lovers,");
    expected.push_back("days");
    expected.push_back("lovers");
    assertVectorEquals("Values : Frankenstein", expected, Frankenstein.getValues("youthful"));

    expected.clear();
    expected.push_back("hill,");
    expected.push_back("crests");
    expected.push_back("dell,");
    assertVectorEquals("Values : SleepyHollow", expected, SleepyHollow.getValues("woody"));

    assertEquals("GenerateSentence : Frankenstein", "Clerval entreating me invincible repugnance to reflection.", Frankenstein.generateSentence());
    assertEquals("GenerateSentence : Sleepy Hollow", "As Ichabod.", SleepyHollow.generateSentence());

    cout << endl << testCount << " tests passed out of " << testTotal << " total tests" << endl;
    return 0;
}


// Helper Functions
bool assertTrue(const string& nameOfTest, bool actual) {
    if (actual == true) {
        // Green colored text
        cout << GREEN << "PASSED "
             << RESET << nameOfTest << ": test successfully resulted in 'true'" << endl;
        testCount++;
        return true;
    }
    // Red colored text
    cout << RED << "FAILED "
         << RESET << nameOfTest << ": test unsuccessfully resulted in 'false'" << endl;
    return false;
}

bool assertEquals(const string& nameOfTest, double expected, double actual) {
    if (abs(expected - actual) < 0.005)  {
        // Green colored text
        cout << GREEN << "PASSED "
             << RESET << nameOfTest << ": expected and actual '" << actual << "'" << endl;
        testCount++;
        return true;
    }
    // Red colored text
    cout << RED << "FAILED "
         << RESET << nameOfTest << ": expected '" << expected << "'' but actual '" << actual << "'" << endl;
    return false;
}

template <typename T, typename U>
bool assertEquals(const string& nameOfTest, const T& expected, const U& actual) {
    if (expected == actual) {
        // Green colored text
        cout << GREEN << "PASSED "
             << RESET << nameOfTest << ": expected and actual '" << actual << "'" << endl;
        testCount++;
        return true;
    }
    // Red colored text
    cout << RED << "FAILED "
         << RESET << nameOfTest << ": expected '" << expected << "' but actually '" << actual << "'" << endl;
    return false;
}

template <typename T, typename U>
bool assertVectorEquals(const string& nameOfTest, const vector<T>& expected, const vector<U>& actual) {
    if (expected.size() == actual.size()) {
        for (size_t i = 0; i < expected.size(); i++) {
            if (expected[i] != actual[i]) {
                // Red colored text
                cout << RED << "FAILED "
                     << RESET << nameOfTest << ": expected '" << expected[i] << "' but actually '" << actual[i] << "'" << endl;
                return false;
            }
        }

        // Green colored text
        cout << GREEN << "PASSED "
             << RESET << nameOfTest << ": expected and actual lists match: {";
        for (int i = 0; i < expected.size(); i++) {
            cout << " " << expected[i];
        }
        cout << " }" << endl;

        testCount++;
        return true;
    }

    // Red colored text
    cout << RED << "FAILED "
         << RESET << nameOfTest << ": expected size '" << expected.size() << "' but actually size is '" << actual.size() << "'" << endl;
    return false;
}
