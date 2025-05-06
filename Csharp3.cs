using System;

class Program
{
    static void Main()
    {
        Console.OutputEncoding = System.Text.Encoding.UTF8;

        int count = 0;
        Console.Write("Введите количество чисел: ");
        int n = int.Parse(Console.ReadLine());

        for (int i = 0; i < n; i++)
        {
            int num = int.Parse(Console.ReadLine());
            num = Math.Abs(num);
            if (num < 10)
            {
                continue;
            }

            int last = num % 10;
            num /= 10;
            int flag = 1;

            while (num > 0)
            {
                if (num % 10 != last)
                {
                    flag = 0;
                    break;
                }
                num /= 10;
            }

            if (flag == 1)
            {
                count++;
            }
        }

        Console.WriteLine("Количество чисел с одинаковыми цифрами: " + count);
    }
}

