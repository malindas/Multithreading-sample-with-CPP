#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <fstream>


using namespace std;
using namespace chrono_literals;

int x = 0 ; // Global variable accessed by both threads
int temp; // temp variable
bool flag = true; // flag = true (Printing to the console is done)
mutex mu; //

fstream file ( "Sytem Log.txt", ios::out | ios::binary | ios::app );



void thread_func1 ( ) {
	while (1) {

		// the access to this function is mutually exclusive
		lock_guard<mutex> guard ( mu );

		// Increment the value of X;
		if (flag == true) {
			x++;
			file << "\t\t Updating Global variables... (Thread 1)" << endl;
			flag = false; // Wainting for printing
			if (x == 10) { 
				x--;
				break; }
		}
		// Sleep thread for 0.5us
		this_thread::sleep_for ( 0.5us );
	}

	// the access to this function is mutually exclusive
	lock_guard<mutex> guard ( mu );
	file << "this is thread 1 (joining back to Main thread) ID:: " << this_thread::get_id ( ) << endl;

}

void thread_func2 ( ) {
	while (1) {

		// the access to this function is mutually exclusive
		lock_guard<mutex> guard ( mu );

		// Print the value of x after an increment
		if (flag == false) {
			if (temp - x == 0) { break; }
			file << "The Value of X is: " << x << " (Thread 2)"<< endl;
			flag = true; // Done printing
			temp = x;
		}

		// Sleep thread for 0.5us
		this_thread::sleep_for ( 0.5us );
	
	}

	// the access to this function is mutually exclusive
	lock_guard<mutex> guard ( mu );
	file << "this is thread 2 (joining back to Main thread) ID:: " << this_thread::get_id ( ) << endl;

}



int main ( int argc, char** argv ) {


	file << "this is my main thread ID:: " << this_thread::get_id ( ) << endl;
	
	/* Initializing threads */
	thread trd1 ( thread_func1 );
	thread trd2 ( thread_func2 );



	/* Finally join to main thread */
	trd1.join ( );
	trd2.join ( );

	file << "this is my main thread ID:: " << this_thread::get_id ( ) << endl;
	file.close ( );
	
	return 0;
}

