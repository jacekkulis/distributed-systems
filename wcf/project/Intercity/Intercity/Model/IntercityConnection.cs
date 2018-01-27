using Intercity.Model;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;
using System.Threading.Tasks;

namespace Intercity
{
    [DataContract]
    public class IntercityConnection
    {
        public IntercityConnection(City beggining, TimeSpan departureTime, City destination, TimeSpan arrivalTime)
        {
            this.beggining = beggining;
            this.departureTime = departureTime;
            this.destination = destination;
            this.arrivalTime = arrivalTime;
        }

        [DataMember]
        private City beggining;
        [DataMember]
        private TimeSpan departureTime;
        [DataMember]
        private City destination;
        [DataMember]
        private TimeSpan arrivalTime;

        public City Beggining
        {
            get
            {
                return beggining;
            }

            set
            {
                beggining = value;
            }
        }

        public TimeSpan DepartureTime
        {
            get
            {
                return departureTime;
            }

            set
            {
                departureTime = value;
            }
        }

        public City Destination
        {
            get
            {
                return destination;
            }

            set
            {
                destination = value;
            }
        }

        public TimeSpan ArrivalTime
        {
            get
            {
                return arrivalTime;
            }

            set
            {
                arrivalTime = value;
            }
        }
    }
}
