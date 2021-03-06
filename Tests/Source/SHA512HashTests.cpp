/*
    Copyright (c) 2017 Xavier Leclercq

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
    IN THE SOFTWARE.
*/

#include "SHA512HashTests.h"
#include "Ishiko/Hash/SHA512Hash.h"
#include <boost/filesystem/operations.hpp>

void AddSHA512HashTests(TestHarness& theTestHarness)
{
    TestSequence& sha512HashTestSequence = theTestHarness.appendTestSequence("SHA512Hash tests");

    new HeapAllocationErrorsTest("Creation test 1", SHA512HashCreationTest1, sha512HashTestSequence);

    new HeapAllocationErrorsTest("value test 1", SHA512HashValueTest1, sha512HashTestSequence);
    new HeapAllocationErrorsTest("value test 2", SHA512HashValueTest2, sha512HashTestSequence);
    new HeapAllocationErrorsTest("value test 3", SHA512HashValueTest3, sha512HashTestSequence);
    new HeapAllocationErrorsTest("value test 4", SHA512HashValueTest4, sha512HashTestSequence);
    new HeapAllocationErrorsTest("value test 5", SHA512HashValueTest5, sha512HashTestSequence);

    new HeapAllocationErrorsTest("updateFromFile test 1", SHA512HashUpdateFromFileTest1, sha512HashTestSequence);
    new HeapAllocationErrorsTest("updateFromFile test 2", SHA512HashUpdateFromFileTest2, sha512HashTestSequence);
    new HeapAllocationErrorsTest("updateFromFile test 3", SHA512HashUpdateFromFileTest3, sha512HashTestSequence);
    new HeapAllocationErrorsTest("updateFromFile test 4", SHA512HashUpdateFromFileTest4, sha512HashTestSequence);
    new HeapAllocationErrorsTest("updateFromFile test 5", SHA512HashUpdateFromFileTest5, sha512HashTestSequence);
}

TestResult::EOutcome SHA512HashCreationTest1()
{
    Ishiko::Hash::SHA512Hash hash;
    return TestResult::ePassed;
}

TestResult::EOutcome SHA512HashValueTest1()
{
    Ishiko::Hash::SHA512Hash hash;
    const std::array<unsigned char, 64>& value = hash.value();
   
    std::array<unsigned char, 64> referenceValue =
    {
        0xcf, 0x83, 0xe1, 0x35, 0x7e, 0xef, 0xb8, 0xbd,
        0xf1, 0x54, 0x28, 0x50, 0xd6, 0x6d, 0x80, 0x07,
        0xd6, 0x20, 0xe4, 0x05, 0x0b, 0x57, 0x15, 0xdc,
        0x83, 0xf4, 0xa9, 0x21, 0xd3, 0x6c, 0xe9, 0xce,
        0x47, 0xd0, 0xd1, 0x3c, 0x5d, 0x85, 0xf2, 0xb0,
        0xff, 0x83, 0x18, 0xd2, 0x87, 0x7e, 0xec, 0x2f,
        0x63, 0xb9, 0x31, 0xbd, 0x47, 0x41, 0x7a, 0x81,
        0xa5, 0x38, 0x32, 0x7a, 0xf9, 0x27, 0xda, 0x3e
    };

    // We don't use the operator == to make it easier to
    // debug
    bool equal = true;
    for (size_t i = 0; i < 64; ++i)
    {
        if (value[i] != referenceValue[i])
        {
            equal = false;
            break;
        }
    }

    if (equal)
    {
        return TestResult::ePassed;
    }
    else
    {
        return TestResult::eFailed;
    }
}

TestResult::EOutcome SHA512HashValueTest2()
{
    Ishiko::Hash::SHA512Hash hash;
    const char* text = "abc";
    hash.update(text, strlen(text));
    const std::array<unsigned char, 64>& value = hash.value();

    std::array<unsigned char, 64> referenceValue =
    {
        0xDD, 0xAF, 0x35, 0xA1, 0x93, 0x61, 0x7A, 0xBA,
        0xCC, 0x41, 0x73, 0x49, 0xAE, 0x20, 0x41, 0x31,
        0x12, 0xE6, 0xFA, 0x4E, 0x89, 0xA9, 0x7E, 0xA2,
        0x0A, 0x9E, 0xEE, 0xE6, 0x4B, 0x55, 0xD3, 0x9A,
        0x21, 0x92, 0x99, 0x2A, 0x27, 0x4F, 0xC1, 0xA8,
        0x36, 0xBA, 0x3C, 0x23, 0xA3, 0xFE, 0xEB, 0xBD,
        0x45, 0x4D, 0x44, 0x23, 0x64, 0x3C, 0xE8, 0x0E,
        0x2A, 0x9A, 0xC9, 0x4F, 0xA5, 0x4C, 0xA4, 0x9F
    };

    // We don't use the operator == to make it easier to
    // debug
    bool equal = true;
    for (size_t i = 0; i < 64; ++i)
    {
        if (value[i] != referenceValue[i])
        {
            equal = false;
            break;
        }
    }

    if (equal)
    {
        return TestResult::ePassed;
    }
    else
    {
        return TestResult::eFailed;
    }
}

