bool test_Game_constructor();

int main()
{
    bool tests_passed{true}; // initially set to pass

    tests_passed &= test_Game_constructor(); // test Game constructor

    return tests_passed ? 0 : 1;
}