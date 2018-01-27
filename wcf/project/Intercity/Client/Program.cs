using Client.IntercityService;
using System;
using System.Collections.Generic;
using System.Linq;
using System.ServiceModel;
using System.Text;
using System.Threading.Tasks;

namespace Client
{
    class Program
    {
        static void Main(string[] args)
        {
            IntercityServiceClient client = new IntercityServiceClient();

            /*zla miejscowosc*/
            try
            {
                List<IntercityConnection> directConnectionList = client.FindDirectTrain("Lodz", "Warszawa");
            }
            catch (FaultException<CityDoesntExistException> err)
            {
                Console.WriteLine("Exception: " + err.Detail.Message);
            }

            /*polaczenie nie istnieje*/
            try
            {
                List<IntercityConnection> directConnectionList = client.FindDirectTrain("Kraków", "Warszawa");
                if (directConnectionList.Count == 0)
                {
                    Console.WriteLine("Connection was not found.");
                }
            }
            catch (FaultException<CityDoesntExistException> err)
            {
                Console.WriteLine("Exception: " + err.Detail.Message);
            }


            /*polaczenie bezposrednie*/
            try
            {
                List<IntercityConnection> directConnectionList = client.FindDirectTrain("Łódź", "Warszawa");
                IntercityConnection connection = directConnectionList.FirstOrDefault();
                Console.WriteLine("[{0}, {1}, {2}, {3}]", connection.beggining.cityName, connection.departureTime.ToString(@"hh\:mm"), connection.destination.cityName, connection.arrivalTime.ToString(@"hh\:mm"));
            }
            catch (FaultException<CityDoesntExistException> err)
            {
                Console.WriteLine("Exception: " + err.Detail.Message);
            }

            /*polaczenie posrednie*/
            try
            {
                List<IntercityConnection> connectionWithChangeList = client.FindTrain("Łódź", "Sieradz");
                if (connectionWithChangeList.Count == 0)
                {
                    Console.WriteLine("Connection was not found.");
                }
                else
                {
                    IntercityConnection firstConnection = connectionWithChangeList[0];
                    IntercityConnection secondConnection = connectionWithChangeList[1];
                    Console.Write("[{0}, {1}, {2}, {3}, ", firstConnection.beggining.cityName, firstConnection.departureTime.ToString(@"hh\:mm"), firstConnection.destination.cityName, firstConnection.arrivalTime.ToString(@"hh\:mm"));
                    Console.WriteLine("{0}, {1}, {2}, {3}]", secondConnection.beggining.cityName, secondConnection.departureTime.ToString(@"hh\:mm"), secondConnection.destination.cityName, secondConnection.arrivalTime.ToString(@"hh\:mm"));
                }
               
            }
            catch (FaultException<CityDoesntExistException> err)
            {
                Console.WriteLine("Exception: " + err.Detail.Message);
            }


            Console.Read();
        }
    }
}
