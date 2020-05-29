using Microsoft.AspNetCore.Builder;
using Microsoft.AspNetCore.Http;
using System.Diagnostics;
using System.Threading.Tasks;

using Serilog;
using Serilog.Events;

namespace Server.Tools.Middleware {
    public  class LogMiddleware {
        private  bool _isDebug = Log.IsEnabled(LogEventLevel.Debug);
        private  Stopwatch sw = new Stopwatch();
        private readonly RequestDelegate _next;
        public LogMiddleware(RequestDelegate next)
        {
            _next = next;
        }
        public async Task Invoke(HttpContext context) {
            if(_isDebug) {
                sw.Start();
                await _next(context);
                sw.Stop();
                Log.Debug("Request {0} finished in {1}", context.Request.Path, sw.ElapsedMilliseconds);
            } else {
                await _next(context);
            }

        }
    
    }
}