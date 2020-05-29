using System;

namespace Server.Infrastructure {
    
    public static class AssertTool {
        #nullable enable
        public static void notNull(Object value, string? valueName) {
            if (value == null) {
                throw new Exception (String.Format("{0} is null", valueName));
            }
        }
        #nullable disable
    }
    
}