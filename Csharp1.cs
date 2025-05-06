using System;

class Program
{
    static void Main()
    {
        Console.Write("Введите строку: ");
        string s = Console.ReadLine();
        int count = 0;
        string gl = "AaEeIiOoUuYy";

        foreach (char c in s)
        {
            if (c != ' ')
            {
                if (gl.Contains(c))
                    count++;
                else
                    count--;
            }
        }

        if (count == 0)
            Console.WriteLine("Одинаково");
        else if (count < 0)
            Console.WriteLine("Нет");
        else
            Console.WriteLine("Да");
    }
}

