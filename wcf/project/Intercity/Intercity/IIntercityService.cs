using Intercity.Exception;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.Text;

namespace Intercity
{
    // NOTE: You can use the "Rename" command on the "Refactor" menu to change the interface name "IIntercityService" in both code and config file together.
    [ServiceContract]
    public interface IIntercityService
    {
        void InitializeConnections();

        [OperationContract]
        [FaultContract(typeof(CityDoesntExistException))]
        List<IntercityConnection> FindDirectTrain(string cityNameA, string cityNameB);

        [OperationContract]
        [FaultContract(typeof(CityDoesntExistException))]
        List<IntercityConnection> FindTrain(string cityNameA, string cityNameB);

    }
}
