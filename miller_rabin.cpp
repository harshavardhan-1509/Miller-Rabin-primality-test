#include <iostream>
#include <ctime>
using namespace std;
long long int power(long long int a, long long int r, long long int n)
{
    // It is the fast exponent modulus function
    // this function will calculate the a^r modulo n in least amount of time.
    long long int ans = 1;  
    long long int exponential = a % n; // a modulo n
    while (r > 0)
    {
        if (r % 2 == 1)
        {
            ans = (ans * exponential) % n;
        }
        exponential = (exponential * exponential) % n;
        r = r / 2;
    }
    return ans; //returns final answer
}

bool coprime(long long int n, long long int m)
{
    if (n == 0)
    {
        return 0; // if n = 0 => gcd of n, m is not equal to 1
    }
    if (n == 1)
    {
        return 1; // if n = 1 => gcd of n, m is equal to 1
    }
    else
    {
        return coprime(m % n, n); // recursive calls coprime until n becomes 1 or 0
    }
}

bool isprime(long long int n, long long int a)
{
    // to check whether n is a prime or not
    // a is a random no. less than n to check whether n is a prime or not
    long long int x = n - 1;
    if (!coprime(a, n))
    {
        // is a and n are not coprime then n is not a prime.
        return false;
    }
    else
    {
        if (power(a, n - 1, n) != 1)
        {
            // if a^(phi(n)) mod n != 1 then n is not a prime. 
            return false;
        }
        else
        {
            while (x % 2 == 0)
            {
                if (power(a, x / 2, n) != 1 && power(a, x / 2, n) != n - 1)
                {
                    return false;
                }
                else if (power(a, x / 2, n) == 1)
                {
                    x = x / 2;
                    continue;
                }
                else
                {
                    break;
                }
            }
        }
    }
    return true;
}

bool miller_rabin(long long int n, int x)
{   // X is number of times the random number is generated.
    // increase in X will increase the probabilty of ans correctness.
    bool answer = true;
    while (x > 0)
    {
        long long int a = 2 + rand() % (n - 2);
        if (!isprime(n, a))
        {
            answer = false;
            break;
        }
        x--;
    }
    return answer;
}


int main()
{
    long long int  n;
    cout << "Max range of prime number" << endl;
    cin >> n;
    srand(time(0));
    int count = 0;
    cout << "the prime no.s with in the range are" << endl;
    cout << "2" << endl;
    for (long long int i = 3; i <=  n; i = i + 2)
    {
        // long long int  a = 2+rand()%(i-2);
        if (miller_rabin(i, 10)){
            count++;
            cout << i << endl;
        }
    }
    cout << "no. of primes with in range are " << (count + 1) << endl;
}