TestResult::EOutcome SHA512HashValueTest3()
{
    Ishiko::Hash::SHA512Hash hash;
    const char* text = "abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu";
    hash.update(text, strlen(text));
    const std::array<unsigned char, 64>& value = hash.value();

    std::array<unsigned char, 64> referenceValue =
    {
        0x8E, 0x95, 0x9B, 0x75, 0xDA, 0xE3, 0x13, 0xDA,
        0x8C, 0xF4, 0xF7, 0x28, 0x14, 0xFC, 0x14, 0x3F,
        0x8F, 0x77, 0x79, 0xC6, 0xEB, 0x9F, 0x7F, 0xA1,
        0x72, 0x99, 0xAE, 0xAD, 0xB6, 0x88, 0x90, 0x18,
        0x50, 0x1D, 0x28, 0x9E, 0x49, 0x00, 0xF7, 0xE4,
        0x33, 0x1B, 0x99, 0xDE, 0xC4, 0xB5, 0x43, 0x3A,
        0xC7, 0xD3, 0x29, 0xEE, 0xB6, 0xDD, 0x26, 0x54,
        0x5E, 0x96, 0xE5, 0x5B, 0x87, 0x4B, 0xE9, 0x09
    };

    // We don't use the operator == to make it easier to
    // debug
    bool equal = true;
    for (size_t i = 0; i < 64; ++i)
    {
        if (value[i] != referenceValue[i])
        {
            equal = false;
            break;
        }
    }

    if (equal)
    {
        return TestResult::ePassed;
    }
    else
    {
        return TestResult::eFailed;
    }
}

TestResult::EOutcome SHA512HashValueTest4()
{
    Ishiko::Hash::SHA512Hash hash;
    std::string text(1000000, 'a');
    hash.update(text.c_str(), text.size());
    const std::array<unsigned char, 64>& value = hash.value();

    std::array<unsigned char, 64> referenceValue =
    {
        0xe7, 0x18, 0x48, 0x3d, 0x0c, 0xe7, 0x69, 0x64,
        0x4e, 0x2e, 0x42, 0xc7, 0xbc, 0x15, 0xb4, 0x63,
        0x8e, 0x1f, 0x98, 0xb1, 0x3b, 0x20, 0x44, 0x28,
        0x56, 0x32, 0xa8, 0x03, 0xaf, 0xa9, 0x73, 0xeb,
        0xde, 0x0f, 0xf2, 0x44, 0x87, 0x7e, 0xa6, 0x0a,
        0x4c, 0xb0, 0x43, 0x2c, 0xe5, 0x77, 0xc3, 0x1b,
        0xeb, 0x00, 0x9c, 0x5c, 0x2c, 0x49, 0xaa, 0x2e,
        0x4e, 0xad, 0xb2, 0x17, 0xad, 0x8c, 0xc0, 0x9b
    };

    // We don't use the operator == to make it easier to
    // debug
    bool equal = true;
    for (size_t i = 0; i < 64; ++i)
    {
        if (value[i] != referenceValue[i])
        {
            equal = false;
            break;
        }
    }

    if (equal)
    {
        return TestResult::ePassed;
    }
    else
    {
        return TestResult::eFailed;
    }
}

TestResult::EOutcome SHA512HashValueTest5()
{
    Ishiko::Hash::SHA512Hash hash;
    std::string text("abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmno");
    for (size_t i = 0; i < 16777216; ++i)
    {
        hash.update(text.c_str(), text.size());
    }
    const std::array<unsigned char, 64>& value = hash.value();

    std::array<unsigned char, 64> referenceValue =
    {
        0xb4, 0x7c, 0x93, 0x34, 0x21, 0xea, 0x2d, 0xb1,
        0x49, 0xad, 0x6e, 0x10, 0xfc, 0xe6, 0xc7, 0xf9,
        0x3d, 0x07, 0x52, 0x38, 0x01, 0x80, 0xff, 0xd7,
        0xf4, 0x62, 0x9a, 0x71, 0x21, 0x34, 0x83, 0x1d,
        0x77, 0xbe, 0x60, 0x91, 0xb8, 0x19, 0xed, 0x35,
        0x2c, 0x29, 0x67, 0xa2, 0xe2, 0xd4, 0xfa, 0x50,
        0x50, 0x72, 0x3c, 0x96, 0x30, 0x69, 0x1f, 0x1a,
        0x05, 0xa7, 0x28, 0x1d, 0xbe, 0x6c, 0x10, 0x86
    };

    // We don't use the operator == to make it easier to
    // debug
    bool equal = true;
    for (size_t i = 0; i < 64; ++i)
    {
        if (value[i] != referenceValue[i])
        {
            equal = false;
            break;
        }
    }

    if (equal)
    {
        return TestResult::ePassed;
    }
    else
    {
        return TestResult::eFailed;
    }
}

