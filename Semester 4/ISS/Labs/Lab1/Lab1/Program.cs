using System;
using System.Collections.Generic;

class Program
{
    static List<int> Base10ToBase2(int numberInBase10)
    {
        List<int> numberInBase2 = new List<int>();
        while (numberInBase10 != 0)
        {
            int rest = numberInBase10 % 2;
            numberInBase10 = numberInBase10 / 2;
            numberInBase2.Add(rest);
        }
        return numberInBase2;
    }

    static List<int> Base10ToList(int numberInBase10)
    {
        List<int> result = new List<int>();
        while (numberInBase10 != 0)
        {
            int rest = numberInBase10 % 10;
            numberInBase10 = numberInBase10 / 10;
            result.Add(rest);
        }
        return result;
    }

    static bool IsListPalindrome(List<int> list)
    {
        int i = 0;
        int j = list.Count - 1;
        while (true)
        {
            if (i >= j)
                return true;
            if (list[i] != list[j])
                return false;
            i++;
            j--;
        }
    }

    static bool Check(int number)
    {
        return IsListPalindrome(Base10ToBase2(number)) && IsListPalindrome(Base10ToList(number));
    }

    static void Sum()
    {
        int sum = 0;
        for (int i = 0; i < 1000000; i++)
        {
            if (Check(i))
            {
                sum += i;
            }
        }
        Console.WriteLine(sum);
    }

    static void Main()
    {
        Sum();
    }
}
