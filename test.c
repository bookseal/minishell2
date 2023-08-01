#include <stdio.h>
#include <stdbool.h>

bool is_valid_token(const char* token) {
    if (!token) return false;

    int i = 0;
    char opening_quote = token[0];

    // Check if the first character is a quote
    if (opening_quote != '\'' && opening_quote != '\"') {
        return false;
    }

    while (token[i] != '\0') {
        i++;
    }

    // If the last character isn't the same type of quote, it's not a valid token
    if (token[i-1] != opening_quote) {
        return false;
    }

    return true;
}

int main() {
    const char* valid_token1 = "'this is a valid token'";
    const char* valid_token2 = "\"this is also a valid token\"";
    const char* invalid_token1 = "'this is not a valid token";
    const char* invalid_token2 = "\"this is not a valid token";
    const char* invalid_token3 = "this is not a valid token'";

    printf("Valid token 1 test: %s\n", is_valid_token(valid_token1) ? "Passed" : "Failed");
    printf("Valid token 2 test: %s\n", is_valid_token(valid_token2) ? "Passed" : "Failed");
    printf("Invalid token 1 test: %s\n", is_valid_token(invalid_token1) ? "Failed" : "Passed");
    printf("Invalid token 2 test: %s\n", is_valid_token(invalid_token2) ? "Failed" : "Passed");
    printf("Invalid token 3 test: %s\n", is_valid_token(invalid_token3) ? "Failed" : "Passed");

    return 0;
}
