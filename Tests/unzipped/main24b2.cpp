// 
// 234218 Data Structures 1.
// Semester: 2023B (spring).
// Wet Exercise #1.
// 
// Recommended TAB size to view this file: 8.
// 
// The following main file is necessary to link and run your code.
// This file is READ ONLY: even if you submit something else, the compiler ..
// .. WILL use our file.
// 

#include "pirates24b2.h"
#include <string>
#include <iostream>

using namespace std;


void print(string cmd, StatusType res);
void print(string cmd, output_t<int> res);

#include <iostream>
#include <type_traits>

using namespace std;

#include <iostream>
#include <type_traits>

using namespace std;

template <typename T>
class Tester {
public:
    Tester(T* ocean)
        : m_ocean(ocean), get_pirate_rank_ptr(nullptr) {
        // Check if T has a member function get_pirate_rank using SFINAE
        assign_get_pirate_rank_ptr<T>();
    }

    T* m_ocean;
    using GetPirateRankPtr = output_t<int> (T::*)(int);
    GetPirateRankPtr get_pirate_rank_ptr;

    StatusType run(string op) {
        int d1, d2;
        if (!op.compare("add_fleet")) {
            cin >> d1;
            print(op, m_ocean->add_fleet(d1));
        } else if (!op.compare("add_pirate")) {
            cin >> d1 >> d2;
            print(op, m_ocean->add_pirate(d1, d2));
        } else if (!op.compare("pay_pirate")) {
            cin >> d1 >> d2;
            print(op, m_ocean->pay_pirate(d1, d2));
        } else if (!op.compare("num_ships_for_fleet")) {
            cin >> d1;
            print(op, m_ocean->num_ships_for_fleet(d1));
        } else if (!op.compare("get_pirate_money")) {
            cin >> d1;
            print(op, m_ocean->get_pirate_money(d1));
        } else if (!op.compare("get_pirate_rank")) {
            cin >> d1;
            if (get_pirate_rank_ptr) {
                print(op, (m_ocean->*get_pirate_rank_ptr)(d1));
            } else {
                cout << "get_pirate_rank: Command not supported" << endl;
            }
        } else if (!op.compare("unite_fleets")) {
            cin >> d1 >> d2;
            print(op, m_ocean->unite_fleets(d1, d2));
        } else if (!op.compare("pirate_argument")) {
            cin >> d1 >> d2;
            print(op, m_ocean->pirate_argument(d1, d2));
        } else {
            return StatusType::FAILURE;
        }
        return StatusType::SUCCESS;
    }

private:
    // Helper struct to detect if get_pirate_rank exists in T
    template <typename U>
    struct has_get_pirate_rank {
        template <typename V>
        static auto test(int) -> decltype(&V::get_pirate_rank, std::true_type());

        template <typename>
        static std::false_type test(...);

        static constexpr bool value = decltype(test<U>(0))::value;
    };

    // Function to assign get_pirate_rank_ptr using SFINAE
    template <typename U>
    typename std::enable_if<has_get_pirate_rank<U>::value>::type
    assign_get_pirate_rank_ptr() {
        get_pirate_rank_ptr = &U::get_pirate_rank;
    }

    // Fallback for types without get_pirate_rank
    template <typename U>
    typename std::enable_if<!has_get_pirate_rank<U>::value>::type
    assign_get_pirate_rank_ptr() {
        get_pirate_rank_ptr = nullptr;
    }
};

int main()
{
    // Init
    oceans_t *obj = new oceans_t();
    Tester<oceans_t> tester = Tester<oceans_t>(obj);
	
    // Execute all commands in file
	string op;
	while (cin >> op)
    {
        StatusType result = tester.run(op);
        if (result != StatusType::SUCCESS) {
            cout << "Unknown command: " << op << endl;
            return -1;
        }
        // Verify no faults
        if (cin.fail()){
            cout << "Invalid input format" << endl;
            return -1;
        }
    }

    // Quit 
	delete obj;
	return 0;
}

// Helpers
static const char *StatusTypeStr[] =
{
   	"SUCCESS",
	"ALLOCATION_ERROR",
	"INVALID_INPUT",
	"FAILURE"
};

void print(string cmd, StatusType res) 
{
	cout << cmd << ": " << StatusTypeStr[(int) res] << endl;
}

void print(string cmd, output_t<int> res)
{
    if (res.status() == StatusType::SUCCESS) {
	    cout << cmd << ": " << StatusTypeStr[(int) res.status()] << ", " << res.ans() << endl;
    } else {
	    cout << cmd << ": " << StatusTypeStr[(int) res.status()] << endl;
    }
}
