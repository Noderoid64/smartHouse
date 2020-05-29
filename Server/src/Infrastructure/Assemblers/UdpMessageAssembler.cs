using System;
using System.Text;
using System.Net;

using Serilog;
using Serilog.Events;

using Server.Infrastructure.Model;

namespace Server.Infrastructure.Assemblers {
    public class UdpMessageAssembler {

        private readonly bool _isDebug = Log.IsEnabled(LogEventLevel.Debug);
        private const int MESSAGE_ELEMENTS_COUNT = 5;
        private const char MESSAGE_PARTS_SPLITTER = '|';
        private const int MAC_POS = 0;
        private const int TYPE_POS = 1;
        private const int VERSION_POS = 2;
        private const int COMMAND_POS = 3;
        private const int DATA_POS = 4;

        public UdpMessage assemble(string message, IPEndPoint source) {
            UdpMessage result = null;
            string [] parts = message.Split(MESSAGE_PARTS_SPLITTER);
            if (parts.Length == MESSAGE_ELEMENTS_COUNT) {
                result = new UdpMessage();
                result.macAddress = parts[MAC_POS];
                result.type = parts[TYPE_POS];
                result.version = parts[VERSION_POS];
                result.command = int.Parse(parts[COMMAND_POS]);
                result.data = Encoding.ASCII.GetBytes(parts[DATA_POS]);
                
                result.lastPing = DateTime.Now;
                result.ip = source.Address.ToString();
            } else {
                Log.Warning(String.Format("Message split not to {0} parts", MESSAGE_ELEMENTS_COUNT));
                Log.Warning("The message is {0}", message);
                result = null;
            }
            return result;
        }
    }
}
