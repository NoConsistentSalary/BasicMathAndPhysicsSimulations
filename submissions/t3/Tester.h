#pragma once
#include "math.h"
#include <functional>
#include "Testcases.h"

namespace Tester
{

	template <typename To, typename From>
	To convert(From& value)
	{
		return static_cast<To>(value);
	}

	//-----------------------------------------------------------------
	//						Print functions
	//-----------------------------------------------------------------

	template <typename T>
	void printFloat(T p)
	{
		std::cout << p << "\n";
	}

	template <typename T>
	void printVector(T p)
	{
		std::cout << math::vec_to_string(p) << "\n";
	}

	template <typename T>
	void printMatrix(T p)
	{
		std::cout << math::mat_to_string(p) << "\n";
	}

	//-----------------------------------------------------------------
	//						Other print functions
	//-----------------------------------------------------------------

	int whatTemplateType(auto var)
	{
		if (typeid(var) == typeid(float))
		{
			return 0;
		}
		else if (typeid(var) == typeid(math::vec2))
		{
			return 1;
		}
		else if (typeid(var) == typeid(math::vec3))
		{
			return 2;
		}
		else if (typeid(var) == typeid(math::vec4))
		{
			return 3;
		}
		else if (typeid(var) == typeid(math::mat3))
		{
			return 4;
		}
		else if (typeid(var) == typeid(math::mat4))
		{
			return 5;
		}
	}

	void printTestInfo(variant_type printable,int whatType)
	{
		switch (whatType)
		{
		case 0:
			printFloat<float>(std::get<float>(printable));
			break;

		case 1:
			printVector<math::vec2>(std::get<math::vec2>(printable));
			break;

		case 2:
			printVector<math::vec3>(std::get<math::vec3>(printable));
			break;

		case 3:
			printVector<math::vec4>(std::get<math::vec4>(printable));
			break;

		case 4:
			printMatrix<math::mat3>(std::get<math::mat3>(printable));
			break;

		case 5:
			printMatrix<math::mat4>(std::get<math::mat4>(printable));
			break;

		default:
			break;
		}
	}
	
	//-----------------------------------------------------------------
	//						Test functions
	//-----------------------------------------------------------------

	/*
	for non overloaded functions
	should work in all cases
	*/
	template <typename T, typename Func, typename... Args>
	bool testFunction(T expectedOutput, Func func, Args... args)
	{
		variant_type result = func(args...);
		//std::cout << math::vec_to_string(result) << "\n";
		return expectedOutput == result;
	}

	/*
	for overloaded functions that take 2 of the same type and returns of the same type
	amout of arguments:		2
	same types:				for return and all arguments
	arguments passed as:	both const ref
	*/
	template <typename T>
	bool testFunctionIOverloaded0(T expectedOutput, T(*func)(const T&, const T&), const T&arg1, const T&arg2)
	{
        printf("argument1:\n");
        printTestInfo(arg1, whatTemplateType(arg1));
        printf("argument2:\n");
        printTestInfo(arg2, whatTemplateType(arg2));

		auto result = func(arg1, arg2);

        printf("Result:\n");
		printTestInfo(result, whatTemplateType(result));
        printf("\n");

		return expectedOutput == result;
	}

	/*
	for overloaded functions that take 2 of different type
	amout of arguments:		2
	same types:				for return and arg2
	arguments passed as:	arg2 as const ref
	*/
	template <typename T0,typename T1>
	bool testFunctionIOverloaded1(T0 expectedOutput, T0(*func)(T1, const T0&), T1 arg1, const T0& arg2)
	{
        printf("argument1:\n");
        printTestInfo(arg1, whatTemplateType(arg1));
        printf("argument2:\n");
        printTestInfo(arg2, whatTemplateType(arg2));

		auto result = func(arg1, arg2);

        printf("Result:\n");
        printTestInfo(result, whatTemplateType(result));
        printf("\n");

		return expectedOutput == result;
	}

	/*
	for overloaded functions that take 2 of different type
	amout of arguments:		2
	same types:				for return and arg1
	arguments passed as:	arg1 as const ref
	*/
	template <typename T0, typename T1>
	bool testFunctionIOverloaded2(T0 expectedOutput, T0(*func)(const T0&, T1), const T0& arg1, T1 arg2)
	{
        printf("argument1:\n");
        printTestInfo(arg1, whatTemplateType(arg1));
        printf("argument2:\n");
        printTestInfo(arg2, whatTemplateType(arg2));

		auto result = func(arg1, arg2);

        printf("Result:\n");
        printTestInfo(result, whatTemplateType(result));
        printf("\n");

		return expectedOutput == result;
	}