TestResult::EOutcome SHA512HashUpdateFromFileTest1(Test& test)
{
    Ishiko::Hash::SHA512Hash hash;
    hash.updateFromFile((test.environment().getTestDataDirectory() / "EmptyFile.txt").string());
    const std::array<unsigned char, 64>& value = hash.value();

    std::array<unsigned char, 64> referenceValue =
    {
        0xcf, 0x83, 0xe1, 0x35, 0x7e, 0xef, 0xb8, 0xbd,
        0xf1, 0x54, 0x28, 0x50, 0xd6, 0x6d, 0x80, 0x07,
        0xd6, 0x20, 0xe4, 0x05, 0x0b, 0x57, 0x15, 0xdc,
        0x83, 0xf4, 0xa9, 0x21, 0xd3, 0x6c, 0xe9, 0xce,
        0x47, 0xd0, 0xd1, 0x3c, 0x5d, 0x85, 0xf2, 0xb0,
        0xff, 0x83, 0x18, 0xd2, 0x87, 0x7e, 0xec, 0x2f,
        0x63, 0xb9, 0x31, 0xbd, 0x47, 0x41, 0x7a, 0x81,
        0xa5, 0x38, 0x32, 0x7a, 0xf9, 0x27, 0xda, 0x3e
    };

    // We don't use the operator == to make it easier to
    // debug
    bool equal = true;
    for (size_t i = 0; i < 64; ++i)
    {
        if (value[i] != referenceValue[i])
        {
            equal = false;
            break;
        }
    }

    if (equal)
    {
        return TestResult::ePassed;
    }
    else
    {
        return TestResult::eFailed;
    }
}

TestResult::EOutcome SHA512HashUpdateFromFileTest2(Test& test)
{
    Ishiko::Hash::SHA512Hash hash;
    hash.updateFromFile((test.environment().getTestDataDirectory() / "abc.txt").string());
    const std::array<unsigned char, 64>& value = hash.value();

    std::array<unsigned char, 64> referenceValue =
    {
        0xDD, 0xAF, 0x35, 0xA1, 0x93, 0x61, 0x7A, 0xBA,
        0xCC, 0x41, 0x73, 0x49, 0xAE, 0x20, 0x41, 0x31,
        0x12, 0xE6, 0xFA, 0x4E, 0x89, 0xA9, 0x7E, 0xA2,
        0x0A, 0x9E, 0xEE, 0xE6, 0x4B, 0x55, 0xD3, 0x9A,
        0x21, 0x92, 0x99, 0x2A, 0x27, 0x4F, 0xC1, 0xA8,
        0x36, 0xBA, 0x3C, 0x23, 0xA3, 0xFE, 0xEB, 0xBD,
        0x45, 0x4D, 0x44, 0x23, 0x64, 0x3C, 0xE8, 0x0E,
        0x2A, 0x9A, 0xC9, 0x4F, 0xA5, 0x4C, 0xA4, 0x9F
    };

    // We don't use the operator == to make it easier to
    // debug
    bool equal = true;
    for (size_t i = 0; i < 64; ++i)
    {
        if (value[i] != referenceValue[i])
        {
            equal = false;
            break;
        }
    }

    if (equal)
    {
        return TestResult::ePassed;
    }
    else
    {
        return TestResult::eFailed;
    }
}

TestResult::EOutcome SHA512HashUpdateFromFileTest3(Test& test)
{
    Ishiko::Hash::SHA512Hash hash;
    hash.updateFromFile((test.environment().getTestDataDirectory() / "smallfile.txt").string());
    const std::array<unsigned char, 64>& value = hash.value();

    std::array<unsigned char, 64> referenceValue =
    {
        0x8E, 0x95, 0x9B, 0x75, 0xDA, 0xE3, 0x13, 0xDA,
        0x8C, 0xF4, 0xF7, 0x28, 0x14, 0xFC, 0x14, 0x3F,
        0x8F, 0x77, 0x79, 0xC6, 0xEB, 0x9F, 0x7F, 0xA1,
        0x72, 0x99, 0xAE, 0xAD, 0xB6, 0x88, 0x90, 0x18,
        0x50, 0x1D, 0x28, 0x9E, 0x49, 0x00, 0xF7, 0xE4,
        0x33, 0x1B, 0x99, 0xDE, 0xC4, 0xB5, 0x43, 0x3A,
        0xC7, 0xD3, 0x29, 0xEE, 0xB6, 0xDD, 0x26, 0x54,
        0x5E, 0x96, 0xE5, 0x5B, 0x87, 0x4B, 0xE9, 0x09
    };

    // We don't use the operator == to make it easier to
    // debug
    bool equal = true;
    for (size_t i = 0; i < 64; ++i)
    {
        if (value[i] != referenceValue[i])
        {
            equal = false;
            break;
        }
    }

    if (equal)
    {
        return TestResult::ePassed;
    }
    else
    {
        return TestResult::eFailed;
    }
}

