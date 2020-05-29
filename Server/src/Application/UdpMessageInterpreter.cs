using Server.Infrastructure.Model;
using Server.Infrastructure;

namespace Server.Application {
    public class UdpMessageInterpreter {

        private DeviceService deviceService;

        public UdpMessageInterpreter(DeviceService deviceService) {
            this.deviceService = deviceService;
        }

        public void interpret(UdpMessage message) {
            AssertTool.notNull(message, "message");
            if (isGeneralCommand(message)) {
                interpretGeneralCommands(message);
            } else {
                interpretStationCommands(message);
            }
        }

        private void interpretGeneralCommands(UdpMessage message) {
            switch(message.command) {
                case Command.REGISTER_DEVICE: {

                } break;
                case Command.UPDATE_STATUS: {
                    this.deviceService.updateStatus(message.macAddress, message.ip);
                } break;
            }
        }

        private void interpretStationCommands(UdpMessage message) {

        }

        private bool isGeneralCommand(UdpMessage message) {
            return message.command < Command.LAST_GENERAL_COMMAND;
        }
    }
}