	/*
	for overloaded functions that take 2 of the same type and returns different type
	amout of arguments:		2
	same types:				for arguments, return different
	arguments passed as:	both as const ref
	*/
	template <typename T0, typename T1>
	bool testFunctionIOverloaded3(T0 expectedOutput, T0(*func)(const T1&, const T1&), const T1& arg1, const T1& arg2)
	{
        printf("argument1:\n");
        printTestInfo(arg1, whatTemplateType(arg1));
        printf("argument2:\n");
        printTestInfo(arg2, whatTemplateType(arg2));

		auto result = func(arg1, arg2);

        printf("Result:\n");
        printTestInfo(result, whatTemplateType(result));
        printf("\n");

		return expectedOutput == result;
	}

	/*
	takes only one argument and returns different type
	amout of arguments:		1
	same types:				no
	arguments passed as:	const ref
	*/
	template <typename T0, typename T1>
	bool testFunctionIOverloaded4(T0 expectedOutput, T0(*func)(const T1&), const T1& arg)
	{
        printf("argument:\n");
        printTestInfo(arg, whatTemplateType(arg));

		auto result = func(arg);

        printf("Result:\n");
        printTestInfo(result, whatTemplateType(result));
        printf("\n");

		return expectedOutput == result;
	}

	/*
	takes only one argument and returns same type
	amout of arguments:		1
	same types:				return and argument
	arguments passed as:	const ref
	*/
	template <typename T>
	bool testFunctionIOverloaded5(T expectedOutput, T(*func)(const T&), const T& arg)
	{
        printf("argument:\n");
        printTestInfo(arg, whatTemplateType(arg));

		auto result = func(arg);

        printf("Result:\n");
        printTestInfo(result, whatTemplateType(result));
        printf("\n");

		return expectedOutput == result;
	}

	/*
	amout of arguments:		2
	same types:				for return and arg2
	arguments passed as:	both const ref
	*/
	template <typename T0, typename T1>
	bool testFunctionIOverloaded6(T0 expectedOutput, T0(*func)(const T1&, const T0&), const T1& arg1, const T0& arg2)
	{
        printf("argument1:\n");
        printTestInfo(arg1, whatTemplateType(arg1));
        printf("argument2:\n");
        printTestInfo(arg2, whatTemplateType(arg2));

		auto result = func(arg1, arg2);

        printf("Result:\n");
        printTestInfo(result, whatTemplateType(result));
        printf("\n");

		return expectedOutput == result;
	}

	/*
	amout of arguments:		1
	same types:				no
	arguments passed as:	not const ref
	*/
	template <typename T0, typename T1>
	bool testFunctionIOverloaded7(T0 expectedOutput, T0(*func)(T1), T1 arg)
	{
        printf("argument:\n");
        printTestInfo(arg, whatTemplateType(arg));

		auto result = func(arg);

        printf("Result:\n");
        printTestInfo(result, whatTemplateType(result));
        printf("\n");

		return expectedOutput == result;
	}

	//-----------------------------------------------------------------
	//						Parce and test functions
	//-----------------------------------------------------------------

    /*
    Run testcase fur function that takses 2 arguments with same type
    also returns the same type
    includes: addition, subtraction, vec3 cross product AND mat multiplication
    */
    template<typename Type>
    bool parceAndTest0(const std::vector<Testcase>& testcases, int selection)
    {

        int counter = 0;

        for (Testcase t : testcases)
        {

            Type expOut = std::get<Type>(t.expOut);
            Type arg1 = std::get<Type>(t.arg1);
            Type arg2 = std::get<Type>(t.arg2);

            if (selection == 0)
            {
                if (false == Tester::testFunctionIOverloaded0<Type>(
                    expOut,
                    math::add,
                    arg1, arg2
                ))
                {
                    printf("%i\n", counter);
                    return false;
                }
            }
            else if (selection == 1)
            {
                if (false == Tester::testFunctionIOverloaded0<Type>(
                    expOut,
                    math::sub,
                    arg1, arg2
                ))
                {
                    printf("%i\n", counter);
                    return false;
                }
            }
            /*
            else if (selection == 2)
            {
                if (false == Tester::testFunctionIOverloaded0<Type>(
                    expOut,
                    math::cross,
                    arg1, arg2
                ))
                {
                    return false;
                }
            }
            */
            /*
            else if (selection == 3)
            {
                if (false == Tester::testFunctionIOverloaded0<Type>(
                    expOut,
                    math::mul,
                    arg1, arg2
                ))
                {
                    return false;
                }
            }
            */
            else
            {
                printf("%i\n", counter);
                printf("Wrongful function activation\n");
                return false;
            }

            counter++;
        }

        return true;
    }

