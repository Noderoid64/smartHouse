using System;
using System.Net.Sockets;
using System.Text;
using System.Net;
using System.Threading.Tasks;
using Serilog;

using Server.Domain.Services;

namespace Server.Services
{
    public class UdpClient : IUdpClient
    {

        public event Action<string, IPEndPoint> receive;

        private Object receiveLocker = new Object();
        private System.Net.Sockets.UdpClient client;
        private const int port = 4446;
        private readonly IPAddress multicastGroupIp;
        public UdpClient()
        {
            Log.Information("hello udp");
            this.client = new System.Net.Sockets.UdpClient(port);
            // TODO read from config
            this.multicastGroupIp = IPAddress.Parse("230.0.0.0");

            try {
                client.JoinMulticastGroup(multicastGroupIp);
            } catch (Exception ex) {
                Log.Error("UdpClient | error: " + ex.ToString());
            }

            Task.Run(() => handleServer());
        }

        private async void handleServer() {
            while (true) {
                Log.Information("UdpClient | wait for message to receive");
                UdpReceiveResult result = await client.ReceiveAsync();
                string stringResult = Encoding.ASCII.GetString(result.Buffer);
                Log.Information("UdpClient | receive message from " + result.RemoteEndPoint.ToString() +  ": " + stringResult);
                this.receive?.Invoke(stringResult, result.RemoteEndPoint);
            }
        }

        public async void sendMulticastAsync(string message)
        {
            byte[] datagram = Encoding.ASCII.GetBytes(message);
            IPEndPoint endPoint = new IPEndPoint(multicastGroupIp, port);
            await client.SendAsync(datagram, datagram.Length , endPoint);
        }
    }
}