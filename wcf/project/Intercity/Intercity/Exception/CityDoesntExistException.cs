using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;
using System.Threading.Tasks;

namespace Intercity.Exception
{
    [DataContract]
    public class CityDoesntExistException
    {
        [DataMember]
        public string Message;
    }
}
