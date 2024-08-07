using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace diamond.Model
{
    public class TcpSockets
    {
        private Socket soc;
        public Socket Soc { get { return soc; } set { soc = value;} }
        public TcpSockets() { }

        public void SocConnet ()
        {
            var myserver=IPAddress.Parse("10.10.21.122");
            Socket soc = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            soc.Connect(myserver, 10001);
            if(!soc.Connected) 
            {
                Console.Error.WriteLine("연결실패");
            }

        }
        
    }
}