    /*
    Run testcase fur function that takses 2 arguments with different type.
    returns the same type as the arg2
    includes: multiplications
    *///               vec            float
    template<typename Type0, typename Type1>
    bool parceAndTest1(const std::vector<Testcase>& testcases)
    {
        int counter = 0;

        for (Testcase t : testcases)
        {
            Type0 expOut = std::get<Type0>(t.expOut);
            Type1 arg1 = std::get<Type1>(t.arg1);           //float
            Type0 arg2 = std::get<Type0>(t.arg2);

            if (false == Tester::testFunctionIOverloaded1<Type0, Type1>(
                expOut,
                math::mul,
                arg1, arg2
            ))
            {
                printf("%i\n", counter);
                return false;
            }

            counter++;
        }

        return true;
    }

    /*
    Run testcase fur function that takses 2 arguments with different type.
    returns the same type as the arg1
    includes: multiplications, divisions,
    *///               vec            float
    template<typename Type0, typename Type1>
    bool parceAndTest2(const std::vector<Testcase>& testcases, bool multiplication)
    {

        int counter = 0;

        for (Testcase t : testcases)
        {
            Type0 expOut = std::get<Type0>(t.expOut);
            Type0 arg1 = std::get<Type0>(t.arg1);
            Type1 arg2 = std::get<Type1>(t.arg2);           //float

            if (multiplication)
            {
                if (false == Tester::testFunctionIOverloaded2<Type0, Type1>(
                    expOut,
                    math::mul,
                    arg1, arg2
                ))
                {
                    printf("%i\n", counter);
                    return false;
                }
            }
            else
            {
                if (false == Tester::testFunctionIOverloaded2<Type0, Type1>(
                    expOut,
                    math::div,
                    arg1, arg2
                ))
                {
                    printf("%i\n", counter);
                    return false;
                }
            }

            counter++;
        }

        return true;
    }

    /*
    Run testcase fur function that takses 2 arguments with same type.
    but returns a different type
    includes: dot product, cross product,
    *///               vec            float
    template<typename Type0, typename Type1>
    bool parceAndTest3(const std::vector<Testcase>& testcases)
    {

        int counter = 0;

        for (Testcase t : testcases)
        {
            Type1 expOut = std::get<Type1>(t.expOut);   //float
            Type0 arg1 = std::get<Type0>(t.arg1);
            Type0 arg2 = std::get<Type0>(t.arg2);

            if (false == Tester::testFunctionIOverloaded3<Type1, Type0>(
                expOut,
                math::dot,
                arg1, arg2
            ))
            {
                printf("%i\n", counter);
                return false;
            }
            counter++;
        }

        return true;
    }

    /*
    Run testcase for function that take 1 argument.
    but returns a different type
    includes: lenght, determinant, scaling, translation, rotations
    *///               vec            float
    template<typename Type0, typename Type1>
    bool parceAndTest4(const std::vector<Testcase>& testcases, int selection)
    {

        int counter = 0;

        for (Testcase t : testcases)
        {
            Type1 expOut = std::get<Type1>(t.expOut);   //float
            Type0 arg = std::get<Type0>(t.arg1);

            if (selection == 0)
            {
                if (false == Tester::testFunctionIOverloaded4<Type1, Type0>(
                    expOut,
                    math::length,
                    arg
                ))
                {
                    printf("%i\n", counter);
                    return false;
                }
            }
            /*else if (selection == 1)
            {
                if (false == Tester::testFunctionIOverloaded4<Type1, Type0>(
                    expOut,
                    math::det,
                    arg
                ))
                {
                    printf("%i\n", counter);
                    return false;
                }
            }
            else if (selection == 2)
            {
                if (false == Tester::testFunctionIOverloaded4<Type1, Type0>(
                    expOut,
                    math::scaling,
                    arg
                ))
                {
                    printf("%i\n", counter);
                    return false;
                }
            }
            else if (selection == 3)
            {
                if (false == Tester::testFunctionIOverloaded4<Type1, Type0>(
                    expOut,
                    math::translation,
                    arg
                ))
                {
                    printf("%i\n", counter);
                    return false;
                }
            }*/
            else
            {
                printf("%i\n", counter);
                printf("Wrongful function activation\n");
                return false;
            }

            counter++;
        }

        return true;
    }

    /*
    Run testcase for function that take 1 argument.
    and returns same type
    includes: transpose, inverse
    *///               vec            float
    template<typename Type>
    bool parceAndTest5(const std::vector<Testcase>& testcases, bool transpose)
    {

        int counter = 0;

        for (Testcase t : testcases)
        {
            Type expOut = std::get<Type>(t.expOut);   //float
            Type arg = std::get<Type>(t.arg1);

            if (transpose)
            {
                if (false == Tester::testFunctionIOverloaded5<Type>(
                    expOut,
                    math::transpose,
                    arg
                ))
                {
                    printf("%i\n", counter);
                    return false;
                }
            }
            else
            {
                if (false == Tester::testFunctionIOverloaded5<Type>(
                    expOut,
                    math::inverse,
                    arg
                ))
                {
                    printf("%i\n", counter);
                    return false;
                }
            }

            counter++;

        }

        return true;
    }

