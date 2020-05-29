using System.Net;
using System;

using Serilog;
using Serilog.Events;

using Server.Application;
using Server.Infrastructure.Services;
using Server.Infrastructure.Assemblers;
using Server.Infrastructure.Model;



namespace Server.Interface
{
    public class UdpDeviceInterface
    {
        private UdpService client;
        private UdpMessageInterpreter messageInterpreter;
        private UdpMessageAssembler assembler;

        public UdpDeviceInterface(UdpService client, UdpMessageInterpreter messageInterpreter)
        {
            this.client = client;
            this.messageInterpreter = messageInterpreter;
            this.assembler = new UdpMessageAssembler();

            this.client.receive += handleDeviceMessage;
        }

        private void handleDeviceMessage(string message, IPEndPoint source)
        {
            if (Log.IsEnabled(LogEventLevel.Information))
            {
                Log.Information("onReceive: " + message + " " + source.Address + ":" + source.Port);
            }
            UdpMessage udpMessage = assembler.assemble(message, source);
            this.messageInterpreter.interpret(udpMessage);
        }
    }
}
