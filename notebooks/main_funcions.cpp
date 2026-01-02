#include <cstdio>
#include <vector>
#include <string>

void func1()
{
	printf("%s\n", __FUNCTION__);
}

namespace my_ns
{
	void func2()
	{
		printf("%s\n", __FUNCTION__);
	}
}

namespace func
{
	/// <summary>
	/// generaattori funktio, joka generpoi N verran elementtejä vektoriin
	/// </summary>
	/// <param name="N">Elementtien lukumaara</param>
	/// <param name="f"></param>
	/// <returns></returns>

	template<typename T>
	auto gen(size_t N, auto f)
	{
		std::vector<T> res;
		for (size_t i = 0; i<N; i++)
		{
			res.push_back(f(i));
		}
		return res;
	}

	template<typename T>
	void print(const T& val)
	{
		printf("%s ", std::to_string(val).c_str());
	}

	template<>
	void print(const std::string& val)
	{
		printf("%s ", val.c_str());
	}

	template<typename T, typename ... Args>
	void print(T value, Args ... args)
	{
		print(value);
		print(std::forward<Args>(args) ...);
	}

	template<typename T>
	void print(const std::vector<T>& values)
	{
		for (size_t i = 0; i < values.size(); i++)
		{
			print(values[i]);
		}
	}

	template<typename T>
	auto map(const auto& vec, auto f)
	{
		return gen<T>(vec.size(), [f, &vec](auto i) {
			return f(vec[i]);
			});
	}

	template<typename T>
	auto reduce(const auto& vec, auto f, T initialValue = 0)
	{
		for (size_t i = 0; i < vec.size(); i++)
		{
			initialValue = f(initialValue,vec[i]);
		}
		return initialValue;
	}

	//esim pistetulo
	template<typename T>
	auto sumReduce(const auto& vec)
	{
		return reduce<T>(vec, [](auto lhs, auto rhs) {
			return lhs + rhs;
			}, 0);
	}

	template<typename T>
	auto filter(const auto& vec, auto f)
	{
		std::vector<T> res;
		for (size_t i = 0; i < vec.size(); i++)
		{
			if (f(vec[i]))
			{
				res.push_back(vec[i]);
			}
		}
		return res;
	}

}


int main()
{

	func::print(1,2,3,4,5);

	func1();
	my_ns::func2();

	[]()
		{
			printf("Hello from lambda: %s\n", __FUNCTION__);
		}();

	const auto my_func = []()
		{
			printf("Hello from my func: %s\n", __FUNCTION__);
		};

	my_func();

	auto values = func::gen<float>(10, [](auto i) {
		return float(i) * float(i);
		});

	//aloittelijoille
	auto pow2 = [](auto num) -> float
		{
			return float(num * num);
		};

	auto values_new = func::gen<float>(10, pow2);

	func::print(values);

	const auto zeroes = func::gen<float>(5, [](auto) {return 0.0f; });

	auto twos = func::map<float>(zeroes, [](float valueIn){
		return float(valueIn + 2);
		});

	printf("\nzeroes:\n");
	func::print(zeroes);
	printf("\ntwos\n");
	func::print(twos);

	auto test_values = func::gen<float>(5, [](auto i) {return float(i+1); });
	
	auto sum_of_values = func::sumReduce<float>(test_values);

	printf("\nValues:\n");
	func::print(test_values);
	printf("\nSumOfValues:\n");
	func::print(sum_of_values);


	auto test_values2 = func::gen<float>(15, [](auto i) {return float(i + 1); });

	auto filtered = func::filter<float>(test_values2, [](auto value) {
		return value >= 5 && value <= 10;
		});
	printf("\nNonfiltered:\n");
	func::print(test_values2);
	printf("\nfiltered:\n");
	func::print(filtered);
	

	return 0;
}