    /*
    ..
    *///
    template<typename Type0, typename Type1>
    bool parceAndTest6(const std::vector<Testcase>& testcases, bool transpose)
    {

        int counter = 0;

        for (Testcase t : testcases)
        {
            Type0 expOut = std::get<Type0>(t.expOut);
            Type1 arg1 = std::get<Type1>(t.arg1);
            Type0 arg2 = std::get<Type0>(t.arg2);


            if (false == Tester::testFunctionIOverloaded6<Type0, Type1>(
                expOut,
                math::mul,
                arg1, arg2
            ))
            {
                printf("%i\n", counter);
                return false;
            }

            counter++;

        }

        return true;
    }

    /*
    ..
    *///
    template<typename Type0, typename Type1>
    bool parceAndTest7(const std::vector<Testcase>& testcases, int selection)
    {

        int counter = 0;

        for (Testcase t : testcases)
        {
            Type0 expOut = std::get<Type0>(t.expOut);
            Type1 arg = std::get<Type1>(t.arg1);

            if (selection == 0)
            {
                if (false == Tester::testFunctionIOverloaded7<Type0, Type1>(
                    expOut,
                    math::rotation,
                    arg
                ))
                {
                    printf("%i\n", counter);
                    return false;
                }
            }
            else if (selection == 1)
            {
                if (false == Tester::testFunctionIOverloaded7<Type0, Type1>(
                    expOut,
                    math::scaling,
                    arg
                ))
                {
                    printf("%i\n", counter);
                    return false;
                }
            }
            else if (selection == 2)
            {
                if (false == Tester::testFunctionIOverloaded7<Type0, Type1>(
                    expOut,
                    math::rotationX,
                    arg
                ))
                {
                    printf("%i\n", counter);
                    return false;
                }
            }
            else if (selection == 3)
            {
                if (false == Tester::testFunctionIOverloaded7<Type0, Type1>(
                    expOut,
                    math::rotationY,
                    arg
                ))
                {
                    printf("%i\n", counter);
                    return false;
                }
            }
            else if (selection == 4)
            {
                if (false == Tester::testFunctionIOverloaded7<Type0, Type1>(
                    expOut,
                    math::rotationZ,
                    arg
                ))
                {
                    printf("%i\n", counter);
                    return false;
                }
            }
            else
            {
                printf("%i\n", counter);
                printf("Wrongful function activation\n");
                return false;
            }

            counter++;
        }

        return true;
    }

    /*
    These functions are in the exeption function, because the program would not compile
    if they were done in the regular manner.
    */
    bool execptions(const std::vector<Testcase>& testcases, int selection)
    {

        int counter = 0;

        for (Testcase t : testcases)
        {

            if (selection == 0)
            {
                if (false == Tester::testFunctionIOverloaded0<math::vec3>(
                    std::get<math::vec3>(t.expOut),
                    math::cross,
                    std::get<math::vec3>(t.arg1), std::get<math::vec3>(t.arg2)
                ))
                {
                    printf("%i\n", counter);
                    return false;
                }
            }
            else if (selection == 1)
            {
                //float cross(const vec2& lhs, const vec2& rhs)
                if (false == Tester::testFunctionIOverloaded3<float, math::vec2>(
                    std::get<float>(t.expOut),
                    math::cross,
                    std::get<math::vec2>(t.arg1), std::get<math::vec2>(t.arg2)
                ))
                {
                    printf("%i\n", counter);
                    return false;
                }
            }
            else if (selection == 2)
            {
                if (false == Tester::testFunctionIOverloaded0<math::mat3>(
                    std::get<math::mat3>(t.expOut),
                    math::mul,
                    std::get<math::mat3>(t.arg1), std::get<math::mat3>(t.arg2)
                ))
                {
                    printf("%i\n", counter);
                    return false;
                }
            }
            else if (selection == 3)
            {
                if (false == Tester::testFunctionIOverloaded0<math::mat4>(
                    std::get<math::mat4>(t.expOut),
                    math::mul,
                    std::get<math::mat4>(t.arg1), std::get<math::mat4>(t.arg2)
                ))
                {
                    printf("%i\n", counter);
                    return false;
                }
            }

            counter++;
        }

        return true;
    }

    //-----------------------------------------------------------------
    //						Testcase runners
    //-----------------------------------------------------------------

