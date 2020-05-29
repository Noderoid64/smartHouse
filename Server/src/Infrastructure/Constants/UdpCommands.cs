namespace Server.Infrastructure {
    public static class Command {
        public const int LAST_GENERAL_COMMAND = 40;

        // General commands
        public const int REGISTER_DEVICE = 0;
        public const int UPDATE_STATUS = 1;

        // Station commands
        public const int SEND_TEMPERATURE = 41;
        public const int SEND_HUMIDITY = 42;
        public const int SEND_CO2 = 43;
    }
}