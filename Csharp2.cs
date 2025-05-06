using System;
using System.Text;

class Program
{
    static void Main()
    {
        Console.OutputEncoding = Encoding.UTF8;

        int matches = 0;
        Console.Write("Введите количество команд: ");
        int commands = int.Parse(Console.ReadLine());

        while (commands != 1)
        {
            if (commands % 2 == 0)
            {
                matches += commands / 2;
                commands = commands / 2;
            }
            else
            {
                matches += (commands - 1) / 2 + 1;
                commands = (commands - 1) / 2;
            }
        }

        Console.WriteLine("Количество сыгранных матчей: " + matches);
    }
}