    void runTestcasesV2()
    {
        printf("\n# TESTCASES FOR VEC2\n\n\n");

        for (size_t i = 0; i < TestcasesV2.size(); i++)
        {
            if (TestcasesV2[i].size())
            {
                switch (i)
                {
                case 0:
                    printf("------------------ V2 ADDITION ------------------\n");
                    if (false == parceAndTest0<math::vec2>(TestcasesV2[0], 0))
                    {
                        printf("ERROR 0\n");
                        exit(1);
                    }
                    break;

                case 1:
                    printf("------------------ V2 SUBTRACTION ------------------\n");
                    if (false == parceAndTest0<math::vec2>(TestcasesV2[1], 1))
                    {
                        printf("ERROR 1\n");
                        exit(1);
                    }
                    break;

                case 2:
                    printf("------------------ V2 multiplication0 ------------------\n");
                    if (false == parceAndTest1<math::vec2, float>(TestcasesV2[2]))
                    {
                        printf("ERROR 2\n");
                        exit(1);
                    }
                    break;

                case 3:
                    printf("------------------ V2 multiplication1 ------------------\n");
                    if (false == parceAndTest2<math::vec2, float>(TestcasesV2[3], true))
                    {
                        printf("ERROR 3\n");
                        exit(1);
                    }
                    break;

                case 4:
                    printf("------------------ V2 division ------------------\n");
                    if (false == parceAndTest2<math::vec2, float>(TestcasesV2[4], false))
                    {
                        printf("ERROR 4\n");
                        exit(1);
                    }
                    break;

                case 5:
                    printf("------------------ V2 dot ------------------\n");
                    if (false == parceAndTest3<math::vec2, float>(TestcasesV2[5]))
                    {
                        printf("ERROR 5\n");
                        exit(1);
                    }
                    break;

                case 6:
                    printf("------------------ V2 cross ------------------\n");
                    if (false == execptions(TestcasesV2[6], 1))
                    {
                        printf("ERROR 6\n");
                        exit(1);
                    }
                    break;

                case 7:
                    printf("------------------ V2 lenght ------------------\n");
                    if (false == parceAndTest4<math::vec2, float>(TestcasesV2[7], 0))
                    {
                        printf("ERROR 7\n");
                        exit(1);
                    }
                    break;

                default:
                    break;
                }
            }
        }
    }

    void runTestcasesV3()
    {
        printf("\n# TESTCASES FOR VEC3\n\n\n");

        for (size_t i = 0; i < TestcasesV3.size(); i++)
        {
            if (TestcasesV3[i].size())
            {
                switch (i)
                {
                case 0:
                    printf("------------------ V3 ADDITION ------------------\n");
                    if (false == parceAndTest0<math::vec3>(TestcasesV3[0], 0))
                    {
                        printf("ERROR 0\n");
                        exit(1);
                    }
                    break;

                case 1:
                    printf("------------------ V3 SUBTRACTION ------------------\n");
                    if (false == parceAndTest0<math::vec3>(TestcasesV3[1], 1))
                    {
                        printf("ERROR 1\n");
                        exit(1);
                    }
                    break;

                case 2:
                    printf("------------------ V3 multiplication0 ------------------\n");
                    if (false == parceAndTest1<math::vec3, float>(TestcasesV3[2]))
                    {
                        printf("ERROR 2\n");
                        exit(1);
                    }
                    break;

                case 3:
                    printf("------------------ V3 multiplication1 ------------------\n");
                    if (false == parceAndTest2<math::vec3, float>(TestcasesV3[3], true))
                    {
                        printf("ERROR 3\n");
                        exit(1);
                    }
                    break;

                case 4:
                    printf("------------------ V3 division ------------------\n");
                    if (false == parceAndTest2<math::vec3, float>(TestcasesV3[4], false))
                    {
                        printf("ERROR 4\n");
                        exit(1);
                    }
                    break;

                case 5:
                    printf("------------------ V3 dot ------------------\n");
                    if (false == parceAndTest3<math::vec3, float>(TestcasesV3[5]))
                    {
                        printf("ERROR 5\n");
                        exit(1);
                    }
                    break;

                case 6:
                    printf("------------------ V3 cross ------------------\n");
                    if (false == execptions(TestcasesV3[6], 0))
                    {
                        printf("ERROR 6\n");
                        exit(1);
                    }
                    break;

                case 7:
                    printf("------------------ V3 length ------------------\n");
                    if (false == parceAndTest4<math::vec3, float>(TestcasesV3[7], 0))
                    {
                        printf("ERROR 6\n");
                        exit(1);
                    }
                    break;

                default:
                    break;
                }
            }
        }
    }