TestResult::EOutcome SHA512HashUpdateFromFileTest4(Test& test)
{
    // Generate a file with a million 'a' characters in it
    // We generate the file because we do not want to store such a large file in version control
    std::string testFilePath = (test.environment().getTestOutputDirectory() / "milliona.txt").string();
    boost::filesystem::remove(testFilePath);
    std::ofstream testFile(testFilePath);
    for (size_t i = 0; i < 100000; ++i)
    {
        testFile.write("aaaaaaaaaa", 10);
    }
    testFile.close();

    Ishiko::Hash::SHA512Hash hash;
    hash.updateFromFile(testFilePath);
    const std::array<unsigned char, 64>& value = hash.value();

    std::array<unsigned char, 64> referenceValue =
    {
        0xe7, 0x18, 0x48, 0x3d, 0x0c, 0xe7, 0x69, 0x64,
        0x4e, 0x2e, 0x42, 0xc7, 0xbc, 0x15, 0xb4, 0x63,
        0x8e, 0x1f, 0x98, 0xb1, 0x3b, 0x20, 0x44, 0x28,
        0x56, 0x32, 0xa8, 0x03, 0xaf, 0xa9, 0x73, 0xeb,
        0xde, 0x0f, 0xf2, 0x44, 0x87, 0x7e, 0xa6, 0x0a,
        0x4c, 0xb0, 0x43, 0x2c, 0xe5, 0x77, 0xc3, 0x1b,
        0xeb, 0x00, 0x9c, 0x5c, 0x2c, 0x49, 0xaa, 0x2e,
        0x4e, 0xad, 0xb2, 0x17, 0xad, 0x8c, 0xc0, 0x9b
    };

    // We don't use the operator == to make it easier to
    // debug
    bool equal = true;
    for (size_t i = 0; i < 64; ++i)
    {
        if (value[i] != referenceValue[i])
        {
            equal = false;
            break;
        }
    }

    boost::filesystem::remove(testFilePath);
    if (equal)
    {
        return TestResult::ePassed;
    }
    else
    {
        return TestResult::eFailed;
    }
}

TestResult::EOutcome SHA512HashUpdateFromFileTest5(Test& test)
{
    // Generate a file with a million 'a' characters in it
    // We generate the file because we do not want to store such a large file in version control
    std::string testFilePath = (test.environment().getTestOutputDirectory() / "gigabyte.txt").string();
    boost::filesystem::remove(testFilePath);
    std::ofstream testFile(testFilePath);
    std::string text("abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmno");
    for (size_t i = 0; i < 16777216; ++i)
    {
        testFile.write(text.c_str(), text.size());
    }
    testFile.close();

    Ishiko::Hash::SHA512Hash hash;
    hash.updateFromFile(testFilePath);
    const std::array<unsigned char, 64>& value = hash.value();

    std::array<unsigned char, 64> referenceValue =
    {
        0xb4, 0x7c, 0x93, 0x34, 0x21, 0xea, 0x2d, 0xb1,
        0x49, 0xad, 0x6e, 0x10, 0xfc, 0xe6, 0xc7, 0xf9,
        0x3d, 0x07, 0x52, 0x38, 0x01, 0x80, 0xff, 0xd7,
        0xf4, 0x62, 0x9a, 0x71, 0x21, 0x34, 0x83, 0x1d,
        0x77, 0xbe, 0x60, 0x91, 0xb8, 0x19, 0xed, 0x35,
        0x2c, 0x29, 0x67, 0xa2, 0xe2, 0xd4, 0xfa, 0x50,
        0x50, 0x72, 0x3c, 0x96, 0x30, 0x69, 0x1f, 0x1a,
        0x05, 0xa7, 0x28, 0x1d, 0xbe, 0x6c, 0x10, 0x86
    };

    // We don't use the operator == to make it easier to
    // debug
    bool equal = true;
    for (size_t i = 0; i < 64; ++i)
    {
        if (value[i] != referenceValue[i])
        {
            equal = false;
            break;
        }
    }

    boost::filesystem::remove(testFilePath);
    if (equal)
    {
        return TestResult::ePassed;
    }
    else
    {
        return TestResult::eFailed;
    }
}
