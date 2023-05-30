//
// Created by comme on 5/10/2023.
//

#ifndef YELLOW_BELT_CPP_TEST_IS_PALINDOM_H
#define YELLOW_BELT_CPP_TEST_IS_PALINDOM_H
#include <string>
#include "../test_runner.h"

bool IsPalindrom(std::string word){
    for(int i = 0; i < word.length() / 2; i++){
        if(word[i] != word[word.length() - 1 - i])
            return false;
    }
    return true;
}

void test_is_palindrom(){
    {
        std::string empty;
        AssertEqual(IsPalindrom(empty), true, "empty string should be palindrome");
    }
    {
        std::string one_letter = "a";
        AssertEqual(IsPalindrom(one_letter), true, "one letter is always palindrome");
    }
    {
        std::string two_same = "aa";
        AssertEqual(IsPalindrom(two_same), true, "two same letters should be palindrome");
    }
    {
        std::string two_case_different = "Aa";
        AssertEqual(IsPalindrom(two_case_different), false, "case is different");
    }
    {
        std::string three = "bab";
        AssertEqual(IsPalindrom(three), true, "case and letters are the same");
    }
    {
        std::string madam = "madam";
        AssertEqual(IsPalindrom(madam), true, "everything is the same madam, should pass");
    }
    {
        std::string madAm = "madAm";
        AssertEqual(IsPalindrom(madAm), false, "case is different");
    }
    {
        std::string notPalindrom = "notPalindrom";
        AssertEqual(IsPalindrom(notPalindrom), false, "it's not a palindrome");
    }
    {
        std::string mada4am = "mada4am";
        AssertEqual(IsPalindrom(mada4am), false, "it's a shit");
    }
    {
        std::string big_palindrome = "wasitacaroracatisaw";
        AssertEqual(IsPalindrom(big_palindrome), true, "big but palindrom");
    }
    {
        std::string blank_palindrome = " ";
        AssertEqual(IsPalindrom(blank_palindrome), true, "blank should be palindrome");
    }
    {
        std::string blank_palindrome = "médem";
        AssertEqual(IsPalindrom(blank_palindrome), false, "blank should be palindrome ");
    }
    {
        std::string not_palindrom = "racecar";
        AssertEqual(IsPalindrom(not_palindrom), true, "racecar is palindrom");
    }
    {
        std::string with_whitespaces = "s a d a m";
        AssertEqual(IsPalindrom(with_whitespaces), false, "s a d a m is palindrome");
    }
    {
        std::string abba = "aba ba";
        AssertEqual(IsPalindrom(abba), false, "aba ba is not a palindrome");
    }
    {
        std::string abba = "\nabba\n";
        AssertEqual(IsPalindrom(abba), true, "abba with special characters is a palindrome");
    }
}

#endif //YELLOW_BELT_CPP_TEST_IS_PALINDOM_H