    void runTestcasesV4()
    {
        printf("\n# TESTCASES FOR VEC4\n\n\n");

        for (size_t i = 0; i < TestcasesV4.size(); i++)
        {
            if (TestcasesV4[i].size())
            {
                switch (i)
                {
                case 0:
                    printf("------------------ V4 ADDITION ------------------\n");
                    if (false == parceAndTest0<math::vec4>(TestcasesV4[0], 0))
                    {
                        printf("ERROR 0\n");
                        exit(1);
                    }
                    break;

                case 1:
                    printf("------------------ V4 SUBTRACTION ------------------\n");
                    if (false == parceAndTest0<math::vec4>(TestcasesV4[1], 1))
                    {
                        printf("ERROR 1\n");
                        exit(1);
                    }
                    break;

                case 2:
                    printf("------------------ V4 multiplication0 ------------------\n");
                    if (false == parceAndTest1<math::vec4, float>(TestcasesV4[2]))
                    {
                        printf("ERROR 2\n");
                        exit(1);
                    }
                    break;

                case 3:
                    printf("------------------ V4 multiplication1 ------------------\n");
                    if (false == parceAndTest2<math::vec4, float>(TestcasesV4[3], true))
                    {
                        printf("ERROR 3\n");
                        exit(1);
                    }
                    break;

                case 4:
                    printf("------------------ V4 division ------------------\n");
                    if (false == parceAndTest2<math::vec4, float>(TestcasesV4[4], false))
                    {
                        printf("ERROR 4\n");
                        exit(1);
                    }
                    break;

                case 5:
                    printf("------------------ V4 dot ------------------\n");
                    if (false == parceAndTest3<math::vec4, float>(TestcasesV4[5]))
                    {
                        printf("ERROR 5\n");
                        exit(1);
                    }
                    break;

                case 6:
                    printf("------------------ V4 length ------------------\n");
                    if (false == parceAndTest4<math::vec4, float>(TestcasesV4[6], 0))
                    {
                        printf("ERROR 6\n");
                        exit(1);
                    }
                    break;

                default:
                    break;
                }
            }
        }
    }

    void runTestcasesM3()
    {
        printf("\n# TESTCASES FOR MAT3\n\n\n");

        for (size_t i = 0; i < TestcasesM3.size(); i++)
        {
            int count = 0;

            if (TestcasesM3[i].size())
            {
                switch (i)
                {
                case 0:
                    printf("------------------ M3 determinant ------------------\n");
                    count = 0;
                    for (Testcase t : TestcasesM3[0])
                    {
                        if (false == Tester::testFunctionIOverloaded4<float, math::mat3>(
                            std::get<float>(t.expOut),
                            math::det,
                            std::get<math::mat3>(t.arg1)
                        ))
                        {
                            printf("%i\n", count);
                            printf("ERROR 0\n");
                            exit(1);
                        }
                        count++;
                    }
                    break;

                case 1:
                    printf("------------------ M3 transpose ------------------\n");
                    count = 0;
                    for (Testcase t : TestcasesM3[1])
                    {
                        if (false == Tester::testFunctionIOverloaded5<math::mat3>(
                            std::get<math::mat3>(t.expOut),
                            math::transpose,
                            std::get<math::mat3>(t.arg1)
                        ))
                        {
                            printf("%i\n", count);
                            printf("ERROR 1\n");
                            exit(1);
                        }
                        count++;
                    }
                    break;

                case 2:
                    printf("------------------ M3 inverse ------------------\n");
                    count = 0;
                    for (Testcase t : TestcasesM3[2])
                    {
                        if (false == Tester::testFunctionIOverloaded5<math::mat3>(
                            std::get<math::mat3>(t.expOut),
                            math::inverse,
                            std::get<math::mat3>(t.arg1)
                        ))
                        {
                            printf("%i\n", count);
                            printf("ERROR 2\n");
                            exit(1);
                        }
                        count++;
                    }
                    break;

                case 3:
                    printf("------------------ M3 multiplication0 ------------------\n");
                    count = 0;
                    for (Testcase t : TestcasesM3[3])
                    {
                        if (false == Tester::testFunctionIOverloaded0<math::mat3>(
                            std::get<math::mat3>(t.expOut),
                            math::mul,
                            std::get<math::mat3>(t.arg1), std::get<math::mat3>(t.arg2)
                        ))
                        {
                            printf("%i\n", count);
                            printf("ERROR 3\n");
                            exit(1);
                        }
                        count++;
                    }
                    break;

                case 4:
                    printf("------------------ M3 multiplication1 ------------------\n");
                    count = 0;
                    for (Testcase t : TestcasesM3[4])
                    {
                        if (false == Tester::testFunctionIOverloaded6<math::vec2, math::mat3>(
                            std::get<math::vec2>(t.expOut),
                            math::mul,
                            std::get<math::mat3>(t.arg1), std::get<math::vec2>(t.arg2)
                        ))
                        {
                            printf("%i\n", count);
                            printf("ERROR 4\n");
                            exit(1);
                        }
                        count++;
                    }
                    break;

                case 5:
                    printf("------------------ M3 multiplication2 ------------------\n");
                    count = 0;
                    for (Testcase t : TestcasesM3[5])
                    {
                        if (false == Tester::testFunctionIOverloaded6<math::vec3, math::mat3>(
                            std::get<math::vec3>(t.expOut),
                            math::mul,
                            std::get<math::mat3>(t.arg1), std::get<math::vec3>(t.arg2)
                        ))
                        {
                            printf("%i\n", count);
                            printf("ERROR 5\n");
                            exit(1);
                        }
                        count++;
                    }
                    break;

                case 6:
                    printf("------------------ M3 scaling ------------------\n");
                    count = 0;
                    for (Testcase t : TestcasesM3[6])
                    {
                        if (false == Tester::testFunctionIOverloaded4<math::mat3, math::vec2>(
                            std::get<math::mat3>(t.expOut),
                            math::scaling,
                            std::get<math::vec2>(t.arg1)
                        ))
                        {
                            printf("%i\n", count);
                            printf("ERROR 6\n");
                            exit(1);
                        }
                        count++;
                    }
                    break;

                case 7:
                    printf("------------------ M3 translation ------------------\n");
                    count = 0;
                    for (Testcase t : TestcasesM3[7])
                    {
                        if (false == Tester::testFunctionIOverloaded4<math::mat3, math::vec2>(
                            std::get<math::mat3>(t.expOut),
                            math::translation,
                            std::get<math::vec2>(t.arg1)
                        ))
                        {
                            printf("%i\n", count);
                            printf("ERROR 7\n");
                            exit(1);
                        }
                        count++;
                    }
                    break;

                case 8:
                    printf("------------------ M3 rotation ------------------\n");
                    count = 0;
                    for (Testcase t : TestcasesM3[8])
                    {
                        if (false == Tester::testFunctionIOverloaded7<math::mat3, float>(
                            std::get<math::mat3>(t.expOut),
                            math::rotation,
                            std::get<float>(t.arg1)
                        ))
                        {
                            printf("%i\n", count);
                            printf("ERROR 8\n");
                            exit(1);
                        }
                        count++;
                    }
                    break;

                default:
                    break;
                }
            }
        }
    }

