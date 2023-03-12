#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unicode/utypes.h>
#include <unicode/ucnv.h>
#include <unicode/unistr.h>

// Function to translate a string from Romanian to English using ICU
std::string translateRomanianToEnglish(const std::string& romanian) {
    // Create a Unicode string from the Romanian string
    UnicodeString romanianUnicode = UnicodeString::fromUTF8(romanian.c_str());

    // Create a converter to translate from Romanian to English
    UErrorCode err = U_ZERO_ERROR;
    UConverter* converter = ucnv_open("ro_EN", &err);

    // Allocate a buffer to hold the translated string
    int32_t capacity = romanianUnicode.length() * ucnv_getMaxCharSize(converter);
    char* buffer = new char[capacity];

    // Translate the string
    int32_t length = ucnv_fromUChars(converter, buffer, capacity, romanianUnicode.getBuffer(), romanianUnicode.length(), &err);
    if (U_FAILURE(err)) {
        std::cerr << "Error translating string: " << u_errorName(err) << std::endl;
        return "";
    }

    // Create a new string from the translated buffer
    std::string english(buffer, length);

    // Clean up
    delete[] buffer;
    ucnv_close(converter);

    return english;
}

int main() {
    // Open the input and output CSV files
    std::ifstream input("meniu.csv");
    std::ofstream output("meniu_eng.csv");

    // Read the input CSV file line by line
    std::string line;
    while (std::getline(input, line)) {
        // Split the line into fields using a stringstream
        std::vector<std::string> fields;
        std::stringstream ss(line);
        std::string field;
        while (std::getline(ss, field, ',')) {
            fields.push_back(field);
        }

        // Translate each field from Romanian to English
        for (auto& field : fields) {
            field = translateRomanianToEnglish(field);
        }

        // Write the translated fields to the output CSV file
        for (size_t i = 0; i < fields.size(); i++) {
            output << fields[i];
            if (i < fields.size() - 1) {
                output << ",";
            }
        }
        output << std::endl;
    }

    return 0;
}
