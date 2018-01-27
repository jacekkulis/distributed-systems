using HelloWorldClient.HelloWorldServiceReference;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HelloWorldClient
{
    class Program
    {
        static void Main(string[] args)
        {
            HelloWorldServiceClient client = new HelloWorldServiceClient();
            Console.WriteLine("Write your nickname: ");
            string name = Console.ReadLine();

            Console.WriteLine("Waiting for response from service...");
            Console.WriteLine(client.SayHelloWorld(name));
            client.Close();
            Console.ReadLine();
        }
    }
}
