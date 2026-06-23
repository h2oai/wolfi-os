#include <soci/soci.h>
#include <soci/postgresql/soci-postgresql.h> // This is crucial
#include <iostream>
#include <string>
#include <stdexcept> // For standard exceptions
#include <cassert>

using namespace std;
using namespace soci;

int main() {
    try {
        // Establish connection to the PostgreSQL database
        session sql("postgresql://dbname=testdb user=wolfi");

        int id = 1; // Assuming this is the ID of the record to be queried
        string name;
        int salary;

        // Prepare and execute the SQL query
        sql << "SELECT name, salary FROM persons WHERE id = :id", use(id), into(name), into(salary);

        // Validate the fetched data
        assert(name == "Wolfi Rocks" && salary == 50000);

        // Output the result if the assertion passes
        cout << "Test Passed: Name: " << name << ", Salary: " << salary << endl;

    } catch (const soci::soci_error& e) {
        // Catch and report any database-related errors
        cerr << "Database error: " << e.what() << endl;
        return 1;

    } catch (const exception& e) {
        // Catch and report any other standard exceptions
        cerr << "Error: " << e.what() << endl;
        return 1;

    } catch (...) {
        // Catch and report any non-standard exceptions
        cerr << "Unknown error occurred" << endl;
        return 1;
    }

    return 0;
}
