#define SOL_CHECK_ARGUMENTS
#include <sol.hpp>

#include <vector>
#include <iostream>

int main(int, char**) {
	std::cout << "=== containers example ===" << std::endl;

	sol::state lua;
	lua.open_libraries();

	lua.script(R"(
		function f (x)
			print('--- Calling f ---')
			for k, v in pairs(x) do
				print(k, v)
			end
		end
		)");

	// Have the function we 
	// just defined in Lua
	sol::function f = lua["f"];

	// Set a global variable called 
	// "arr" to be a vector of 5 lements
	lua["arr"] = std::vector<int>{ 2, 4, 6, 8, 10 };

	// Call it, see 5 elements
	// printed out
	f(lua["arr"]);

	// Mess with it in C++
	// Containers are stored as userdata, unless you
	// use `sol::as_table()` and `sol::as_table_t`.
	std::vector<int>& reference_to_arr = lua["arr"];
	reference_to_arr.push_back(12);

	// Call it, see *6* elements
	// printed out
	f(lua["arr"]);

	std::cout << std::endl;

	return 0;
}