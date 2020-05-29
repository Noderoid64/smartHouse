using System;

namespace Server.Infrastructure.Model
{
    public class UdpMessage
    {
        public string macAddress { get; set; }
        public string type { get; set; }
        public string version { get; set; }
        public int command { get; set; }
        public byte[] data { get; set; }

        public string ip {get;set;}
        public DateTime lastPing {get;set;}
    }
}