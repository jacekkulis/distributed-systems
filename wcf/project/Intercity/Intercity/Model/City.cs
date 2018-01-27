using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;
using System.Threading.Tasks;

namespace Intercity.Model
{
    [DataContract]
    public class City
    {
        public City(string cityName)
        {
            this.cityName = cityName;
        }

        [DataMember]
        private string cityName;

        public string CityName
        {
            get
            {
                return cityName;
            }

            set
            {
                cityName = value;
            }
        }
    }
}
