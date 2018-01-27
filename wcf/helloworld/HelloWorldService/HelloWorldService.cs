using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.Text;

namespace HelloWorldService
{
    // NOTE: You can use the "Rename" command on the "Refactor" menu to change the class name "HelloWorldService" in both code and config file together.
    public class HelloWorldService : IHelloWorldService
    {
        public string SayHelloWorld(string name)
        {
            return string.Format("Hello world from {0}", name);
        }
    }
}
