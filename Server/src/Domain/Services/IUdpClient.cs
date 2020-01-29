using System;
using System.Net;

namespace Server.Domain.Services {
    public interface IUdpClient
    {
        void sendMulticastAsync(string message);
        event Action<string, IPEndPoint> receive;
    }
}