    void runTestcasesM4()
    {
        printf("\n# TESTCASES FOR MAT4\n\n\n");

        for (size_t i = 0; i < TestcasesM4.size(); i++)
        {
            int count = 0;

            if (TestcasesM4[i].size())
            {
                switch (i)
                {
                case 0:
                    printf("------------------ M4 determinant ------------------\n");
                    count = 0;
                    for (Testcase t : TestcasesM4[0])
                    {
                        if (false == Tester::testFunctionIOverloaded4<float, math::mat4>(
                            std::get<float>(t.expOut),
                            math::det,
                            std::get<math::mat4>(t.arg1)
                        ))
                        {
                            printf("%i\n", count);
                            printf("ERROR 0\n");
                            exit(1);
                        }
                        count++;
                    }
                    break;

                case 1:
                    printf("------------------ M4 transpose ------------------\n");
                    count = 0;
                    for (Testcase t : TestcasesM4[1])
                    {
                        if (false == Tester::testFunctionIOverloaded5<math::mat4>(
                            std::get<math::mat4>(t.expOut),
                            math::transpose,
                            std::get<math::mat4>(t.arg1)
                        ))
                        {
                            printf("%i\n", count);
                            printf("ERROR 1\n");
                            exit(1);
                        }
                        count++;
                    }
                    break;

                case 2:
                    printf("------------------ M4 inverse ------------------\n");
                    count = 0;
                    for (Testcase t : TestcasesM4[2])
                    {
                        if (false == Tester::testFunctionIOverloaded5<math::mat4>(
                            std::get<math::mat4>(t.expOut),
                            math::inverse,
                            std::get<math::mat4>(t.arg1)
                        ))
                        {
                            printf("%i\n", count);
                            printf("ERROR 2\n");
                            exit(1);
                        }
                        count++;
                    }
                    break;

                case 3:
                    printf("------------------ M4 multiplication0 ------------------\n");
                    count = 0;
                    for (Testcase t : TestcasesM4[3])
                    {
                        if (false == Tester::testFunctionIOverloaded0<math::mat4>(
                            std::get<math::mat4>(t.expOut),
                            math::mul,
                            std::get<math::mat4>(t.arg1), std::get<math::mat4>(t.arg2)
                        ))
                        {
                            printf("%i\n", count);
                            printf("ERROR 3\n");
                            exit(1);
                        }
                        count++;
                    }
                    break;

                case 4:
                    printf("------------------ M4 multiplication1 ------------------\n");
                    count = 0;
                    for (Testcase t : TestcasesM4[4])
                    {
                        if (false == Tester::testFunctionIOverloaded6<math::vec3, math::mat4>(
                            std::get<math::vec3>(t.expOut),
                            math::mul,
                            std::get<math::mat4>(t.arg1), std::get<math::vec3>(t.arg2)
                        ))
                        {
                            printf("%i\n", count);
                            printf("ERROR 4\n");
                            exit(1);
                        }
                        count++;
                    }
                    break;

                case 5:
                    printf("------------------ M4 multiplication2 ------------------\n");
                    count = 0;
                    for (Testcase t : TestcasesM4[5])
                    {
                        if (false == Tester::testFunctionIOverloaded6<math::vec4, math::mat4>(
                            std::get<math::vec4>(t.expOut),
                            math::mul,
                            std::get<math::mat4>(t.arg1), std::get<math::vec4>(t.arg2)
                        ))
                        {
                            printf("%i\n", count);
                            printf("ERROR 5\n");
                            exit(1);
                        }
                        count++;
                    }
                    break;

                case 6:
                    printf("------------------ M4 scaling0 ------------------\n");
                    count = 0;
                    for (Testcase t : TestcasesM4[6])
                    {
                        if (false == Tester::testFunctionIOverloaded7<math::mat4, float>(
                            std::get<math::mat4>(t.expOut),
                            math::scaling,
                            std::get<float>(t.arg1)
                        ))
                        {
                            printf("%i\n", count);
                            printf("ERROR 6\n");
                            exit(1);
                        }
                        count++;
                    }
                    break;

                case 7:
                    printf("------------------ M4 scaling1 ------------------\n");
                    count = 0;
                    for (Testcase t : TestcasesM4[7])
                    {
                        if (false == Tester::testFunctionIOverloaded4<math::mat4, math::vec3>(
                            std::get<math::mat4>(t.expOut),
                            math::scaling,
                            std::get<math::vec3>(t.arg1)
                        ))
                        {
                            printf("%i\n", count);
                            printf("ERROR 7\n");
                            exit(1);
                        }
                        count++;
                    }
                    break;

                case 8:
                    printf("------------------ M4 translation ------------------\n");
                    count = 0;
                    for (Testcase t : TestcasesM4[8])
                    {
                        if (false == Tester::testFunctionIOverloaded4<math::mat4, math::vec3>(
                            std::get<math::mat4>(t.expOut),
                            math::translation,
                            std::get<math::vec3>(t.arg1)
                        ))
                        {
                            printf("%i\n", count);
                            printf("ERROR 8\n");
                            exit(1);
                        }
                        count++;
                    }
                    break;

                case 9:
                    printf("------------------ M4 rotationX ------------------\n");
                    count = 0;
                    for (Testcase t : TestcasesM4[9])
                    {
                        if (false == Tester::testFunctionIOverloaded7<math::mat4, float>(
                            std::get<math::mat4>(t.expOut),
                            math::rotationX,
                            std::get<float>(t.arg1)
                        ))
                        {
                            printf("%i\n", count);
                            printf("ERROR 9\n");
                            exit(1);
                        }
                        count++;
                    }
                    break;

                case 10:
                    printf("------------------ M4 rotationY ------------------\n");
                    count = 0;
                    for (Testcase t : TestcasesM4[10])
                    {
                        if (false == Tester::testFunctionIOverloaded7<math::mat4, float>(
                            std::get<math::mat4>(t.expOut),
                            math::rotationY,
                            std::get<float>(t.arg1)
                        ))
                        {
                            printf("%i\n", count);
                            printf("ERROR 10\n");
                            exit(1);
                        }
                        count++;
                    }
                    break;

                case 11:
                    printf("------------------ M4 rotationZ ------------------\n");
                    count = 0;
                    for (Testcase t : TestcasesM4[11])
                    {
                        if (false == Tester::testFunctionIOverloaded7<math::mat4, float>(
                            std::get<math::mat4>(t.expOut),
                            math::rotationZ,
                            std::get<float>(t.arg1)
                        ))
                        {
                            printf("%i\n", count);
                            printf("ERROR 11\n");
                            exit(1);
                        }
                        count++;
                    }
                    break;


                default:
                    break;
                }
            }
        }
    }

}

/*			Function tester
 - auto type for capsuling functions
 - result		(m��ritetty vai laskettu?)
 - arguments
 - ...
 - ...
 - ...
*/