#include <iostream>
#include <system_error>
#include <exception>
#include <string>
using namespace std;

string AskTimeServer() {
    throw system_error(ENETUNREACH, system_category(), "Connection lost");
}

class TimeServer {
public:
    string GetCurrentTime() {
        try {
            last_fetched_time = AskTimeServer();
            return last_fetched_time;
        } catch (system_error& e) {
            cout << e.code() << ' ' << e.what() << endl;
            return last_fetched_time;
        }
    }

private:
    string last_fetched_time = "00:00:00";
};

int main() {
    // Меняя реализацию функции AskTimeServer, убедитесь, что это код работает корректно
    TimeServer ts;
    try {
        cout << ts.GetCurrentTime() << endl;
    } catch (exception& e) {
        cout << "Exception got: " << e.what() << endl;
    }
    return 0;
}
