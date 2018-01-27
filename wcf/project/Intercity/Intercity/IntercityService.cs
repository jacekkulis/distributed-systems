using Intercity.Exception;
using Intercity.Model;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.Text;

namespace Intercity
{
    // NOTE: You can use the "Rename" command on the "Refactor" menu to change the class name "IntercityService" in both code and config file together.
    public class IntercityService : IIntercityService
    {
        List<City> listOfCities;
        List<IntercityConnection> directConnectionList;
        List<IntercityConnection> connectionWithChangeList;

        public IntercityService()
        {
            InitializeConnections();
        }

        public List<IntercityConnection> FindDirectTrain(string cityNameA, string cityNameB)
        {
            if (!listOfCities.Any(c => c.CityName.Equals(cityNameA)) || !listOfCities.Any(c => c.CityName.Equals(cityNameB)))
            {
                CityDoesntExistException exception = new CityDoesntExistException();
                exception.Message = "City doesn't exist.";
                throw new FaultException<CityDoesntExistException>(exception);
            }
           
            if (directConnectionList.FirstOrDefault().Beggining.CityName.Equals(cityNameA) && directConnectionList.FirstOrDefault().Destination.CityName.Equals(cityNameB))
            {
                //found direct connection
                System.Diagnostics.Debug.WriteLine("found and returning list");
                return directConnectionList;
            }
            else
            {
                System.Diagnostics.Debug.WriteLine("connection doesnt exist - null list");
                //connection doesnt exist - null list
                return new List<IntercityConnection>();
            }
        }

        public List<IntercityConnection> FindTrain(string cityNameA, string cityNameB)
        {

            if (!listOfCities.Any(c => c.CityName.Equals(cityNameA)) || !listOfCities.Any(c => c.CityName.Equals(cityNameB)))
            {
                System.Diagnostics.Debug.WriteLine("nie ma takiego city!");
                CityDoesntExistException exception = new CityDoesntExistException();
                exception.Message = "City doesn't exist.";
                throw new FaultException<CityDoesntExistException>(exception);
            }
            

            if (connectionWithChangeList.FirstOrDefault().Beggining.CityName.Equals(cityNameA) && connectionWithChangeList.Last().Destination.CityName.Equals(cityNameB))
            {
                //found direct connection
                System.Diagnostics.Debug.WriteLine("found and returning list");
                return connectionWithChangeList;
            }
            else
            {
                System.Diagnostics.Debug.WriteLine("a co wczesniej");
                System.Diagnostics.Debug.WriteLine("connection doesnt exist - null list");
                //connection doesnt exist - null list
                return new List<IntercityConnection>();
            }
        }

        public void InitializeConnections()
        { 
            string[] cities = new string[4] { "Kraków", "Warszawa", "Łódź", "Sieradz" };
            listOfCities = new List<City>();
            for (int i = 0; i < cities.Length; i++)
            {
                listOfCities.Add(new City(cities[i]));
            }

            /*direct train*/
            directConnectionList = new List<IntercityConnection>();
            directConnectionList.Add(new IntercityConnection(new City("Łódź"), new TimeSpan(7, 35, 0), new City("Warszawa"), new TimeSpan(12, 30, 0)));

            /*train with change*/
            connectionWithChangeList = new List<IntercityConnection>();
            connectionWithChangeList.Add(new IntercityConnection(new City("Łódź"), new TimeSpan(8, 15, 0), new City("Warszawa"), new TimeSpan(10, 30, 0)));
            connectionWithChangeList.Add(new IntercityConnection(new City("Warszawa"), new TimeSpan(10, 45, 0), new City("Sieradz"), new TimeSpan(14, 0, 0)));
          
        }
    }
}
