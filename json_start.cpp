#include<fstream>
#include<iostream>
#include<queue>

#include"json.hpp"
using json = nlohmann::json;
json ex2 = json::parse(R"({
"pi": 3.141,
  "happy": true,
  "name": "Niels",
  "nothing": null,
  "answer": {
    "everything": 42
  },
  "list": [1, 0, 2],
  "object": {
    "currency": "USD",
    "value": 42.99
  }
})");
template<typename T>
struct adl_serializer {
	static void to_json(json& j, const T& value) {
	}
	static void from_json(const json& j, T& value)
	{
	}
};
using json = nlohmann::json;
namespace ns {
	struct person {
		std::string name;
		std::string address;
		int age;
	};
	void to_json(json& j, const person& p) {
		j = json{ {"name",p.name},{"address",p.address},{"age",p.age} };
	}
	void from_json(const json& j, person& p) {
		j.at("name").get_to(p.name);
		j.at("address").get_to(p.address);
		j.at("age").get_to(p.age);
	}
}
int main()
{
	ex2["happy"] = false;
	auto j3 = json::parse(R"({"happy":true,"pi":3.141})");
	std::cout << j3 << std::endl;
	std::cout << ex2 << std::endl;
	std::string str = j3.dump();
	std::cout << j3.dump(4) << std::endl;
	json j_string = "this is a string";
	auto cpp_string = j_string.template get<std::string>();
	std::string cpp_string2;
	j_string.get_to(cpp_string2);
	std::string serialized_string = j_string.dump();

	json j;
	std::cin >> j;
	std::cout << j;
	std::cout << std::setw(4) << j << std::endl;
	std::vector<std::uint8_t>v = { 't','r','u','e' };
	json j1 = json::parse(v.begin(), v.end());
	std::cout << j1;
	json empty_array_explicit = json::array();
	json empty_object_implicit = json({});
	json empty_object_explicit = json::object();

	json j = "{\"happy\":true,\"pi\":3.141}";
	auto j = R"({"happy":true,"pi":3.141})"_json;
	json j;
	j.push_back("foo");
	j.push_back(1);
	j.push_back(true);
	j.emplace_back(1.78);
	for (json::iterator it = j.begin(); it != j.end(); ++it)
	{
		std::cout << *it << "\n";
	}
	for (auto& element : j)
	{
		std::cout << element << "\n";
	}
	const auto tmp = j[0].template get<std::string>();
	j[1] = 42;
	bool foo = j.at(2);
	j == R"(["foo",1,true,1.78])"_json;
	j.size();
	j.empty();
	j.type();
	j.clear();
	json o;
	o["foo"] = 23;
	o["bar"] = false;
	std::vector<int>c_vector{1, 2, 3, 4};
	json j_vec(c_vector);
	std::deque<double>c_deque{1.2, 2.3, 3.4, 5.6};
	json j_deque(c_deque);
	std::array<unsigned long, 4>c_array{{1, 2, 3, 4}};
	json j_array(c_array);
	json j_original = R"({"baz":["one","two","three"],"foo":"bar"})"_json;
	j_original["baz/1"_json_pointer];

	return 0;
}