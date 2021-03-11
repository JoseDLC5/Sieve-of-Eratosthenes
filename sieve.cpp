/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Jose de la Cruz
 * Date        : 9/16/2020
 * Description : Sieve of Eratosthenes
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

class PrimesSieve {
public:
    PrimesSieve(int limit);

    ~PrimesSieve() {
        delete [] is_prime_;
    }

    int num_primes() const {
        return num_primes_;
    }

    void display_primes() const;

private:
    // Instance variables
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    // Method declarations
    int count_num_primes() const;
    void sieve();
    static int num_digits(int num);
    void print_is_prime();
    void count_max_prime();
};

PrimesSieve::PrimesSieve(int limit) : 
is_prime_{new bool[limit + 1]}, limit_{limit} {
    sieve();
}

void PrimesSieve::display_primes() const {
    // TODO: write code to display the primes in the format specified in the
    // requirements document.
    const int max_prime_width = num_digits(max_prime_),
    primes_per_row = 80 / (max_prime_width + 1);
    int row_counter = 0;

    cout << "\nNumber of primes found: " << num_primes_ << endl;
    cout << "Primes up to " << limit_ << ":\n";

    //cout << setw(80);


    if(num_primes_ <= primes_per_row){
        for (int i = 2; i <= limit_; i++){
            if (is_prime_[i] && i != max_prime_)
            {
                cout << i << " ";
            }
        }
        cout << max_prime_;
    }
    else
    {
        for (int i = 0; i <= limit_; i++)
        {
            if (is_prime_[i] && i != max_prime_ && row_counter < primes_per_row - 1)
            {
                cout << setw(max_prime_width) << i << " ";
                row_counter++;
            }
            else if (is_prime_[i] && i != max_prime_)
            {
                cout << setw(max_prime_width) << i << endl;
                row_counter = 0;
            }
        }
        cout << max_prime_;
    }
}
    


    
    


int PrimesSieve::count_num_primes() const {
    int count = 0;
    for (int i = 0; i <= limit_; i++)
    {
        if(is_prime_[i]){
            count++;
        }
    }
    return count;
}

void PrimesSieve::sieve() {
    is_prime_[0] = false;
    is_prime_[1] = false;
    for (int i = 2; i <= limit_; i++)
    {
        is_prime_[i] = true;
    }

    for (int i = 2; i <= sqrt(limit_) ; i++)
    {
        if(is_prime_[i]){
            for (int j = i*i; j <= limit_; j=j+i)
            {
                is_prime_[j] = false;
            }
        }
    }
    
    num_primes_ = count_num_primes();

    count_max_prime();
}

int PrimesSieve::num_digits(int num) {
    int count = 0;
    while (num > 0)
    {
        num = num/10;
        count++;
    }
    return count;
}

void PrimesSieve::print_is_prime(){
    for (int i = 0; i <= limit_; i++)
    {
        if(is_prime_[i]){
            cout << "True\n";
        }
        else
        {
            cout << "False\n";
        }
        
    }
}

void PrimesSieve::count_max_prime(){
    for (int i = 0; i <= limit_; i++)
    {
        if(is_prime_[i]){
            max_prime_ = i;
        }
    }
}

int main() {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }

    // TODO: write code that uses your class to produce the desired output.
    PrimesSieve sieve(limit);

    sieve.display_primes();
    return 0;

}
