namespace Server.Model.Value
{
    public class DeviceVersion
    {
        public int major { get; set; }
        public int minor { get; set; }
        public int patch { get; set; }

        public DeviceVersion () {}

        public DeviceVersion (string version) {
            string[] parts = version.Split('.');
            if (parts.Length == 3) {
                DeviceVersion result = new DeviceVersion();
                result.major = int.Parse(parts[0]);
                result.minor = int.Parse(parts[1]);
                result.patch = int.Parse(parts[2]);
            } else {
                throw new System.Exception("Device version cannot be assembled");
            }
        }

        public override string ToString() {
            return major + "." + minor + "." + patch;
        }
    }
}